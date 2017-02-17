/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Object.hpp"

namespace java {
namespace lang {
class System;

/**
 * <p> A container object that holds a fixed number of values of a single type.</p>
 *
 * <p> Unlike standard arrays, the array length can be adjusted up or down without incurring expensive copy operations
 *     (smooth capacity increase / decrease). </p>
 *
 * <p> To support FastHeap allocations/deallocations Array elements are not continuous (fractal structure).
 *     Bulk copies of array elements should be performed using java::lang::System::arraycopy </p>
 *
 * <p> Note: This class implementation is derived from org.javolution.util.FractalArray but optimized for C++.</p>
 *
 * @version 7.0
 */
template<typename E> class Array final : public virtual Object {
friend class System;
    Array(int length, Value* value) : length(length), Object(value) {}
public:
    Array(Void = nullptr) {}

    /** The length property of the array which can be set (for non-const arrays) without
     *  modifying the capacity of the array.To adjust the capacity to the length, the method
     *  setLength should be used. */
    int length;

    /** Returns a new array of small/optimized length. */
    static Array<E> newInstance() {
        return Array(BlockValue::MAX_CAPACITY, new BlockValue());
    }

    /**
     *  Returns an array of specified length.
     *
     * @throws NegativeArraySizeException if the specified length is negative
     */
    static Array<E> newInstance(int length) {
        Array<E> tmp = newInstance();
        tmp.setLength(length);
        return tmp;
    }

    /**
     * Returns the element at specified index.
     *
     * @throws ArrayIndexOutOfBoundsException if the specified index is not in range [0..length[
     */
    E& operator[](int index) {
        if ((index < 0) || (index >= length))
            Object::Exceptions::throwArrayIndexOutOfBoundsException();
        return this_<Value>()->elementAt(index);
    }

    // const version.
    const E& operator[](int index) const {
        if ((index < 0) || (index >= length))
            Object::Exceptions::throwArrayIndexOutOfBoundsException();
        return this_<Value>()->elementAt(index);
    }

    /**
     * Returns a new array, holding the same elements as this one.
     */
    Array<E> clone() const {
        return Array<E>(length, this_<Value>()->clone());
    }

    /**
     * Sets the length of this array and adjust its capacity accordingly (decreasing the length will
     * result in the deletion of the last elements at and after the new length).
     *
     * @throws NegativeArraySizeException if the specified length is negative
     */
    void setLength(int newLength) {
        if (newLength < 0)
             Object::Exceptions::throwNegativeArraySizeException();
         *this = Array<E>(newLength, this_<Value>()->setLength(newLength));
    }

    ////////////////////
    // Implementation //
    ////////////////////

    class Value: public Object::Value {
    public:
        virtual E& elementAt(int index) = 0;
        virtual const E& elementAt(int index) const = 0;
        virtual Value* setLength(int length) = 0;
        virtual Value* clone() const = 0;
    };


private:

    class BlockValue4;
    class BlockValue8;

    class BlockValue: public Value {
        typedef BlockValue This;
        typedef BlockValue4 Outer;
    public:

        static const size_t SIZE = Type::FastHeap::BLOCK_CAPACITY / sizeof(E);
        static const int SHIFT = (SIZE >= 256) ? 8 : (SIZE >= 128) ? 7 : (SIZE >= 64) ? 6 : (SIZE >= 32) ? 5 :
                                         (SIZE >= 16) ? 4 : (SIZE >= 8) ? 3 : 2;
        static const int MAX_CAPACITY = 1 << SHIFT;
        static const int MASK = MAX_CAPACITY - 1;

        E elements[1 << SHIFT];

        E& elementAt(int index) override {
            return elements[index];
        }

        const E& elementAt(int index) const override {
            return elements[index];
        }

        Value* setLength(int length) override {
            static bool isFundamental = std::is_fundamental<E>::value;
            if (length > MAX_CAPACITY) {
                Outer* outer = new Outer();
                outer->blocks[0] = this;
                return outer->setLength(length);
            }
            if (!isFundamental) {
                E none;
                for (int i = length; i < MAX_CAPACITY;)
                    elements[i++] = none; // Ensures dereferencing of non-primitives types (e.g. Objects)
            }
            return this;
        }

        This* clone() const override {
            This* copy = new This();
            for (int i=0; i < MAX_CAPACITY; ++i) {
                copy->elements[i] = elements[i];
            }
            return copy;
        }

    };

    class BlockValue4 : public Value {
        typedef BlockValue Inner;
        typedef BlockValue4 This;
        typedef BlockValue8 Outer;
    public:
        static const int SHIFT = Inner::SHIFT + 4;
        static const int MASK = (1 << SHIFT) - 1;
        static const int MAX_CAPACITY = 1 << SHIFT;

        Object blocks[16];

        E& elementAt(int index) override {
            return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
        }

        const E& elementAt(int index) const override {
            return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
        }

        Value* setLength(int length) override {
            if (length <= Inner::MAX_CAPACITY)
                return (blocks[0].this_<Inner>())->setLength(length);
            for (int i = 0; i < 16; ++i) {
                int indexMin = i << Inner::SHIFT; // Included
                int indexMax = (i + 1) << Inner::SHIFT; // Excluded.
                if (indexMin < length) {
                    if (blocks[i] == nullptr)
                        blocks[i] = new Inner();
                    if (indexMax > length)
                        blocks[i].this_<Inner>()->setLength(length & Inner::MASK);
                } else { // indexMin >= length,
                    if (blocks[i] == nullptr)
                        break;
                    blocks[i] = nullptr;
                }
            }
            if (length <= MAX_CAPACITY)
                return this;
            Outer* outer = new Outer();
            outer->blocks[0] = this;
            return outer->setLength(length);
        }

        This* clone() const override {
            This* copy = new This();
            for (int i=0; i < 16; ++i) {
                if (blocks[i] == nullptr) break;
                copy->blocks[i] = blocks[i];
            }
            return copy;
        }
    };

    class BlockValue8 : public Value {
        typedef BlockValue4 Inner;
        typedef BlockValue8 This;
        // typedef BlockValue12 Outer;
    public:
        static const int SHIFT = Inner::SHIFT + 4;
        static const int MASK = (1 << SHIFT) - 1;
        static const int MAX_CAPACITY = 1 << SHIFT;

        Object blocks[16];

        E& elementAt(int index) override {
            return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
        }

        const E& elementAt(int index) const override {
                return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
        }

        Value* setLength(int length) override {
            return length == 0 ? nullptr : this;// TODO
        }

        This* clone() const override {
            This* copy = new This();
            for (int i=0; i < 16; ++i) {
                if (blocks[i] == nullptr) break;
                copy->blocks[i] = blocks[i];
            }
            return copy;
        }
    };

};

}
}

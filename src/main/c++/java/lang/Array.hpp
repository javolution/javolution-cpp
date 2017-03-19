/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <cstring>
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
template<typename E> class Array final : public Object {
public:
    class Value: public Object::Value {
    public:
        virtual E& elementAt(int index) = 0;
        virtual const E& elementAt(int index) const = 0;
        virtual Value* setLength(int length) = 0;
        virtual Value* clone() const = 0;
    };

    CLASS(Array)

    /** The length property of the array which can be set (for non-const arrays) without
     *  modifying the capacity of the array. To adjust the capacity to the length, the method
     *  setLength should be used. */
    int length;

    /** Returns a new array of small/optimized length. */
    static Array<E> newInstance() {
        Array<E> tmp = new BlockValue();
        tmp.length = BlockValue::MAX_CAPACITY;
        return tmp;
    }

    /**
     *  Returns an array of specified length.
     *
     * @throws NegativeArraySizeException if the specified length is negative
     */
    static Array<E> newInstance(int length) {
        Array<E> tmp = new BlockValue();
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
        Array<E> tmp = this_<Value>()->clone();
        tmp.length = length;
        return tmp;
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
        Array<E> tmp = this_<Value>()->setLength(newLength);
        tmp.length = newLength;
        *this = tmp;
    }

    /** Consumer function which can be used to iterate over array elements (see <code>forEach</code>). */
    typedef std::function<void(E)> Consumer;

    /** Performs an action for each element of this array.
     *  For example: <code>names.forEach([](const String& name) { System::out.println(name);})</code> */
    void forEach(const Consumer& action) {
        Value* array = this_<Value>();
        for (int i=0; i < length; i++) action(array->elementAt(i)); // TBD: Use recursions...
    }

private:

    class BlockValue4;
    class BlockValue8;
    class BlockValue12;
    class BlockValue16;
    class BlockValue20;
    class BlockValue24;
    class BlockValue28;
    class BlockValue32;

    class BlockValue: public Value {
        typedef BlockValue This;
        typedef BlockValue4 Outer;
    public:

        static const size_t SIZE = FastHeap::BLOCK_FREE_SIZE / sizeof(E);
        static const int SHIFT = (SIZE >= 256) ? 8 : (SIZE >= 128) ? 7 : (SIZE >= 64) ? 6 : (SIZE >= 32) ? 5 :
                                         (SIZE >= 16) ? 4 : (SIZE >= 8) ? 3 : 2;
        static const int MAX_CAPACITY = 1 << SHIFT;
        static const int MASK = MAX_CAPACITY - 1;

        E elements[MAX_CAPACITY];

        E& elementAt(int index) override {
            return elements[index];
        }

        const E& elementAt(int index) const override {
            return elements[index];
        }

        Value* setLength(int length) override {
            if (length > MAX_CAPACITY) 
                return (new Outer(this))->setLength(length);
            bool isFundamental = std::is_fundamental<E>::value;
            if (!isFundamental) {
                E none {};
                for (int i = length; i < MAX_CAPACITY;)
                    elements[i++] = none; // Ensures dereferencing of non-primitives types (e.g. Objects)
            }
            return this;
        }

        This* clone() const override {
            This* copy = new This();
            bool isFundamental = std::is_fundamental<E>::value;
            if (isFundamental) {
            	std::memcpy(copy->elements, elements, MAX_CAPACITY * sizeof(E) );
            } else {
                for (int i=0; i < MAX_CAPACITY; ++i) {
                    copy->elements[i] = elements[i];
                }
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

        BlockValue4() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
        BlockValue4(Inner* block0) { blocks[0] = block0; }

        E& elementAt(int index) override {
            return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
        }

        const E& elementAt(int index) const override {
            return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
        }

        Value* setLength(int length) override {
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
			if (length <= Inner::MAX_CAPACITY)
				return (blocks[0].this_<Inner>())->setLength(length);
			return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
        }

        This* clone() const override {
            This* copy = new This();
            for (int i=0; i < 16; ++i) {
                if (blocks[i] == nullptr) break;
                copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
            }
            return copy;
        }
    };

    class BlockValue8 : public Value {
         typedef BlockValue4 Inner;
         typedef BlockValue8 This;
         typedef BlockValue12 Outer;
     public:
         static const int SHIFT = Inner::SHIFT + 4;
         static const int MASK = (1 << SHIFT) - 1;
         static const int MAX_CAPACITY = 1 << SHIFT;

         Object blocks[16];

         BlockValue8() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue8(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
	     }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

    class BlockValue12 : public Value {
         typedef BlockValue8 Inner;
         typedef BlockValue12 This;
         typedef BlockValue16 Outer;
     public:
         static const int SHIFT = Inner::SHIFT + 4;
         static const int MASK = (1 << SHIFT) - 1;
         static const int MAX_CAPACITY = 1 << SHIFT;

         Object blocks[16];

         BlockValue12() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue12(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
         }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

    class BlockValue16 : public Value {
         typedef BlockValue12 Inner;
         typedef BlockValue16 This;
         typedef BlockValue20 Outer;
     public:
         static const int SHIFT = Inner::SHIFT + 4;
         static const int MASK = (1 << SHIFT) - 1;
         static const int MAX_CAPACITY = 1 << SHIFT;

         Object blocks[16];

         BlockValue16() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue16(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
         }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

    class BlockValue20 : public Value {
         typedef BlockValue16 Inner;
         typedef BlockValue20 This;
         typedef BlockValue24 Outer;
     public:
         static const int SHIFT = Inner::SHIFT + 4;
         static const int MASK = (1 << SHIFT) - 1;
         static const int MAX_CAPACITY = 1 << SHIFT;

         Object blocks[16];

         BlockValue20() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue20(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
         }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

    class BlockValue24 : public Value {
         typedef BlockValue20 Inner;
         typedef BlockValue24 This;
         typedef BlockValue28 Outer;
     public:
         static const int SHIFT = Inner::SHIFT + 4;
         static const int MASK = (1 << SHIFT) - 1;
         static const int MAX_CAPACITY = 1 << SHIFT;

         Object blocks[16];

         BlockValue24() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue24(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
         }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

    class BlockValue28 : public Value {
         typedef BlockValue24 Inner;
         typedef BlockValue28 This;
         typedef BlockValue32 Outer;
     public:
         static const Type::int64 SHIFT = Inner::SHIFT + 4;
         static const Type::int64 ONE = 1;
         static const Type::int64 MASK = (ONE << SHIFT) - 1;
         static const Type::int64 MAX_CAPACITY = ONE << SHIFT;

         Object blocks[16];

         BlockValue28() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue28(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[index >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
             for (Type::int64 i = 0; i < 16; ++i) {
            	 Type::int64 indexMin = i << Inner::SHIFT; // Included
            	 Type::int64 indexMax = (i + 1) << Inner::SHIFT; // Excluded.
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return (length <= MAX_CAPACITY) ? this : (new Outer(this))->setLength(length);
         }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

    class BlockValue32 : public Value {
         typedef BlockValue28 Inner;
         typedef BlockValue32 This;
     public:
         static const Type::int64 SHIFT = Inner::SHIFT + 4;
         static const Type::int64 ONE = 1;
         static const Type::int64 MASK = (ONE << SHIFT) - 1;

         Object blocks[16];

         BlockValue32() { for (int i = 0; i < 16; ++i) blocks[i] = new Inner(); }
         BlockValue32(Inner* block0) { blocks[0] = block0; }
		 
		 E& elementAt(int index) override {
             return (blocks[((Type::int64)index) >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         const E& elementAt(int index) const override {
             return (blocks[((Type::int64)index) >> Inner::SHIFT].this_<Inner>())->elementAt(index & Inner::MASK);
         }

         Value* setLength(int length) override {
             for (Type::int64 i = 0; i < 16; ++i) {
            	 Type::int64 indexMin = i << Inner::SHIFT; // Included
            	 Type::int64 indexMax = (i + 1) << Inner::SHIFT; // Excluded.
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
			 if (length <= Inner::MAX_CAPACITY)
				 return (blocks[0].this_<Inner>())->setLength(length);
			 return this;
         }

         This* clone() const override {
             This* copy = new This();
             for (int i=0; i < 16; ++i) {
                 if (blocks[i] == nullptr) break;
                 copy->blocks[i] = blocks[i].cast_<Inner>()->clone();
             }
             return copy;
         }
     };

};

}
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Number.hpp"
#include "java/lang/String.hpp"

namespace java {
namespace lang {

/**
 * This class represents a 32 bits integer value.
 * 
 * Autoboxing and direct comparisons with <code>int</code> type
 * is supported. For example: <pre><code>
 *      Integer i = 13;
 *      ...
 *      if (i >= 0) { ... }
 * <code></pre>
 *
 * @version 7.0
 */
class Integer final : public Number::Interface {

    /**
     * Holds the 32 bits integer value.
     */
    Type::int32 value;

public:

    /** A constant holding the maximum value (<code>2^31 - 1</code>). **/
    static const Integer MAX_VALUE;

    /** A constant holding the minimum value (<code>-2^31</code>). **/
    static const Integer MIN_VALUE;

    /** Autoboxing constructor. */
    Integer(Type::int32 value) :
            value(value) {
    }

    /**
     * Returns a Integer having the specified value.
     */
    static Integer valueOf(int value) {
        return Integer(value);
    }

    /**
     * Compares this integer with the one specified.
     */
    bool equals(const Integer& that) const {
        return value == that.value;
    }

    ////////////////////////
    // Overriding methods //
    ////////////////////////

    Type::int32 intValue() const override {
        return value;
    }

    Type::int64 longValue() const override {
        return (Type::int64) value;
    }

    float floatValue() const override {
        return (float) value;
    }

    double doubleValue() const override {
        return (double) value;
    }

    String toString() const override {
        return String::valueOf(value);
    }

    bool equals(const Object&) const override {
        return false; // Not related.
    }

    int hashCode() const override {
        return (int) value;
    }

    //////////////////////////
    // Operator Overloading //
    //////////////////////////

    Integer& operator=(Type::int32 i) {
        value = i;
        return *this;
    }

    Integer& operator=(const Integer& that) {
        value = that.value;
        return *this;
    }

    bool operator==(const Integer& that) const {
        return value == that.value;
    }

    bool operator!=(const Integer& that) const {
        return value != that.value;
    }

    operator Type::int32() const { // Deboxing.
        return value;
    }

};

}
}

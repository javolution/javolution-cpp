/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Number.hpp"
#include "java/lang/Comparable.hpp"
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
class Integer final : public Number::Abstract, public virtual Comparable<Integer>::Interface {

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
    static Integer valueOf(Type::int32 value) {
        return Integer(value);
    }

    /**
     * Compares two {@code int} values numerically.
     */
    static int compare(Type::int32 x, Type::int32 y) {
        return (x < y) ? -1 : ((x == y) ? 0 : 1);
    }

    /**
     * Compares this integer with the one specified for order.
     */
    int compareTo(const Integer& that) const override {
        return compare(value, that.value);
    }

    /**
     * Compares this integer with the one specified for equality.
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

    bool equals(const Object& other) const override {
        if (this == other) return true;
        Integer* that = other.cast_<Integer>();
        return equals(*that);
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

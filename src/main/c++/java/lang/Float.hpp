/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <limits>
#include "java/lang/Number.hpp"
#include "java/lang/Comparable.hpp"
#include "java/lang/String.hpp"

namespace java {
namespace lang {

/**
 * This class represents a 32 bits float value.
 *
 * Autoboxing and comparisons with <code>float</code> type are supported.
 * For example: <pre><code>
 *      Float f = 13.3f;
 *      if (f >= 0.0f) { ... }
 * </code></pre>
 *
 * @version 7.0
 */
class Float final : public Number::Abstract, public virtual Comparable<Float>::Interface {

    /**
     * Holds the 32 bits float value.
     */
    float value;

public:

    /** A constant holding the positive infinity of type {@code float}. */
     static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();

     /** A constant holding the negative infinity of type {@code float}. */
     static constexpr float NEGATIVE_INFINITY = -POSITIVE_INFINITY;

     /** A constant holding a Not-a-Number (NaN) value of type {@code float}. */
     static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();

    /** Autoboxing constructor. */
    Float(float value) :
            value(value) {
    }

    /**
     * Returns a float having the specified value.
     */
    static Float valueOf(float value) {
        return Float(value);
    }

    /** Indicates if the specified number is a Not-a-Number (NaN) value. */
    static bool isNaN(float f) {
        return (f != f);
    }

    /** Indicates if the specified number is infinitely large in magnitude. */
    static bool isInfinite(float f) {
        return (f == POSITIVE_INFINITY) || (f == NEGATIVE_INFINITY);
    }

    /** Compares the two specified {@code float} values.*/
    static int compare(float f1, double f2) {
        if (f1 < f2) return -1;
        if (f1 > f2) return 1;
        Type::int32 i1 = *((Type::int32*)&f1);
        Type::int32 i2 = *((Type::int32*)&f2);
        if (i1 == i2) return 0;
        return (i1 < i2) ? -1 : 1;
    }

    /**
     * Compares this float with the one specified for order.
     */
    int compareTo(const Float& that) const override {
        return Float::compare(value, that.value);
    }

   /**
     * Compares this float with the one specified for equality.
     */
    bool equals(const Float& that) const {
        return value == that.value;
    }

    ////////////////////////
    // Overriding methods //
    ////////////////////////

    Type::int32 intValue() const override {
        return (Type::int32) value;
    }

    Type::int64 longValue() const override {
        return (Type::int64) value;
    }

    float floatValue() const override {
        return value;
    }

    double doubleValue() const override {
        return (double) value;
    }

    String toString() const override {
        return String::valueOf(value);
    }

    bool equals(const Object& other) const override {
        if (this == other) return true;
        Float* that = other.cast_<Float>();
        return equals(*that);
    }

    int hashCode() const override {
        return (int) value;
    }

    //////////////////////////
    // Operator Overloading //
    //////////////////////////

    Float& operator=(float f) {
        value = f;
        return *this;
    }

    Float& operator=(const Float& that) {
        value = that.value;
        return *this;
    }

    bool operator==(const Float& that) const {
        return value == that.value;
    }

    bool operator!=(const Float& that) const {
        return value != that.value;
    }

    operator float() const { // Deboxing.
        return value;
    }

};

}
}

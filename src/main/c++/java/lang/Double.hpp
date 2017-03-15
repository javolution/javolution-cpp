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
 * This class represents a 64 bits float value.
 *
 * Autoboxing and comparisons with <code>double</code> type are supported.
 * For example: <pre><code>
 *      Double d = 13.3;
 *      if (d >= 0.0) { ... }
 * </code></pre>
 *
 * @version 7.0
 */
class Double final : public Number::Abstract, public virtual Comparable<Double>::Interface {

    double value;

public:

    /** A constant holding the positive infinity of type {@code double}. */
    static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

    /** A constant holding the negative infinity of type {@code double}. */
    static constexpr double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

    /** A constant holding a Not-a-Number (NaN) value of type {@code double}. */
    static constexpr double NaN = std::numeric_limits<float>::quiet_NaN();

    /** Autoboxing constructor. */
    Double(double value) :
            value(value) {
    }

    /** Returns a double having the specified value. */
    static Double valueOf(double value) {
        return Double(value);
    }

    /** Indicates if the specified number is a Not-a-Number (NaN) value. */
    static bool isNaN(double d) {
        return (d != d);
    }

    /** Indicates if the specified number is infinitely large in magnitude. */
    static bool isInfinite(double d) {
        return (d == POSITIVE_INFINITY) || (d == NEGATIVE_INFINITY);
    }

    /** Compares the two specified {@code double} values.*/
    static int compare(double d1, double d2) {
        if (d1 < d2)
            return -1;
        if (d1 > d2)
            return 1;
        Type::int64* p1 = reinterpret_cast<Type::int64*>(&d1);
        Type::int64* p2 = reinterpret_cast<Type::int64*>(&d2);
        if (*p1 == *p2)
            return 0;
        return (*p1 < *p2) ? -1 : 1;
    }

    /**
     * Compares this double with the one specified for order.
     */
    int compareTo(const Double& that) const override {
        return Double::compare(value, that.value);
    }

    /**
     * Compares this double with the one specified for equality.
     */
    bool equals(const Double& that) const {
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
        return (float) value;
    }

    double doubleValue() const override {
        return value;
    }

    String toString() const override {
        return String::valueOf(value);
    }

    bool equals(const Object& other) const override {
        if (this == other) return true;
        Double* that = other.cast_<Double>();
        return equals(*that);
    }

    int hashCode() const override {
        return (int) value;
    }

    //////////////////////////
    // Operator Overloading //
    //////////////////////////

    Double& operator=(double d) {
        value = d;
        return *this;
    }

    Double& operator=(const Double& that) {
        value = that.value;
        return *this;
    }

    bool operator==(const Double& that) const {
        return value == that.value;
    }

    bool operator!=(const Double& that) const {
        return value != that.value;
    }

    operator double() const { // Deboxing.
        return value;
    }

};

}
}

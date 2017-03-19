/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <limits>
#include "java/lang/String.hpp"
#include "java/lang/Class.hpp"

namespace java {
namespace lang {

/**
 * This value-type represents a 32 bits float value.
 *
 * Autoboxing and comparisons with <code>float</code> type are supported.
 * For example: <pre><code>
 *      Float f = 13.3f;
 *      if (f >= 0.0f) { ... }
 * </code></pre>
 *
 * @version 7.0
 */
class Float final {

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

     /** Default constructor (zero). */
     Float() :
             value(0.0f) {
     }

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
    static int compare(float f1, float f2) {
        if (f1 < f2) return -1;
        if (f1 > f2) return 1;
        Type::int32* p1 = reinterpret_cast<Type::int32*>(&f1);
        Type::int32* p2 = reinterpret_cast<Type::int32*>(&f2);
        if (*p1 == *p2)
            return 0;
        return (*p1 < *p2) ? -1 : 1;
    }

    /**
     * Compares this float with the one specified for order.
     */
    int compareTo(const Float& that) const {
        return Float::compare(value, that.value);
    }

    /////////////////////////////////////////////////////////////
    // Object::Interface Equivalent methods (for template use) //
    /////////////////////////////////////////////////////////////

    int hashCode() const {
        return (int) value;
    }

    bool equals(const Float& that) const {
        return value == that.value;
    }

    String toString() const  {
        return String::valueOf(value);
    }

    Class getClass() const {
          return Class::forName("java::lang::Float");
    }

    //////////////////////////////////////////////////
    // Number Equivalent methods (for template use) //
    //////////////////////////////////////////////////

    Type::int32 intValue() const {
        return (Type::int32) value;
    }

    Type::int64 longValue() const {
        return (Type::int64) value;
    }

    float floatValue() const {
        return value;
    }

    double doubleValue() const {
        return (double) value;
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

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"
#include "java/lang/Class.hpp"

namespace java {
namespace lang {

/**
 * This value-type represents a 32 bits integer value.
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
class Integer final {

    /**
     * Holds the 32 bits integer value.
     */
    Type::int32 value;

public:

    /** A constant holding the maximum value (<code>2^31 - 1</code>). **/
    static const Integer MAX_VALUE;

    /** A constant holding the minimum value (<code>-2^31</code>). **/
    static const Integer MIN_VALUE;

    /** Default constructor (zero). */
    Integer() :
            value(0) {
    }

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
    int compareTo(const Integer& that) const {
        return compare(value, that.value);
    }

    /////////////////////////////////////////////////////////////
    // Object::Interface Equivalent methods (for template use) //
    /////////////////////////////////////////////////////////////

    int hashCode() const {
        return value;
    }

    bool equals(const Integer& that) const {
        return value == that.value;
    }

    String toString() const  {
        return String::valueOf(value);
    }

    Class getClass() const {
          return Class::forName("java::lang::Integer");
    }

    //////////////////////////////////////////////////
    // Number Equivalent methods (for template use) //
    //////////////////////////////////////////////////

    Type::int32 intValue() const {
        return value;
    }

    Type::int64 longValue() const {
        return (Type::int64) value;
    }

    float floatValue() const {
        return (float) value;
    }

    double doubleValue() const {
        return (double) value;
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

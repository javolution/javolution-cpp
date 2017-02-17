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
 * This class represents a 64 bits Long value. Unlike java.lang.Long
 * an exception is raised if a conversion to a primitive type would result
 * in a truncation.
 *
 * Autoboxing and direct comparisons with <code>long</code> type
 * is supported. For example: <pre><code>
 *      Long i = 13;
 *      ...
 *      if (i >= 0) { ... }
 * <code></pre>
 *
 * @version 7.0
 */
class Long final : public Number::Interface {

    /**
     * Holds the 64 bits Long value.
     */
    Type::int64 value;

public:

    /** A constant holding the maximum value (<code>2^63 - 1</code>). **/
    static const Long MAX_VALUE;

    /** A constant holding the minimum value (<code>-2^63</code>). **/
    static const Long MIN_VALUE;

    /** Autoboxing constructor. */
    Long(Type::int64 value) :
            value(value) {
    }

    /**
     * Returns a Long having the specified value.
     */
    static Long valueOf(Type::int64 value) {
        return Long(value);
    }

    /**
     * Compares this Long with the one specified.
     */
    bool equals(const Long& that) const {
        return value == that.value;
    }

    ////////////////////////
    // Overriding methods //
    ////////////////////////

    Type::int32 intValue() const override {
        return (Type::int32) value;
    }

    Type::int64 longValue() const override {
        return value;
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

    Long& operator=(Type::int64 i) {
        value = i;
        return *this;
    }

    Long& operator=(const Long& that) {
        value = that.value;
        return *this;
    }

    bool operator==(const Long& that) const {
        return value == that.value;
    }

    bool operator!=(const Long& that) const {
        return value != that.value;
    }

    operator Type::int64() const { // Deboxing.
        return value;
    }
};

}
}

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
 * This class represents a 64 bits float value. Unlike java.lang.Float
 * an exception is raised if a conversion to a primitive type would result
 * in a truncation.
 *
 * Autoboxing and comparisons with <code>double</code> type are supported.
 * For example: <pre><code>
 *      Double d = 13.3;
 *      if (d >= 0.0) { ... }
 * </code></pre>
 *
 * @version 7.0
 */
class Double final : public Number::Interface {

    double value;

public:

    /** Autoboxing constructor. */
    Double(double value) :
            value(value) {
    }

    /**
     * Returns a double having the specified value.
     */
    static Double valueOf(double value) {
        return Double(value);
    }

    /**
     * Compares this double with the one specified.
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

    bool equals(const Object&) const override {
        return false; // Not related.
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

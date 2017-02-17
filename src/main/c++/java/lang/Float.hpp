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
 * This class represents a 32 bits float value. Unlike java.lang.Float an exception is raised if a conversion
 * to a primitive type would result in a truncation.
 *
 * Autoboxing and comparisons with <code>float</code> type are supported.
 * For example: <pre><code>
 *      Float f = 13.3f;
 *      if (f >= 0.0f) { ... }
 * </code></pre>
 *
 * @version 7.0
 */
class Float final : public Number::Interface {

    /**
     * Holds the 32 bits float value.
     */
    float value;

public:

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

    /**
     * Compares this float with the one specified.
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

    bool equals(const Object&) const override {
        return false; // Not related.
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

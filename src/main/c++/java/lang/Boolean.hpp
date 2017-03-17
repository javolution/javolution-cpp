/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"

namespace java {
namespace lang {

/**
 * This value-type represents the primitive <code>bool</code>
 *
 * Autoboxing and direct comparisons with  <code>bool</code> type are supported.
 * For example: <pre><code>
 *      Boolean b = false;
 *      ...
 *      if (b == false) { ... }
 * </code></pre>
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Boolean.html">
 *       Java - Boolean</a>
 * @version 7.0
 */
class Boolean final : public virtual Object::Interface { // Value-Type.

    bool value;

public:

    /** The Boolean object corresponding to the primitive value <code>true</code>. */
    static const Boolean TRUE;

    /** The Boolean object corresponding to the primitive value <code>false</code>. */
    static const Boolean FALSE;

    /** Default constructor (false). */
    Boolean() :
            value(false) {
    }

    /** Autoboxing constructor. */
    Boolean(bool value) :
            value(value) {
    }

    /**
     * Returns a bool having the specified value.
     */
    static Boolean valueOf(bool value) {
        return value ? TRUE : FALSE;
    }

    /**
     * Returns the primitive bool value for this bool object.
     */
    bool boolValue() const {
        return value;
    }

    /**
     * Compares this bool with the one specified.
     */
    bool equals(const Boolean& that) const {
        return value == that.value;
    }

    ////////////////////////
    // Overriding methods //
    ////////////////////////

    String toString() const override {
        return String::valueOf(value);
    }

    bool equals(const Object& other) const override {
        if (this == other) return true;
        Boolean* that = other.cast_<Boolean>();
        return equals(*that);
    }

    int hashCode() const override {
        return (int) value;
    }

    //////////////////////////
    // Operator Overloading //
    //////////////////////////

    Boolean& operator=(bool b) {
        value = b;
        return *this;
    }

    Boolean& operator=(const Boolean& that) {
        value = that.value;
        return *this;
    }

    bool operator==(const Boolean& that) const {
        return value == that.value;
    }

    bool operator!=(const Boolean& that) const {
        return value != that.value;
    }

    operator bool() const { // Deboxing.
        return value;
    }

};

}
}

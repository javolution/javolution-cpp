/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"

namespace java {
namespace lang {

class Boolean_Heap;

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
class Boolean : public virtual Object::Interface { // Value-Type.

    bool value;

public:

    /** Since Boolean is a value-type (stack allocated), define an handle type on heap allocated Boolean. */
    typedef Boolean_Heap Heap;

    /** The Boolean object corresponding to the primitive value <code>true</code>. */
    static const Boolean TRUE;

    /** The Boolean object corresponding to the primitive value <code>false</code>. */
    static const Boolean FALSE;

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

class Boolean_Heap final : public virtual Object {
public:
    class Value final : public Object::Value, public virtual Boolean {
    public:

        Value(bool b) : Boolean(b) {}

        String toString() const override {
              return Boolean::toString();
        }

        bool equals(const Object& other) const override {
              return Boolean::equals(other);
        }

        int hashCode() const override {
              return Boolean::hashCode();
        }
    };
    CTOR(Boolean_Heap, Value)

    /** Returns a new heap allocated boolean having the specified value. */
    static Boolean_Heap newInstance(bool b) {
        return new Value(b);
    }

};

}
}

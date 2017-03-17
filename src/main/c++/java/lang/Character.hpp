/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"
#include "java/lang/IllegalArgumentException.hpp"
#include "java/lang/ArithmeticException.hpp"

namespace java {
namespace lang {

/**
 * This class wraps the value of the primitive type <code>Type::uchar</code> (Unicode UTF-16 character) in an object.
 *
 * Autoboxing and direct comparisons with <code>char</code> (ASCII) and <code>Type::uchar</code> are supported.
 * For example: <pre><code>
 *      Character b = 'x';
 *      ...
 *      if (b >= u'µ') { ... }
 * </code></pre>
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Character.html">
 *       Java - Character</a>
 * @version 7.0
 */
class Character final : public virtual Object::Interface { // Value-Type.

    Type::uchar value;

public:

    /** Default constructor ('\0'). */
    Character() :
            value(0) {
    }

    /**
     * Autoboxing constructor from ascii character.
     * @throw IllegalArgumentException if the specified character is not ascii.
     */
    Character(char value) :
            value(value) {
        if (value > 127)
            throw IllegalArgumentException("Not an ASCII character (consider using Type::uchar)");
    }

    /** Autoboxing constructor from wide character. */
    Character(Type::uchar value) :
            value(value) {
    }

    /**
     * Returns a character having the specified value.
     */
    static Character valueOf(Type::uchar value) {
        return Character(value);
    }

    /**
     * Returns the primitive character value for this Character object.
     */
    Type::uchar charValue() const {
        return value;
    }

    /**
     * Compares this character with the one specified.
     */
    bool equals(const Character& that) const {
        return value == that.value;
    }

    /**
     * Returns the ASCII character value for this character.
     * @throw ArithmeticException if this character cannot be represented as an ascii character.
     */
    unsigned char asciiValue() const {
        if (value > 127)
            throw ArithmeticException("Not an ASCII character");
        return (char) value;
    }

    ////////////////////////
    // Overriding methods //
    ////////////////////////

    String toString() const override {
        return String::valueOf(value);
    }

    bool equals(const Object& other) const override {
        if (this == other) return true;
        Character* that = other.cast_<Character>();
        return equals(*that);
    }

    int hashCode() const override {
        return (int) value;
    }

    //////////////////////////
    // Operator Overloading //
    //////////////////////////

    Character& operator=(bool b) {
        value = b;
        return *this;
    }

    Character& operator=(const Character& that) {
        value = that.value;
        return *this;
    }

    bool operator==(const Character& that) const {
        return value == that.value;
    }

    bool operator!=(const Character& that) const {
        return value != that.value;
    }

    operator Type::uchar() const { // Deboxing.
        return value;
    }

    operator char() const { // Deboxing
        return asciiValue();
    }

};

}
}

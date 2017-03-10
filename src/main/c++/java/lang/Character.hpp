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
class Character_Heap;

/**
 * This class wraps the value of the primitive type <code>wchar</code> in an object.
 *
 * Autoboxing and direct comparisons with <code>char</code> (ASCII) and <code>wchar</code> are supported.
 * For example: <pre><code>
 *      Character b = 'x';
 *      ...
 *      if (b >= L'µ') { ... }
 * </code></pre>
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Character.html">
 *       Java - Character</a>
 * @version 7.0
 */
class Character : public virtual Object::Interface { // Value-Type.

    Type::wchar value;

public:
    /** Since Character is a value-type (stack allocated), define an handle type on heap allocated Character. */
    typedef Character_Heap Heap;

    /**
     * Autoboxing constructor from ascii character.
     * @throw IllegalArgumentException if the specified character is not ascii.
     */
    Character(char value) :
            value(value) {
        if (value > 127)
            throw IllegalArgumentException("not an ascii character (consider using Type::wchar)");
    }

    /** Autoboxing constructor from wide character. */
    Character(Type::wchar value) :
            value(value) {
    }

    /**
     * Returns a character having the specified value.
     */
    static Character valueOf(Type::wchar value) {
        return Character(value);
    }

    /**
     * Returns the primitive character value for this Character object.
     */
    Type::wchar charValue() const {
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
            throw ArithmeticException("wchar to ascii overflow");
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

    operator Type::wchar() const { // Deboxing.
        return value;
    }

    operator char() const { // Deboxing
        return asciiValue();
    }

};

class Character_Heap final : public virtual Object {
public:
    class Value final : public Object::Value, public virtual Character {
    public:

        Value(char c) : Character(c) {}
        Value(Type::wchar c) : Character(c) {}

        String toString() const override {
              return Character::toString();
        }

        bool equals(const Object& other) const override {
              return Character::equals(other);
        }

        int hashCode() const override {
              return Character::hashCode();
        }
    };

    CTOR(Character_Heap, Value)

    /** Returns a new heap allocated character having the specified character value. */
    static Character_Heap newInstance(char c) {
        return new Value(c);
    }

    /** Returns a new heap allocated character having the specified wide-character value. */
    static Character_Heap newInstance(Type::wchar c) {
        return new Value(c);
    }
};

}
}

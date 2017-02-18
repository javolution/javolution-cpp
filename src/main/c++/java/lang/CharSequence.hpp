/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Object.hpp"

namespace java {
namespace lang {

/**
 * This class represents a readable sequence of char values.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/CharSequence.html">
 *       Java - CharSequence</a>
 * @version 7.0
 */
class CharSequence: public virtual Object {
public:
    class Interface: public virtual Object::Interface {
    public:
        virtual Type::wchar charAt(int index) const = 0;
        virtual int length() const = 0;
        virtual CharSequence subSequence(int start, int end) const = 0;
    };
    CharSequence(Void = nullptr) {}

    /**
     * Returns the char value at the specified index.
     */
    Type::wchar charAt(int index) const {
        return this_cast_<Interface>()->charAt(index);
    }

    /**
     * Returns the length of this character sequence.
     */
    int length() const {
        return this_cast_<Interface>()->length();
    }

    /**
     * Returns a CharSequence that is a subsequence of this sequence.
     */
    CharSequence subSequence(int start, int end) const {
        return this_cast_<Interface>()->subSequence(start, end);
    }

};

}
}

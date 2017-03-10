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

        /**
         * Returns the char value at the specified index.
         */
        virtual Type::wchar charAt(int index) const = 0;

        /**
         * Returns the length of this character sequence.
         */
        virtual int length() const = 0;

        /**
         * Returns a CharSequence that is a subsequence of this sequence.
         */
        virtual CharSequence subSequence(int start, int end) const = 0;

    };

    CharSequence(Void = nullptr) {}

    // Exported Interface methods.

    Type::wchar charAt(int index) const {
        return this_cast_<Interface>()->charAt(index);
    }

    int length() const {
        return this_cast_<Interface>()->length();
    }

    CharSequence subSequence(int start, int end) const {
        return this_cast_<Interface>()->subSequence(start, end);
    }

};

}
}

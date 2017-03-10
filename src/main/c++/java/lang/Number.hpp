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
 * This abstract class defines the methods to be implemented by numerics types.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Number.html">
 *       Java - Number</a>
 * @version 7.0
 */
class Number: public virtual Object {
public:
    class Abstract: public virtual Object::Interface {
    public:
        /**
         * Returns the value of the specified number as a 32 bits <code>int</code>.
         */
        virtual Type::int32 intValue() const = 0;

        /**
         * Returns the value of the specified number as a 64 bits <code>long</code>.
         */
        virtual Type::int64 longValue() const = 0;

        /**
         * Returns the value of the specified number as an <code>float</code>.
         */
        virtual float floatValue() const = 0;

        /**
         * Returns the value of the specified number as an <code>double</code>.
         */
        virtual double doubleValue() const = 0;
    };

    CTOR(Number, Abstract)

    /**
     * Returns the value of the specified number as an <code>int8</code>.
     */
    Type::int8 byteValue() const {
        return (Type::int8) intValue();
    }

    /**
     * Returns the value of the specified number as an <code>int16</code>.
     */
    Type::int16 shortValue() const {
        return (Type::int16) intValue();
    }

    // Exported Abstract methods.

    Type::int32 intValue() const {
        return this_cast_<Abstract>()->intValue();
    }

    Type::int64 longValue() const {
        return this_cast_<Abstract>()->longValue();
    }

    float floatValue() const {
        return this_cast_<Abstract>()->floatValue();
    }

    double doubleValue() const {
        return this_cast_<Abstract>()->doubleValue();
    }

};

}
}

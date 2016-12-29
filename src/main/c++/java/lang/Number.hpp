/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _JAVA_LANG_NUMBER_HPP
#define _JAVA_LANG_NUMBER_HPP

#include "java/lang/Object.hpp"

namespace java {
    namespace lang {
        class Number_API;
        typedef Type::Handle<Number_API> Number;
    }
}

/**
 * This class represents the number base class.
 *
 * @see  <a href="http://java.sun.com/javase/6/docs/api/java/lang/Number.html">
 *       Java - Number</a>
 * @version 1.0
 */
class java::lang::Number_API : public virtual java::lang::Object_API {
public:

    /**
     * Returns the value of the specified number as an <code>Type::int32</code>.
     *
     * @return the numeric value represented by this number.
     */
    virtual Type::int32 intValue() const = 0;

    /**
     * Returns the value of the specified number as an <code>Type::int64</code>.
     *
     * @return the numeric value represented by this number.
     */
    virtual Type::int64 longValue() const = 0;

    /**
     * Returns the value of the specified number as an <code>Type::float32</code>.
     *
     * @return the numeric value represented by this number.
     */
    virtual Type::float32 floatValue() const = 0;

    /**
     * Returns the value of the specified number as an <code>Type::float64</code>.
     *
     * @return the numeric value represented by this number.
     */
    virtual Type::float64 doubleValue() const = 0;

    /**
     * Returns the value of the specified number as an <code>Type::int8</code>.
     *
     * @return the numeric value represented by this number.
     */
    virtual Type::int8 byteValue() const {
        return (Type::int8)intValue();
    }

    /**
     * Returns the value of the specified number as an <code>Type::int16</code>.
     *
     * @return the numeric value represented by this number.
     */
    virtual Type::int16 shortValue() const {
        return (Type::int16)intValue();
    }

};

#endif

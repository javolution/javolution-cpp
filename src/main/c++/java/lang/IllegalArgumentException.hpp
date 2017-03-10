/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/RuntimeException.hpp"

namespace java {
namespace lang {

/**
 * Thrown to indicate that a method has been passed an illegal or inappropriate argument.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/IllegalArgumentException.html">
 *       Java - IllegalArgumentException</a>
 * @version 7.0
 */
class IllegalArgumentException: public RuntimeException {
public:
    class Value: public RuntimeException::Value {
    };

    /** Creates an illegal argument exception with the specified optional message.*/
    IllegalArgumentException(const String message = nullptr, Value* value = new Value()) :
            RuntimeException(message, value) {
    }
};

}
}

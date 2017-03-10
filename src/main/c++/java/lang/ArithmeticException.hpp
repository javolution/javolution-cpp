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
 * Thrown when an exceptional arithmetic condition has occurred.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/ArithmeticException.html">
 *       Java - ArithmeticException</a>
 * @version 7.0
 */
class ArithmeticException: public RuntimeException {
public:
    class Value: public RuntimeException::Value {
    };

    /** Creates an arithmetic exception with the specified optional message.*/
    ArithmeticException(const String& message = nullptr, Value* value = new Value()) :
            RuntimeException(message, value) {
    }

};

}
}

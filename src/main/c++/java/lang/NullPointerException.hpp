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
 * Thrown when an application attempts to use <code>nullptr</code> in a case where an object is required.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/NullPointerException.html">
 *       Java - NullPointerException</a>
 * @version 7.0
 */
class NullPointerException: public RuntimeException {
public:
    class Value: public RuntimeException::Value {
    };

    /** Creates a null pointer exception with the specified optional message.*/
    NullPointerException(const String message = nullptr, Value* value = new Value()) :
            RuntimeException(message, value) {
    }
};

}
}

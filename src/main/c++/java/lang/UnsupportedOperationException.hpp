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
 * Thrown to indicate that the requested operation is not supported.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/UnsupportedOperationException.html">
 *       Java - UnsupportedOperationException</a>
 * @version 7.0
 */

class UnsupportedOperationException: public RuntimeException {
public:
    class Value: public RuntimeException::Value {
    };

    /** Creates an unsupported operation exception with the specified optional message.*/
    UnsupportedOperationException(const String& message = nullptr, Value* value = new Value()) :
            RuntimeException(message, value) {
    }
};

}
}

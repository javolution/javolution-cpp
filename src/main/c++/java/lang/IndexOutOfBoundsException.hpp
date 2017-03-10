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
 * Thrown to indicate that an index of some sort (such as to an array,
 * to a string, or to a vector) is out of range.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/IndexOutOfBoundsException.html">
 *       Java - IndexOutOfBoundsException</a>
 * @version 7.0
 */
class IndexOutOfBoundsException: public RuntimeException {
public:
    class Value: public RuntimeException::Value {
    };

    /** Creates an index out of bounds exception with the specified optional message.*/
    IndexOutOfBoundsException(const String& message = nullptr, Value* value = new Value()) :
            RuntimeException(message, value) {
    }
};

}
}

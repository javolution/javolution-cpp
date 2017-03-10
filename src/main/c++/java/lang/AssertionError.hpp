/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Error.hpp"

namespace java {
namespace lang {

/**
 * Thrown to indicate that an assertion has failed.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/AssertionError.html">
 *       Java - AssertionError</a>
 * @version 7.0
 */
class AssertionError: public Error {
public:
    class Value: public Error::Value {
    };

    /** Creates an assertion error with the specified optional message.*/
    AssertionError(const String& message = nullptr, Value* value = new Value()) :
            Error(message, value) {
    }
};

}
}

/*
/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/AssertionError.hpp"

namespace junit {
namespace framework {

/**
 * Thrown when a JUnit assertion failed.
 * @version 7.0
 */
class AssertionFailedError: public AssertionError {
public:

    class Value: public AssertionError::Value {
    };

    /** Creates an assertion failed error with the specified optional message.*/
    AssertionFailedError(const String& message = nullptr, Value* value = new Value()) :
            AssertionError(message, value) {
    }
};

}
}

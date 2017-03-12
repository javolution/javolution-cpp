/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Exception.hpp"

namespace java {
namespace lang {

/**
 * This class and its sub-classes represents exception which should not 
 * occur during normal program execution (typically programming error!).
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/RuntimeException.html">
 *       Java - RuntimeException</a>
 * @version 7.0
 */
class RuntimeException: public Exception {
public:

    /** Creates a runtime exception with the specified optional message.*/
    RuntimeException(const String& message = nullptr) :
            Exception(message) {
    }

};

}
}

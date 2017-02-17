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
 * Thrown to indicate that the requested operation is not allowed.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/SecurityException.html">
 *       Java - SecurityException</a>
 * @version 7.0
 */

class SecurityException: public RuntimeException {
public:
    SecurityException(const String& message = nullptr, const String& classname = "java::lang::SecurityException") :
            RuntimeException(message, classname) {
    }
};

}
}

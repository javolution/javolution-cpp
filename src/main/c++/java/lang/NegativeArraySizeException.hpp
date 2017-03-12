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
 * Thrown if an application tries to create an array with negative size.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/NegativeArraySizeException.html">
 *       Java - NegativeArraySizeException</a>
 * @version 7.0
 */
class NegativeArraySizeException: public RuntimeException {
public:

    /** Creates a negative array size exception with the specified optional message.*/
    NegativeArraySizeException(const String& message = nullptr) :
            RuntimeException(message) {
    }
};

}
}

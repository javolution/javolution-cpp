/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Throwable.hpp"

namespace java {
namespace lang {

/**
 * This class and its subclasses indicates serious problems that a reasonable application should not try to catch.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Error.html">
 *       Java - Error</a>
 * @version 7.0
 */
class Error: public Throwable {
public:

    /** Creates an error with the specified optional message.*/
    Error(const String& message = nullptr) :
            Throwable(message) {
    }

};

}
}

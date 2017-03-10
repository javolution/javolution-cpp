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
 * This class and its subclasses are a form of <code>Throwable</code> that indicates conditions that a reasonable
 * application might want to catch.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Exception.html">
 *       Java - Exception</a>
 * @version 7.0
 */
class Exception: public Throwable {
public:
    class Value: public Throwable::Value {
    };

    /** Creates an exception with the specified optional message.*/
    Exception(const String& message = nullptr, Value* value = new Value()) :
            Throwable(message, value) {
    }
};

}
}

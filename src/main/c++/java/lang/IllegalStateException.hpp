/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/RuntimeException.hpp"

namespace java { namespace lang {

/**
 * Thrown to signal that a method has been invoked at an illegal or
 * inappropriate time.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/IllegalStateException.html">
 *       Java - IllegalStateException</a>
 * @version 7.0
 */
class IllegalStateException : public RuntimeException {
public:
	IllegalStateException(const String message = nullptr,
            const String& classname = "java::lang::IllegalStateException") :
			RuntimeException(message, classname) {
	}
};
}}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <exception>
#include <booster/backtrace.hpp>
#include "java/lang/String.hpp"

#define LINE_INFO (*java::lang::StringBuilder::newInstance()).append("File: ").append((int)__FILE__).append(", Line: ").append((int)__LINE__).toString()

namespace java {
namespace lang {

/**
 * The class is the superclass of all errors and exceptions.
 * Instances of this class should be thrown by value and caught by reference.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Throwable.html">
 *       Java - Throwable</a>
 * @version 7.0
 */
class Throwable: public virtual Object::Interface, public booster::backtrace { // Value type.

	String message;
	String classname;

public:

	Throwable(const String& message = nullptr, const String& classname = "java::lang::Throwable") :
			message(message), classname(classname) {
	}

	/**
	 * Prints this throwable and its backtrace to the standard error stream.
	 */
	JAVOLUTION_DLL
	virtual void printStackTrace() const;

	/**
	 * Returns the detail message of this exception or nullptr if none.
	 */
	virtual String getMessage() const {
		return message;
	}

	/**
	 * Returns a short description of this throwable (classname + ": " + getMessage())
	 */
	JAVOLUTION_DLL
	virtual String toString() const;

	/**
	 * Returns a null terminated character sequence that may be used to identify the exception (C++).
	 */
	JAVOLUTION_DLL
	virtual const char* what() const throw ();
};

}
}

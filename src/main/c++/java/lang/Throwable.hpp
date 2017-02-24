/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <exception>
#include "java/lang/String.hpp"
#include "booster/backtrace.hpp"

#define LINE_INFO (String::valueOf("File: ") + __FILE__ + ", Line: " + __LINE__)

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
class Throwable: public booster::backtrace, public std::exception, public virtual Object::Interface  { // Value type.

	String message;
	String classname;

public:

	/** Creates a Throwable with specified message. */
	Throwable(const String& message = nullptr, const String& classname = "java::lang::Throwable") :
			message(message), classname(classname) {
	}

	/**
	 * Returns the detail message of this exception or nullptr if none.
	 */
	virtual String getMessage() const {
		return message;
	}

	/**
	 * Returns a short description of this throwable (classname + ": " + getMessage())
	 */
	virtual String toString() const {
		return (message != nullptr) ? classname + ": " + message : classname;
	}

	/**
	 * Returns a null terminated character sequence that may be used to identify the exception (C++).
	 */
	virtual const char* what() const throw () {
		return toString().toUTF8().c_str();
	}

	/**
	* Prints this throwable and its backtrace to the standard error stream.
	*/
	virtual void printStackTrace() const;
};

}
}

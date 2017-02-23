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
class Throwable: public booster::backtrace, public virtual Object::Interface  { // Value type.

	String message;
	String classname;

public:

	Throwable(const String& message = nullptr, const String& classname = "java::lang::Throwable") :
			message(message), classname(classname) {
	   //     std::ostringstream res;
	   //     res.imbue(std::locale::classic());
	   //     res << _message << std::endl;
	        std::cerr << booster::trace(*this) << std::endl << std::flush;;
	}

	/**
	 * Prints this throwable and its backtrace to the standard error stream.
	 */
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
	virtual String toString() const;

	/**
	 * Returns a null terminated character sequence that may be used to identify the exception (C++).
	 */
	virtual const char* what() const throw ();
};

}
}

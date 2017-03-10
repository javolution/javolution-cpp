/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <exception>
#include "booster/backtrace.hpp"
#include "java/lang/String.hpp"

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
class Throwable: public booster::backtrace, public std::exception, public virtual Object {
public:

    class Value: public Object::Value {
    friend class Throwable;
        String message;
    public:
        /**
         * Returns the detail message of this exception or nullptr if none.
         */
        virtual String getMessage() const {
            return message;
        }

        /**
         * Returns a short description of this throwable (classname + ": " + getMessage())
         */
        virtual String toString() const override;

    };

    /** Creates a throwable exception with specified optional message. */
    Throwable(const String& message = nullptr, Value* value = new Value()) :
            Object(value) {
        value->message = message;
    }

    /**
     * Prints this throwable and its backtrace to the standard error stream.
     */
    void printStackTrace() const;

    /**
     * Returns a null terminated character sequence that may be used to identify the exception (C++).
     */
    const char* what() const throw () {
        return toString().toUTF8().c_str();
    }

    // Exported Value methods.

    String getMessage() const {
        return this_<Value>()->getMessage();
    }

};

}
}

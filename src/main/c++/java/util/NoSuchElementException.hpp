/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _JAVA_UTIL_NO_SUCH_ELEMENT_EXCEPTION_HPP
#define _JAVA_UTIL_NO_SUCH_ELEMENT_EXCEPTION_HPP

#include "java/lang/RuntimeException.hpp"

namespace java {
    namespace util {
        class NoSuchElementException_API;
        class NoSuchElementException : public java::lang::RuntimeException { 
        public:
            NoSuchElementException(Type::NullHandle = Type::Null) : java::lang::RuntimeException() {} // Null
            NoSuchElementException(NoSuchElementException_API* ptr) : java::lang::RuntimeException((java::lang::RuntimeException_API*)ptr) {}
        };
    }
}

/**
 * Thrown to indicate that there are no more elements in a collection.
 *
 * @see  <a href="http://java.sun.com/javase/6/docs/api/java/util/NoSuchElementException.html">
 *       Java - NoSuchElementException</a>
 * @version 1.0
 */
class java::util::NoSuchElementException_API : public java::lang::RuntimeException_API {
protected:

    NoSuchElementException_API(java::lang::String const& message) :
        java::lang::RuntimeException_API(message) {
    };

public:

    /**
     * Returns the runtime exception having the specified message.
     *
     * @param message the exception message.
     */
    static NoSuchElementException newInstance(java::lang::String const& message = Type::Null) {
        return new NoSuchElementException_API(message);
    }

};

#endif

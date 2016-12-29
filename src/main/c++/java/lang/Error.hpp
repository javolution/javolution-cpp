/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _JAVA_LANG_ERROR_HPP
#define _JAVA_LANG_ERROR_HPP

#include "java/lang/Throwable.hpp"

namespace java {
    namespace lang {
        class Error_API;
        class Error : public Throwable { 
        public:
            Error(Type::NullHandle = Type::Null) : Throwable() {} // Null
            Error(Error_API* ptr) : Throwable((Throwable_API*)ptr) {}
        };
    }
}

/**
 * This class and its subclasses indicates serious problems that a reasonable
 * application should not try to catch.
 *
 * @see  <a href="http://java.sun.com/javase/6/docs/api/java/lang/Error.html">
 *       Java - Error</a>
 * @version 1.0
 */
class java::lang::Error_API : public java::lang::Throwable_API {
protected:

    Error_API(String message) : Throwable_API(message) {
    };

public:

    /**
     * Returns an Error having the specified message.
     *
     * @param message the Error message.
     */
    static Error newInstance(String const& message = Type::Null) {
        return new Error_API(message);
    }
};

#endif

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _JUNIT_FRAMEWORK_ASSERTION_FAILED_ERROR_HPP
#define _JUNIT_FRAMEWORK_ASSERTION_FAILED_ERROR_HPP

#include "java/lang/RuntimeException.hpp"

namespace junit {
    namespace framework {
        class AssertionFailedError_API;
        class AssertionFailedError : public java::lang::RuntimeException {
        public:
            AssertionFailedError(Type::NullHandle = Type::Null) : java::lang::RuntimeException() {} // Null
            AssertionFailedError(AssertionFailedError_API* ptr) : java::lang::RuntimeException((java::lang::RuntimeException_API*)ptr) {}
        };
    }
}

/**
 * Thrown when an assertion failed.
 *
 * @see  <a href="http://junit.org/apidocs/junit/framework/AssertionFailedError.html">
 *       JUnit - AssertionFailedError</a>
 * @version 1.0
 */
class junit::framework::AssertionFailedError_API : public java::lang::RuntimeException_API {
protected:

    AssertionFailedError_API(java::lang::String const& message) :
        java::lang::RuntimeException_API(message) {
    };

public:

    /**
     * Returns the runtime exception having the specified message.
     *
     * @param message the exception message.
     */
    static AssertionFailedError newInstance(java::lang::String const& message = Type::Null) {
        return new AssertionFailedError_API(message);
    }

};

#endif

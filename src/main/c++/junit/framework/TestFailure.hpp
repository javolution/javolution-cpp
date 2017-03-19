/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Throwable.hpp"
#include "junit/framework/Test.hpp"

namespace junit {
namespace framework {

/**
 * A {@code TestFailure} collects a failed test together with the caught exception.
 *
 * @see TestResult
 *
 * @version 7.0
 */
class TestFailure : public Object {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Value: public Object::Value {
    protected:

        Test fFailedTest;
        Throwable fThrownException;

    public:

        /**
         * Constructs a TestFailure with the given test and exception.
         */
        Value(const Test& failedTest, const Throwable& thrownException) {
            fFailedTest = failedTest;
            fThrownException = thrownException;
        }

        /**
         * Gets the failed test.
         */
        Test failedTest() const {
            return fFailedTest;
        }

        /**
         * Gets the thrown exception.
         */
        Throwable thrownException() const {
            return fThrownException;
        }

        /**
         * Returns a short description of the failure.
         */
        String toString() const override {
            return fFailedTest.toString() + ": " + fThrownException.getMessage();
        }

    };

    CLASS(TestFailure)

    // Exported Value methods.

    Test failedTest() const {
        return this_<Value>()->failedTest();
    }

    Throwable thrownException() const {
        return this_<Value>()->thrownException();
    }

};

}
}

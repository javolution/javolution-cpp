/*
 /*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "junit/framework/AssertionFailedError.hpp"
#include "junit/framework/ComparisonCompactor.hpp"

namespace junit {
namespace framework {

/**
 * Thrown when an assert equals for Strings failed.
 * @version 7.0
 */
class ComparisonFailure: public AssertionFailedError {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Value: public AssertionFailedError::Value {
        static const int MAX_CONTEXT_LENGTH = 20;
        String fExpected;
        String fActual;
    public:

        Value(const String& expected, const String& actual) :
                AssertionFailedError::Value() {
            fExpected = expected;
            fActual = actual;
        }

        /**
         * Returns "..." in place of common prefix and "..." in
         * place of common suffix between expected and actual.
         *
         * @see Throwable#getMessage()
         */
        virtual String getMessage() const override {
            ComparisonCompactor cc = new ComparisonCompactor::Value(MAX_CONTEXT_LENGTH, fExpected, fActual);
            return cc.compact(AssertionFailedError::Value::getMessage()); // compact(super.getMessage())
        }

        /**
         * Gets the actual string value
         */
        virtual String getActual() const {
            return fActual;
        }

        /**
         * Gets the expected string value
         */
        virtual String getExpected() const {
            return fExpected;
        }

    };

    CTOR(ComparisonFailure, Value)

    /** Constructs a comparison failure. */
    ComparisonFailure(const String& message, const String& expected, const String& actual) :
            AssertionFailedError(message, new Value(expected, actual)) {
    }

    // Exported Value methods.

    String getActual() const {
        return this_<Value>()->getActual();
    }

    String getExpected() const {
        return this_<Value>()->getExpected();
    }

};

}
}

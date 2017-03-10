/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Object.hpp"

namespace junit {
namespace framework {
class TestResult;

/**
 * A <em>Test</em> can be run and collect its results.
 * @version 7.0
 * @see TestResult
 */
class Test: public virtual Object {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Interface: public virtual Object::Interface {
    public:

        /**
         * Counts the number of test cases that will be run by this test.
         */
        virtual int countTestCases() const = 0;

        /**
         * Runs a test and collects its result in a TestResult instance.
         */
        virtual void run(TestResult& result) = 0;

    };

    CTOR(Test, Interface)

    // Exported Interface methods.

    int countTestCases() const {
        return this_cast_<Interface>()->countTestCases();
    }

    void run(TestResult& result);

};

}
}


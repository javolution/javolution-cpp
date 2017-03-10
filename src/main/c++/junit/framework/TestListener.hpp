/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "junit/framework/Test.hpp"
#include "junit/framework/AssertionFailedError.hpp"

namespace junit {
namespace framework {

/**
 * A Listener for test progress.
 *
 * @version 7.0
 */
class TestListener: public virtual Object {
public:

    class Interface: public virtual Object::Interface {
    public:

        /**
         * An error occurred.
         */
        virtual void addError(const Test& test, const Throwable& e) = 0;

        /**
         * A failure occurred.
         */
        virtual void addFailure(const Test& test, const AssertionFailedError& e) = 0;

        /**
         * A test ended.
         */
        virtual void endTest(const Test& test) = 0;

        /**
         * A test started.
         */
        virtual void startTest(const Test& test) = 0;
    };

    CTOR(TestListener, Interface)

    // Exported Interface methods.

    void addError(const Test& test, const Throwable& e) {
        this_cast_<Interface>()->addError(test, e);
    }

    void addFailure(const Test& test, const AssertionFailedError& e) {
        this_cast_<Interface>()->addFailure(test, e);
    }

    void endTest(const Test& test)  {
        this_cast_<Interface>()->endTest(test);
    }

    void startTest(const Test& test)  {
        this_cast_<Interface>()->startTest(test);
    }

};

}
}


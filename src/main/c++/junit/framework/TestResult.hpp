/*
 /*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Array.hpp"
#include "junit/framework/TestCase.hpp"
#include "junit/framework/TestFailure.hpp"
#include "junit/framework/TestListener.hpp"

namespace junit {
namespace framework {

/**
 * A <code>TestResult</code> collects the results of executing
 * a test case. It is an instance of the Collecting Parameter pattern.
 * The test framework distinguishes between <i>failures</i> and <i>errors</i>.
 * A failure is anticipated and checked for with assertions. Errors are
 * unanticipated problems like an {@link ArrayIndexOutOfBoundsException}.
 *
 * @version 7.0
 */
class TestResult: public virtual Object {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Value: public Object::Value {
        Type::Mutex monitor; // Allows for synchronization on TestResult instances.
    protected:
        Array<TestFailure> fFailures;
        Array<TestFailure> fErrors;
        Array<TestListener> fListeners;
        int fRunTests;
        volatile bool fStop;
    public:

        /** Default constructor.*/
        Value() {
            fFailures = Array<TestFailure>::newInstance(0);
            fErrors = Array<TestFailure>::newInstance(0);
            fListeners = Array<TestListener>::newInstance(0);
            fRunTests = 0;
            fStop = false;
        }

        /**
         * Runs a TestCase.
         */
        virtual void run(TestCase& test);

        /**
         * Adds an error to the list of errors. The passed in exception
         * caused the error.
         */
        virtual void addError(const Test& test, const Throwable& e);

        /**
         * Adds a failure to the list of failures. The passed in exception
         * caused the failure.
         */
        virtual void addFailure(const Test& test, const AssertionFailedError& e);

        /**
         * Registers a TestListener.
         */
        virtual void addListener(const TestListener& listener);

        /**
         * Informs the result that a test was completed.
         */
        virtual void endTest(const Test& test);

        /**
         * Gets the number of detected errors.
         */
        virtual int errorCount() const {
             return fErrors.length;
        }

        /**
         * Gets the number of detected failures.
         */
        virtual int failureCount() const {
            return fFailures.length;
        }

        /**
         * Gets the number of run tests.
         */
        virtual int runCount() const {
            return fRunTests;
        }

        /**
         * Checks whether the test run should stop.
         */
        virtual bool shouldStop() const {
             return fStop;
        }

        /**
         * Informs the result that a test will be started.
         */
        virtual void startTest(const Test& test);

        /**
         * Marks that the test run should stop.
         */
        virtual void stop() {
             fStop = true;
        }

        /**
         * Returns whether the entire test was successful or not.
         */
        virtual bool wasSuccessful() const {
            return failureCount() == 0 && errorCount() == 0;
        }

        /**
         * Prints the test result summary (counters) to System::out.
         * Returns <code>0</code> only if no error or failure.
         */
        virtual int  printSummary() const;

        Type::Mutex& monitor_() const override {
             return const_cast<Type::Mutex&>(monitor);
        }
    };

    CTOR(TestResult, Value)

    // Exported Value methods.

    void run(TestCase& test) {
        this_<Value>()->run(test);
    }

    void addError(const Test& test, const Throwable& e) {
        this_<Value>()->addError(test, e);
    }

    void addFailure(const Test& test, const AssertionFailedError& e) {
        this_<Value>()->addFailure(test, e);
    }

    void addListener(const TestListener& listener) {
        this_<Value>()->addListener(listener);
    }

    void endTest(const Test& test) {
        this_<Value>()->endTest(test);
    }

    int errorCount() const {
        return this_<Value>()->errorCount();
    }

    int failureCount() const {
        return this_<Value>()->failureCount();
    }

    int runCount() const {
        return this_<Value>()->runCount();
    }

    bool shouldStop() const {
        return this_<Value>()->shouldStop();
    }

    void startTest(const Test& test) {
        this_<Value>()->startTest(test);
    }

    void stop() {
        this_<Value>()->stop();
    }

    bool wasSuccessful() const {
        return this_<Value>()->wasSuccessful();
    }

    int printSummary() const {
        return this_<Value>()->printSummary();
    }

};

}
}

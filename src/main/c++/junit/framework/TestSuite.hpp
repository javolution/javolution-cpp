/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Array.hpp"
#include "java/lang/String.hpp"
#include "java/lang/Class.hpp"
#include "junit/framework/Test.hpp"

namespace junit {
namespace framework {
class TestResult;

/**
 * A <code>TestSuite</code> is a <code>Composite</code> of Tests.
 * It runs a collection of test cases. Here is an example using the dynamic test definition.
 * <pre>
 * TestSuite suite = new TestSuite::Value("MathTest");
 * suite.addTest(new MathTest::Value("testAdd", &testAdd));
 * suite.addTest(new MathTest::Value("testDivideByZero", &testDivideByZero));
 * </pre>
 * <p>
 *
 * @version 7.0
 */
class TestSuite: public virtual Test {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Value: public Object::Value, public virtual Test::Interface {
        String fName;
        Array<Test> fTests =  Array<Test>::newInstance(0);
    public:

        /**
          * Constructs an empty test suite.
          */
        Value()  {
        }

        /**
         * Constructs a test suite of specified name.
         */
        Value(const String& name) : fName(name) {
        }

        /**
         * Adds a test to the suite.
         */
        virtual void addTest(const Test& test);

        /**
         * Counts the number of test cases that will be run by this test.
         */
        virtual int countTestCases() const override;

        /**
         * Returns the name of the suite.
         */
        virtual String getName() const {
            return fName;
        }

        /**
         * Sets the name of the suite.
         */
        void setName(const String& name) {
            fName = name;
        }

        /**
         * Runs the tests and collects their result in a TestResult.
         */
        virtual void run(TestResult& result) override;

        /**
         * Returns the test at the given index.
         */
        virtual Test testAt(int index) const {
            return fTests[index];
        }

        /**
         * Returns the number of tests in this suite.
         */
        virtual int testCount() const {
            return fTests.length;
        }

    };

    CTOR(TestSuite, Value)

    // Exported Value methods.

    void addTest(const Test& test) {
        this_<Value>()->addTest(test);
    }

    String getName() const {
        return this_<Value>()->getName();
    }

    void setName(const String& name) const {
        this_<Value>()->setName(name);
    }

    Test testAt(int index) const {
        return this_<Value>()->testAt(index);
    }

    int testCount() const {
        return this_<Value>()->testCount();
    }

};

}
}

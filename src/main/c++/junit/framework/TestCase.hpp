/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Class.hpp"
#include "java/lang/Exception.hpp"
#include "junit/framework/Assert.hpp"
#include "junit/framework/Test.hpp"

/** Macro to define a test class for the specified method. */
#define TEST(TEST_METHOD_) class TEST_METHOD_ : public Value { \
public: \
    void runTest() throw (Throwable) { \
          Value::TEST_METHOD_(); \
    } \
};

namespace junit {
namespace framework {

/**
 * A test case defines the fixture to run multiple tests. To define a test case<br/>
 * <ol>
 *   <li>implement a subclass of <code>TestCase</code></li>
 *   <li>define instance variables that store the state of the fixture</li>
 *   <li>initialize the fixture state by overriding {@link #setUp()}</li>
 *   <li>clean-up after a test by overriding {@link #tearDown()}.</li>
 * </ol>
 * Each test runs in its own fixture so there can be no side effects among test runs.
 * Here is an example:
 * <pre>
 * class MathTest : public TestCase {
 * public:
 *    class Value : public TestCase::Value {
 *    protected:
 *        double fValue1;
 *        double fValue2;
 *
 *        void setUp() {
 *           fValue1= 2.0;
 *           fValue2= 3.0;
 *        }
 *    };
 *    CLASS_BASE(MathTest, TestCase)
 * };
 * </pre>
 *
 * For each test implement a method which interacts with the fixture.
 * Verify the expected results with assertions specified.
 * <pre>
 *    void testAdd() {
 *       double result= fValue1 + fValue2;
 *       assertTrue(result == 5.0);
 *    }
 * </pre>
 *
 * Once the methods are defined you can run each method separately .
 * <pre>
 * TEST(testAdd)
 * MathTest test = new testAdd();
 * test.run();
 * </pre>
 *
 * Or you can collect them in a TestSuite.
 * <pre>
 * static TestSuite suite() {
 *    TestSuite tests = new TestSuite::Value("MathTest");
 *    tests.addTest(new testAdd());
 *    tests.addTest(new testDivideByZero());
 *    return tests;
 * }
 * </pre>
 *
 * @see TestResult
 * @see TestSuite
 * @version 7.0
 */
class TestCase: public Test {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Value: public Object::Value, public Assert, public virtual Test::Interface {
    protected:

        /**
         * Creates a default TestResult object.
         */
        virtual TestResult createResult();

        /**
         * Runs the test and assert its state.
         */
        virtual void runTest() throw (Throwable) = 0;

        /**
         * Sets up the fixture, for example, open a network connection.
         * This method is called before a test is executed.
         */
        virtual void setUp() throw (Exception) {
        }

        /**
         * Tears down the fixture, for example, close a network connection.
         * This method is called after a test is executed.
         */
        virtual void tearDown() throw (Exception) {
        }

    public:

        /**
         * Counts the number of test cases executed by run(TestResult result).
         */
        virtual int countTestCases() const override {
            return 1;
        }

        /**
         * A convenience method to run this test, collecting the results with a default TestResult object.
         */
        virtual TestResult run();

        /**
         * Runs the test case and collects the results in TestResult.
         */
        virtual void run(TestResult& result) override;

        /**
         * Runs the bare test sequence.
         */
        virtual void runBare() throw (Throwable);

        /**
         * Returns a string representation of the test case.
         */
        virtual String toString() const override {
            return getName() + "(" + getClass().getName() + ")";
        }

        /**
         * Gets the name of a TestCase (by default it is the class name).
         */
        virtual String getName() const {
            return getClass().getName();
        }

    };

    CLASS_BASE(TestCase, Test)

    TestResult run();

    void runBare() throw (Throwable) {
        return this_<Value>()->runBare();
    }

    String getName() {
        return this_<Value>()->getName();
    }

};

}
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/System.hpp"
#include "junit/framework/TestResult.hpp"

using namespace junit::framework;

void TestResult::Value::run(TestCase& test) {
    startTest(test);
    try {
        test.runBare();
    } catch (AssertionFailedError& e) {
        addFailure(test, e);
    } catch (Throwable& e) {
        addError(test, e);
    }
    endTest(test);
}

void TestResult::Value::addError(const Test& test, const Throwable& e) {
    synchronized (this) {
        fErrors.setLength(fErrors.length + 1);
        fErrors[fErrors.length - 1] = new TestFailure::Value(test, e);
        for (int i = 0; i < fListeners.length; i++) {
            fListeners[i].addError(test, e);
        }
    }
}

void TestResult::Value::addFailure(const Test& test, const AssertionFailedError& e) {
    synchronized (this) {
        fFailures.setLength(fFailures.length + 1);
        fFailures[fFailures.length - 1] = new TestFailure::Value(test, e);
        for (int i = 0; i < fListeners.length; i++) {
            fListeners[i].addFailure(test, e);
        }
    }
}

void TestResult::Value::addListener(const TestListener& listener) {
    synchronized (this) {
        fListeners.setLength(fListeners.length + 1);
        fListeners[fListeners.length - 1] = listener;
    }
}

void TestResult::Value::endTest(const Test& test) {
    for (int i = 0; i < fListeners.length; i++) {
        fListeners[i].endTest(test);
    }
}

void TestResult::Value::startTest(const Test& test) {
    int count = test.countTestCases();
    synchronized (TestResult(this)) {
        fRunTests += count;
    }
    for (int i = 0; i < fListeners.length; i++) {
        fListeners[i].startTest(test);
    }
}


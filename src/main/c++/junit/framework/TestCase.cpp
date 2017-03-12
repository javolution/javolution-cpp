/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "junit/framework/TestCase.hpp"
#include "junit/framework/TestResult.hpp"
using namespace junit::framework;

TestResult TestCase::Value::createResult() {
    return new TestResult::Value();
}

TestResult TestCase::Value::run() {
    TestResult result = createResult();
    run(result);
    return result;
}

void TestCase::Value::run(TestResult& result) {
    TestCase test = this;
    result.run(test);
}

void TestCase::Value::runBare() throw (Throwable) {
    setUp();
    try {
        runTest();
    } catch (Throwable& running) {
        tearDown();
        throw; // re-throw
    }
    tearDown();
}

TestResult TestCase::run() {
    return this_<Value>()->run();
}


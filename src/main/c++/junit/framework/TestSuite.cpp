/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "junit/framework/TestSuite.hpp"
#include "junit/framework/TestResult.hpp"

using namespace junit::framework;

void TestSuite::Value::addTest(const Test& test) {
    fTests.setLength(fTests.length + 1);
    fTests[fTests.length - 1] = test;
}

int TestSuite::Value::countTestCases() const {
    int count = 0;
    for (int i = 0; i < fTests.length; i++) {
        count += fTests[i].countTestCases();
    }
    return count;
}

void TestSuite::Value::run(TestResult& result) {
    for (int i = 0; i < fTests.length; i++) {
        if (result.shouldStop()) {
            break;
        }
        fTests[i].run(result);
    }
}


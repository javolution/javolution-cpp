/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "junit/framework/Test.hpp"
#include "junit/framework/TestResult.hpp"

using namespace junit::framework;

void Test::run(TestResult& result) {
    return this_cast_<Interface>()->run(result);
}


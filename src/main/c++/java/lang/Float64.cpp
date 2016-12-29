/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Float64.hpp"

using namespace java::lang;
using namespace java::lang;


Float64 Float64_API::createStaticZero() { // Static.
    return Float64(new Float64_API(0.0f));
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include <chrono>
#include "java/lang/System.hpp"

using namespace java::lang;

const Class OutPrintStream::CLASS = Class::forName("java::lang::System::out");
const Class ErrPrintStream::CLASS = Class::forName("java::lang::System::err");

const OutPrintStream System::out = OutPrintStream();
const ErrPrintStream System::err = ErrPrintStream();

Type::int64 System::currentTimeMillis() {
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}



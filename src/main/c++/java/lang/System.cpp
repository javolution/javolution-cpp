/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/System.hpp"

using namespace java::lang;

const Class OutPrintStream::CLASS = Class::forName("java::lang::System::out");
const Class ErrPrintStream::CLASS = Class::forName("java::lang::System::err");

const OutPrintStream System::out = OutPrintStream();
const ErrPrintStream System::err = ErrPrintStream();


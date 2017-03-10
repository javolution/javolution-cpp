/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include <sstream>
#include "java/lang/Throwable.hpp"
#include "java/lang/Class.hpp"
#include "java/lang/System.hpp"
#include "java/lang/StringBuilder.hpp"
#include "java/lang/Thread.hpp"

String Throwable::Value::toString() const {
   String classname = getClass().getName();
   return (message != nullptr) ? classname + ": " + message : classname;
}

void Throwable::printStackTrace() const {
    StringBuilder sb = new StringBuilder::Value();
    sb.append("Exception in thread ").append('"').append(Thread::currentThread().getName()).append("\" ");
    sb.append(toString());
    sb.append('\n');
	std::ostringstream res;
	res.imbue(std::locale::classic());
	res << booster::trace(*this) << std::endl;
	sb.append(res.str());
	System::err.println(sb);
}

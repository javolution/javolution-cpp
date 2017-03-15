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

String Throwable::toString() const {
   String classname = getClass().getName();
   String s = getClass().getName();
   String msg = getLocalizedMessage();
   return (msg != nullptr) ? classname + ": " + msg : classname;
}

String Throwable::getStackTrace() const {
    StringBuilder sb = new StringBuilder::Value();
    std::ostringstream res;
    res.imbue(std::locale::classic());
    res << booster::trace(*this);
    sb.append(res.str());
    return sb.toString();
}

void Throwable::printStackTrace() const {
    StringBuilder sb = new StringBuilder::Value();
    sb.append("Exception in thread ").append('"').append(Thread::currentThread().getName()).append("\" ");
    sb.append(toString());
    sb.append('\n');
    sb.append(getStackTrace());
    System::err.println(sb);
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Throwable.hpp"
#include "java/lang/System.hpp"
#include "java/lang/Class.hpp"
#include <ostream>
#include <sstream>

void Throwable::printStackTrace() const {
    // TODO
    System::err.println(*this);
}

String Throwable::toString() const {
    return (message != nullptr) ? classname + ": " + message : classname;
}

const char* Throwable::what() const throw() { // Standard C++ exception contract.
    return toString().toUTF8().c_str();
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Throwable.hpp"
#include "java/lang/StringBuilder.hpp"
#include "java/lang/Class.hpp"
#include "org/javolution/log/Logging.hpp"
#include <string.h>
#include <stdlib.h>
#include <ostream>
#include <sstream>

using namespace java::lang;
using namespace org::javolution::log;

const char* Throwable::what() const throw() { // Standard C++ exception contract.
                return this->get()->toString()->toUTF8().c_str();
}

Throwable_API::Throwable_API(String const& message) {
    _message = message;
    // Automatically show the stack trace of any exception being raised.
    // Unless the error logging is disabled.
    printStackTrace();
}

void Throwable_API::printStackTrace() const {
    if (!Logging_API::isLogErrorEnabled(L"JAVA")) return;
    std::ostringstream res;
    res.imbue(std::locale::classic());
    res << _message << std::endl;
    res << booster::trace(*this);
    Logging_API::error(L"JAVA", L"STACK TRACE - ", String_API::valueOf(res.str()));
}


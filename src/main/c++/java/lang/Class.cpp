/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#include "java/lang/Class.hpp"


#ifdef JAVOLUTION_MSVC

Class Class::forType(const std::type_info& info) {
    String name = String::valueOf(info.name());
    if (name.startsWith("class ")) {
        name = name.substring(6);
    }
    if (name.endsWith("::Value")) {
        name = name.substring(0, name.length() - 7);
    }
    return Class::forName(name);
}

#else // Demangle

#include <cstdlib>
#include <memory>
#include <cxxabi.h>

Class Class::forType(const std::type_info& info) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
            abi::__cxa_demangle(info.name(), NULL, NULL, &status),
            std::free
        };
    if (status != 0) throw Throwable("abi::__cxa_demangle failed (" + String::valueOf(status) + ")");
    String name = res.get();
    if (name.endsWith("::Value")) {
        name = name.substring(0, name.length() - 7);
    }
    return Class::forName(name);
}
#endif

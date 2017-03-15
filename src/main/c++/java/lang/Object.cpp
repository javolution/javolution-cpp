/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include <typeinfo> // Used for Object::getClass() (C++ Reflection)
#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/StringBuilder.hpp"
#include "java/lang/Class.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "java/lang/NullPointerException.hpp"
#include "java/lang/ArrayIndexOutOfBoundsException.hpp"
#include "java/lang/NegativeArraySizeException.hpp"


///////////////////////
// Object_Interface //
///////////////////////

#ifdef JAVOLUTION_MSVC

Class Object_Interface::getClass() const {
    String name = String::valueOf(typeid(*this).name());
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

Class Object_Interface::getClass() const {
	int status = -1;
	std::unique_ptr<char, void(*)(void*)> res {
	        abi::__cxa_demangle(typeid(*this).name(), NULL, NULL, &status),
	        std::free
	    };
	if (status != 0) throw Throwable(String::valueOf("abi::__cxa_demangle failed (") + status + ")");
    String name = res.get();
    if (name.endsWith("::Value")) {
        name = name.substring(0, name.length() - 7);
    }
    return Class::forName(name);
}
#endif

String Object_Interface::toString() const {
	std::size_t address = reinterpret_cast<std::size_t>(this);
    StringBuilder sb = new StringBuilder::Value();
    return sb.append("Object#").append((long long)address).toString();
}

Type::Mutex& Object_Interface::monitor_() const {
    throw UnsupportedOperationException("Object::monitor_() not implemented");
}

Class Object::getClass() const {
      if (valuePtr == nullptr) throw NullPointerException();
      return valuePtr->getClass();
}

String Object::toString() const {
    if (valuePtr == nullptr) throw NullPointerException();
    return valuePtr->toString();
}

void Object_Exceptions::throwNullPointerException()  {
    throw NullPointerException();
}

void Object_Exceptions::throwArrayIndexOutOfBoundsException()  {
    throw ArrayIndexOutOfBoundsException();
}

void Object_Exceptions::throwNegativeArraySizeException() {
    throw NegativeArraySizeException();
}

std::ostream& operator<<(std::ostream& os, const Object& that) {
    return (that != nullptr) ? os << that.toString().toUTF8() : os << "null";
}


/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/StringBuilder.hpp"
#include "java/lang/Class.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "java/lang/NullPointerException.hpp"
#include "java/lang/ArrayIndexOutOfBoundsException.hpp"
#include "java/lang/NegativeArraySizeException.hpp"
#include <typeinfo> // Used for Object::getClass() (C++ Reflection)


///////////////////////
// Object_Interface //
///////////////////////

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

std::wostream& operator<<(std::wostream& wos, const Object& that) {
    return (that != nullptr) ? wos << that.toString().toWString() : wos << "null";
}


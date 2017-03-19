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

////////////////
// Exceptions //
////////////////

void Object_Exceptions::throwNullPointerException()  {
    throw NullPointerException();
}

void Object_Exceptions::throwArrayIndexOutOfBoundsException()  {
    throw ArrayIndexOutOfBoundsException();
}

void Object_Exceptions::throwNegativeArraySizeException() {
    throw NegativeArraySizeException();
}

////////////
// Values //
////////////

Class Object_Value::getClass() const {
	return Class::forType(typeid(*this));
}

String Object_Value::toString() const {
	std::size_t address = reinterpret_cast<std::size_t>(this);
    StringBuilder sb = new StringBuilder::Value();
    return sb.append("Object#").append((long long)address).toString();
}

Type::Mutex& Object_Value::monitor_() const {
    throw UnsupportedOperationException("monitor_() methods should be overridden");
}

////////////
// Object //
////////////

Class Object::getClass() const {
      if (valuePtr == nullptr) throw NullPointerException();
      return valuePtr->getClass();
}

String Object::toString() const {
    if (valuePtr == nullptr) throw NullPointerException();
    return valuePtr->toString();
}

std::ostream& operator<<(std::ostream& os, const Object& that) {
    return (that != nullptr) ? os << that.toString().toUTF8() : os << "null";
}


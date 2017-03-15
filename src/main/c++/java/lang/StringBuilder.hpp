/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <sstream>
#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/Boolean.hpp"
#include "java/lang/Character.hpp"
#include "java/lang/IllegalArgumentException.hpp"
#include "java/lang/IndexOutOfBoundsException.hpp"
#include "java/lang/Integer.hpp"
#include "java/lang/Long.hpp"
#include "java/lang/Float.hpp"
#include "java/lang/Double.hpp"

namespace java {
namespace lang {

/**
 * This class represents a mutable sequence of characters.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/StringBuilder.html">
 *       Java - StringBuilder</a>
 * @version 7.0
 */
class StringBuilder final : public virtual CharSequence {
public:
	class Value final : public Object::Value, public virtual CharSequence::Interface {
		static const int CHARS_INC = 32; // Smooth length increment.
		Array<Type::uchar> uchars = Array<Type::uchar>::newInstance();
		int count = 0;
		bool immutable = false; // Becomes immutable after toString() is called since the array will be shared.
	public:

		StringBuilder append(Type::uchar uc);

		StringBuilder append(const String& str);

		StringBuilder append(const char* chars);

		StringBuilder append(const Type::uchar* chars);

        StringBuilder append(const Type::u8string& str);

		Type::uchar charAt(int index) const override {
			if (index >= count)
				throw IndexOutOfBoundsException();
			return uchars[index];
		}

		int length() const override {
			return count;
		}

		CharSequence subSequence(int start, int end) const override {
			return toString().substring(start, end);
		}

		String toString() const override {
			Value* self = const_cast<Value*>(this); // Removes constness.
			self->uchars.length = count; // Ok, small reduction adjustment (no need to call setLength).
			self->immutable = true;
			return new String::Value(self->uchars); // Share the same array.
		}

	};

	CTOR(StringBuilder, Value)

	/**
	 * Appends the textual representation of the specified object.
	 */
	StringBuilder append(const Object& obj) {
		return append(String::valueOf(obj));
	}

	/**
	 * Appends the specified string.
	 */
	StringBuilder append(const String& str) {
		return this_<Value>()->append(str);
	}

	/**
	 * Appends the specified int value.
	 */
	StringBuilder append(int value) {
		std::ostringstream out;
		out << value;
		return append(out.str());
	}

	/**
	 * Appends the specified long value.
	 */
	StringBuilder append(long value) {
		std::ostringstream out;
		out << value;
		return append(out.str());
	}

	/**
	 * Appends the specified long long value (at least 64 bits).
	 */
	StringBuilder append(long long value) {
		std::ostringstream out;
		out << value;
		return append(out.str());
	}

	/**
	 * Appends the specified 32 bits float value.
	 */
	StringBuilder append(float value) {
		std::ostringstream out;
		out << value;
		return append(out.str());
	}

	/**
	 * Appends the specified 64 bits float value.
	 */
	StringBuilder append(double value) {
		std::ostringstream out;
		out << value;
		return append(out.str());
	}

	/**
	 * Appends the specified C++ ASCII characters (null terminated).
	 *
	 * @throws IllegalArgumentException if any character is not ASCII.
	 */
	StringBuilder append(const char* chars) {
		return this_<Value>()->append(chars);
	}

    /**
     * Appends the specified UTF-8 characters (string).
     */
    StringBuilder append(const Type::u8string& str) {
        return this_<Value>()->append(str);
    }

	/**
	 * Appends the specified Unicode (UTF-16) characters (null terminated).
	 */
	StringBuilder append(const Type::uchar* chars) {
		return this_<Value>()->append(chars);
	}

	/**
	 * Appends the specified ASCII character.
	 *
	 * @throw IllegalArgumentException if the specified value is not ASCII.
	 */
	StringBuilder append(char ascii) {
		if (ascii > 127)
			throw IllegalArgumentException("Non-ASCII Character");
		return append((Type::uchar) ascii);
	}

	/**
	 * Appends the specified Unicode character (UTF-16), e.g. <code>sb.append(u'€');</code>
	 */
	StringBuilder append(Type::uchar uc) {
		return this_<Value>()->append(uc);
	}

	/**
	 * Appends the specified bool object.
	 */
	StringBuilder append(bool value) {
		return append(value ? "true" : "false");
	}

	//////////////////
	// CharSequence //
	//////////////////

	Type::uchar charAt(int index) const {
		return this_<Value>()->charAt(index);
	}

	int length() const {
		return this_<Value>()->length();
	}

	CharSequence subSequence(int start, int end) const {
		return this_<Value>()->subSequence(start, end);
	}

};
}
}

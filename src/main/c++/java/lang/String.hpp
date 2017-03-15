/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <string>
#include "java/lang/CharSequence.hpp"
#include "java/lang/Array.hpp"

namespace java {
namespace lang {
class String;
class StringBuilder;

/**
 * A string of 16-bits Unicode characters (<code>Type::uchar</code>).
 *
 * This class supports autoboxing with <code>char*</code> (ASCII) and <code>Type::uchar*</code>,
 * e.g. <code>String str = u"Éléphant";</code>
 *
 * Concatenation using the operator '+' is supported as long as the first instance is a String.
 * <pre><code>
 * if (invalidRange(srcPos, dstPos, length))
 *    throw IndexOutOfBoundsException(String::valueOf("srcPos: ") +
 *        srcPos + ", dstPos: " + dstPos + ", length: " + length);
 * </code></pre>
 *
 * @version 7.0
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/String.html">Java - String</a>
 */
class String final : public virtual CharSequence {
public:

	class Value final : public Object::Value, public virtual CharSequence::Interface {
		friend class StringBuilder;
		Array<Type::uchar> uchars;
		Value(const Array<Type::uchar>& uchars) :
				uchars(uchars) {
		}
	public:

		String substring(int beginIndex, int endIndex) const;

		String concat(const String& that) const;

		bool startsWith(const String& prefix, int offset) const;

		bool endsWith(const String& suffix) const;

		bool equals(const Object& obj) const override;

		bool equals(const String& that) const;

		int hashCode() const override;

		Type::u8string toUTF8() const;

		Type::uchar charAt(int index) const override {
			return uchars[index];
		}

		int length() const override {
			return uchars.length;
		}

		CharSequence subSequence(int start, int end) const override {
			return substring(start, end);
		}

		String toString() const override {
			return const_cast<Value*>(this);
		}
	};

	CTOR(String, Value)

	/**
	 * Returns the string representing the specified object ("null" if (obj == nullptr)).
	 */
	static String valueOf(const Object& obj) {
		return obj == nullptr ? "null" : obj.toString();
	}

	/**
	 * Equivalent to <code>obj.toString()</code>
	 */
	static String valueOf(const Object::Interface& obj) {
		return obj.toString();
	}

    /**
     * Returns the string holding the specified ASCII characters (null terminated).
     *
     * @throws IllegalArgumentException if any character is not an ASCII character.
     */
    static String valueOf(const char* chars);

	/**
	 * Returns the string holding the specified UTF-16 characters (null terminated).
	 */
	static String valueOf(const Type::uchar* chars);

	/**
	 * Returns the string holding the specified UTF-8 characters.
	 */
	static String valueOf(const Type::u8string& str);

    /**
     * Returns the string holding the specified ASCII character.
     *
     * @throws IllegalArgumentException if the specified character is not an ASCII character.
     */
    static String valueOf(char value);

	/**
	 * Returns the string holding the specified UTF-16 Unicode character.
	 */
	static String valueOf(Type::uchar value);

	/**
	 * Returns the string holding the decimal representation of the specified int value.
	 */
	static String valueOf(int value);

	/**
	 * Returns the string holding the decimal representation of the specified long value.
	 */
	static String valueOf(long value);

	/**
	 * Returns the string holding the decimal representation of the specified long long value (at least 64 bits).
	 */
	static String valueOf(long long value);

	/**
	 * Returns the string holding the decimal representation of the specified 32 bits floating point value.
	 */
	static String valueOf(float value);

	/**
	 * Returns the string holding the decimal representation of the specified 64 bits floating point value.
	 */
	static String valueOf(double value);

	/**
	 * Returns the string holding the representation of the specified boolean value.
	 */
	static String valueOf(bool value);

	/**
	 * Returns a new string that is a substring of this string.
	 */
	String substring(int beginIndex) const {
		return substring(beginIndex, length());
	}

	/**
	 * Returns a new string that is a substring of this string.
	 */
	String substring(int beginIndex, int endIndex) const {
		return this_<Value>()->substring(beginIndex, endIndex);
	}

	/**
	 * Returns the result of the concatenation of this string with the one specified.
	 */
	String concat(const String& that) const {
		return this_<Value>()->concat(that);
	}

	/**
	 * Tests if this string starts with the specified prefix.
	 */
	bool startsWith(const String& prefix) const {
		return startsWith(prefix, 0);
	}
	/**
	 * Tests if the substring of this string beginning at the specified offset starts with the specified prefix.
	 */
	bool startsWith(const String& prefix, int offset) const {
		return this_<Value>()->startsWith(prefix, offset);
	}

	/**
	 * Tests if this string ends with the specified suffix.
	 */
	bool endsWith(const String& suffix) const {
		return this_<Value>()->endsWith(suffix);
	}

	/**
	 * Indicates whether the specified object is a string holding the same characters as this string.
	 */
	bool equals(const Object& other) const {
		return this_<Value>()->equals(other);
	}

	/**
	 * Indicates whether the specified string is holding the same characters as this string.
	 */
	bool equals(const String& that) const {
		return this_<Value>()->equals(that);
	}

	/**
	 * Returns a UTF-8 string corresponding to this string object (can be used for serialization purpose).
	 */
	Type::u8string toUTF8() const {
		return this_<Value>()->toUTF8();
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

	/////////////////////////////////////////
	// Autoboxing and literal assignments. //
	/////////////////////////////////////////

	Object& operator=(Void) { // Since new assignments are defined, they all need to be explicit (no inheritance).
		return Object::operator=(nullptr);
	}

	String& operator=(const char* chars) {
		return *this = String::valueOf(chars);
	}

	String(const char* chars) {
		*this = String::valueOf(chars);
	}

	String& operator=(const Type::uchar* chars) {
		return *this = String::valueOf(chars);
	}

	String(const Type::uchar* chars) {
		*this = String::valueOf(chars);
	}

	template<typename E>
	String operator+(const E& e) const {
		return concat(String::valueOf(e));
	}

};

}
}


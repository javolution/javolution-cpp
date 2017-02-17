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
 * A string of wide characters (wchar).
 *
 * This class supports autoboxing with <code>char*</code> and <code>wchar_t*</code>,
 * e.g. <code>String str = L"Éléphant";</code>
 *
 * Concatenations with string literals (including wide strings) is supported (the first element should be a String).
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
    String(Void = nullptr) {}
    String(Value* value) : Object(value) {}

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
     * Returns the string holding the specified wide characters
     * (null terminated).
     */
    JAVOLUTION_DLL
    static String valueOf(const Type::wchar* wchars);

    /**
     * Returns the string holding the specified C++ wide string.
     */
    JAVOLUTION_DLL
    static String valueOf(const std::wstring& wstr);

    /**
     * Returns the string holding the specified UTF-8 simple characters
     * (null terminated).
     */
    JAVOLUTION_DLL
    static String valueOf(const char* chars);

    /**
     * Returns the string holding the specified UTF-8 C++ string.
     */
    JAVOLUTION_DLL
    static String valueOf(const std::string& str);

    /**
     * Returns the string holding the specified wide character.
     */
    JAVOLUTION_DLL
    static String valueOf(Type::wchar value);

    /**
     * Returns the string holding the specified ascii character.
     */
    JAVOLUTION_DLL
    static String valueOf(char value);

    /**
     * Returns the string holding the decimal representation of the specified int value.
     */
    JAVOLUTION_DLL
    static String valueOf(int value);

    /**
     * Returns the string holding the decimal representation of the specified long value.
     */
    JAVOLUTION_DLL
    static String valueOf(long value);

    /**
     * Returns the string holding the decimal representation of the specified long long value (at least 64 bits).
     */
    JAVOLUTION_DLL
    static String valueOf(long long value);

    /**
     * Returns the string holding the decimal representation of the specified 32 bits floating point value.
     */
    JAVOLUTION_DLL
    static String valueOf(float value);

    /**
     * Returns the string holding the decimal representation of the specified 64 bits floating point value.
     */
    JAVOLUTION_DLL
    static String valueOf(double value);

    /**
     * Returns the string holding the representation of the specified boolean value.
     */
    JAVOLUTION_DLL
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
        if (this == other) return true;
        String that = other.cast_<Value>();
        return equals(that);
    }

    /**
     * Indicates whether the specified string is holding the same characters as this string.
     */
    bool equals(const String& that) const {
        return this_<Value>()->equals(that);
    }

    /**
     * Returns the C++ wide string corresponding to this string object.
     */
    std::wstring toWString() const {
        return this_<Value>()->toWString();
    }

    /**
     * Returns the C++ char string (UTF-8 encoded) corresponding to this string object
     * (can be used for serialization purpose).
     */
    std::string toUTF8() const {
        return this_<Value>()->toUTF8();
    }

    //////////////////
    // CharSequence //
    //////////////////

    Type::wchar charAt(int index) const {
        return this_<Value>()->charAt(index);
    }

    int length() const  {
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

    String(std::string const& str) {
        *this = String::valueOf(str);
    }

    String& operator=(const Type::wchar* wchars) {
        return *this = String::valueOf(wchars);
    }

    String(const Type::wchar* wchars) {
        *this = String::valueOf(wchars);
    }

    String(std::wstring const& wstr) {
        *this = String::valueOf(wstr);
    }

    template<typename E>
    String operator+(const E& e) const {
        return concat(String::valueOf(e));
    }

    ////////////////////
    // Implementation //
    ////////////////////

    class Value final : public Object::Value, public virtual CharSequence::Interface {
        friend class StringBuilder;

        Array<Type::wchar> wchars;
        Value(const Array<Type::wchar>& wchars) :
                wchars(wchars) {
        }

    public:

        JAVOLUTION_DLL
        String substring(int beginIndex, int endIndex) const;

        JAVOLUTION_DLL
        String concat(const String& that) const;

        JAVOLUTION_DLL
        bool startsWith(const String& prefix, int offset) const;

        JAVOLUTION_DLL
        bool endsWith(const String& suffix) const;

        JAVOLUTION_DLL
        bool equals(const Object& obj) const override;

        JAVOLUTION_DLL
        bool equals(const String& that) const;

        JAVOLUTION_DLL
        int hashCode() const override;

        JAVOLUTION_DLL
        std::wstring toWString() const;

        JAVOLUTION_DLL
        std::string toUTF8() const;

        Type::wchar charAt(int index) const override {
            return wchars[index];
        }

        int length() const override {
            return wchars.length;
        }

        CharSequence subSequence(int start, int end) const override {
            return substring(start, end);
        }

        String toString() const override {
            return String(new Value(wchars));
        }
    };

};

}
}


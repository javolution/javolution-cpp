/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/String.hpp"
#include "java/lang/StringBuilder.hpp"
#include "java/lang/IndexOutOfBoundsException.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "java/lang/System.hpp"

String String::valueOf(const Type::wchar* value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(const std::wstring& value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(const char* value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(const std::string& value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(Type::wchar value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(char value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(int value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(long value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(long long value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(float value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(double value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::valueOf(bool value) {
    StringBuilder sb = StringBuilder::newInstance();
    return sb.append(value).toString();
}

String String::Value::substring(int beginIndex, int endIndex) const {
    if ((beginIndex < 0) || (endIndex > length()) || (beginIndex > endIndex))
        throw IndexOutOfBoundsException();
    int length = endIndex - beginIndex;
    Array<Type::wchar> tmp = Array<Type::wchar>::newInstance(length);
    System::arraycopy(wchars, beginIndex, tmp, 0, length);
    return String(new Value(tmp));
}

String String::Value::concat(const String& that) const {
    Array<Type::wchar> tmp = wchars.clone();
    tmp.setLength(length() + that.length());
    System::arraycopy(that.this_<Value>()->wchars, 0, tmp, length(), that.length());
    return String(new Value(tmp));
}

bool String::Value::startsWith(const String& prefix, int offset) const {
    int prefixLength = prefix.length();
    if (prefixLength + offset > length())
        return false;
    for (int i = 0; i < prefixLength; i++) {
        if (charAt(i + offset) != prefix.charAt(i))
            return false;
    }
    return true;
}

bool String::Value::endsWith(const String& suffix) const {
    int suffixLength = suffix.length();
    int offset = length() - suffixLength;
    if (offset < 0)
        return false;
    for (int i = 0; i < suffixLength; i++) {
        if (charAt(i + offset) != suffix.charAt(i))
            return false;
    }
    return true;
}

bool String::Value::equals(const Object& other) const {
    if (this == other) return true;
    String that = other.cast_<String::Value>();
    return equals(that);
}

bool String::Value::equals(const String& that) const {
    if (that == nullptr)
        return false;
    if (length() != that.length())
        return false;
    for (int i = 0, n = length(); i < n; ++i) {
        if (charAt(i) != that.charAt(i))
            return false;
    }
    return true;
}

int String::Value::hashCode() const {
    int h = 0;
    for (int i = 0, n = length(); i < n; ++i) {
        h = 31 * h + charAt(i);
    }
    return h;
}

std::wstring String::Value::toWString() const {
    static const int BUFFER_LENGTH = 1024;
    int len = length();
    if (len > BUFFER_LENGTH) { // Possible buffer overflow, split the work.
        int half = len / 2;
        return substring(0, half).toWString() + substring(half, len).toWString();
    }
    Type::wchar buffer[BUFFER_LENGTH];
    for (int i = 0; i < len; ++i)
        buffer[i] = charAt(i);
    return std::wstring(buffer, len);
}

std::string String::Value::toUTF8() const {
    static const int BUFFER_LENGTH = 1024;
    int len = length();
    if (len * 4 > BUFFER_LENGTH) { // Possible buffer overflow, split the work.
        int half = len / 2;
        return substring(0, half).toUTF8() + substring(half, len).toUTF8();
    }
    char buffer[BUFFER_LENGTH];
    for (int i = 0, j = 0;;) {
        if (i >= len)
            return std::string(buffer, j); // Done.
        Type::wchar w = charAt(i++);
        if (w <= 0x7f) {
            buffer[j++] = (char) w;
        } else if (w <= 0x7ff) {
            buffer[j++] = (char) (0xc0 | ((w >> 6) & 0x1f));
            buffer[j++] = (char) (0x80 | (w & 0x3f));
        } else if (w <= 0xffff) {
            buffer[j++] = (char) (0xe0 | ((w >> 12) & 0x0f));
            buffer[j++] = (char) (0x80 | ((w >> 6) & 0x3f));
            buffer[j++] = (char) (0x80 | (w & 0x3f));
#ifndef _WINDOWS
        } else if (w <= 0x10ffff) { // On windows wchar_t is 16 bits!
            buffer[j++] = (char) (0xf0 | ((w >> 18) & 0x07));
            buffer[j++] = (char) (0x80 | ((w >> 12) & 0x3f));
            buffer[j++] = (char) (0x80 | ((w >> 6) & 0x3f));
            buffer[j++] = (char) (0x80 | (w & 0x3f));
#endif
        } else {
            throw UnsupportedOperationException("Unsupported Wide Character");
        }
    }
}


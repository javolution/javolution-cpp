/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include <locale>
#include <codecvt>
#include "java/lang/String.hpp"
#include "java/lang/StringBuilder.hpp"
#include "java/lang/IndexOutOfBoundsException.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "java/lang/System.hpp"

String String::valueOf(const char* value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(const Type::uchar* value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(const Type::u8string& value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(char value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(Type::uchar value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(int value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(long value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(long long value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(float value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(double value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::valueOf(bool value) {
    StringBuilder sb = new StringBuilder::Value();
    return sb.append(value).toString();
}

String String::Value::substring(int beginIndex, int endIndex) const {
    if ((beginIndex < 0) || (endIndex > length()) || (beginIndex > endIndex))
        throw IndexOutOfBoundsException();
    int length = endIndex - beginIndex;
    Array<Type::uchar> tmp = Array<Type::uchar>::newInstance(length);
    System::arraycopy(uchars, beginIndex, tmp, 0, length);
    return String(new Value(tmp));
}

String String::Value::concat(const String& that) const {
    Array<Type::uchar> tmp = uchars.clone();
    tmp.setLength(length() + that.length());
    System::arraycopy(that.this_<Value>()->uchars, 0, tmp, length(), that.length());
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

Type::u8string String::Value::toUTF8() const {
    static const int BUFFER_LENGTH = 1024;
    int len = length();
    if (len > BUFFER_LENGTH) { // Possible buffer overflow, split the work.
        int half = len / 2;
        return substring(0, half).toUTF8() + substring(half, len).toUTF8();
    }
    Type::uchar buffer[BUFFER_LENGTH];
    for (int i = 0; i < len; ++i) buffer[i] = charAt(i); // TODO : Replace with Array::forEach
    std::u16string u16(buffer, len);
#ifdef JAVOLUTION_MSVC
    // https://connect.microsoft.com/VisualStudio/feedback/details/1403302/unresolved-external-when-using-codecvt-utf8
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
    auto p = reinterpret_cast<const int16_t *>(u16.data());
    return convert.to_bytes(p, p + u16.size());
#else
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
#endif
}

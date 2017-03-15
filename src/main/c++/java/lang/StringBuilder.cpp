/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include <locale>
#include <codecvt>
#include "java/lang/StringBuilder.hpp"
#include "java/lang/System.hpp"

StringBuilder StringBuilder::Value::append(Type::uchar uc) {
    if (immutable) {
        uchars = uchars.clone();
        immutable = false;
    }
    if (count >= uchars.length)
        uchars.setLength(uchars.length + CHARS_INC);
    uchars[count++] = uc;
    return this;
}

StringBuilder StringBuilder::Value::append(const String& str) {
    if (str == nullptr)
        return append("null");
    if (immutable) {
        uchars = uchars.clone();
        immutable = false;
    }
    int strLength = str.length();
    if (count + strLength > uchars.length)
        uchars.setLength(uchars.length + strLength + CHARS_INC);
    System::arraycopy(str.this_<String::Value>()->uchars, 0, uchars, count, strLength);
    count += strLength;
    return this;
}

StringBuilder StringBuilder::Value::append(const Type::uchar* chars) {
    if (immutable) {
        uchars = uchars.clone();
        immutable = false;
    }
    for (int i = 0;;) {
        Type::uchar uc = chars[i++];
        if (uc == 0)
            break;
        if (count >= uchars.length)
            uchars.setLength(uchars.length + CHARS_INC);
        uchars[count++] = uc;
    }
    return this;
}

StringBuilder StringBuilder::Value::append(const char* chars) {
    if (immutable) {
        uchars = uchars.clone();
        immutable = false;
    }
    for (int i = 0;;) {
        unsigned char c = (unsigned char) chars[i++];
        if (c > 0x7f)
            throw IllegalArgumentException("Illegal non-ASCII character");
        if (c == 0)
            break;
        if (count >= uchars.length)
            uchars.setLength(uchars.length + CHARS_INC);
        uchars[count++] = (Type::uchar) c;
    }
    return this;
}

StringBuilder StringBuilder::Value::append(const Type::u8string& str) {
#ifdef JAVOLUTION_MSVC
    // https://connect.microsoft.com/VisualStudio/feedback/details/1403302/unresolved-external-when-using-codecvt-utf8
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
    std::basic_string<int16_t> u16 = convert.from_bytes(str);
    auto p = reinterpret_cast<const Type::uchar *>(u16.c_str());
    return append(p);
#else
    std::u16string u16_conv = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> { }.from_bytes(str);
    return append(u16_conv.c_str());
#endif
}


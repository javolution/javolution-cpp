/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/StringBuilder.hpp"
#include "java/lang/System.hpp"

StringBuilder StringBuilder::Value::append(Type::wchar wc) {
    if (immutable) {
        wchars = wchars.clone();
        immutable = false;
    }
    if (count >= wchars.length)
        wchars.setLength(wchars.length + WCHARS_INC);
    wchars[count++] = wc;
    return this;
}

StringBuilder StringBuilder::Value::append(const String& str) {
    if (str == nullptr) return append("null");
    if (immutable) {
        wchars = wchars.clone();
        immutable = false;
    }
    int strLength = str.length();
    if (count + strLength > wchars.length) wchars.setLength(wchars.length + strLength + WCHARS_INC);
    System::arraycopy(str.this_<String::Value>()->wchars, 0, wchars, count, strLength);
    count += strLength;
    return this;
}

StringBuilder StringBuilder::Value::append(const Type::wchar* chars) {
    if (immutable) {
        wchars = wchars.clone();
        immutable = false;
    }
    for (int i=0;;) {
        Type::wchar c = chars[i++];
        if (c == 0) break;
        if (count >= wchars.length) wchars.setLength(wchars.length + WCHARS_INC);
        wchars[count++] = c;
    }
    return this;
}

StringBuilder StringBuilder::Value::append(const char* chars) {
    if (immutable) {
        wchars = wchars.clone();
        immutable = false;
    }
    Type::wchar w = 0;
    int bytes = 0;
    for (int i=0;;) {
        unsigned char c = (unsigned char) chars[i++];
        if (c == 0) break;
        if (count >= wchars.length) wchars.setLength(wchars.length + WCHARS_INC);
        if (c <= 0x7f) { // One byte.
            if (bytes != 0) throw IllegalArgumentException("Invalid UTF-8 sequence");
            wchars[count++] = (Type::wchar) c;
        } else if (c <= 0xbf) { // Multi-bytes content.
            if (bytes == 0) throw IllegalArgumentException("Invalid UTF-8 sequence");
            w = ((w << 6) | (c & 0x3f));
            bytes--;
            if (bytes == 0) wchars[count++] =  w;
        } else if (c <= 0xdf) { // Two bytes sequence start.
            bytes = 1;
            w = c & 0x1f;
        } else if (c <= 0xef) { // Three bytes sequence start.
            bytes = 2;
            w = c & 0x0f;
        } else if (c <= 0xf7) { // Four bytes sequence start.
            bytes = 3;
            w = c & 0x07;
        } else {
            throw IllegalArgumentException("Invalid UTF-8 sequence");
        }
    }
    if (bytes !=0) throw IllegalArgumentException("Early termination of UTF-8 character sequence");
    return this;
}


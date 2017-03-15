/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"

namespace junit {
namespace framework {

/**
 * Reduces error message size when comparing strings.
 * @version 7.0
 */
class ComparisonCompactor: public virtual Object {
public:

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

    class Value: public Object::Value {

        int fContextLength;
        String fExpected;
        String fActual;
        int fPrefix;
        int fSuffix;

    public:

        Value(int contextLength, const String& expected, const String& actual)
        : fContextLength(contextLength), fExpected(expected), fActual(actual) {
        }

        virtual String compact(const String& message);

        virtual String compactString(const String& source);

        virtual void findCommonPrefix();

        virtual void findCommonSuffix();

        virtual String computeCommonPrefix();

        virtual String computeCommonSuffix();

        virtual bool areStringsEqual();

    };

    CTOR (ComparisonCompactor, Value)

    // Exported Value methods.

    String compact(const String& message) {
        return this_<Value>()->compact(message);
    }

};

}
}

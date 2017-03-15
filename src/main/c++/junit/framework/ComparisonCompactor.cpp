/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "junit/framework/ComparisonCompactor.hpp"
#include "junit/framework/Assert.hpp"

using namespace junit::framework;

String ComparisonCompactor::Value::compact(const String& message) {
    if (fExpected == nullptr || fActual == nullptr || areStringsEqual()) {
        return Assert::format(message, fExpected, fActual);
    }
    findCommonPrefix();
    findCommonSuffix();
    String expected = compactString(fExpected);
    String actual = compactString(fActual);
    return Assert::format(message, expected, actual);
}

String ComparisonCompactor::Value::compactString(const String& source) {
    static const String DELTA_END = "]";
    static const String DELTA_START = "[";
    String result = DELTA_START + source.substring(fPrefix, source.length() - fSuffix + 1) + DELTA_END;
    if (fPrefix > 0) {
        result = computeCommonPrefix() + result;
    }
    if (fSuffix > 0) {
        result = result + computeCommonSuffix();
    }
    return result;
}

void ComparisonCompactor::Value::findCommonPrefix() {
    fPrefix = 0;
    int end = Math::min(fExpected.length(), fActual.length());
    for (; fPrefix < end; fPrefix++) {
        if (fExpected.charAt(fPrefix) != fActual.charAt(fPrefix)) {
            break;
        }
    }
}

void ComparisonCompactor::Value::findCommonSuffix() {
    int expectedSuffix = fExpected.length() - 1;
    int actualSuffix = fActual.length() - 1;
    for (; actualSuffix >= fPrefix && expectedSuffix >= fPrefix; actualSuffix--, expectedSuffix--) {
        if (fExpected.charAt(expectedSuffix) != fActual.charAt(actualSuffix)) {
            break;
        }
    }
    fSuffix = fExpected.length() - expectedSuffix;
}

String ComparisonCompactor::Value::computeCommonPrefix() {
    static const String ELLIPSIS = "...";
    return (fPrefix > fContextLength ? ELLIPSIS : "")
            + fExpected.substring(Math::max(0, fPrefix - fContextLength), fPrefix);
}

String ComparisonCompactor::Value::computeCommonSuffix() {
    static const String ELLIPSIS = "...";
    int end = Math::min(fExpected.length() - fSuffix + 1 + fContextLength, fExpected.length());
    return fExpected.substring(fExpected.length() - fSuffix + 1, end)
            + (fExpected.length() - fSuffix + 1 < fExpected.length() - fContextLength ? ELLIPSIS : "");
}

bool ComparisonCompactor::Value::areStringsEqual() {
    return fExpected.equals(fActual);
}

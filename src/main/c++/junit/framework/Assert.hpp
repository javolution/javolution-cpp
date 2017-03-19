/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"
#include "java/lang/Boolean.hpp"
#include "java/lang/Character.hpp"
#include "java/lang/Double.hpp"
#include "java/lang/Float.hpp"
#include "java/lang/Long.hpp"
#include "java/lang/Integer.hpp"
#include "java/lang/Math.hpp"

#include "junit/framework/ComparisonFailure.hpp"

namespace junit {
namespace framework {

/**
 * This class represents a set of assert methods. Messages are only displayed when an assert fails.
 * @version 7.0
 */
class Assert {

    ////////////////////////////////////////////////////////////////////////
    // Translated to C++ from public domain java source files (junit 3.x) //
    ////////////////////////////////////////////////////////////////////////

protected:

    /**
     * Protect constructor since it is a static only class
     */
    Assert() {
    }

public:

    /**
     * Asserts that a condition is true. If it isn't it throws an AssertionFailedError with the given message.
     */
    static void assertTrue(const String& message, bool condition) {
        if (!condition) fail(message);
    }

    /**
     * Asserts that a condition is true. If it isn't it throws an AssertionFailedError.
     */
    static void assertTrue(bool condition) {
        assertTrue(nullptr, condition);
    }

    /**
     * Asserts that a condition is false. If it isn't it throws an AssertionFailedError with the given message.
     */
    static void assertFalse(const String& message, bool condition) {
        assertTrue(message, !condition);
    }

    /**
     * Asserts that a condition is false. If it isn't it throws an AssertionFailedError.
     */
    static void assertFalse(bool condition) {
        assertFalse(nullptr, condition);
    }

    /**
     * Fails a test with the given message.
     */
    static void fail(const String& message) {
        if (message == nullptr)
            throw AssertionFailedError();
        throw AssertionFailedError(message);
    }

    /**
     * Fails a test with no message.
     */
    static void fail() {
        fail(nullptr);
    }

    /**
     * Asserts that two objects are equal. If they are not an AssertionFailedError is thrown with the given message.
     */
    static void assertEquals(const String& message, const Object& expected, const Object& actual) {
        if (expected == nullptr && actual == nullptr) return;
        if (expected != nullptr && expected.equals(actual)) return;
        failNotEquals(message, expected, actual);
    }

    /**
     * Asserts that two objects are equal. If they are not an AssertionFailedError is thrown.
     */
    static void assertEquals(const Object& expected, const Object& actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that two Strings are equal.
     */
    static void assertEquals(const String& message, const String& expected, const String& actual) {
        if (expected == nullptr && actual == nullptr) return;
        if (expected != nullptr && expected.equals(actual)) return;
        String cleanMessage = (message == nullptr) ? "" : message;
        throw ComparisonFailure(cleanMessage, expected, actual);
    }

    /**
     * Asserts that two Strings are equal.
     */
    static void assertEquals(const String& expected, const String& actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that two doubles are equal concerning a delta. If they are not an AssertionFailedError is
     * thrown with the given message.  If the expected value is infinity then the delta value is ignored.
     */
    static void assertEquals(const String& message, double expected, double actual, double delta) {
        if (Double::compare(expected, actual) == 0) return;
        if (!(Math::abs(expected - actual) <= delta)) {
            failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
        }
    }

    /**
     * Asserts that two doubles are equal concerning a delta. If the expected value is infinity then the delta
     * value is ignored.
     */
    static void assertEquals(double expected, double actual, double delta) {
        assertEquals(nullptr, expected, actual, delta);
    }

    /**
     * Asserts that two floats are equal concerning a positive delta. If they are not an AssertionFailedError
     * is thrown with the given message. If the expected value is infinity then the delta value is ignored.
     */
    static void assertEquals(const String& message, float expected, float actual, float delta) {
        if (Float::compare(expected, actual) == 0) return;
        if (!(Math::abs(expected - actual) <= delta)) {
            failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
        }
    }

    /**
     * Asserts that two floats are equal concerning a delta. If the expected
     * value is infinity then the delta value is ignored.
     */
    static void assertEquals(float expected, float actual, float delta) {
        assertEquals(nullptr, expected, actual, delta);
    }

    /**
     * Asserts that two longs are equal. If they are not an AssertionFailedError is thrown with the given message.
     */
    static void assertEquals(const String& message, long expected, long actual) {
        if (Long::valueOf(expected).equals(actual)) return;
        failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
    }

    /**
     * Asserts that two longs are equal.
     */
    static void assertEquals(long expected, long actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that two bools are equal. If they are not an AssertionFailedError is thrown with the given message.
     */
    static void assertEquals(const String& message, bool expected, bool actual) {
        if (Boolean::valueOf(expected).equals(actual)) return;
        failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
    }

    /**
     * Asserts that two booleans are equal.
     */
    static void assertEquals(bool expected, bool actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that two chars are equal. If they are not an AssertionFailedError is thrown with the given message.
     */
    static void assertEquals(const String& message, char expected, char actual) {
        if (Character::valueOf(expected).equals(actual)) return;
        failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
    }

    /**
     * Asserts that two chars are equal.
     */
    static void assertEquals(char expected, char actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that two characters are equal. If they are not an AssertionFailedError
     * is thrown with the given message.
     */
    static void assertEquals(const String& message, Type::uchar expected, Type::uchar actual) {
        if (Character::valueOf(expected).equals(actual)) return;
        failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
    }

    /**
     * Asserts that two wide chars are equal.
     */
    static void assertEquals(Type::uchar expected, Type::uchar actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that two ints are equal. If they are not an AssertionFailedError is thrown with the given message.
     */
    static void assertEquals(const String& message, int expected, int actual) {
        if (Integer::valueOf(expected).equals(actual)) return;
        failNotEquals(message, String::valueOf(expected), String::valueOf(actual));
    }

    /**
     * Asserts that two ints are equal.
     */
    static void assertEquals(int expected, int actual) {
        assertEquals(nullptr, expected, actual);
    }

    /**
     * Asserts that an object isn't null.
     */
    static void assertNotNull(const Object& object) {
        assertNotNull(nullptr, object);
    }

    /**
     * Asserts that an object isn't null. If it is an AssertionFailedError is thrown with the given message.
     */
    static void assertNotNull(const String& message, const Object& object) {
        assertTrue(message, object != nullptr);
    }

    /**
     * Asserts that an object is null. If it isn't an {@link AssertionError} is thrown.
     * Message contains: Expected: <null> but was: object
     */
    static void assertNull(const Object& object) {
        if (object != nullptr) {
            assertNull(String::valueOf("Expected: <null> but was: ") + object.toString(), object);
        }
    }

    /**
     * Asserts that an object is null.  If it is not an AssertionFailedError is thrown with the given message.
     */
    static void assertNull(const String& message, const Object& object) {
        assertTrue(message, object == nullptr);
    }

    /**
     * Asserts that two objects refer to the same object. If they are not an AssertionFailedError is thrown with
     * the given message.
     */
    static void assertSame(const String& message, const Object& expected, const Object& actual) {
        if (expected == actual) {
            return;
        }
        failNotSame(message, expected, actual);
    }

    /**
     * Asserts that two objects refer to the same object. If they are not the same an AssertionFailedError is thrown.
     */
    static void assertSame(const Object& expected, const Object& actual) {
        assertSame(nullptr, expected, actual);
    }

    /**
     * Asserts that two objects do not refer to the same object. If they do refer to the same object an
     * AssertionFailedError is thrown with the given message.
     */
    static void assertNotSame(const String& message, const Object& expected, const Object& actual) {
        if (expected == actual) {
            failSame(message);
        }
    }

    /**
     * Asserts that two objects do not refer to the same object. If they do refer to the same object
     * an AssertionFailedError is thrown.
     */
    static void assertNotSame(const Object& expected, const Object& actual) {
        assertNotSame(nullptr, expected, actual);
    }

    static void failSame(const String& message) {
        String formatted = (message != nullptr) ? message + " " : "";
        fail(formatted + "expected not same");
    }

    static void failNotSame(const String& message, const Object& expected, const Object& actual) {
        String formatted = (message != nullptr) ? message + " " : "";
        fail(formatted + "expected same:<" + String::valueOf(expected) + "> was not:<" + String::valueOf(actual) + ">");
    }

    static void failNotEquals(const String& message, const Object& expected, const Object& actual) {
        fail(format(message, expected, actual));
    }

    static String format(const String& message, const Object& expected, const Object& actual) {
        String formatted = "";
        if (message != nullptr && message.length() > 0) {
            formatted = message + " ";
        }
        return formatted + "expected:<" + String::valueOf(expected) + "> but was:<" + String::valueOf(actual) + ">";
    }

};

}
}

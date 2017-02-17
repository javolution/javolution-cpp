/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"
#include "java/lang/Class.hpp"
#include "java/lang/IndexOutOfBoundsException.hpp"
#include "iostream"

namespace java {
namespace lang {

// TODO: Move to java.io.PrintStream
class OutPrintStream: public Object {
    JAVOLUTION_DLL
    static const Class CLASS;
public:

    void println() const {
        synchronized(CLASS){
        std::wcout << std::endl << std::flush;
    }
}

template<typename T> void print(T t) const {
    synchronized(CLASS) {
        std::wcout << String::valueOf(t).toWString() << std::flush;
    }
}
template<typename T> void println(T t) const {
    synchronized(CLASS) {
        std::wcout << String::valueOf(t).toWString() << std::endl << std::flush;
    }
}
};

// TODO: Move to java.io.PrintStream
class ErrPrintStream: public Object {
    JAVOLUTION_DLL
    static const Class CLASS;
public:

    void println() const {
        synchronized(CLASS){
        std::wcerr << std::endl << std::flush;
    }
}
template<typename T> void print(T t) const {
    synchronized(CLASS) {
        std::wcerr << String::valueOf(t).toWString() << std::flush;
    }
}
template<typename T> void println(T t) const {
    synchronized(CLASS) {
        std::wcerr << String::valueOf(t).toWString() << std::endl << std::flush;
    }
}
};

/**
 * The System class contains several useful class fields and methods.
 *
 * @version 7.0
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/System.html">
 *       Java - System</a>
 */
class System {

    /** Utility class, cannot be instantiated. */
    System() {
    }

public:

    /** Standard output stream. */
    JAVOLUTION_DLL
    static const OutPrintStream out;

    /** Standard error stream. */
    JAVOLUTION_DLL
    static const ErrPrintStream err;

    /**
     * Copies an array from the specified source array, beginning at the specified position, to the specified
     * position of the destination array. This method ensures that copy constructors of the array elements (if any)
     * are being called.
     *
     * @throws IndexOutOfBoundsException if <code>(srcPos+length &gt; src.length)
     *          || (dstPos+length &gt; dst.length)</code>
     */
    template<class E> static void arraycopy(const Array<E>& src, int srcPos, Array<E>& dst, int dstPos, int length) {
        if ((srcPos < 0) || (dstPos < 0) || (length < 0) || (srcPos + length > src.length)
                || (dstPos + length > dst.length))
            throw IndexOutOfBoundsException(
                    String::valueOf("srcPos: ") + srcPos + ", dstPos: " + dstPos + ", length: " + length);
        Array<E>::Value * srcValue = src.this_<Array<E>::Value>();
        Array<E>::Value * dstValue = dst.this_<Array<E>::Value>();
        for (int i = 0; i < length; ++i) {
            dstValue->elementAt(dstPos + i) = srcValue->elementAt(srcPos + i);
        }
    }

};

}
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Object.hpp"

namespace java {
namespace lang {

/**
 * This interface imposes a total ordering on the objects of each class that implements it.
 * This ordering is referred to as the class's <i>natural ordering</i>,
 * and the class's <tt>compareTo</tt> method is referred to as its <i>natural comparison method</i>.<p>
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Comparable.html">
 *       Java - Comparable</a>
 * @version 7.0
 */
template<class T>
class Comparable: public virtual Object {
public:

    class Interface: public virtual Object::Interface {
    public:

        /**
         * Compares this object with the specified object for order.  Returns a
         * negative integer, zero, or a positive integer as this object is less
         * than, equal to, or greater than the specified object.
         */
        virtual int compareTo(const T& that) const = 0;

    };

    CTOR(Comparable, Interface)

    // Exported Interface methods.

    int compareTo(const T& that) const {
        return this_cast_<Interface>()->compareTo(that);
    }

};

}
}

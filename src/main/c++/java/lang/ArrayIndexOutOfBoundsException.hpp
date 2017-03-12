/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/IndexOutOfBoundsException.hpp"

namespace java {
namespace lang {

/**
 * Thrown to indicate that an array has been accessed with an illegal index.
 * The index is either negative or greater than or equal to the size of the array.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/ArrayIndexOutOfBoundsException.html">
 *       Java - ArrayIndexOutOfBoundsException</a>
 * @version 7.0
 */
class ArrayIndexOutOfBoundsException: public IndexOutOfBoundsException {
public:

    /** Creates an array index out of bounds exception with the specified optional message.*/
    ArrayIndexOutOfBoundsException(const String& message = nullptr) :
            IndexOutOfBoundsException(message) {
    }

};

}
}


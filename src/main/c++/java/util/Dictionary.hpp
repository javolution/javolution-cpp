/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _JAVA_UTIL_DICTIONARY_HPP
#define _JAVA_UTIL_DICTIONARY_HPP

#include "java/lang/String.hpp"
#include "org/javolution/util/FastMap.hpp"

namespace java {
    namespace util {
        typedef org::javolution::util::FastMap<java::lang::String, java::lang::String> Dictionary;
        typedef org::javolution::util::FastMap_API<java::lang::String, java::lang::String> Dictionary_API;
    }
}

/**
 * This class is obsolete and should be replaced by the Map interface
 * (this dictionary is a rename of org::javolution::util::FastMap<String,String>).
 *
 * @see  <a href="http://java.sun.com/javase/6/docs/api/java/lang/Dictionary.html">
 *       Java - Dictionary</a>
 * @version 1.0
 */


#endif

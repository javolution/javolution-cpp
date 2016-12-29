/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Class.hpp"
#include "java/lang/Error.hpp"
#include "org/javolution/util/FastMap.hpp"

using namespace java::lang;
using namespace org::javolution::util;


Class_ANY Class_ANY_API::forName(String const& className) { // Maintains unicity.
    static FastMap<String, Class_ANY> nameToClass = FastMap_API<String, Class_ANY>::newMap();
    Class_ANY newClass;
    synchronized (nameToClass) {
        Class_ANY existingClass = nameToClass->get(className);
        if (existingClass != Type::Null) return existingClass;
        newClass = new Class_ANY_API(className);
        nameToClass->put(className->intern(), newClass);
    }
    return newClass;
}

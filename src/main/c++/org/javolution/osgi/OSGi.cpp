/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "org/javolution/osgi/OSGi.hpp"
#include "org/javolution/internal/osgi/OSGiImpl.hpp"

using namespace org::javolution::osgi;
using namespace org::javolution::internal::osgi;

OSGi OSGi_API::newInstance() {
    return new OSGiImpl_API();
}

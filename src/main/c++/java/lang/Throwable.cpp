/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Throwable.hpp"
#include "java/lang/System.hpp"
#include <sstream>

void Throwable::printStackTrace() const {
	System::err.println(*this);
	std::ostringstream res;
	res.imbue(std::locale::classic());
	res << booster::trace(*this) << std::endl;
	System::err.println(String::valueOf(res.str()));
}

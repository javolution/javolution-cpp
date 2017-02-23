/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "Javolution.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "java/lang/IllegalArgumentException.hpp"

using namespace java::lang;

Type::FastHeap Type::FastHeap::INSTANCE;

void Type::FastHeap::setSize(int size) {
	if (size == queueSize) return;
	if (queueSize != 0)
		throw UnsupportedOperationException("FastHeap resizing not supported.");
	bool isPowerOf2 = ((size != 0) && !(size & (size - 1)));
	if (!isPowerOf2)
		throw IllegalArgumentException("Size should be a power of two.");
	queueSize = size;
	queueMask = size - 1;
	queue = new void*[size];

	buffer = new Block[size];
	bufferFirst = &buffer[0];
	bufferLast = &buffer[size - 1];

	for (int i = 0; i < size; ++i) {
		queue[i] = &buffer[i];
	}
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "Javolution.hpp"
#include "java/lang/RuntimeException.hpp"
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

#ifdef _SOLARIS // Add missing define in Solaris 10 (pthreads.h)
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif

#ifndef _WINDOWS
Type::Mutex::Mutex() {
	Type::int32 rc = pthread_mutexattr_init(&attr);
	if (rc != 0) throw RuntimeException("pthread_mutexattr_init returns " + rc);
    rc = pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	if (rc != 0) throw RuntimeException("pthread_mutexattr_settype returns " + rc);
    rc = pthread_mutex_init (&mutex, &attr);
	if (rc != 0) throw RuntimeException("pthread_mutex_init returns " + rc);
    rc = pthread_mutexattr_destroy(&attr);
	if (rc != 0) throw RuntimeException("pthread_mutexattr_destroy returns " + rc);
}

Type::Mutex::~Mutex() {
	Type::int32 rc = pthread_mutex_destroy(&mutex);
	if (rc != 0) throw RuntimeException("pthread_mutex_destroy returns " + rc);
}

Type::ScopedLock::ScopedLock(Mutex& m) : mutex(m.mutex){
	Type::int32 rc = pthread_mutex_lock(&mutex);
	if (rc != 0) throw RuntimeException("pthread_mutex_lock returns " + rc);
    isLocked = true;
}

Type::ScopedLock::~ScopedLock() {
	Type::int32 rc = pthread_mutex_unlock(&mutex);
	if (rc != 0) throw RuntimeException("pthread_mutex_unlock returns " + rc);
}
#endif

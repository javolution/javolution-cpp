/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include <exception>
#include "java/lang/Thread.hpp"
#include "java/lang/Throwable.hpp"
#include "java/lang/Error.hpp"
#include "java/lang/IllegalArgumentException.hpp"
#include "java/lang/System.hpp"

const Thread Thread::MAIN = new Thread::Value(nullptr, "Thread-Main");
Type::atomic_count Thread::threadNumber;
thread_local Thread Thread::current = nullptr;

void Thread::Value::run() {
    if (target != nullptr) target.run();
}

#ifdef JAVOLUTION_MSVC

#include <windows.h>
DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
	try {
		Thread::Value* thisThread = (Thread::Value*) lpParam;
		Thread::current = thisThread;
		thisThread->run();
	}
	catch (Throwable& error) {
		error.printStackTrace();
	}
	catch (const std::exception& ex) {
		System::err.println(String::valueOf("C++ Exception : ") + ex.what());
	}
	catch (...) {
		System::err.println("Unknown C++ Error!");
	}
	return 0;
}
void Thread::Value::start() {
	DWORD threadId;
	nativeThreadPtr = CreateThread(nullptr, // default security attributes
		0, // use default stack size
		MyThreadFunction, // thread function name
		this, // argument to thread function
		0, // use default creation flags
		&threadId); // returns the thread identifier
}
void Thread::Value::join() {
	WaitForSingleObject(nativeThreadPtr, INFINITE);
}

Thread::Value::Value(const Runnable& target, const String& threadName) :
	target(target) {
	name = (threadName != nullptr) ? threadName : String::valueOf("Thread-") + ++threadNumber;
}

Thread::Value::~Value() {
}

void Thread::sleep(long millis) {
	if (millis < 0) throw IllegalArgumentException("negative time");
	Sleep((DWORD)millis); // Windows::Thread method.
}

#else

#include <pthread.h>
#include <unistd.h>
#include <time.h>

extern "C" {
	void * MyThreadFunction(void* threadPtr) {
		try {
			Thread::Value* thisThread = ((Thread::Value*) threadPtr);
			Thread::current = thisThread;
			thisThread->run();
		}
		catch (Throwable& error) {
			error.printStackTrace();
		}
		catch (const std::exception& ex) {
			System::err.println(String::valueOf("C++ Exception : ") + ex.what());
		}
		catch (...) {
			System::err.println("Unknown C++ Error!");
		}
		// TODO : Ensure deletion when execution is over!
		return nullptr;
	}
}

void Thread::Value::start() {
	pthread_create((pthread_t*)nativeThreadPtr, nullptr, MyThreadFunction, (void*) this);
}

void Thread::Value::join() {
	pthread_t* pthreadPtr = (pthread_t*)nativeThreadPtr;
	if (pthread_join(*pthreadPtr, nullptr) != 0)
		throw Error("Thread_Type::join() internal error");
}

Thread::Value::Value(const Runnable& target, const String& name) :
	target(target) {
	name = (threadName != nullptr) ? threadName : String::valueOf("Thread-") + ++threadNumber;
	nativeThreadPtr = new pthread_t();
}

Thread::Value::~Value() {
	pthread_t* pthreadPtr = (pthread_t*)nativeThreadPtr;
	delete pthreadPtr;
}

void Thread::sleep(long msec) {
	if (millis < 0) throw IllegalArgumentException("negative time");
	enum {
		NANOSEC_PER_MSEC = 1000000
	};
	struct timespec sleepTime;
	struct timespec remainingSleepTime;
	sleepTime.tv_sec = msec / 1000;
	sleepTime.tv_nsec = (msec % 1000) * NANOSEC_PER_MSEC;
	nanosleep(&sleepTime, &remainingSleepTime);
}

#endif


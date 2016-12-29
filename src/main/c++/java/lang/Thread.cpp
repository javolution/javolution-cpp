/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Thread.hpp"
#include <exception>
#include "java/lang/Throwable.hpp"
#include "java/lang/Error.hpp"

void java::lang::Thread_API::run() {
    if (_target != Type::Null) {
        try {
            _target->run();
        } catch (java::lang::Throwable& error) {
            std::wcerr << error << std::endl;
            error->printStackTrace();
        } catch (const std::exception& ex) {
            std::wcerr << "ERREUR : " << ex.what() << std::endl;
        } catch (...) {
            std::wcerr << "Unknown C++ Error!" << std::endl;
        }
    }
}

#ifndef _WINDOWS

#include <pthread.h>
#include <unistd.h>
#include <time.h>

extern "C" {
    void * MyThreadFunction(void* threadPtr) {
        ((java::lang::Thread_API*)threadPtr)->run();
        // TODO : Ensure deletion when execution is over!
        return NULL;
    }
}

void java::lang::Thread_API::start() {
    pthread_create((pthread_t*) _nativeThreadPtr, NULL, MyThreadFunction, (void*) this);
}

void java::lang::Thread_API::join() {
    pthread_t* pthreadPtr = (pthread_t*) _nativeThreadPtr;
    if (pthread_join(*pthreadPtr, NULL) != 0)
        throw java::lang::Error_API::newInstance(L"Thread_API::join() internal error");
}

void java::lang::Thread_API::sleep(Type::int64 msec) {
	  enum { NANOSEC_PER_MSEC = 1000000 };
	  struct timespec sleepTime;
	  struct timespec remainingSleepTime;
	  sleepTime.tv_sec = msec / 1000;
	  sleepTime.tv_nsec = (msec % 1000) * NANOSEC_PER_MSEC;
	  nanosleep(&sleepTime, &remainingSleepTime);
}

java::lang::Thread_API::Thread_API(Runnable const& target, String const& name) :
		_target(target), _name(name) {
    _nativeThreadPtr = new pthread_t();
}

java::lang::Thread_API::~Thread_API() {
    pthread_t* pthreadPtr = (pthread_t*) _nativeThreadPtr;
    delete pthreadPtr;
}

#else

#include <windows.h>
DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
    java::lang::Thread_API* thisThread = (java::lang::Thread_API*) lpParam;
    thisThread->run();
    return 0;
}
void java::lang::Thread_API::start() {
    DWORD threadId;
    _nativeThreadPtr = CreateThread(
            NULL, // default security attributes
            0, // use default stack size
            MyThreadFunction, // thread function name
            this, // argument to thread function
            0, // use default creation flags
            &threadId); // returns the thread identifier
}
void java::lang::Thread_API::join() {
    WaitForSingleObject(_nativeThreadPtr, INFINITE);
}
void java::lang::Thread_API::sleep(Type::int64 millis) {
    Sleep((DWORD)millis); // Windows::Thread method.
}
java::lang::Thread_API::Thread_API(Runnable const& target, String const& name) : _target(target), _name(name) {
}
java::lang::Thread_API::~Thread_API() {
}

#endif


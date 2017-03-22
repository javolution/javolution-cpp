#ifndef _THREAD_H_
#define _THREAD_H_

#include <windows.h>	//windows APIs
#include <errno.h>		//error numbers
#include "Debug.h"		//our debugging / logging capabilities

#pragma once

/**
 * Encapsulates a win32 thread. Basically it's just raw calls
 * to the windows APIs, but with easier syntax.
 */
class Thread {
public:
	/**
	 * See MSDN http://msdn.microsoft.com/en-us/library/windows/desktop/ms682453(v=vs.85).aspx
	 * for details. 
	 * This webpage also tells the difference between 'CreateThread' and '_beginthreadex':
	 * 
	 * A thread in an executable that calls the C run-time library (CRT) should use the _beginthreadex 
	 * and _endthreadex functions for thread management rather than CreateThread and ExitThread; this 
	 * requires the use of the multithreaded version of the CRT. If a thread created using CreateThread 
	 * calls the CRT, the CRT may terminate the process in low-memory conditions.
	 * 
	 * Because we are running the exectuable in the C++ run-time, so we should use CreateThread.
	 */
	Thread(
		LPTHREAD_START_ROUTINE lpStartAddress,				// pointer to thread function
		LPVOID lpParameter,									// argument for new thread
		LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL,	// pointer to security attributes
		DWORD dwStackSize = 0								// initial thread stack size
		);

	/*
	 * In Windows system, we use 'WaitForSingleObject' as a replacement to 'pthread_join',
	 * See http://www.cs.rpi.edu/academics/courses/netprog/WindowsThreads.html for example.
	 *
	 * 'WaitForSingleObject' acts exactly same as 'pthread_join' while we set the parameter
	 * to 'INFINITE', i.e, if we'd like, we can control the period of thread blocking.
	 */
	DWORD join(
		DWORD dwMilliseconds = INFINITE
		);

	/*
	 * See MSDN http://msdn.microsoft.com/en-us/library/windows/desktop/ms682659(v=vs.85).aspx
	 * for details.
	 * Per MSDN, this method should not be used anymore, and here is the reason for this:
	 *
	 * ExitThread is the preferred method of exiting a thread in C code. However, in C++ code, 
	 * the thread is exited before any destructors can be called or any other automatic cleanup 
	 * can be performed. Therefore, in C++ code, you should return from your thread function.
	 *
	 * Because we are using C++ here, we should exit a thread through the thread function.
	 */
	//VOID exitThread(
	//	);

private:
	DWORD m_dwThreadId;
	HANDLE m_hThread;
};

/**
 * Encapsulates a mutex. Basically it's just raw calls to the windows APIs, but with 
 * easier syntax.
 */
class Lock {
public:
	/** Create a mutex with default security attributes. */
	Lock(LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL);

	/** Constructing the 'Lock' object with an existed mutex. */
	Lock(HANDLE mutex);
	
	/** Default destructor. */
	~Lock();

	/** Block INFINITE for the lock. */
	BOOL obtainBlocking();

	/** Try to obtain the lock, return TRUE if the lock was obtained. */
	BOOL obtainDontBlock();

	/** Release the lock. */
	BOOL release();

	/** Get the HANDLE of inner mutex. */
	HANDLE getMutex();

	/** Determines whether we will clean up the mutex in the destructor. */
	void setShouldDeleteMutex(BOOL bShouldDelete);

private:
	HANDLE m_hMutex;
	BOOL m_bShouldDeleteMutex;
};


/**
 * Defines the data context of a condition variable, this is from SEC-3.4 of
 * article http://www.cs.wustl.edu/~schmidt/win32-cv-1.html.
 */
typedef struct {

	INT iWaitersCount;					//number of waiting threads.

	
	CRITICAL_SECTION csWaitersCountLock;//serialize access to <iWaitersCount>.
	  
	
	HANDLE hSema;						//semaphore used to queue up threads waiting for the condition to become signaled. 
	

	HANDLE hWaitersDone;				//an auto-reset event used by the broadcast/signal thread to wait for all the waiting
										//thread(s) to wake up and be released from the semaphore. 
	  
	BOOL bWasBroadcast;					//keeps track of whether we were broadcasting or signaling, this allows us to 
										//optimize the code if we're just signaling.

} CONDITION_VARIABLE_CONTEXT;


/**
 * Encapsulates the condition variable, the inner implementation is from SEC-3.4 of 
 * article http://www.cs.wustl.edu/~schmidt/win32-cv-1.html.
 * 
 * Since Windows's 'Condition Variable APIs' is introduced after Windows Vista, so it
 * can't be applied to a XP system. We are creating our own 'ConditionVariable' with 
 * OS primitives of XP by following above article.
 */
class Condition {
public:

	/** Create a condition variable with OS primitives supported by XP. */
	Condition();

	/** Do clean up here. */
	~Condition();

	/**
	 * Unlocks the given lock, waits to be awoken, relocks the lock when it is awoken,
	 * and then returns. It can be awoken for any reason, so you should double check
	 * that the condition is still true.
	 */
	void wait(Lock *lock);

	/** Wakes up one or more threads waiting for this condition variable. */
	void notify();

	/** Wakes up every thread waiting for this condition variable. */
	void notifyAll();

private:
	CONDITION_VARIABLE_CONTEXT m_cv;
};

/**
 * Combines mutexes and condition variables to emulate the behavior of a 
 * Java synchronized block with wait() and signal() calls inside.
 */
class JavaLock {
public:
	/**
	 * You can specify a lock or condition variable in particular if you want,
	 * but it'll make a default one for you if you want.
	 */
	JavaLock(Lock* lock = new Lock(), Condition* condition = new Condition());

	/** Deletes the lock and condition. */
	~JavaLock();
	
	/** Obtains the lock. Equivalent to <code>synchronized(someObject){</code> in Java. */
	void enterSynchronize();
	
	/** 
	 * Releases the lock. Equivalent to <code>}</code> at the end of a 
	 * synchronized block in Java. 
	 */	
	void exitSynchronize();
	
	/**
	 * See Condition::wait(). Must be called between enterSynchronize
	 * and exitSynchronize(). Same behavior as Java.
	 */
	void wait();
	
	/**
	 * See Condition::notify(). Must be called between enterSynchronize 
	 * and exitSynchronize(). Same behavior as Java. 
	 */
	void notify();
	
	/**
	 * See Condition::notifyAll().  Must be called between enterSynchronize 
	 * and exitSynchronize(). Same behavior as Java. 
	 */
	void notifyAll();

private:
	Condition* m_pCondition;
	Lock* m_pLock;
};

#endif /*_THREAD_H_*/
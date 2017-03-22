#ifndef MULTITASKING_H_
#define MULTITASKING_H_

#include <pthread.h>	//threads
#include <errno.h>		//error numbers
#include "Debug.h"		//our debugging / logging capabilities

/**
 * Encapsulates a pthread_t.  Basically just raw calls
 * to the pthread API, but with easier syntax.
 */ 
class Thread {
public:
	/** 
	 * You can set it's scheduling parameters by setting attr
	 * See http://www.unix.org/version2/whatsnew/threadsref.html
	 * for details. 
	 */
	Thread(void* (*start_routine)(void*), void *arg = NULL, pthread_attr_t *attr = NULL);
	/** Blocks until this thread ends and returns a pointer to its return value. */
	void* join();
	
	/** STATIC! Ends the calling thread.  Optional parameter allows it to return a value on its close. */
	static void endThread(void *returnValue = NULL);
	
private:
	pthread_t m_thread;
};

/**
 * Encapsulates a pthread_mutex_t.  Basically just raw calls
 * to the pthread API, but with easier syntax.
 */ 
class Lock {
public:
	/** A master lock to be shared by threads should they be so inclined. */
	static Lock masterLock;

	/** Default type is Recursive, which is probably the correct kind. */
	Lock(int type = PTHREAD_MUTEX_RECURSIVE);
	/** Creates a lock around a specified (and already initialized) mutex. */
	Lock(pthread_mutex_t* mutex);
	/** Locks need to be destroyed properly. */
	~Lock();
	/** Blocks indefinitely for the lock. */
	void obtainBlocking();
	/** Returns true if the lock was obtained (if the lock was free), and false otherwise. */
	bool obtainDontBlock();
	/** Releases the lock. */
	void release();
	/** Makes the mutex_t available. */
	pthread_mutex_t* getMutex();
	
	/** Determines what happens in the destructor. */
	void setShouldDeleteMutex(bool shouldDelete);
	
private:
	pthread_mutex_t* m_mutex;
	pthread_mutexattr_t* m_attr;
	
	bool m_shouldDeleteMutex;
	bool m_shouldDeleteAttr;
};

/**
 * Encapsulates a pthread_cond_t.  Basically just raw calls
 * to the pthread API, but with easier syntax.
 */
class Condition {
public:
	/** Condition attributes allow out-of-process notification, but that's all. */
	Condition(pthread_condattr_t* attr = NULL);
	/** Conditions need to be destroyed. */
	~Condition();
	/** 
	 * Unlocks the given lock, waits to be awoken, relocks the lock when it is awoken,
	 * and then returns.  It can be awoken for any reason, so you should double check
	 * that the condition is still true.
	 */
	void wait(Lock* lock);
	/** Same as above, but with a timeout. */
	void wait(Lock* lock, U32 timeout_us);
	/** Wakes up one or more threads waiting for this condition variable. */
	void notify();
	/** Wakes up every thread waiting for this condition variable. */
	void notifyAll();
	
private:
	pthread_cond_t m_cond; 
};

/**
 * Combines pthread mutexes and conditions to emulate the behavior
 * of a Java synchronized block with wait() and signal() calls inside.
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
	/** Obtains the lock.  Equivalent to <code>synchronized(someObject){</code> in Java. */
	void enterSynchronize();
	/** Releases the lock.  Equivalent to <code>}</code> at the end of a synchronized block in Java. */	
	void exitSynchronize();
	/** See Condition::wait().  Must be called between enterSynchronize and exitSynchronize(). Same behavior as Java. */
	void wait();
	/** Same as wait(), but with a timeout */
	void wait(U32 timeout_us);
	/** See Condition::notify().  Must be called between enterSynchronize and exitSynchronize(). Same behavior as Java. */
	void notify();
	/** See Condition::notifyAll().  Must be called between enterSynchronize and exitSynchronize(). Same behavior as Java. */
	void notifyAll();

private:
	Condition* 	m_condition;
	Lock* 		m_lock;
	IFDEBUG(bool m_isLocked);
};

#endif /*MULTITASKING_H_*/

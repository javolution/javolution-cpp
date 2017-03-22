#include "ThreadPosix.hpp"

/////////////////////////////////////////
//Thread class
/////////////////////////////////////////
Thread::Thread(void* (*start_routine)(void*), void *arg, pthread_attr_t *attr) {
	int error = pthread_create(&m_thread,attr,start_routine,arg);
	ASSERT(error==0)
	(void) error;
}

void* Thread::join() {
	void* returnValuePtr;
	int error = pthread_join(m_thread, &returnValuePtr);
	ASSERT(error == 0);
	(void) error;
	return returnValuePtr;
}

//THIS FUNCTION IS STATIC
void Thread::endThread(void *returnValue) {
	pthread_exit(returnValue); 
}


/////////////////////////////////////////
//Lock class
/////////////////////////////////////////
Lock Lock::masterLock = Lock();

Lock::Lock(int type) {
	m_shouldDeleteMutex = true;
	m_shouldDeleteAttr  = true;
	m_attr = new pthread_mutexattr_t;
	pthread_mutexattr_settype(m_attr, type);
	m_mutex = new pthread_mutex_t;
	int error = pthread_mutex_init(m_mutex, m_attr);
	ASSERT(error==0)
	(void) error;
}

Lock::Lock(pthread_mutex_t* mutex) {
	m_mutex = mutex;
	m_shouldDeleteMutex = false;
	m_shouldDeleteAttr  = false;
}

Lock::~Lock() {
	if(m_shouldDeleteMutex){
		int error = pthread_mutex_destroy(m_mutex);
		ASSERT(error==0)
		(void) error;
		delete m_mutex;
	}
	if(m_shouldDeleteAttr){
		int error = pthread_mutexattr_destroy(m_attr);
		ASSERT(error==0)
		(void) error;
		delete m_attr;
	}
}

void Lock::obtainBlocking() {
	int error = pthread_mutex_lock(m_mutex);
	ASSERT_PERROR(error==0)
	(void) error;
}

bool Lock::obtainDontBlock() {
	int error = pthread_mutex_trylock(m_mutex);
	return error==0;
}

void Lock::release() {
	int error =	pthread_mutex_unlock(m_mutex);
	ASSERT_PERROR(error==0)
	(void) error;
}

pthread_mutex_t* Lock::getMutex() {
	return m_mutex;
}

void Lock::setShouldDeleteMutex(bool shouldDelete) {
	m_shouldDeleteMutex = shouldDelete;
}

/////////////////////////////////////////
//Condition class
/////////////////////////////////////////
Condition::Condition(pthread_condattr_t* attr) {
	LOG("WARNING!  Thread signaling is IFFY under LinuxThreads (Linux kernels pre 2.6)\n")
	int error = pthread_cond_init(&m_cond, attr);
	ASSERT(error==0)
	(void) error;
}

Condition::~Condition() {
	int error = pthread_cond_destroy(&m_cond);
	ASSERT(error==0)
	(void) error;
}

void Condition::wait(Lock* lock) {
	pthread_cond_wait(&m_cond, lock->getMutex());
}

void Condition::wait(Lock* lock, U32 timeout_us) {	
	//{tv_sec,tv_nsec}, 1us = 1000ns
	struct timespec timeToWait = {timeout_us / 1000000, (timeout_us * 1000) % 1000000000};
	pthread_cond_timedwait(&m_cond, lock->getMutex(),&timeToWait);
}

void Condition::notify() {
	pthread_cond_signal(&m_cond);
}

void Condition::notifyAll() {
	pthread_cond_broadcast(&m_cond);
}

/////////////////////////////////////////
//JavaLock class
/////////////////////////////////////////
JavaLock::JavaLock(Lock* lock, Condition* condition) {
	m_lock = lock;
	m_condition = condition;
	IFDEBUG(m_isLocked = false;)
}

JavaLock::~JavaLock() {
	delete m_lock;
	delete m_condition;	
}

void JavaLock::enterSynchronize() {
	ASSERT(!m_isLocked)
	m_lock->obtainBlocking();
	IFDEBUG(m_isLocked = true;)	
}

void JavaLock::exitSynchronize() {
	ASSERT(m_isLocked)
	m_lock->release();
	IFDEBUG(m_isLocked = false;)		
}

void JavaLock::wait() {
	ASSERT(m_isLocked)
	IFDEBUG(m_isLocked = false;)
	m_condition->wait(m_lock);
	IFDEBUG(m_isLocked = true;)
}

void JavaLock::wait(U32 timeout_us) {
	ASSERT(m_isLocked)
	IFDEBUG(m_isLocked = false;)
	m_condition->wait(m_lock,timeout_us);
	IFDEBUG(m_isLocked = true;)
}

void JavaLock::notify() {
	ASSERT(m_isLocked)
	m_condition->notify();
}

void JavaLock::notifyAll() {
	ASSERT(m_isLocked)
	m_condition->notifyAll();	
}

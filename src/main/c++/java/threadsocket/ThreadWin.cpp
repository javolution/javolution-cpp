#include "ThreadWin.hpp"

/////////////////////////////////////////
//Thread class
/////////////////////////////////////////
Thread::Thread(
	LPTHREAD_START_ROUTINE lpStartAddress,				// pointer to thread function
	LPVOID lpParameter,									// argument for new thread
	LPSECURITY_ATTRIBUTES lpThreadAttributes,			// pointer to security attributes
	DWORD dwStackSize) {								// initial thread stack size
	m_hThread = CreateThread (
		lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, 0, &m_dwThreadId
		);
	ASSERT(m_hThread != NULL);
}

DWORD Thread::join(DWORD dwMilliseconds) {
	return WaitForSingleObject (
		m_hThread,
		dwMilliseconds
		);
}

/////////////////////////////////////////
//Lock class
/////////////////////////////////////////
Lock::Lock(LPSECURITY_ATTRIBUTES lpMutexAttributes) {
	m_bShouldDeleteMutex = TRUE;
	m_hMutex = CreateMutex (
		lpMutexAttributes,	// default security attributes
        FALSE,				// initially not owned
        NULL				// unnamed mutex      
		);
	ASSERT(m_hMutex != NULL);
}

Lock::Lock(HANDLE mutex) {
	m_bShouldDeleteMutex = FALSE;
	m_hMutex = mutex;
}

Lock::~Lock() {
	if (m_bShouldDeleteMutex) {
		BOOL bResult = CloseHandle(m_hMutex);
		ASSERT(bResult);
	}
}

BOOL Lock::obtainBlocking() {
	DWORD dwWaitResult = WaitForSingleObject ( 
		m_hMutex,	// handle to mutex
		INFINITE	// no time-out interval
		);

	// The thread got ownership of an abandoned mutex
    // The database is in an indeterminate state.
    BOOL bResult = (dwWaitResult != WAIT_ABANDONED);
	ASSERT(bResult);

	return bResult;
}

BOOL Lock::obtainDontBlock() {
	// The pthread_mutex_trylock function is used to acquire 
	// a lock on the specified mutex variable. If the mutex has 
	// already been acquired by another thread, the function will 
	// return with an EBUSY indication rather than blocking.
	//
	// To achieve the same functionality in the Windows threading
	// model set the Milliseconds parameter to zero for the 
	// WaitForSingleObject call. You will receive a WAIT_TIMEOUT 
	// indication if the mutex was not signaled when you invoked 
	// the function.

	DWORD dwWaitResult = WaitForSingleObject ( 
		m_hMutex,	// handle to mutex
		0			// time-out immediately
		);

	BOOL bResult = (dwWaitResult != WAIT_TIMEOUT);
	ASSERT(bResult);

	return bResult;
}

BOOL Lock::release() {
	BOOL bResult = ReleaseMutex (m_hMutex);
	ASSERT(bResult);

	return bResult;
}

HANDLE Lock::getMutex() {
	return m_hMutex;
}

void Lock::setShouldDeleteMutex(BOOL bShouldDelete) {
	m_bShouldDeleteMutex = bShouldDelete;
}

/////////////////////////////////////////
//Condition class
/////////////////////////////////////////
Condition::Condition() {
	m_cv.iWaitersCount = 0;
	m_cv.bWasBroadcast = FALSE;
	m_cv.hSema = CreateSemaphore (
		NULL,       // no security
        0,          // initially 0
        0x7fffffff, // max count
        NULL		// unnamed 
		);

	InitializeCriticalSection (&m_cv.csWaitersCountLock);
	
	m_cv.hWaitersDone = CreateEvent (
		NULL,	// no security
        FALSE,	// auto-reset
        FALSE,	// non-signaled initially
        NULL	// unnamed
		);
}

Condition::~Condition() {
	DeleteCriticalSection (&m_cv.csWaitersCountLock);
}

void Condition::wait(Lock *lock) {
	// Avoid race conditions.
	EnterCriticalSection (&m_cv.csWaitersCountLock);
	m_cv.iWaitersCount++;
	LeaveCriticalSection (&m_cv.csWaitersCountLock);

	// This call atomically releases the mutex and waits on the semaphore 
	// until <notify> or <notifyAll> are called by another thread.
	SignalObjectAndWait (lock->getMutex(), m_cv.hSema, INFINITE, FALSE);

	// Reacquire lock to avoid race conditions.
	EnterCriticalSection (&m_cv.csWaitersCountLock);

	// We're no longer waiting...
	m_cv.iWaitersCount--;

	// Check to see if we're the last waiter after <notifyAll>.
	BOOL bLastWaiter = m_cv.bWasBroadcast && m_cv.iWaitersCount == 0;

	LeaveCriticalSection (&m_cv.csWaitersCountLock);

	// If we're the last waiter thread during this particular broadcast
	// then let all the other threads proceed.
	if (bLastWaiter) {
		// This call atomically signals the <hWaitersDone> event and waits until
		// it can acquire the <lock>.  This is required to ensure fairness. 
		SignalObjectAndWait (m_cv.hWaitersDone, lock->getMutex(), INFINITE, FALSE);
	}
	else {
		// Always regain the external mutex since that's the guarantee we
		// give to our callers. 
		WaitForSingleObject (lock->getMutex(), INFINITE);
	}
}

void Condition::notify() {
	EnterCriticalSection (&m_cv.csWaitersCountLock);
	BOOL bHaveWaiters = m_cv.iWaitersCount > 0;
	LeaveCriticalSection (&m_cv.csWaitersCountLock);

	// If there aren't any waiters, then this is a no-op.  
	if (bHaveWaiters)
		ReleaseSemaphore (m_cv.hSema, 1, 0);
}

void Condition::notifyAll() {
	// This is needed to ensure that <iWaitersCount> and <bWasBroadcast> are
	// consistent relative to each other.
	EnterCriticalSection (&m_cv.csWaitersCountLock);
	BOOL bHaveWaiters = FALSE;

	if (m_cv.iWaitersCount > 0) {
		// We are broadcasting, even if there is just one waiter...
		// Record that we are broadcasting, which helps optimize
		// <wait> for the non-broadcast case.
		m_cv.bWasBroadcast = TRUE;
		bHaveWaiters = TRUE;
	}

	if (bHaveWaiters) {
		// Wake up all the waiters atomically.
		ReleaseSemaphore (m_cv.hSema, m_cv.iWaitersCount, 0);

		LeaveCriticalSection (&m_cv.csWaitersCountLock);

		// Wait for all the awakened threads to acquire the counting
		// semaphore. 
		WaitForSingleObject (m_cv.hWaitersDone, INFINITE);
		// This assignment is okay, even without the <csWaitersCountLock> held 
		// because no other waiter threads can wake up to access it.
		m_cv.bWasBroadcast = FALSE;
	}
	else {
		LeaveCriticalSection (&m_cv.csWaitersCountLock);
	}
}

/////////////////////////////////////////
//JavaLock class
/////////////////////////////////////////
JavaLock::JavaLock(Lock* lock, Condition* condition) {
	m_pLock = lock;
	m_pCondition = condition;
}

JavaLock::~JavaLock() {
	delete m_pLock;
	delete m_pCondition;
}

void JavaLock::enterSynchronize() {
	if (m_pLock != NULL) {
		m_pLock->obtainBlocking();
	}
}

void JavaLock::exitSynchronize() {
	if (m_pLock != NULL) {
		m_pLock->release();
	}
}

void JavaLock::wait() {
	if (m_pCondition != NULL) {
		m_pCondition->wait(m_pLock);
	}
}

void JavaLock::notify() {
	if (m_pCondition != NULL) {
		m_pCondition->notify();
	}
}

void JavaLock::notifyAll() {
	if (m_pCondition != NULL) {
		m_pCondition->notifyAll();
	}
}

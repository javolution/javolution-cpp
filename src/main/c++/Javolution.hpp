/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <cstdint>
#include <atomic>
#include "boost/detail/lightweight_mutex.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined __CYGWIN__
#define _WINDOWS
#define _DEPRECATED(text) __declspec(deprecated(#text))
#pragma warning(disable: 4290) //  Visual C++ does not implement checked exceptions (throw declaration ignored).
#endif

#if defined(__linux)
#define _LINUX
#define _DEPRECATED(text) __attribute__ ((deprecated(#text)))
#endif

// Generic helper definitions for shared library support, ref. http://gcc.gnu.org/wiki/Visibility
// For gcc compilations the option  -fvisibility=hidden and -fvisibility-inlines-hidden
// should be used to export only symbols explicitly marked as *_DLL
#if defined _WINDOWS
#define HELPER_DLL_IMPORT __declspec(dllimport)
#define HELPER_DLL_EXPORT __declspec(dllexport)
#else
#if __GNUC__ >= 4
#define HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
#define HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
#else
#define HELPER_DLL_IMPORT
#define HELPER_DLL_EXPORT
#endif
#endif

// Now we use the generic helper definitions above to define JAVOLUTION_DLL (components using the JAVOLUTION can do the same).
#ifndef JAVOLUTION_DLL // Only if there is no user override (e.g. static build).
#ifdef JAVOLUTION_DLL_EXPORT // The JAVOLUTION DLL is being built.
#define JAVOLUTION_DLL HELPER_DLL_EXPORT
#else // The JAVOLUTION DLL is being used.
#define JAVOLUTION_DLL HELPER_DLL_IMPORT
#endif
#endif

#define CTOR(CLASS) CLASS(Void = nullptr) {} CLASS(Value* value) : Object(value) {}

namespace Type {

////////////////////////////////////
// Define portable primitive types.
////////////////////////////////////

typedef wchar_t wchar;
typedef bool boolean;
typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32; // Should be the same as 'int'
typedef std::int64_t int64;
typedef std::atomic_int atomic_count; // No Mutex on 32-bits hardware.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Lock-free heap of fixed-size blocks. Real-time systems should ensure that no heap allocation exceeding
// the block size is ever performed in order to avoid non time-deterministic system heap allocations.
// The maximum capacity of the FastHeap is about 13/26 GBytes (on 32/64 bits systems).
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FastHeap {

    static const size_t MAX_HANDLES = 16;
    struct Block { // Capable of holding 16 pointers (size of 64/128 bytes on 32/64 bits systems) plus reference count.
        Type::atomic_count refCount;
        void* addresses[MAX_HANDLES];
        Block() : refCount(0) {}
    };

    Type::atomic_count newCount; // Number of block allocated minus one.
    Type::atomic_count delCount; // Number of blocks deleted minus one.

    void** queue = nullptr; // Circular queue of memory blocks.
    int queueSize = 0; // Size of the queue (power of 2).
    int queueMask = 0; // Mask (size -1)

    Block* buffer = nullptr; // Memory buffer.
    void* bufferFirst = nullptr; // Address of first block in buffer.
    void* bufferLast = nullptr; // Address of last block in buffer.

    Type::int64 systemHeapCount = 0; // Number of system heap allocations when enabled (should be zero).
    size_t blockSize = 0; // 0 when disabled, else BLOCK_SIZE
    int maxUseCount = 0;

public:
    FastHeap() : newCount(-1), delCount(-1) {}

    /** The free block capacity in bytes (excludes reference count member). */
    static const size_t BLOCK_FREE_SIZE = MAX_HANDLES * sizeof(void*);

    /** The global instance. */
    JAVOLUTION_DLL
    static FastHeap INSTANCE;

    /** The maximum number of CPUs accessing a fast heap instance simultaneously (32). */
    static const int MAX_CPU = 32; // To avoids newCount and delCount collisions.

    /** The block size in bytes. */
    static const size_t BLOCK_SIZE = sizeof(Block);

    /** Sets the number of blocks managed by this heap (should be a power of 2).*/
    JAVOLUTION_DLL
    void setSize(int size);

    /** Returns the number of blocks managed by this heap (memory usage is: size * BLOCK_MEMORY). */
    int getSize() {
    	return queueSize;
    }

    /** Returns the maximum number of blocks used simultaneously since the heap is enabled.*/
    int getMaxUsage() {
        return maxUseCount;
    }

    /** Returns the number of system heap allocations performed since the heap is enabled.*/
    Type::int64 getSystemHeapCount() {
        return systemHeapCount;
    }

    /** Allocates from buffer if size < BLOCK_SIZE. */
    inline void* allocate(size_t size) {
        if (size <= blockSize) {
            int useCount = newCount - delCount + MAX_CPU;
            if (useCount < queueSize) {
            	if (maxUseCount <= useCount) maxUseCount = ++useCount;
                return queue[++newCount & queueMask];
            } // Else heap under-sized.
        } // Else size too big.
        if (blockSize > 0)
            ++systemHeapCount; // Counts only when enabled.
        return ::operator new(size);
    }

    /** Restores to buffer if previously allocated from buffer. */
    inline void deallocate(void* mem) {
        if ((mem < bufferFirst) || (mem > bufferLast)) // Not in buffer memory.
            return ::operator delete(mem);
        queue[++delCount & queueMask] = mem;
    }

    /** Indicates if fast heap allocations are enabled (false by default). */
    Type::boolean isEnabled() {
        return (blockSize != 0);
    }

    /** Enables fast heap allocations. If the heap size is not set, a default heap size of 64 MBytes is used. */
    void enable() {
        if (blockSize != 0) // Already enabled.
            return;
        if (queueSize == 0) // Size not set.
            setSize(64 * 1024 * 1024);
        systemHeapCount = 0;
        maxUseCount = 0;
        blockSize = BLOCK_SIZE;
    }

    /** Disables buffer allocations. */
    void disable() {
        if (blockSize == 0)
            return; // Already disabled.
        blockSize = 0;
    }

    /** Delete FastHeap and associated buffers. */
    ~FastHeap() {
        delete[] buffer;
        delete[] queue;
    }

};

///////////////////////////////////////////////////////////////////////////////////////
/// Define the synchronized keyword implemented using boost mutexes.
// See http://www.codeproject.com/KB/threads/cppsyncstm.aspx
// The synchronized parameter should be an object having the monitor_()
// method implemented (e.g. collection classes).
// The synchronized macro is exception-safe, since it unlocks its mutex upon destruction.
///////////////////////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS // Use boost lightweight mutex implementation.
typedef boost::detail::lightweight_mutex Mutex;

class ScopedLock : public boost::detail::lightweight_mutex::scoped_lock {
public:

    explicit ScopedLock(Mutex& m) : boost::detail::lightweight_mutex::scoped_lock(m) {
        isLocked = true;
    }
    bool isLocked;
};
#else  // We cannot use boost lightweight mutex because non-recursive.

class ScopedLock;

class Mutex {
    friend class ScopedLock;
public:
    JAVOLUTION_DLL
    Mutex();JAVOLUTION_DLL
    ~Mutex();
private:
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
};

class ScopedLock {
public:
    JAVOLUTION_DLL
    explicit ScopedLock(Mutex& m);

    JAVOLUTION_DLL
    ~ScopedLock();

    bool isLocked;
private:
    pthread_mutex_t& mutex;
};
#endif

} // End Type::

#define synchronized(obj) for(Type::ScopedLock lock_(obj.monitor_()); lock_.isLocked; lock_.isLocked=false)


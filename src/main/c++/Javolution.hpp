/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "boost/detail/atomic_count.hpp"
#include "boost/detail/lightweight_mutex.hpp"
#include "boost/cstdint.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined __CYGWIN__
#define _WINDOWS
#define _DEPRECATED(text) __declspec(deprecated(#text))
#pragma warning(disable: 4290) //  Visual C++ does not implement checked exceptions (throw declaration ignored).
#endif

#if defined(__sun)
#define _SOLARIS
#define _DEPRECATED(text)
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
typedef boost::int8_t int8;
typedef boost::int16_t int16;
typedef boost::int32_t int32;
typedef boost::int64_t int64;
typedef boost::detail::atomic_count atomic_count;

///////////////////////////////////////////////////////////////////////////////////////
// Define Lock-free heap of fixed-size blocks. Real-time systems should ensure
// that no heap allocation exceeding the block size is ever performed in order to avoid
// non time-deterministic system heap allocations
///////////////////////////////////////////////////////////////////////////////////////

class FastHeap {

    static const size_t MAX_HANDLES = 16;
    struct Block { // Capable of holding 16 pointers (size of 64/128 bytes on 32/64 bits systems) plus reference count.
        Type::atomic_count refCount;
        void* addresses[MAX_HANDLES];
        Block() : refCount(0) {}
    };

    Type::atomic_count newCount = -1; // Number of block allocated minus one.
    Type::atomic_count delCount = -1; // Number of blocks deleted minus one.

    void** queue = nullptr; // Circular queue of memory blocks.
    size_t queueSize = 0; // Size of the queue (power of 2).
    size_t queueMask = 0; // Mask (size -1)

    Block* buffer = nullptr; // Memory buffer.
    void* bufferFirst = nullptr; // Address of first block in buffer.
    void* bufferLast = nullptr; // Address of last block in buffer.

    Type::int64 systemHeapCount = 0; // Number of system heap allocations when enabled (should be zero).
    size_t blockSize = 0; // 0 when disabled, else BLOCK_SIZE
    size_t maxUseCount = 0; // Maximum number of blocks allocated simultaneously.

public:

    /** Returns the block capacity in bytes (excluding reference count). */
    static const size_t BLOCK_CAPACITY = MAX_HANDLES * sizeof(void*);

    /** The global FastHeap instance. */
    JAVOLUTION_DLL
    static FastHeap INSTANCE;

    /** The maximum number of CPUs accessing a fast heap instance simultaneously (32). */
    static const size_t MAX_CPU = 32; // Power of 2 - Avoids newCount and delCount collisions.

    /** The fixed-block size (32 bytes). */
    static const size_t BLOCK_SIZE = sizeof(Block);

    /** Sets the heap size in bytes (e.g. 64 * 1024 * 1024 for 64 MBytes).
     *  If the specified heap size is not a power of two, an exception is thrown. */
    JAVOLUTION_DLL
    void setHeapSize(size_t sizeInBytes);

    /** Returns the maximum heap utilization in bytes (up to heap size if
     *  the heap is under-sized).*/
    size_t getHeapMaxUsage() {
        return (maxUseCount + MAX_CPU) * BLOCK_SIZE;
    }

    /** Returns the number of standard heap allocations performed
     *  while the fast heap is enabled (should be zero unless the heap is
     *  under-sized or allocations of more than 32 bytes are requested).*/
    Type::int64 getSystemHeapCount() {
        return systemHeapCount;
    }

    /** Allocates from buffer if size < BLOCK_SIZE. */
    inline void* allocate(size_t size) {
        if (size <= blockSize) {
            size_t useCount = newCount - delCount;
            if (useCount < maxUseCount)
                return queue[++newCount & queueMask];
            if (useCount + MAX_CPU < queueSize) {
                maxUseCount = useCount;
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

    /** Indicates if FastHeap is enabled. */
    Type::boolean isEnabled() {
        return (blockSize != 0);
    }

    /** Enables buffer allocations. If the heap minimum size is not set,
     *  a default minimum heap size of 64 MBytes is used. */
    void enable() {
        if (blockSize != 0)
            return; // Already enabled.
        if (queue == nullptr)
            setHeapSize(64 * 1024 * 1024);
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


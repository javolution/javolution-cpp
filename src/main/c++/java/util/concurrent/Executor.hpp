/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _JAVA_UTIL_CONCURRENT_EXECUTOR_HPP
#define _JAVA_UTIL_CONCURRENT_EXECUTOR_HPP

#include "java/lang/Object.hpp"
#include "java/lang/Runnable.hpp"

namespace java {
    namespace util {
        namespace concurrent {
            class Executor_API;
            typedef Type::Handle<Executor_API> Executor;
        }
    }
}

/**
 * This class represents object that executes submitted <code>Runnable</code>
 * tasks.
 *
 * @see  <a href="http://java.sun.com/javase/6/docs/api/java/util/concurrent/Executor.html">
 *       Java - Executor</a>
 * @version 1.6
 */
class java::util::concurrent::Executor_API : public virtual java::lang::Object_API {
public:

  /**
     * Executes the given command at some time in the future.  The command
     * may execute in a new thread, in a pooled thread, or in the calling
     * thread, at the discretion of the <code>Executor</code> implementation.
     *
     * @param command the runnable task
     * @throws RejectedExecutionException if this task cannot be
     *         accepted for execution.
     */
    virtual void execute(java::lang::Runnable const& command) = 0;

};

#endif

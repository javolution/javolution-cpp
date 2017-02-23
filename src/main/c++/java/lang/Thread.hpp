/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"
#include "java/lang/Runnable.hpp"

namespace java {
namespace lang {

/**
 * This class represents an execution thread.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Thread.html">
 *       Java - Thread</a>
 * @version 7.0
 */
class Thread: public virtual Runnable {

	JAVOLUTION_DLL
	static Type::atomic_count threadNumber; // Autonumbering anonymous threads.

public:
	class Value: public Object::Value, public virtual Runnable::Interface {
		Runnable target;
		String name;
		void* nativeThreadPtr;
	public:
		JAVOLUTION_DLL
		static thread_local Thread current;

		JAVOLUTION_DLL
		Value(const Runnable& target = nullptr, const String& name = nullptr);

		JAVOLUTION_DLL
		virtual void start();

		JAVOLUTION_DLL
		virtual void join();

		JAVOLUTION_DLL
		virtual void run() override;

		JAVOLUTION_DLL
		~Value() override;

		String getName() {
			return name;
		}

	};CTOR(Thread)

	/**
	 * Returns a thread having the specified target to be executed and the specified name.
	 */
	static Thread newInstance(const Runnable& target, const String& name = nullptr) {
		String threadName = (name != nullptr) ? name : "Thread-" + ++Thread::threadNumber;
		return new Value(target, threadName);
	}

	/**
	 * Returns a reference to the currently executing thread object.
	 */
	static Thread currentThread() {
		return Thread::Value::current;
	}

	/**
	 * Returns this thread's name.
	 */
	String getName() const {
		return this_<Value>()->getName();
	}

	/**
	 * Causes this thread to begin execution of the <code>run</code> method of
	 * this thread. It is never legal to start a thread more than once.
	 * In particular, a thread may not be restarted once it has completed
	 * execution.
	 */
	void start() {
		this_<Value>()->start();
	}

	/**
	 * Waits for this thread to die.
	 */
	void join() {
		this_<Value>()->join();
	}

	/**
	 * If this thread was constructed using a separate Runnable run object, then that Runnable object's run method is
	 * called; otherwise, this method does nothing and returns.
	 */
	void run() {
		this_<Value>()->run();
	}

	/**
	 * Causes the currently executing thread to sleep (temporarily cease execution) for the specified number of
	 * milliseconds, subject to the precision and accuracy of system timers and schedulers. The thread
	 * does not lose ownership of any monitors.
	 */
	JAVOLUTION_DLL
	static void sleep(long millis);
};

}
}

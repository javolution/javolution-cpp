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

	static const Thread MAIN; // The main thread.
	static Type::atomic_count threadNumber; // Autonumbering anonymous threads.

public:

	/** Thread Value base class. */
	class Value: public Object::Value, public virtual Runnable::Interface {
		Runnable target;
		String name;
		void* nativeThreadPtr;
	public:
		static thread_local Value* current;

		/**
		* Creates a thread having the specified target to be executed and the specified name.
		*/
		Value(const Runnable& target = nullptr, const String& name = nullptr);

		/**
		* Causes this thread to begin execution of the <code>run</code> method of
		* this thread. It is never legal to start a thread more than once.
		* In particular, a thread may not be restarted once it has completed
		* execution.
		*/
		virtual void start();

		/**
		* Waits for this thread to die.
		*/
		virtual void join();

		/**
		* If this thread was constructed using a separate Runnable run object, then that Runnable object's run method is
		* called; otherwise, this method does nothing and returns.
		*/
		virtual void run() override;

		/**
		* Returns this thread's name.
		*/
		String getName() {
			return name;
		}

		~Value() override;

	};CTOR(Thread)

	/**
	 * Returns a reference to the currently executing thread object.
	 */
	static const Thread currentThread() {
	    return Thread::Value::current != nullptr ? Thread::Value::current : Thread::MAIN;
	}

	/**
	* Causes the currently executing thread to sleep (temporarily cease execution) for the specified number of
	* milliseconds, subject to the precision and accuracy of system timers and schedulers. The thread
	* does not lose ownership of any monitors.
	*
	* @throw IllegalArgumentException if the value of msec is negative
	*/
	static void sleep(long msec);

	// Convenience methods.

	String getName() const {
		return this_<Value>()->getName();
	}

	void start() {
		this_<Value>()->start();
	}

	void join() {
		this_<Value>()->join();
	}

	void run() {
		this_<Value>()->run();
	}

};

}
}

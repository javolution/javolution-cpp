/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"

namespace java {
namespace lang {

/**
 * This class represents a class instances. They can be used to perform static synchronized operations
 * (synchronization on the whole class).
 * <pre><code>
 * class Foo : public Object {
 *     static const Class CLASS; // Class::forName("org::acme::Foo") in compilation body (.cpp)
 *     static Foo getInstance(String id) {
 *         synchronized (CLASS) { // Equivalent to "static synchronized"
 *             ...
 *         }
 *     }
 * };</code></pre>
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Class.html">
 *       Java - Class</a>
 * @version 1.1
 */
class Class final : public virtual Object {
public:
	class Value: public Object::Value {
		friend class Class;
		String name;
		Type::Mutex monitor;
		Value(const String& name) :
				name(name) {
		}
	public:

		String getName() const {
			return name;
		}

		bool equals(const Object& other) const override {
			if (this == other)
				return true;
			Class that = other.cast_<Value>();
			return equals(that);
		}

		bool equals(const Class& that) const {
			if (that == nullptr)
				return false;
			return name.equals(that.getName());
		}

		int hashCode() const override {
			return name.hashCode();
		}

		String toString() const override {
			return String::valueOf("Class ") + getName();
		}

		Type::Mutex& monitor_() const override {
			return const_cast<Type::Mutex&>(monitor);
		}

	};CTOR(Class)

	/** Returns the class having the specified name. */
	static Class forName(const String& name) {
		return new Value(name);
	}

	/** Returns the class name of this instance (for example "java::lang::Boolean"). */
	String getName() const {
		return this_<Value>()->getName();
	}

};

}
}

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Object.hpp"

namespace java {
namespace lang {

/**
 * This class interface should be implemented by any class whose instances are intended to be executed by a thread.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Runnable.html">
 *       Java - Runnable</a>
 * @version 7.0
 */
class Runnable: public virtual Object {
public:
    Runnable(Void = nullptr) {}

    /**
     * When an object implementing interface Runnable is used to create a thread, starting the thread causes
     * the object's run method to be called in that separately executing thread.
     */
    void run() {
        this_cast<Interface>()->run();
    }

    class Interface: public virtual Object::Interface {
    public:
        virtual void run() = 0;
    };

};

}
}

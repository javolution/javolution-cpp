## Javolution C++
#### The C++ Solution for Real-Time and Embedded Systems
##### Because real-time programming requires a time-predictable standard library.

>        "It looks like Java, it tastes likes Java... but it is C++"

### Javolution C++ - All the benefits of Javolution for C++ developpers.

Java is fast, very fast, but Javolution C++, can make your Java code even faster!

- **High-Performance** 
    - With Javolution small immutable objects (such as Boolean, Char, Integer, Double) are allocated on the stack instead of the heap leading to around 10x performance improvement according to our tests (see javolution-cpp-test github project). 
    - All Java parameterized classes (e.g. collections/maps) are true C++ templates (no syntactic sugar).
    - Javolution C++ supports natively the latest Java 8 feature such as lambda expressions (see examples below). 
    - Javolution does not need a garbage collector, memory management is done internally through smart pointers ("polluter pays principle" applied to threads).
    - For hard real-time applications, a lock-free / fixed-size memory allocator (Type::FastHeap) can be enabled (no system call if the heap is correctly sized).

- **Real-Time** - Since Javolution C++ is a port of Javolution Real-Time classes, it exhibits the same "real-time" characteristics (even better since there is no jitter caused by JIT compilation, class loading/initialization or heap allocations).

- **Easy** - Someone not knowledgeable in C++ but familiar with Java can quickly start developing complex applications in C++. About 90 % of Javolution C++ source code is common with Java. 

- **OSGi** - An open-source implementation of OSGi has been partially ported from Java to C++ and is included in the library.

- **JUnit** - JUnit has also been ported (see GitHub javolution/javolution-cpp-test for usage), the port took less than one day !

- **Maven-Based** - Javolution C++ can be used through Maven (available from Maven central).

- **Portable** - Any application based on Javolution C++ can be compiled without modification on Linux POSIX and Visual C++ (as long as the compiler supports most common C++11 features). 

- **Free** - JVM licensing for embedded systems can be problematic and expensive. It is not the case for Javolution which is free and always will be (MIT license). 
  
For consistency and maintainability we follow the Java Style (http://geosoft.no/development/javastyle.html).

```cpp
String str = "Hello"; 
StringBuilder sb = new StringBuilder::Value(); // Operator 'new' is performed on the Value type. 
sb.append("Hell").append('o');
Object obj = sb.toString();                       
assert(obj.equals(str));
assert(str.equals(obj));

E get(int i) {
    if (i >= length) throw IndexOutOfRangeException(); // Throws by value (no 'new'), but caught by reference (&).
    return data[i];
}

void Thread::run() {
    try {
        if (target != nullptr) target.run(); 
    } catch (Throwable& e) { // Catch all instances derived from Throwable.
        System::err.println(e);
    }
}

class Runnable : public virtual Object { // Java-like type (pointer).
public:
    class Interface : public virtual Object::Interface { // The actual interface (abstract)
    public:
        virtual void run() = 0;    
    }; 
    CTOR(Runnable, Interface)
    void run() { this_cast_<Interface>()->run(); } // Default implementation (dynamic cast)
};
``` 

Parameters to constructors/functions are usually passed as 'const' references (const Object&) and functions results are returned by value.
 
```cpp
#pragma once 
#include "java/lang/String.hpp" // Import.

namespace org { namespace acme { // Package org::acme

class Foo : public virtual Runnable { // Pointer type.
public:
    class Value : public Object::Value, public virtual Runnable::Interface  {  // Value type (hold method description/contract)
 
        Runnable action;
        String message;
 
    public:
    
        Value(const Runnable& action = nullptr, const String& message = nullptr) 
        : action(action), message(message) {}         
    
        virtual void setMessage(const String& msg) { 
            message = msg;
        }

        virtual void run() override {
            if (message != nullptr) System::out.println(message);
            if (action != nullptr) action.run();
        }
    };
    
    CTOR(Foo, Value) // Foo constructors (from nullptr and Value*)
        
    // Exported Value methods.
        
    void setMessage(const String& value) {  
        this_<Value>()->setMessage(value);
    }
    
    void run() {  // Optional (inherited from Runnable), here to avoid dynamic cast.
        this_<Value>()->run();
    }
}; 

}}
``` 
Here are some illustrative snippets of C++ source code

```cpp
Foo foo = new Foo::Value(); // Default parameters supported.
foo.setMessage("Hello");
foo.run(); // Prints "Hello"

bool equals(const Object& other) const override {
    if (this == other) return true;
    Foo that = other.cast_<Foo::Value>(); // null if invalid cast (C++)
    return equals(that);
}

bool equals(const Foo& that) const {
    if (that == nullptr) return false;
     return (message == nullptr) ? (that.message == nullptr) : message.equals(that.message);
} 

List<String> list = FastTable<String>::newTable(); 
list.add("first");                                  
list.add("second");
list.add("third");
list.add(nullptr);
list.forEach([](const String& name) { System::out.println(name);}) // Lambda expression.
``` 

### Usage

The simplest way to use the Javolution C++ static library is through Maven with the native plugin (http://www.mojohaus.org/maven-native/native-maven-plugin/) with the following dependencies in your pom.xml (see javolution-cpp-test project for an example how to build an executable). Windows (Visual C++) and Linux (gcc) compilations will be supported with no change in your code (write once, run everywhere principle).

```
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>javolution</artifactId>
            <version>7.0.0</version>
            <type>inczip</type>  <!-- Headers (.hpp) compilation dependency -->
        </dependency>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>javolution</artifactId>
            <version>7.0.0</version>
            <type>lib</type> <!-- Static library dependency -->
            <classifier>${native.classifier}</classifier> <!-- linux, win32, win64 -->
        </dependency>
```

In order to guarantee worst case execution time and internal heap memory (managed by Javolution) can be enabled during bundle activation and the maximum heap usage can be shown at deactivation. Small immutable objects (such as java::lang::Boolean, java::lang::Char, java::lang::Integer, etc.) are manipulated by value (value-types) and don't use the heap.

```cpp
int main(int, char**) {
    
    OSGi osgi = new OSGi::Value();
    
    JavolutionActivator javolution = new JavolutionActivator::Value();
    javolution.setHeapSize(256 * 1024 * 1024); // 256 MBytes
    osgi.start(javolution);
    
    ... // Starts others bundles 
    
    try {
        ... // Run main
    } catch (Throwable& error) {
        error.printStackTrace();
    }
    
    ... // Stops others bundles.
    
    LogContext::info("Maximum Heap Usage (bytes): ", javolution.getMaximumHeapUsage());
    osgi.stop(javolution);
    
}
```

### Links

- Website: http://javolution.org

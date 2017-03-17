## Javolution C++
#### The C++ Solution for Real-Time and Embedded Systems
##### Because real-time programming requires a time-predictable standard library.

>        "It looks like Java, it tastes likes Java... but it is C++"

### Javolution C++ - All the benefits of Javolution for C++ developpers.

Java is fast, very fast, but Javolution C++ can make it even faster!

- **High-Performance** 
    - With Javolution small immutable objects (e.g. Integer, Double) are allocated on the stack (10-15x speed improvement). 
    - Parameterized classes (e.g. collections/maps) are "true" C++ templates (not syntactic sugar).
    - Provides native support for latest Java 8 features such as lambda expressions. 
    - No garbage collector, memory management is done through smart pointers (reference counting).
    - For hard real-time applications, a lock-free / jitter-free memory allocator (Type::FastHeap) is provided.

- **Real-Time** - Javolution C++ is a port of Javolution Real-Time classes, it exhibits the same "real-time" characteristics, even better since there is no jitter caused by JIT compilation, class loading/initialization or garbage collection.

- **Easy** - About 90% of your source code will be identical to Java code (syntactically and library wise). Someone not knowledgeable in C++ but familiar with Java can quickly start developing complex applications in C++.

- **Safe** - Only a very limited sub-set of C++ should be used (the "java-like" part), reducing the C++ pitfalls to fall into.

- **Java Reuse** - Existing Java code can be ported quickly (since 90% of the code stays the same); JUnit and OSGi have been ported in a few days and are now included with the library.

- **Maven-Based** - Javolution C++ can be used through Maven (available from Maven central).

- **Portable** - Application based on Javolution C++ can be compiled without modification on Linux POSIX and Visual C++ (as long as the compiler supports C++11 features). 

- **Free** - JVM licensing for embedded and real-time systems can be problematic and expensive. It is not the case for Javolution which is free and always will be (MIT license). 
  
For consistency and maintainability we recommend following the Java Style (http://geosoft.no/development/javastyle.html).

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
    class Value : public Object::Value, public virtual Runnable::Interface  {  // Value type (holds member methods)
 
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
        
    // Exported Public Methods.
    void setMessage(const String& value) {  this_<Value>()->setMessage(value); }    
    void run() { this_<Value>()->run(); } // Optional (inherited from Runnable).
}; 

}}
``` 
Here are some illustrative snippets of C++ source code

```cpp
Foo foo = new Foo::Value(); // Default parameters are supported.
foo.setMessage("Hello");
foo.run(); // Prints "Hello"

bool equals(const Object& other) const override {
    if (this == other) return true;
    Foo that = other.cast_<Foo::Value>(); // null if invalid cast (C++ specific)
    return equals(that);
}

bool equals(const Foo& that) const {
    if (that == nullptr) return false;
     return (message == nullptr) ? (that.message == nullptr) : message.equals(that.message);
} 

List<String> list = FastTable<String>::newTable(); // Factory method. 
list.add("first");                                  
list.add("second");
list.add("third");
list.add(nullptr); // null value supported.
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

In order to reduce potential jitter Type::FastHeap can be enabled during bundle activation and the maximum heap usage can be shown at deactivation. Small immutable objects (such as java::lang::Boolean, java::lang::Char, java::lang::Integer, etc.) are manipulated by value (value-types) and don't use the heap.

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

## Javolution C++
#### The C++ Solution for Real-Time and Embedded Systems
##### Because real-time programming requires a time-predictable standard library.

>        "It looks like Java, it tastes likes Java... but it is C++"

### Javolution C++ - All the benefits of Javolution for C++ developpers.

Java is fast, very fast, but Javolution C++, can make your Java code even faster!

- **High-Performance** 
    - With Javolution small immutable objects (such as Boolean, Char, Integer, Double) are allocated on the stack instead of the heap (they are manipulated by value). 
    - All Java parameterized classes (e.g. collections/maps) are true C++ templates (no syntactic sugar). 
    - Javolution does not need a garbage collector, memory management is done internally by smart pointers through reference counting.
    - Javolution uses a lock-free / fixed-size memory allocator (Type::FastHeap) which if correctly sized allows your application to run significantly faster (5-10x) without jitter.

- **Real-Time** - Since Javolution C++ is a port of Javolution Real-Time classes, it exhibits the same real-time characteristics (even better since there is no jitter caused by JIT compilation, class loading/initialization or heap allocations).

- **Easy** - Someone not knowledgeable in C++ but familiar with Java can quickly start developing complex applications in C++ The conversion of Java code to C++ is straightforward and can be done automatically using javolution/javaToCpp (soon available on GitHub).

- **OSGi** - An open-source implementation of OSGi has been partially ported from Java to C++ and is included in the library.

- **JUnit** - JUnit has also been ported (see GitHub javolution/javolution-cpp-test for usage).

- **Maven-Based** - Javolution C++ can be used through Maven (available from Maven central).

- **Portable** - Any application based on Javolution C++ can be compiled without modification on Linux POSIX and Visual C++ (as long as the compiler supports most common C++11 features).

- **Free** - JVM licensing for embedded systems can be problematic and expensive. It is not the case for Javolution which is free and always will be (MIT license). 
  
For consistency and maintainability we follow the Java Style (http://geosoft.no/development/javastyle.html).

```cpp
String str = "Hello"; 
StringBuilder sb = new StringBuilder::Value(); 
sb.append("Hell").append('o');
Object obj = sb.toString();                       
assert(obj.equals(str));
assert(str.equals(obj));

E get(int i) {
    if (i >= length) throw IndexOutOfRangeException(); // Throws by value, but caught by reference (&).
    return data[i];
}

void Thread::run() {
    try {
        if (target != nullptr) target.run(); 
    } catch (Throwable& e) { // Catch all instances derived from Throwable.
        System::err.println(e);
    }
}

class Runnable : public virtual Object { // Java-like type (sub-type of Object).
public:
    class Interface : public virtual Object::Interface { // The actual interface (abstract)
    public:
        virtual void run() = 0;    
    }; 
    Runnable(Void = nullptr) {} // Default constructor (null) 
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
    class Value : public Object::Value, public virtual Runnable::Interface  {  // Value type.
 
        Runnable action;
        String message;
 
    public:
    
        Value(const Runnable& a = nullptr, const String& m = nullptr) 
        : action(a), message(m) {}         
    
        virtual void setMessage(const String& msg) { 
            message = msg;
        }

        virtual void run() override {
            if (message != nullptr) System::out.println(message);
            if (action != nullptr) action.run();
        }
    };
    
    CTOR(Foo) // Foo constructors (for null and Value*).
        
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
    Foo that = other.cast_<Foo::Value>(); // null if invalid cast.
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
System::out.println(list); //  [first, second, third, null]
``` 

### Usage

The simplest way to use the Javolution C++ static library is through Maven with the native plugin (http://www.mojohaus.org/maven-native/native-maven-plugin/) with the following dependencies (for an example of pom.xml to build an executable check out the javolution-cpp-test project).
Two popular platforms are supported: Windows (Visual C++) and Linux (gcc).

```
    <dependencies>
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

In order to guarantee the worst case execution time, the size of the internal heap memory (managed by Javolution) can be set during bundle activation and the maximum heap usage can be shown at deactivation. Small immutable objects (such as java::lang::Boolean, java::lang::Char, java::lang::Integer, etc.) are manipulated by value (value-types) and don't use the heap.

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

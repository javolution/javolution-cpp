## Javolution C++
#### The C++ Solution for Real-Time and Embedded Systems
##### Because real-time programming requires a time-predictable standard library.

>        "It looks like Java, it tastes likes Java... but it is C++"

### Javolution C++ - All the benefits of Javolution for C++ developpers.

Java is fast, very fast, but Javolution C++, can make your Java code even faster!

- **High-Performance** 
    - With Javolution small immutable objects (such as Boolean, Char, Integer, Double) are allocated on the stack instead of the heap (they are manipulated by value). 
    - All Java parameterized classes (e.g. collections/maps) are true C++ templates (no syntactic sugar). 
    - Javolution does not need a garbage collector, memory management is done by the objects themselves through reference counting.

- **Real-Time** - Since Javolution C++ is a port of Javolution Real-Time classes, it exhibits the same real-time characteristics (even better since there is no jitter caused by JIT or class loading/initialization).

- **Easy** - Someone not knowledgeable in C++ but familiar with Java can quickly start developing complex applications in C++ The conversion of Java code to C++ is straightforward and can be done automatically using javolution/javaToCpp (soon available on GitHub).

- **OSGi** - An open-source implementation of OSGi has been partially ported from Java to C++ and is included in the library.

- **JUnit** - JUnit has also been ported (see GitHub javolution/javalution-cpp-test for usage).

- **Maven-Based** - Javolution C++ can be used through Maven (available from Maven central).

- **Portable** - Any application based on Javolution C++ will run identically on Linux POSIX, Solaris and Window Visual C++

- **Free** - JVM licensing for embedded systems can be problematic and expensive. It is not the case for Javolution which is free and always will be (MIT license). 
  
Here is an example of header class (org/acme/Foo.hpp) based on Javolution C++ showing the strong similarities with Java
  
```cpp
#ifndef _ORG_ACME_FOO_HPP
#define _ORG_ACME_FOO_HPP

#include "java/lang/Object.hpp" // Same as Java import
#include "java/lang/String.hpp"

namespace org { namespace acme { // Same as Java package.

/* The class Foo_Type is the actual Foo type (not a pointer), it specifies the instance members. */
class Foo_Type : public virtual java::lang::Object_Type { 
    java::lang::String msg;
public:
    Foo_Type(const java::lang::String& msg) : msg(msg) {} // Read-only parameters passed as const references.
    void set(const java::lang::String& msg) {
        this->msg = msg;                                  // . replaced by ->
    }
    virtual java::lang::String toString() const override { 
        return msg;
    }
};

/** Foo is a pointer (smart pointer) on a Foo_Type instance, e.g. Foo foo = new Foo_Type("Hello")
    It there are static members, they will be defined in the Foo class. */
typedef Type::Handle<Foo_Type> Foo; // No static members, a typedef works fine.

}}
#endif
``` 
Here are some illustrative snippets of C++ source code
```cpp
Type::boolean equals(const Object& obj) const override { 
    Foo that = Type::handle_cast<Foo_Type>(obj); // Unlike Java, invalid cast returns null 
    if (that == Type::Null) return false;        // instead of raising an exception. 
     return equals(that);
}

Type::boolean equals(const Foo& that) const {
    return this->msg->equals(that->msg);
} 

List<String> list = FastTable<String>::newTable(); // Automatic upcasting.
list->add("first");
list->add("second");
list->add("third");
list->add(Type::Null);
System::out->println(list); //  [first, second, third, null]

``` 
### Usage

The simplest way to use Javolution C++ is through Maven with the native plugin (http://www.mojohaus.org/maven-native/native-maven-plugin/) and the following dependencies in your pom.xml (for a pom.xml example you may look at the javolution-cpp-test repository).
Three major platforms are supported: Windows (Visual C++), Linux (gcc) and Solaris (CC).

```
    <dependencies>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>libjavolution</artifactId>
            <version>1.0.0</version>
            <type>inczip</type>  <!-- Headers (.hpp) compilation dependency -->
        </dependency>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>libjavolution</artifactId>
            <version>1.0.0</version>
            <type>${compile.dependency.type}</type> <!-- Linked library dependency (.lib on Windows) -->
            <classifier>${compile.dependency.classifier}</classifier>
        </dependency>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>libjavolution</artifactId>
            <version>1.0.0</version>
            <type>${runtime.dependency.type}</type> <!-- Runtime dependency (.dll on Windows) -->
            <classifier>${runtime.dependency.classifier}</classifier>
        </dependency>
```

In order to guarantee the worst case execution time, the size of the heap memory used by classes derived from  java::lang::Object_Type can be set during bundle activation. 
Small immutable objects (such as java::lang::Boolean, java::lang::Char, java::lang::Integer, etc.) are manipulated by value and don't use the heap.

```cpp
int main(int, char**) {
    
    OSGi osgi = new OSGi_Type();
    
    Activator javolutionActivator = new JavolutionActivator_Type();
    javolutionActivator->setHeapSize(256 * 1024 * 1024); // 256 MBytes
    osgi->start("Javolution", javolutionActivator);
    
    ... // Starts others bundles 
    
    try {
        ... // Run main
    } catch (java::lang::Throwable& error) {
        System::err->println(error);
        error->printStackTrace();
    }
    
    ... // Stops others bundles.
    
    osgi->stop("Javolution"); // Will log the maximum heap usage.
    
}
```

### Links

- Website: http://javolution.org

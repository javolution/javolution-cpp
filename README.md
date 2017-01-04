## Javolution C++
#### The C++ Solution for Real-Time and Embedded Systems
##### Because real-time programming requires a time-predictable standard library.

>        "It looks like Java, it tastes likes Java... but it is C++"

### Javolution C++ - All the benefits of Javolution for C++ developpers.

Javolution C++ makes it easy for developper to reuse / port any existing Java code.
It includes a port of standard Java classes (java.lang/java.util), OSGi (org.osgi) and JUnit (junit.framework). Garbage collection is done through reference counting (smart pointers).
The syntax is very close to the Java syntax (see Javolution source code). 
Here is a typical C++ header class (org/acme/Foo.hpp) using the Javolution framework.
  
```cpp
#ifndef _ORG_ACME_FOO_HPP
#define _ORG_ACME_FOO_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"

namespace org { namespace acme { // Package

class Foo_Type : public virtual java::lang::Object_Type { // 'virtual' used for Object_Type and interfaces.
    java::lang::String msg;
public:
    Foo_Type(const java::lang::String& msg) : msg(msg) {} // Read-only parameters passed as const references.
    void set(const java::lang::String& msg) {
        this->msg = msg;
    }
    virtual java::lang::String toString() const override { 
        return msg;
    }
};
typedef Type::Handle<Foo_Type> Foo; // Smart pointer, e.g. Foo foo = new Foo_Type("Hello")
}}
#endif
``` 
Here are some illustrative snippets of C++ source code
```cpp
// Allows chaining, e.g. sb->append("Duration: ")->append(t)->append("ms")
StringBuilder StringBuilder_Type::append(...) {
    ...
    return this; // Implicit conversion from StringBuilder_Type* to StringBuilder.
}

Type::boolean equals(const Object& obj) const override { 
    Foo that = Type::dynamic_handle_cast<Foo_Type>(obj); // Unlike Java, invalid cast returns null 
    if (that == Type::Null) return false;                // instead of raising an exception. 
     return equals(that);
}

Type::boolean equals(const Foo& that) const {
    return this->msg->equals(that->msg);
} 

List<String> list = FastTable<String>::newTable();
list->add("first");
list->add("second");
list->add("third");
list->add(Type::Null);
std::cout << list << std::endl; //  [first, second, third, null]

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

In order to guarantee the worst case execution time, the size of the heap memory used by  
Java-Like Objects (derived from java::lang::Object_Type) can be set during bundle activation.

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
        std::wcerr << error << std::endl;
        error->printStackTrace();
    }
    
    ... // Stops others bundles.
    
    osgi->stop("Javolution"); // Will log the maximum heap usage.
    
}
```

### Links

- Website: http://javolution.org

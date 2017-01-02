## Javolution C++
#### The C++ Solution for Real-Time and Embedded Systems
##### Because real-time programming requires a time-predictable standard library.

>        "It looks like Java, it tastes likes Java... but it is C++"

### Javolution C++ - All the benefits of Javolution for C++ developpers.

Javolution C++ makes it easy for developper to reuse / port any existing Java code.
It includes a port of standard Java classes (java.lang/java.util), OSGi (org.osgi) and JUnit (junit.framework). Garbage collection is done through reference counting (smart pointers).
Its syntax is very close to the Java syntax (more info in the Wiki).
Here is a typical C++ header class (org/acme/Foo.hpp) using the Javolution framework.
  
```cpp
#ifndef _ORG_ACME_FOO_HPP
#define _ORG_ACME_FOO_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"

namespace org { namespace acme { // Package
class Foo_API : public virtual java::lang::Object_API { // virtual used only for Object_API and Interfaces (multiple inheritance)
    java::lang::String msg;
public:
    Foo_API(const java::lang::String& msg) : msg(msg) {} // Read-only parameters are passed as const reference (optimization) 
    void set(const java::lang::String& msg) {
        this->msg = msg;
    }
    virtual java::lang::String toString() const { // virtual not necessary if class final (e.g. private constructor)
        return msg;
    }
};
typedef Type::Handle<Foo_API> Foo; // Smart pointer, e.g. Foo foo = new Foo_API("Hello")
}}
#endif
``` 
Here are some illustrative snippets of C++ source code
```cpp
 // Allows chaining, e.g. sb->append("Duration: ")->append(t)->append("ms")
 StringBuilder StringBuilder_API::append(...) {
    ...
    return this; // Implicit conversion from StringBuilder_API* to StringBuilder.
 }

Type::boolean equals(const Object& obj) const { 
    Foo that = Type::dynamic_handle_cast<Foo_API>(obj); // Unlike Java, invalid cast returns null instead of raising an exception. 
    if (that == Type::Null) return false;
     return equals(that);
}
Type::boolean equals(const Foo& that) const { ... } 

List<String> list = FastTable<String>::newTable(); 
list->add("first");
list->add("second");
list->add("third");
list->add(Type::Null);
std::cout << list << std::endl; //  [first, second, third, null]

``` 
### Usage
The simplest way to use Javolution C++ is through Maven with the native plugin and the following dependency in your POM.xml (for a pom.xml example you may look at the javolution-cpp-test repository)

```
    <dependencies>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>libjavolution</artifactId>
            <version>7.0.0</version>
            <type>inczip</type>
        </dependency>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>libjavolution</artifactId>
            <version>7.0.0</version>
            <type>${compile.dependency.type}</type>
            <classifier>${compile.dependency.classifier}</classifier>
        </dependency>
        <dependency>
            <groupId>org.javolution</groupId>
            <artifactId>libjavolution</artifactId>
            <version>${project.version}</version>
            <type>${runtime.dependency.type}</type>
            <classifier>${runtime.dependency.classifier}</classifier>
        </dependency>
```

### Links

- Website: http://javolution.org

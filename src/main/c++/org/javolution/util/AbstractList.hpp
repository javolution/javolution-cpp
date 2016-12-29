/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#ifndef _ORG_JAVOLUTION_UTIL_ABSTRACT_LIST_HPP
#define _ORG_JAVOLUTION_UTIL_ABSTRACT_LIST_HPP

#include "org/javolution/util/AbstractCollection.hpp"
#include "java/util/List.hpp"

namespace org { namespace javolution { namespace util {
        template<class E>class AbstractList_API;

        // Defines AbstractList<E> handler alias.
        template<class E> class AbstractList : public Type::Handle<AbstractList_API<E> > {
        public:
            AbstractList(Type::NullHandle = Type::Null) : Type::Handle<AbstractList_API<E> >() {} // Null
            template<class Y> AbstractList(Type::Handle<Y> const & r) : Type::Handle<AbstractList_API<E> >(r) {}
            AbstractList(AbstractList_API<E>* ptr) : Type::Handle<AbstractList_API<E> >(ptr) {}
        };
}}}

/**
 * This class provides a skeletal implementation of the List interface to minimize
 * the effort required to implement this interface backed by a "random access"
 * data store (such as an array). For sequential access data (such as a linked list),
 *  AbstractSequentialList should be used in preference to this class.
 *
 * @see  <a href="http://java.sun.com/javase/6/docs/api/java/util/AbstractList.html">
 *       Java - AbstractList</a>
 * @version 1.0
 */
template<class E>
class org::javolution::util::AbstractList_API : public org::javolution::util::AbstractCollection_API<E>, public virtual java::util::List_API<E> {
protected:

    /**
     * Default constructor.
     */
    AbstractList_API() {
    };

public:

    // Methods from List hidden by current methods should be 'unhidden' 
    using java::util::List_API<E>::add; // add(Type::int32, E) hidden.
    using java::util::List_API<E>::addAll; // addAll(Type::int32, Collection) hidden
    using java::util::List_API<E>::remove; // remove(Type::int32) hidden.


    // Overrides methods common to AbstractCollection and List to remove ambiguity.
    // (e.g. Visual C++ Warning C4250)

    virtual Type::boolean add(E const& element) {
         return AbstractCollection_API<E>::add(element);
    }

    virtual Type::boolean addAll(java::util::Collection<E> const& c) {
        return AbstractCollection_API<E>::addAll(c);
    }

    virtual void clear() {
        AbstractCollection_API<E>::clear();
    }

    virtual Type::boolean contains(E const& value) const {
        return AbstractCollection_API<E>::contains(value);
    }

    virtual Type::boolean containsAll(java::util::Collection<E> const& c) const {
        return AbstractCollection_API<E>::containsAll(c);
    }

    virtual Type::boolean isEmpty() const {
        return AbstractCollection_API<E>::isEmpty();
    }

    virtual java::util::Iterator<E> iterator() const {
        return AbstractCollection_API<E>::iterator();
    }

    virtual Type::boolean remove(E const& element) {
        return AbstractCollection_API<E>::remove(element);
    }
    
    virtual Type::boolean removeAll(java::util::Collection<E> const& c) {
        return AbstractCollection_API<E>::removeAll(c);
    }

    virtual Type::boolean retainAll(java::util::Collection<E> const& c) {
        return AbstractCollection_API<E>::retainAll(c);
    }

    virtual Type::int32 size() const {
        return AbstractCollection_API<E>::size();
    }

    virtual Type::Array<java::lang::Object> toArray() const {
        return AbstractCollection_API<E>::toArray();
    }

    virtual Type::Array<E> toArray(Type::Array<E> const& result) const {
        return AbstractCollection_API<E>:: toArray(result);
    }

    virtual Type::boolean equals(java::lang::Object const& obj) const {
        return AbstractCollection_API<E>::equals(obj);
    }

    virtual Type::int32 hashCode() const {
        return AbstractCollection_API<E>::hashCode();
    }

    virtual java::lang::String toString() const {
        return AbstractCollection_API<E>::toString();
    }
};

#endif

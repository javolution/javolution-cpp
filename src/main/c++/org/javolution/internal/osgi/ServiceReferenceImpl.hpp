/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _ORG_JAVOLUTION_INTERNAL_OSGI_SERVICE_REFERENCE_IMPL_HPP
#define _ORG_JAVOLUTION_INTERNAL_OSGI_SERVICE_REFERENCE_IMPL_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/StringBuilder.hpp"
#include "org/osgi/framework/Bundle.hpp"
#include "org/osgi/framework/ServiceReference.hpp"

namespace org { namespace javolution { namespace internal { namespace osgi {
    class ServiceReferenceImpl_API;
    typedef Type::Handle<ServiceReferenceImpl_API> ServiceReferenceImpl;
}}}}

using namespace java::lang;
using namespace org::javolution::util;
using namespace org::javolution::internal::osgi;
using namespace org::osgi::framework;

/**
 * Service reference implementation (value type).
 *
 * @version 1.0
 */
class org::javolution::internal::osgi::ServiceReferenceImpl_API : public virtual ServiceReference_API {
public: // Internal classes can have public members visibility.

    Bundle _bundle;
    String _serviceName;
    Object _service;

    ServiceReferenceImpl_API(Bundle const& bundle, String const& serviceName, Object const& service) {
        _bundle = bundle;
        _serviceName = serviceName;
        _service = service;
    }

    Bundle getBundle() const {
        return _bundle;
    }

    // Overrides.
    String toString() const {
        return StringBuilder_API::newInstance()
                ->append("Service ")->append(_serviceName)
                ->append(" from ")->append(_bundle)->toString();
    }
};
#endif

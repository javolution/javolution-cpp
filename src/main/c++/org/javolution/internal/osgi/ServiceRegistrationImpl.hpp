/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _ORG_JAVOLUTION_INTERNAL_OSGI_SERVICE_REGISTRATION_IMPL_HPP
#define _ORG_JAVOLUTION_INTERNAL_OSGI_SERVICE_REGISTRATION_IMPL_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "org/osgi/framework/BundleContext.hpp"
#include "org/osgi/framework/Constants.hpp"
#include "org/osgi/framework/ServiceRegistration.hpp"
#include "org/javolution/internal/osgi/BundleImpl.hpp"
#include "org/javolution/internal/osgi/ServiceReferenceImpl.hpp"

using namespace java::lang;
using namespace org::javolution::util;
using namespace org::javolution::internal::osgi;
using namespace org::osgi::framework;

namespace org { namespace javolution { namespace internal { namespace osgi {
    class ServiceRegistrationImpl_API;
    typedef Type::Handle<ServiceRegistrationImpl_API> ServiceRegistrationImpl;
}}}}

/**
 * Service registration implementation (value type).
 *
 * @version 1.0
 */
class org::javolution::internal::osgi::ServiceRegistrationImpl_API : public virtual ServiceRegistration_API {
public: // Internal classes can have public members visibility.

	ServiceReferenceImpl _serviceReference;

    ServiceRegistrationImpl_API(ServiceReferenceImpl const& serviceReference) {
        _serviceReference = serviceReference;
    }

    ServiceReference getReference() const {
        return _serviceReference;
    }

    void unregister() {
        // Fire event to listeners from all bundles.
        ServiceEvent serviceEvent = new ServiceEvent_API(ServiceEvent_API::UNREGISTERING, _serviceReference);
        Type::dynamic_handle_cast<BundleImpl_API>(_serviceReference->_bundle)->_osgi->fireServiceEvent(serviceEvent);
        Type::dynamic_handle_cast<BundleImpl_API>(_serviceReference->_bundle)->_serviceReferences->remove(_serviceReference);
        _serviceReference->_bundle = Type::Null; // No more active.
    }

};
#endif

/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _ORG_JAVOLUTION_INTERNAL_OSGI_OSGI_IMPL_HPP
#define _ORG_JAVOLUTION_INTERNAL_OSGI_OSGI_IMPL_HPP

#include "org/javolution/util/FastTable.hpp"
#include "org/osgi/framework/ServiceEvent.hpp"
#include "org/osgi/framework/BundleActivator.hpp"
#include "org/osgi/framework/Bundle.hpp"
#include "org/osgi/framework/ServiceListener.hpp"
#include "org/javolution/osgi/OSGi.hpp"

namespace org { namespace javolution { namespace internal { namespace osgi {
    class OSGiImpl_API;
    typedef Type::Handle<OSGiImpl_API> OSGiImpl;
}}}}

/**
 * This class represents the OSGi framework.
 *
 * @version 1.0
 */
class org::javolution::internal::osgi::OSGiImpl_API : public org::javolution::osgi::OSGi_API {
public: // Internal classes can have public members visibility.

   /**
    * Holds all known bundle.
    */
   org::javolution::util::FastTable<org::osgi::framework::Bundle> _bundles;

    /**
     * Creates a new instance.
     */
    OSGiImpl_API() {
        _bundles = new org::javolution::util::FastTable_API<org::osgi::framework::Bundle>();
    }

    // Override
    JAVOLUTION_DLL void start(java::lang::String const& symbolicName, org::osgi::framework::BundleActivator const& activator);

    // Override
    JAVOLUTION_DLL void stop(java::lang::String const& symbolicName);

    // Override
    JAVOLUTION_DLL org::osgi::framework::Bundle getBundle(java::lang::String const& symbolicName) const;

    /**
     * Fires the specified service event (affect all bundles).
     */
    JAVOLUTION_DLL void fireServiceEvent(org::osgi::framework::ServiceEvent const& serviceEvent);

};
#endif

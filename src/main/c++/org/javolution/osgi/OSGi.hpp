/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _ORG_JAVOLUTION_OSGI_OSGI_HPP
#define _ORG_JAVOLUTION_OSGI_OSGI_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "org/osgi/framework/Bundle.hpp"
#include "org/osgi/framework/BundleActivator.hpp"

namespace org { namespace javolution { namespace osgi { 
        class OSGi_API;
        typedef Type::Handle<OSGi_API> OSGi;
}}}

/**
 * This abstract class represents the OSGi framework.
 *
 * The standard convention (http://wiki.eclipse.org/Naming_Conventions) is
 * for all classes not in the org::foo::<component>::internal to
 * be exported. Internal header files should not be included in a public header
 * (they can only be included in the C++ body). Internal header files are not
 * made available outside of the bundle (they are not in the .inczip of the bundle).
 *
 * The activator of a  bundle is usually:
 * org::foo::<component>::osgi::<COMPONENT>Activator
 *
 * @version 1.3
 */
class org::javolution::osgi::OSGi_API : public virtual java::lang::Object_API {
public:

    /**
     * Creates a new OSGi instance.
     */
    JAVOLUTION_DLL static OSGi newInstance();

    /**
     * Starts the bundle having the specified identifier.
     *
     * @param id the bundle identifier.
     * @param  activator the bundle activator instance.
     */
   virtual void start(java::lang::String const& symbolicName, org::osgi::framework::BundleActivator const& activator) = 0;

    /**
     * Stops the bundle having the specified identifier.
     *
     * @param id the bundle identifier.
     */
    virtual void stop(java::lang::String const& symbolicName) = 0;

    /**
     * Returns the bundle having the specified identifier.
     *
     * @param id the bundle identifier.
     */
    virtual org::osgi::framework::Bundle getBundle(java::lang::String const& id) const = 0;

};
#endif

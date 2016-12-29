/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _ORG_JAVOLUTION_LOG_LOGGING_HPP
#define _ORG_JAVOLUTION_LOG_LOGGING_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/Throwable.hpp"

namespace org { namespace javolution { namespace log { 
    class Logging_API;
}}}

/**
 * <p> This class holds the logging facility forwarding logging event
 *     to the appropriate framework selected at run-time (e.g. OSGI logging
 *     when running as an OSGI bundle). Logging can be enabled/disabled
 *     by level on a subject basis (e.g.
 *     <code>setLogErrorEnabled(L"ORG_JAVOLUTION", false)</code> to disables errors
 *     output from ORG_JAVOLUTION).</p>
 *
 * <p> For example:
 *     <pre><code>
 *        public void foo(Param param) {
 *             Logging_API::debug(L"ORG_JAVOLUTION", L"Enter foo() with parameters: ", param);
 *             try {
 *                ...
 *             } catch (RuntimeException ex) {
 *                 Logging_API::error(L"ORG_JAVOLUTION", ex); // Message holds current line location.
 *                 throw; // Rethrows.
 *             }
 *             Logging_API::debug(L"ORG_JAVOLUTION", L"Exit foo()");
 *        }
 *     </code></pre></p>
 *
 * @version 1.0
 */
class org::javolution::log::Logging_API : public virtual java::lang::Object_API {
// Class final, no virtual method.
public:

    /**
     * Logs the specified debug message if debug is activated for
     * the specified subject. If an object is specified and
     * logging is activated the textual representation of the object
     * (<code>obj->toString()</code>) is appended to the message.
     *
     * @param subject the logging subject.
     * @param msg/obj the debug message being formatted and logged.
     */
    JAVOLUTION_DLL static void debug(const wchar_t* subject, const wchar_t* msg);
    JAVOLUTION_DLL static void debug(const wchar_t* subject, const wchar_t* msg, java::lang::Object const& obj);
    JAVOLUTION_DLL static void debug(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2);
    JAVOLUTION_DLL static void debug(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2, java::lang::Object const& obj2);

    /**
     * Logs the specified informative message if informative logging is
     * activated for the specified subject. If an object is specified and
     * logging is activated the textual representation of the object
     * (<code>obj->toString()</code>) is appended to the message.
     *
     * @param subject the logging subject.
     * @param msg/obj the informative message being formatted and logged.
     */
    JAVOLUTION_DLL static void info(const wchar_t* subject, const wchar_t* msg);
    JAVOLUTION_DLL static void info(const wchar_t* subject, const wchar_t* msg, java::lang::Object const& obj);
    JAVOLUTION_DLL static void info(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2);
    JAVOLUTION_DLL static void info(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2, java::lang::Object const& obj2);

    /**
     * Logs the specified warning message if warning logging is
     * activated for the specified subject. If an object is specified and
     * logging is activated the textual representation of the object
     * (<code>obj->toString()</code>) is appended to the message.
     *
     * @param subject the logging subject.
     * @param msg/obj the warning message being formatted and logged.
     */
    JAVOLUTION_DLL static void warning(const wchar_t* subject, const wchar_t* msg);
    JAVOLUTION_DLL static void warning(const wchar_t* subject, const wchar_t* msg, java::lang::Object const& obj);
    JAVOLUTION_DLL static void warning(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2);
    JAVOLUTION_DLL static void warning(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2, java::lang::Object const& obj2);

    /**
     * Logs the specified error message if error logging is
     * activated for the specified subject. If an object is specified and
     * logging is activated the textual representation of the object
     * (<code>obj->toString()</code>) is appended to the message.
     *
     * @param subject the logging subject.
     * @param msg/obj the warning message being formatted and logged.
     */
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg, java::lang::Object const& obj);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2, java::lang::Object const& obj2);

    /**
     * Logs the specified error and error message if error logging is
     * activated for the specified subject. If an object is specified and
     * logging is activated the textual representation of the object
     * (<code>obj->toString()</code>) is appended to the message.
     *
     * @param subject the logging subject.
     * @param msg/obj the warning message being formatted and logged.
     * @param thrown the error being thrown.
     */
    JAVOLUTION_DLL static void error(const wchar_t* subject, java::lang::Throwable const& thrown);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg, java::lang::Throwable const& thrown);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg, java::lang::Object const& obj, java::lang::Throwable const& thrown);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2, java::lang::Throwable const& thrown);
    JAVOLUTION_DLL static void error(const wchar_t* subject, const wchar_t* msg1, java::lang::Object const& obj1, const wchar_t* msg2, java::lang::Object const& obj2, java::lang::Throwable const& thrown);

    //////////////////////
    // LogFilterService //
    //////////////////////

    /**
     * Enables/disables error logging for the specified subject or
     * for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is being enabled/disabled
     *        or <code>null</code> to enable/disable logging for all subjects.
     * @param value <code>true</code> to enable logging for the specified
     *        subject(s) or <code>false</code> to disable logging.
     */
    JAVOLUTION_DLL static void setLogErrorEnabled(const wchar_t* subject, Type::boolean value);

    /**
     * Indicates if error logging is enabled for the specified subject or
     * for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is tested
     *        or <code>null</code> to test for all subjects.
     * @return value <code>true</code> if logging is enabled for the specified
     *        subject(s); <code>false</code> otherwise.
     */
     JAVOLUTION_DLL static Type::boolean isLogErrorEnabled(const wchar_t* subject);

    /**
     * Enables/disables warning and error logging for the specified subject or
     * for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is being enabled/disabled
     *        or <code>null</code> to enable/disable logging for all subjects.
     * @param value <code>true</code> to enable logging for the specified
     *        subject(s) or <code>false</code> to disable logging.
     */
    JAVOLUTION_DLL static void setLogWarningEnabled(const wchar_t* subject, Type::boolean value);

    /**
     * Indicates if warning logging is enabled for the specified subject or
     * for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is tested
     *        or <code>null</code> to test for all subjects.
     * @return value <code>true</code> if logging is enabled for the specified
     *        subject(s); <code>false</code> otherwise.
     */
    JAVOLUTION_DLL static Type::boolean isLogWarningEnabled(const wchar_t* subject);

    /**
     * Enables/disables info, warning and error logging for the specified
     * subject or for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is being enabled/disabled
     *        or <code>null</code> to enable/disable logging for all subjects.
     * @param value <code>true</code> to enable logging for the specified
     *        subject(s) or <code>false</code> to disable logging.
     */
    JAVOLUTION_DLL static void setLogInfoEnabled(const wchar_t* subject, Type::boolean value);

    /**
     * Indicates if info logging is enabled for the specified subject or
     * for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is tested
     *        or <code>null</code> to test for all subjects.
     * @return value <code>true</code> if logging is enabled for the specified
     *        subject(s); <code>false</code> otherwise.
     */
    JAVOLUTION_DLL static Type::boolean isLogInfoEnabled(const wchar_t* subject);

    /**
     * Enables/disables debug, info, warning and error logging for the specified
     * subject or for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is being enabled/disabled
     *        or <code>null</code> to enable/disable logging for all subjects.
     * @param value <code>true</code> to enable logging for the specified
     *        subject(s) or <code>false</code> to disable logging.
     */
    JAVOLUTION_DLL static void setLogDebugEnabled(const wchar_t* subject, Type::boolean value);

    /**
     * Indicates if debug logging is enabled for the specified subject or
     * for all subjects if <code>subject</code> is <code>null</code>.
     *
     * @param subject the subject for which logging is tested
     *        or <code>null</code> to test for all subjects.
     * @return value <code>true</code> if logging is enabled for the specified
     *        subject(s); <code>false</code> otherwise.
     */
    JAVOLUTION_DLL static Type::boolean isLogDebugEnabled(const wchar_t* subject);

private:

    /**
     * Private constructor (should never be instantiated).
     */
    Logging_API() {
    }

    /**
     * Holds mutex for synchronized output.
     */
    JAVOLUTION_DLL static Type::Mutex MUTEX;
};


#endif

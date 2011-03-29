//
// Boost.Process
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// This code may be used under either of the following two licences:
//
//      Permission is hereby granted, free of charge, to any person
//      obtaining a copy of this software and associated documentation
//      files (the "Software"), to deal in the Software without
//      restriction, including without limitation the rights to use,
//      copy, modify, merge, publish, distribute, sublicense, and/or
//      sell copies of the Software, and to permit persons to whom the
//      Software is furnished to do so, subject to the following
//      conditions:
//
//      The above copyright notice and this permission notice shall be
//      included in all copies or substantial portions of the Software.
//
//      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//      EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//      OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//      NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//      HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//      WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//      FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//      OTHER DEALINGS IN THE SOFTWARE. OF SUCH DAMAGE.
//
// Or:
//
//      Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//      http://www.boost.org/LICENSE_1_0.txt)
//

//!
//! \file boost/process/exceptions.hpp
//!
//! Includes the declaration of the exceptions thrown by the library:
//! not_found_error and system_error.
//!

#if !defined(BOOST_PROCESS_EXCEPTIONS_HPP)
/** \cond */
#define BOOST_PROCESS_EXCEPTIONS_HPP
/** \endcond */

#include <boost/process/config.hpp>

#if defined(BOOST_PROCESS_POSIX_API)
#   include <cstring>
#elif defined(BOOST_PROCESS_WIN32_API)
extern "C" {
#   include <windows.h>
}
#   include <boost/assert.hpp>
#else
#   error "Unsupported platform."
#endif

#include <stdexcept>
#include <string>

namespace boost {
namespace process {

// ------------------------------------------------------------------------

//!
//! \brief Run time error initiated in a system call.
//!
//! The system_error exception wraps the information generated by an
//! operating system error.  These errors are the result of incorrect or
//! erroneous system calls.
//!
class system_error :
    public std::runtime_error
{
public:
#if defined(BOOST_PROCESS_DOXYGEN)
    //!
    //! \brief Native type used by the system to report error codes.
    //!
    typedef NativeErrorCodeType code_type;
#elif defined(BOOST_PROCESS_POSIX_API)
    typedef int code_type;
#elif defined(BOOST_PROCESS_WIN32_API)
    typedef DWORD code_type;
#endif

    //!
    //! \brief Constructs a new exception from a system error code.
    //!
    //! Constructs a new exception based on the result of an incorrect
    //! or an erroneous system call.
    //!
    //! \param who String that indicates the class and function where the
    //!            error was first detected.
    //! \param message String that describes the error that occurred
    //!                (typically the system call that failed).
    //! \param sys_err The system error code that identifies the error.
    //!                On a POSIX system this is the value of \a errno
    //!                and on a Win32 system it is the value returned
    //!                by ::GetLastError().
    //!
    system_error(const std::string& who, const std::string& message,
                 code_type sys_err);

    //!
    //! \brief Virtual destructor that does nothing.
    //!
    //! Virtual destructor.  Does nothing special but is required because
    //! of the parent's class destructor.
    //!
    virtual ~system_error(void) throw();

    //!
    //! \brief Returns the native error code.
    //!
    //! Returns the exception's native error code; that is, the value
    //! provided by the operating system when it reported the error.
    //!
    virtual code_type code(void) const throw();

    //!
    //! \brief Returns a formatted message for the exception.
    //!
    //! Generates and returns a formatted error message for the native
    //! error code attached to this exception.  This includes the function
    //! that raised the error, the system call where it was initiated and
    //! the reason for the failure.  The last is determined by ::strerror()
    //! in POSIX systems and ::FormatMessage under Win32.
    //!
    //! \return A constant C string containing the formatted error message.
    //!         The caller must not release it.
    //!
    virtual const char* what(void) const throw();

private:
    //!
    //! \brief Native error code for this exception.
    //!
    code_type m_sys_err;

    //!
    //! \brief Formatted error message for this exception.
    //!
    //! This string contains the formatted error message for this
    //! exception.  It is mutable because it is lazily initialized by the
    //! what() function.
    //!
    mutable std::string m_message;
};

// ------------------------------------------------------------------------

inline
system_error::system_error(const std::string& who,
                           const std::string& message,
                           code_type sys_err) :
    std::runtime_error(who + ": " + message),
    m_sys_err(sys_err)
{
}

// ------------------------------------------------------------------------

inline
system_error::~system_error(void)
    throw()
{
}

// ------------------------------------------------------------------------

inline
system_error::code_type
system_error::code(void)
    const
    throw()
{
    return m_sys_err;
}

// ------------------------------------------------------------------------

inline
const char*
system_error::what(void)
    const
    throw()
{
    try {
        if (m_message.length() == 0) {
            m_message = std::string(std::runtime_error::what()) + ": ";

#if defined(BOOST_PROCESS_POSIX_API)
            m_message += ::strerror(m_sys_err);
#elif defined(BOOST_PROCESS_WIN32_API)
            TCHAR* msg = NULL;
            if (::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                                FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                NULL, m_sys_err, 0,
                                reinterpret_cast<LPTSTR>(&msg),
                                0, NULL) == 0)
                m_message += "Unexpected error in FormatMessage";
            else {
                BOOST_ASSERT(msg != NULL);
                m_message += msg;
                LocalFree(msg);
            }
#endif
        }

        return m_message.c_str();
    } catch (...) {
        return "Unable to format system_error message";
    }
}

// ------------------------------------------------------------------------

//!
//! \brief Indicates that an element could not be found.
//!
//! The not_found_error exception indicates the that an expected element
//! could not be found.  The class is parametrized on the element type so
//! that it can carry a copy of the failing value.
//!
template< class T >
class not_found_error :
    public std::runtime_error
{
public:
    //!
    //! \brief Constructs a new exception.
    //!
    //! Constructs a new exception based on an error message and the
    //! value that could not be found.
    //!
    not_found_error(const std::string& message, const T& value) throw();

    //!
    //! \brief Virtual destructor that does nothing.
    //!
    //! Virtual destructor.  Does nothing special but is required because
    //! of the parent's class destructor.
    //!
    virtual ~not_found_error(void) throw();

    //!
    //! \brief Returns a copy of the value that could not be found.
    //!
    //! Returns a copy of the value that could not be found.
    //!
    const T& get_value(void) const throw();

private:
    T m_value;
};

// ------------------------------------------------------------------------

template< class T >
inline
not_found_error< T >::not_found_error(const std::string& message,
                                      const T& value)
    throw() :
    std::runtime_error(message),
    m_value(value)
{
}

// ------------------------------------------------------------------------

template< class T >
inline
not_found_error< T >::~not_found_error(void)
    throw()
{
}

// ------------------------------------------------------------------------

template< class T >
inline
const T&
not_found_error< T >::get_value(void)
    const
    throw()
{
    return m_value;
}

// ------------------------------------------------------------------------

} // namespace process
} // namespace boost

#endif // !defined(BOOST_PROCESS_EXCEPTIONS_HPP)
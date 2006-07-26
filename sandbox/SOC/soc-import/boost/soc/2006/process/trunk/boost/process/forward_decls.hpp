//
// Boost.Process
//
// Copyright (c) 2006 Julio M. Merino Vidal.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0.  (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt.)
//

//!
//! \file boost/process/forward_decls.hpp
//!
//! This header provides forward declarations for all public types
//! included in the library.  It is interesting to note that those types
//! that are specific to a given platform are only provided if the library
//! is being used in that same platform.
//!

#if !defined(BOOST_PROCESS_FORWARD_DECLS_HPP)
/** \cond */
#define BOOST_PROCESS_FORWARD_DECLS_HPP
/** \endcond */

#include <boost/process/config.hpp>

/** \cond */
namespace boost {
namespace process {

// ------------------------------------------------------------------------

class attributes;

template< class Command_Line, class Attributes >
class basic_child;

template< class Command_Line, class Attributes >
class basic_process;

class command_line;

class launcher;

class pistream;

class postream;

class status;

typedef basic_child< command_line, attributes > child;
typedef basic_process< command_line, attributes > process;

#if defined(BOOST_PROCESS_POSIX_API)
template< class Command_Line, class Attributes >
class basic_posix_child;

class posix_attributes;

class posix_launcher;

typedef basic_posix_child< command_line, attributes > posix_child;
#endif

// ------------------------------------------------------------------------

} // namespace process
} // namespace boost
/** \endcond */

#endif // !defined(BOOST_PROCESS_FORWARD_DECLS_HPP)

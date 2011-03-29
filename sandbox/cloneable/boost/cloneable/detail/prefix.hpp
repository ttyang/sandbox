// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONFIG_HPP
#    include <boost/config.hpp>
#    include <boost/detail/workaround.hpp>
#endif


#if defined(BOOST_MSVC)
#    pragma warning(push)
#    pragma warning(disable:4127)    // Conditional expression is constant.
#    pragma warning(disable:4130)    // Logical operation on address of string constant.
#    pragma warning(disable:4224)    // Parameter previously defined as type.
#    pragma warning(disable:4244)    // Conversion: possible loss of data.
#    pragma warning(disable:4512)    // Assignment operator could not be generated.
#    pragma warning(disable:4706)    // Assignment within conditional expression.
#    pragma warning(disable:4996)    // Function call with parameters that may be unsafe
#else
#    if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
#        pragma warn -8008     // Condition always true/false.
#        pragma warn -8066     // Unreachable code.
#        pragma warn -8071     // Conversion may lose significant digits.
#        pragma warn -8072     // Suspicious pointer arithmetic.
#        pragma warn -8080     // identifier declared but never used.
#    endif
#endif

#ifndef BOOST_CLONEABLE_FORWARD_DECLARATIONS_HPP
#    include <boost/cloneable/forward_declarations.hpp>
#endif

//EOF
// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_FUNCTION_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_FUNCTION_HPP_INCLUDED

#include <boost/function.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function, 1)

#if BOOST_FUNCTION_MAX_ARGS >= 0
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function0, 1)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 1
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function1, 2)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 2
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function2, 3)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 3
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function3, 4)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 4
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function4, 5)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 5
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function5, 6)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 6
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function6, 7)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 7
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function7, 8)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 8
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function8, 9)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 9
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function9, 10)
#endif

#if BOOST_FUNCTION_MAX_ARGS >= 10
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::function10, 11)
#endif

#endif  // BOOST_TYPEOF_BOOST_FUNCTION_HPP_INCLUDED


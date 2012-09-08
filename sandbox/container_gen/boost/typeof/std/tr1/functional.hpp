// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_STD_TR1_FUNCTIONAL_HPP_INCLUDED
#define BOOST_TYPEOF_STD_TR1_FUNCTIONAL_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tr1/functional.hpp>

#if defined BOOST_HAS_TR1_REFERENCE_WRAPPER \
 || defined BOOST_HAS_TR1_RESULT_OF \
 || !defined BOOST_HAS_TR1_RESULT_OF \
 && !defined BOOST_NO_SFINAE \
 && !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || defined BOOST_HAS_TR1_FUNCTION \
 || defined BOOST_HAS_TR1_HASH
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#endif

#if defined BOOST_HAS_TR1_REFERENCE_WRAPPER
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::reference_wrapper, 1)
#else
#include <boost/typeof/boost/ref.hpp>
#endif

#if defined BOOST_HAS_TR1_RESULT_OF
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::result_of, 1)
#elif !defined BOOST_NO_SFINAE \
 && !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/utility/result_of.hpp>
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::result_of, 1)
#endif

#if defined BOOST_HAS_TR1_FUNCTION
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::function, 1)
#else
#include <boost/typeof/boost/function.hpp>
#endif

#if defined BOOST_HAS_TR1_HASH
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::hash, 1)
#else
#include <boost/typeof/boost/functional/hash.hpp>
#endif

#endif  // BOOST_TYPEOF_STD_TR1_FUNCTIONAL_HPP_INCLUDED


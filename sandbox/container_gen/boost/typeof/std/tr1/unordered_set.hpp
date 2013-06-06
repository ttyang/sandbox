// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_STD_TR1_UNORDERED_SET_HPP_INCLUDED
#define BOOST_TYPEOF_STD_TR1_UNORDERED_SET_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tr1/unordered_set.hpp>

#if defined BOOST_HAS_TR1_UNORDERED_SET
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_set, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_set, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_set, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_set, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multiset, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multiset, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multiset, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multiset, 4)
#else
#include <boost/typeof/boost/unordered/unordered_set.hpp>
#endif

#endif  // BOOST_TYPEOF_STD_TR1_UNORDERED_SET_HPP_INCLUDED


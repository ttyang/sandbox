// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_STD_TR1_UNORDERED_MAP_HPP_INCLUDED
#define BOOST_TYPEOF_STD_TR1_UNORDERED_MAP_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tr1/unordered_map.hpp>

#if defined BOOST_HAS_TR1_UNORDERED_MAP
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_map, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_map, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_map, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_map, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multimap, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multimap, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multimap, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::std::tr1::unordered_multimap, 5)
#else
#include <boost/typeof/boost/unordered/unordered_map.hpp>
#endif

#endif  // BOOST_TYPEOF_STD_TR1_UNORDERED_MAP_HPP_INCLUDED


// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_STD_TR1_ARRAY_HPP_INCLUDED
#define BOOST_TYPEOF_STD_TR1_ARRAY_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tr1/array.hpp>

#if defined BOOST_HAS_TR1_ARRAY
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::std::tr1::array
  , (typename)(BOOST_TYPEOF_INTEGRAL(::std::size_t))
)
#else
#include <boost/typeof/boost/array.hpp>
#endif

#endif  // BOOST_TYPEOF_STD_TR1_ARRAY_HPP_INCLUDED


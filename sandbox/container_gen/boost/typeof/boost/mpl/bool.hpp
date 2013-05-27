// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_MPL_BOOL_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_MPL_BOOL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::mpl::bool_, (bool))
BOOST_TYPEOF_REGISTER_TYPE(::boost::mpl::true_)
BOOST_TYPEOF_REGISTER_TYPE(::boost::mpl::false_)

#endif  // BOOST_TYPEOF_BOOST_MPL_BOOL_HPP_INCLUDED


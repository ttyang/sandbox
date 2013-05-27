// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_SET_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_SET_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/parameter/aux_/set.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::set0);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::insert_, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::has_key_, 2);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_SET_HPP


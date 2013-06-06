// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_BINDING_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_BINDING_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter/aux_/result_of0.hpp>
#include <boost/typeof/boost/parameter/aux_/void.hpp>
#include <boost/parameter/binding.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::binding, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::binding, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::lazy_binding, 3);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_BINDING_HPP


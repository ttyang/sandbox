// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_AUX_ARG_LIST_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_AUX_ARG_LIST_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter/aux_/void.hpp>
#include <boost/typeof/boost/parameter/aux_/result_of0.hpp>
#include <boost/typeof/boost/parameter/aux_/default.hpp>
#include <boost/typeof/boost/parameter/aux_/parameter_requirements.hpp>
#include <boost/typeof/boost/parameter/aux_/yesno.hpp>
#include <boost/typeof/boost/parameter/aux_/is_maybe.hpp>
#include <boost/parameter/aux_/arg_list.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::empty_arg_list);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::get_reference, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::arg_list, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::arg_list, 2);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_AUX_ARG_LIST_HPP


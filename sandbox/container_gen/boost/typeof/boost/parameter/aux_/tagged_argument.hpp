// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_AUX_TAGGED_ARGUMENT_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_AUX_TAGGED_ARGUMENT_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter/aux_/void.hpp>
#include <boost/typeof/boost/parameter/aux_/arg_list.hpp>
#include <boost/typeof/boost/parameter/aux_/result_of0.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::arg_list_tag);
BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::tagged_argument_base);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::tagged_argument, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::is_tagged_argument_aux
  , 1
);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::is_tagged_argument, 1);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_AUX_TAGGED_ARGUMENT_HPP


// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_AUX_CAST_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_AUX_CAST_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/parameter/aux_/cast.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::use_default_tag);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::cast, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::as_placeholder_expr
  , 1
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::as_placeholder_expr
  , 2
);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_AUX_CAST_HPP


// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_NAME_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_NAME_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/parameter/keyword.hpp>
#include <boost/typeof/boost/parameter/value_type.hpp>
#include <boost/parameter/name.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::name_tag_base);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::name_tag, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::is_name_tag, 1);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_NAME_HPP


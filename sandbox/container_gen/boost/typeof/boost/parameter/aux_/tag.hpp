// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_AUX_TAG_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_AUX_TAG_HPP

#include <boost/detail/workaround.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/typeof/boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/aux_/tag.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::tag, 2);
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::tag, 3);
#endif

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_AUX_TAG_HPP


// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_AUX_UNWRAP_CV_REFERENCE_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_AUX_UNWRAP_CV_REFERENCE_HPP

#include <boost/detail/workaround.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/ref.hpp>
#include <boost/typeof/boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/unwrap_cv_reference.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::template_keyword_tag);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::is_cv_reference_wrapper
  , 1
);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::get_type, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::unwrap_cv_reference
  , 1
);
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::unwrap_cv_reference
  , 2
);
#endif

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_AUX_UNWRAP_CV_REFERENCE_HPP


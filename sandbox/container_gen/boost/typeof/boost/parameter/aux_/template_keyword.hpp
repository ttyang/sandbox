// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/parameter/aux_/template_keyword.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::template_keyword_tag);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::parameter::aux::is_template_keyword
  , 1
);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::template_keyword, 2);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP


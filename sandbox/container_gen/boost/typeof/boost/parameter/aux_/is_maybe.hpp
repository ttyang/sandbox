// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PARAMETER_AUX_IS_MAYBE_HPP
#define BOOST_TYPEOF_BOOST_PARAMETER_AUX_IS_MAYBE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/parameter/aux_/is_maybe.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::parameter::aux::maybe_base);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::parameter::aux::is_maybe, 1);

#endif  // BOOST_TYPEOF_BOOST_PARAMETER_AUX_IS_MAYBE_HPP


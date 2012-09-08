// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_REF_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_REF_HPP_INCLUDED

#include <boost/ref.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::reference_wrapper, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::is_reference_wrapper, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unwrap_reference, 1)

#endif  // BOOST_TYPEOF_BOOST_REF_HPP_INCLUDED


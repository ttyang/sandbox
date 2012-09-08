//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_C_STR_CMP_SELECTORS_TYPEOF_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_C_STR_CMP_SELECTORS_TYPEOF_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/container_gen/c_str_cmp_selectors.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::c_str_equivalence_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::c_str_ordering_selector);

#endif  // BOOST_CONTAINER_GEN_C_STR_CMP_SELECTORS_TYPEOF_HPP_INCLUDED


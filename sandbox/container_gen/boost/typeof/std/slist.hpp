// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_STD_SLIST_HPP_INCLUDED
#define BOOST_TYPEOF_STD_SLIST_HPP_INCLUDED

#include <boost/config.hpp>

#if !defined BOOST_NO_SLIST

#  if defined BOOST_SLIST_HEADER
#    include BOOST_SLIST_HEADER
#  else
#    include <slist>
#  endif

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/memory.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::BOOST_STD_EXTENSION_NAMESPACE::slist, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::BOOST_STD_EXTENSION_NAMESPACE::slist, 2)

#endif  // !BOOST_NO_SLIST

#endif  // BOOST_TYPEOF_STD_SLIST_HPP_INCLUDED


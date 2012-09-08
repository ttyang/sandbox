// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_CONTAINER_STRING_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_CONTAINER_STRING_HPP_INCLUDED

#include <boost/container/string.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/memory.hpp>
#include <boost/typeof/std/string.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::basic_string, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::basic_string, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::basic_string, 3)

#ifndef __BORLANDC__
//Borland chokes on these "double definitions" of string and wstring
BOOST_TYPEOF_REGISTER_TYPE(::boost::container::string)
BOOST_TYPEOF_REGISTER_TYPE(::boost::container::wstring)
#endif

#endif  // BOOST_TYPEOF_BOOST_CONTAINER_STRING_HPP_INCLUDED


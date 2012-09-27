/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_CONFIG_COMPILER_HPP
#define BOOST_GENERIC_CONFIG_COMPILER_HPP

// ToDo: Make this file detect the compiler and if it has a concept extension

// For now, assume no concept support is present unless the user says so
#define BOOST_GENERIC_COMPILER_HAS_CONCEPTS()                                  \
defined( BOOST_GENERIC_FORCE_COMPILER_HAS_CONCEPTS )

#endif // BOOST_GENERIC_CONFIG_COMPILER_HPP

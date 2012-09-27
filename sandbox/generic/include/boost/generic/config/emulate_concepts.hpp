/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_CONFIG_CONCEPT_SUPPORT_HPP
#define BOOST_GENERIC_CONFIG_CONCEPT_SUPPORT_HPP

#include <boost/generic/config/compiler.hpp>

#if     defined( BOOST_GENERIC_FORCE_CONCEPT_EMULATION )                       \
    || !BOOST_GENERIC_COMPILER_HAS_CONCEPTS()

#define BOOST_GENERIC_EMULATE_CONCEPTS() 1

#else

#define BOOST_GENERIC_EMULATE_CONCEPTS() 0

#endif

#endif // BOOST_GENERIC_CONFIG_CONCEPT_SUPPORT_HPP

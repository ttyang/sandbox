/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_LIMITS_HPP
#define BOOST_GENERIC_LIMITS_HPP

#include <boost/config.hpp>

#ifndef BOOST_GENERIC_CONCEPT_MAX_CONCEPT_MAPS
#define BOOST_GENERIC_CONCEPT_MAX_CONCEPT_MAPS 128
#endif

#ifdef BOOST_NO_VARIADIC_TEMPLATES
#ifndef BOOST_GENERIC_MAX_REQUIRES_EXPRESSIONS
#define BOOST_GENERIC_MAX_REQUIRES_EXPRESSIONS 16
#endif
#endif

#ifdef BOOST_NO_VARIADIC_TEMPLATES
#ifndef BOOST_GENERIC_MAX_CONCEPT_ARITY
#define BOOST_GENERIC_MAX_CONCEPT_ARITY 16
#endif
#endif

#endif // BOOST_GENERIC_LIMITS_HPP

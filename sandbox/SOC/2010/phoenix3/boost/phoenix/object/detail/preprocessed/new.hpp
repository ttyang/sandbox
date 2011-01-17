/*==============================================================================
    Copyright (c) 2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(PHOENIX_PREPROCESSED_NEW)
#define PHOENIX_PREPROCESSED_NEW

#if PHOENIX_LIMIT <= 10
#include <boost/phoenix/object/detail/preprocessed/new_10.hpp>
#elif PHOENIX_LIMIT <= 20
#include <boost/phoenix/object/detail/preprocessed/new_20.hpp>
#elif PHOENIX_LIMIT <= 30
#include <boost/phoenix/object/detail/preprocessed/new_30.hpp>
#elif PHOENIX_LIMIT <= 40
#include <boost/phoenix/object/detail/preprocessed/new_40.hpp>
#elif PHOENIX_LIMIT <= 50
#include <boost/phoenix/object/detail/preprocessed/new_50.hpp>
#else
#error "PHOENIX_LIMIT out of bounds for preprocessed headers"
#endif

#endif


// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CONFIG_EXT_HPP_
#define BOOST_CONFIG_EXT_HPP_

#include <boost/config.hpp>

/** @todo change the structure of this code when moved into Boost.Config which is organized by compiler (and not by feature) */

// If it is possible to pass local types (classes, etc) as template parameters.
// This is not possible in pure C++03 but it is possible in some C++03
// extensions (MSVC, GCC 4.5.x, etc).
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 4)) && \
        defined(__GXX_EXPERIMENTAL_CXX0X__)
    // From GCC 4.5.x when -std=c++0x specified.
#   define BOOST_LOCAL_TYPES_AS_TEMPLATE_PARAMS_
#elif defined(_MSC_VER)
    // For (all?) MSVC (tested on MVSC 8.0).
#   define BOOST_LOCAL_TYPES_AS_TEMPLATE_PARAMS_
#endif

#if !defined(BOOST_LOCAL_TYPES_AS_TEMPLATE_PARAMS_)
#   define BOOST_NO_LOCAL_TYPES_AS_TEMPLATE_PARAMS
#endif

#endif // #include guard


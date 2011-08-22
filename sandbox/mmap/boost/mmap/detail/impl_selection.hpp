////////////////////////////////////////////////////////////////////////////////
///
/// \file impl_selection.hpp
/// ------------------------
///
/// Copyright (c) Domagoj Saric 2011.
///
///  Use, modification and distribution is subject to the Boost Software License, Version 1.0.
///  (See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt)
///
/// For more information, see http://www.boost.org
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#pragma once
#ifndef impl_selection_hpp__05AF14B5_B23B_4CB8_A253_FD2D07B37ECF
#define impl_selection_hpp__05AF14B5_B23B_4CB8_A253_FD2D07B37ECF
//------------------------------------------------------------------------------
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/stringize.hpp"
//------------------------------------------------------------------------------
#if defined( _WIN32 )
    #define BOOST_MMAP_IMPL /win32/
#elif defined( _WIN32_WINNT )
    #define BOOST_MMAP_IMPL /nt/
#elif defined( BOOST_HAS_UNISTD_H )
    #define BOOST_MMAP_IMPL /posix/
#endif

#define BOOST_MMAP_IMPL_INCLUDE( prefix_path, include )                         \
    BOOST_PP_STRINGIZE                                                          \
    (                                                                           \
        BOOST_PP_CAT( BOOST_PP_CAT( prefix_path, BOOST_MMAP_IMPL ), include )   \
    )

//------------------------------------------------------------------------------
#endif // impl_selection_hpp

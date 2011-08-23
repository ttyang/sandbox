
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_HPP_
#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_HPP_

#include "../facility/is.hpp"
#include "../facility/add.hpp"
#include "../facility/remove.hpp"

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_IS_static_assert (1) /* unary */
#define static_assert_BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_IS (1) /* unary */
#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE_static_assert /* nothing */
#define static_assert_BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE /* nothing */

// Is.

#define BOOST_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_IS_)

#define BOOST_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_BACK(token) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_IS)

// Rremove.

#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_FRONT, \
            BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE_)

#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE_BACK(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_BACK, \
            _BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_REMOVE)

// Add.

#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_ADD_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_FRONT, static_assert)

#define BOOST_DETAIL_PP_KEYWORD_STATIC_ASSERT_ADD_BACK(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_BACK, static_assert)

#endif // #include guard


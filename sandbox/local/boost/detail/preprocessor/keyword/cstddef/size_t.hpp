
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_DETAIL_PP_KEYWORD_SIZE_T_HPP_
#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_HPP_

#include "../facility/is.hpp"
#include "../facility/add.hpp"
#include "../facility/remove.hpp"

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_IS_size_t (1) /* unary */
#define size_t_BOOST_DETAIL_PP_KEYWORD_SIZE_T_IS (1) /* unary */
#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_REMOVE_size_t /* nothing */
#define size_t_BOOST_DETAIL_PP_KEYWORD_SIZE_T_REMOVE /* nothing */

// Is.

#define BOOST_DETAIL_PP_KEYWORD_IS_SIZE_T_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_SIZE_T_IS_)

#define BOOST_DETAIL_PP_KEYWORD_IS_SIZE_T_BACK(token) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_DETAIL_PP_KEYWORD_SIZE_T_IS)

// Rremove.

#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_REMOVE_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_SIZE_T_FRONT, \
            BOOST_DETAIL_PP_KEYWORD_SIZE_T_REMOVE_)

#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_REMOVE_BACK(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_SIZE_T_BACK, \
            _BOOST_DETAIL_PP_KEYWORD_SIZE_T_REMOVE)

// Add.

#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_ADD_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_SIZE_T_FRONT, size_t)

#define BOOST_DETAIL_PP_KEYWORD_SIZE_T_ADD_BACK(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_SIZE_T_BACK, size_t)

#endif // #include guard


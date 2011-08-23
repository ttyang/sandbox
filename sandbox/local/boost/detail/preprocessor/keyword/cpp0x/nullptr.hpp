
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_DETAIL_PP_KEYWORD_NULLPTR_HPP_
#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_HPP_

#include "../facility/is.hpp"
#include "../facility/add.hpp"
#include "../facility/remove.hpp"

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_IS_nullptr (1) /* unary */
#define nullptr_BOOST_DETAIL_PP_KEYWORD_NULLPTR_IS (1) /* unary */
#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_nullptr /* nothing */
#define nullptr_BOOST_DETAIL_PP_KEYWORD_NULLPTR_REMOVE /* nothing */

// Is.

#define BOOST_DETAIL_PP_KEYWORD_IS_NULLPTR_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_NULLPTR_IS_)

#define BOOST_DETAIL_PP_KEYWORD_IS_NULLPTR_BACK(token) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_DETAIL_PP_KEYWORD_NULLPTR_IS)

// Rremove.

#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_NULLPTR_FRONT, \
            BOOST_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_)

#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_BACK(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_NULLPTR_BACK, \
            _BOOST_DETAIL_PP_KEYWORD_NULLPTR_REMOVE)

// Add.

#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_ADD_FRONT(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_NULLPTR_FRONT, nullptr)

#define BOOST_DETAIL_PP_KEYWORD_NULLPTR_ADD_BACK(tokens) \
    BOOST_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_DETAIL_PP_KEYWORD_IS_NULLPTR_BACK, nullptr)

#endif // #include guard


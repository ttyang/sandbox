
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_IS_void (1) /* unary */
#define void_BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE_void /* nothing */
#define void_BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT, void)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOID_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_BACK, void)

#endif // #include guard



// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_IS_char32_t (1) /* unary */
#define char32_t_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_REMOVE_char32_t /* nothing */
#define char32_t_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR32_T_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR32_T_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR32_T_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR32_T_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR32_T_FRONT, char32_t)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR32_T_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR32_T_BACK, char32_t)

#endif // #include guard


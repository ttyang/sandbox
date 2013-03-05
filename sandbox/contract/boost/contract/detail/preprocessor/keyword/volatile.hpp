
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_IS_volatile (1) /* unary */
#define volatile_BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_volatile /* nothing */
#define volatile_BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_FRONT, volatile)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_BACK, volatile)

#endif // #include guard


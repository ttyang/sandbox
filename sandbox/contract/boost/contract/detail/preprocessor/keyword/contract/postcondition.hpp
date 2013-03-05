
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_IS_postcondition (1) /* unary */
#define postcondition_BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_REMOVE_postcondition /* nothing */
#define postcondition_BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT, postcondition)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_POSTCONDITION_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_BACK, postcondition)

#endif // #include guard


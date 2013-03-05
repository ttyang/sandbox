
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_CURLY_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CURLY_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_IS_CURLY_BOOST_CONTRACT_DETAIL_PP_LCURLY \
    (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_IS_CURLY_BOOST_CONTRACT_DETAIL_PP_RCURLY \
    (1) /* unary */

// PUBLIC //

// Curly parenthesis macros.

#define BOOST_CONTRACT_DETAIL_PP_LCURLY() {

#define BOOST_CONTRACT_DETAIL_PP_RCURLY() }

// Detect curly parenthesis macros (not curly paren but actual macro names).

#define BOOST_CONTRACT_DETAIL_PP_IS_LCURLY_MACRO(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_IS_CURLY_)

#define BOOST_CONTRACT_DETAIL_PP_IS_RCURLY_MACRO(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_IS_CURLY_)

#endif // #include guard


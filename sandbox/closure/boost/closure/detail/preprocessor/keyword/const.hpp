
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_HPP_
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_HPP_

#include <boost/closure/detail/preprocessor/facility/is.hpp>
#include <boost/closure/detail/preprocessor/facility/add.hpp>
#include <boost/closure/detail/preprocessor/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_IS_const (1) /* unary */
#define const_BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_IS (1) /* unary */
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE_const /* nothing */
#define const_BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_IS_)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_BACK(token) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_IS)

// Remove.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_FRONT, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE_)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_BACK, \
            _BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_REMOVE)

// Add.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_ADD_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_FRONT, const)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_ADD_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_BACK, const)

#endif // #include guard


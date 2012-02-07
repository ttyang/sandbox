
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/local_function for library home page

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_HPP_

#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS_default (1)/* unary */
#define default_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS (1)/* unary */
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_default/*nothing*/
#define default_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE/*nothing*/

// PUBLIC //

// Is.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_BACK(token) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS)

// Remove.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_BACK, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE)

// Add.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_ADD_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT, default)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_ADD_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_BACK, default)

#endif // #include guard


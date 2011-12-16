
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_HPP_
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_HPP_

#include <boost/closure/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/closure/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/closure/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_IS_auto (1) /* unary */
#define auto_BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_IS (1) /* unary */
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE_auto /* nothing */
#define auto_BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_IS_)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_AUTO_BACK(token) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_IS)

// Remove.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_AUTO_FRONT, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE_)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_AUTO_BACK, \
            _BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE)

// Add.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_ADD_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_AUTO_FRONT, auto)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_ADD_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_AUTO_BACK, auto)

#endif // #include guard


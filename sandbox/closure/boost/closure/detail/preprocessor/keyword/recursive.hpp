
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_HPP_
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_HPP_

#include <boost/closure/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/closure/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/closure/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_IS_recursive (1) /* unary */
#define recursive_BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_IS (1) /* unary */
#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_recursive /* nothing */
#define recursive_BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RECURSIVE_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_IS_)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RECURSIVE_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(tokens, \
            _BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_IS)

// Remove.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RECURSIVE_FRONT, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RECURSIVE_BACK, \
            _BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE)

// Add.

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_ADD_FRONT(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RECURSIVE_FRONT, recursive)

#define BOOST_CLOSURE_DETAIL_PP_KEYWORD_RECURSIVE_ADD_BACK(tokens) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RECURSIVE_BACK, recursive)

#endif // #include guard


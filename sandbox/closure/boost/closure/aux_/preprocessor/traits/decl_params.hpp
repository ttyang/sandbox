
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/closure/detail/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/adt.hpp> // For `IS_CONS`.
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

// Param 2-tuple `([auto | register] type name, default_value)`.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_DECL_      0
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_DEFAULT_   1
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_MAX_       2

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_COUNT_DEFAULTS_OP_(s, \
        default_count, param) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_HAS_DEFAULT( \
            param), \
        BOOST_PP_INC \
    , \
        default_count BOOST_PP_TUPLE_EAT(1) \
    )(default_count)

// Precondition: unbinds is a pp-list which is not nil.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_COUNT_DEFAULTS_(params) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_COUNT_DEFAULTS_OP_, \
            0 /* start with defaults_count to 0 */, params)

// Expand to `default ... EMPTY()` if default value, `EMPTY()` otherwise.
// Leading default is kept because default value might not be alphanumeric
// (so failing `CAT` for `IS_EMPTY` check).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_DEFAULT_(param) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_MAX_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_DEFAULT_, param) \
            (/* expand EMPTY */) 

// PUBLIC //

// Expand to param declaration: [auto | register] type name.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_DECL(param) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_MAX_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_INDEX_DECL_, param)

// Expand to param default value (empty if none).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_DEFAULT(param) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_FRONT( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_DEFAULT_(param))

// Expand to 1 if param has default value, 0 otherwise.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_HAS_DEFAULT(param) \
    BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAM_DEFAULT_(param)))

// Expand to pp-list of ALL unbind params.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_PARAMS, decl_traits)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_PARAMS(decl_traits) \
    BOOST_PP_LIST_IS_CONS(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS(decl_traits))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_COUNT_DEFAULTS(decl_traits) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_PARAMS(decl_traits), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_COUNT_DEFAULTS_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS(decl_traits))

#endif // #include guard


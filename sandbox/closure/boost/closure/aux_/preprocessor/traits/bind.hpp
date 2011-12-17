
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_BIND_TRAITS_HPP_
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_HPP_

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

// PRIVATE //

// Non-this bind is 2-tuple `(name_without_type, name_with_type)`.
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_    0
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_       1
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_MAX_             2

// PUBLIC //

// Bind variable (const or not).

// Expand: `[&] var_`.
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_, bind_traits)

// Expand: `[(type_) [&] var_]` (EMPTY if no type_ specified).
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITH_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_, bind_traits) \
            (/* expand EMPTY */)

// Expand: 1 iff type_ specified, 0 otherwise.
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_HAS_TYPE(bind_traits) \
    BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_WITH_TYPE(bind_traits)))

// Bind object this (const or not).

// Expand: `[(type_)]` (EMPTY if no type_ specified).
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_THIS_TYPE(bind_this_type) \
    BOOST_PP_TUPLE_ELEM(1, 0, bind_this_type)(/* expand EMPTY */)

// Expand: 1 iff type_ specified, 0 otherwise.
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_THIS_HAS_TYPE(bind_this_type) \
    BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_THIS_TYPE(bind_this_type)))

#endif // #include guard


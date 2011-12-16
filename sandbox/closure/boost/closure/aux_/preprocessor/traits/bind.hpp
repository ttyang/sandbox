
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

// Bind non-this (const or not).

#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_WITHOUT_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_, bind_traits)

// Could be empty (if no type was explicitly specified).
#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_WITH_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_, bind_traits) \
            (/* expand EMPTY */)

#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_HAVE_TYPE(bind_traits) \
    BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_WITH_TYPE(any_bind)))

// Bind this (const or not).

#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_THIS_TYPE(bind_this_type) \
    BOOST_PP_TUPLE_ELEM(1, 0, bind_this_type)(/* expand EMPTY */)

#define BOOST_CLOSURE_AUX_PP_BIND_TRAITS_THIS_HAS_TYPE(bind_this_type) \
    BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_THIS_TYPE(bind_this_type)))

#endif // #include guard


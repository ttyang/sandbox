
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: `[ERROR_message_text] EMPTY`, EMPTY iff no pp-parsing error.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_ERROR, decl_traits)

// Expand: `[ERROR_message_text]`, EMPTY iff no pp-parsing error.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR(decl_traits)(/* expand EMPTY */)

#endif // #include guard



// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_error.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_const_bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_bind.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/logical/bitand.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_(decl_traits) \
    BOOST_PP_IIF(BOOST_PP_BITAND( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND_THIS( \
                    decl_traits), \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_BIND_THIS(decl_traits)), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SET_ERROR \
    , \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_bind_object_this_multiple_times BOOST_PP_EMPTY)

// PUBLIC //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT(decl_traits) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_ERROR(decl_traits), \
        decl_traits BOOST_PP_TUPLE_EAT(1) /* fwd existing error */ \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_ \
    )(decl_traits)

#endif // #include guard


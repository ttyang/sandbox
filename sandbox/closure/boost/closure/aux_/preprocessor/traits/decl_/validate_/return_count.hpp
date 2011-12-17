
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_error.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_return.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/list/size.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_(decl_traits) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), 1), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SET_ERROR \
    , \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_specify_more_than_one_return_type BOOST_PP_EMPTY)

// PUBLIC //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT(decl_traits) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_ERROR(decl_traits), \
        decl_traits BOOST_PP_TUPLE_EAT(1) /* fwd existing error */ \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_ \
    )(decl_traits)

#endif // #include guard


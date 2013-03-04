
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/traits/base/virtual.hpp>
#include <boost/contract/detail/preprocessor/traits/base/access.hpp>
#include <boost/contract/detail/preprocessor/traits/base/type.hpp>
#include <boost/contract/detail/preprocessor/traits/base/type.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS(base_sign) \
    BOOST_PP_TUPLE_ELEM(2, 0, /* get traits from `(traits, sign)` */ \
    BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_TYPE( \
    BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_VIRTUAL( \
    BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_ACCESS( \
        ( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits at start */ \
        , \
            base_sign \
            /* no trailing NIL because always type at end */ \
        ) \
    ))))

#endif // #include guard


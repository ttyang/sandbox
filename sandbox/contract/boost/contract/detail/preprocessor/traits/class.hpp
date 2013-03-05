
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/traits/class/access.hpp>
#include <boost/contract/detail/preprocessor/traits/class/export.hpp>
#include <boost/contract/detail/preprocessor/traits/class/template.hpp>
#include <boost/contract/detail/preprocessor/traits/class/concepts.hpp>
#include <boost/contract/detail/preprocessor/traits/class/kind.hpp>
#include <boost/contract/detail/preprocessor/traits/class/friend.hpp>
#include <boost/contract/detail/preprocessor/traits/class/name.hpp>
#include <boost/contract/detail/preprocessor/traits/class/specializations.hpp>
#include <boost/contract/detail/preprocessor/traits/class/final.hpp>
#include <boost/contract/detail/preprocessor/traits/class/bases.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to class traits (inspect using `CLASS_TRAITS`).
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS(class_signature) \
    BOOST_PP_TUPLE_ELEM(2, 0, /* get traits from `(traits, sign)` */ \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_BASES( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_FINAL( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_SPECIALIZATIONS( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_NAME( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_KIND( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_FRIEND( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_CONCEPTS( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_TEMPLATE( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_EXPORT( \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_ACCESS( \
        ( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits at start */ \
        , \
            class_signature \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* to end and for empty */ \
        ) \
    )))))))))))

#endif // #include guard


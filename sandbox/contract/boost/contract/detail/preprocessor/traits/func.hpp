
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/traits/func/access.hpp>
#include <boost/contract/detail/preprocessor/traits/func/export.hpp>
#include <boost/contract/detail/preprocessor/traits/func/template.hpp>
#include <boost/contract/detail/preprocessor/traits/func/concepts.hpp>
#include <boost/contract/detail/preprocessor/traits/func/explicit.hpp>
#include <boost/contract/detail/preprocessor/traits/func/inline.hpp>
#include <boost/contract/detail/preprocessor/traits/func/extern.hpp>
#include <boost/contract/detail/preprocessor/traits/func/static.hpp>
#include <boost/contract/detail/preprocessor/traits/func/virtual.hpp>
#include <boost/contract/detail/preprocessor/traits/func/friend.hpp>
#include <boost/contract/detail/preprocessor/traits/func/result_type.hpp>
#include <boost/contract/detail/preprocessor/traits/func/name.hpp>
#include <boost/contract/detail/preprocessor/traits/func/params.hpp>
#include <boost/contract/detail/preprocessor/traits/func/param_concepts.hpp>
#include <boost/contract/detail/preprocessor/traits/func/const.hpp>
#include <boost/contract/detail/preprocessor/traits/func/volatile.hpp>
#include <boost/contract/detail/preprocessor/traits/func/override.hpp>
#include <boost/contract/detail/preprocessor/traits/func/new.hpp>
#include <boost/contract/detail/preprocessor/traits/func/final.hpp>
#include <boost/contract/detail/preprocessor/traits/func/exceptions.hpp>
#include <boost/contract/detail/preprocessor/traits/func/preconditions.hpp>
#include <boost/contract/detail/preprocessor/traits/func/postconditions.hpp>
#include <boost/contract/detail/preprocessor/traits/func/initializers.hpp>
#include <boost/contract/detail/preprocessor/traits/func/catches.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_signature) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CATCHES( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INITIALIZERS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_POSTCONDITIONS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PRECONDITIONS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXCEPTIONS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_FINAL( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_NEW( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_OVERRIDE( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_VOLATILE( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CONST( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PARAM_CONCEPTS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PARAMS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_NAME( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_RESULT_TYPE( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_FRIEND( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_VIRTUAL( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_STATIC( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXTERN( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INLINE( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXPLICIT( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CONCEPTS( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_TEMPLATE( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXPORT( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_ACCESS( \
        ( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits at start */ \
        , \
            function_signature \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* to end and for empty */ \
        ) \
    )))))))))))))))))))))))))

#endif // #include guard


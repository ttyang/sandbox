
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/type.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_REQUIREMENT( \
        traits_sign) \
    /* reuse func param parsing */ \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE(traits_sign)

// PUBLIC //

// Expand to type or named param only requirement `(n, (type_token0, ...))`
// (0-sized array for no type (e.g., named param any type), array to handle
// unwrapped commas).
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT( \
        tparam_traits) \
    BOOST_PP_ARRAY_ELEM(1, BOOST_PP_TUPLE_ELEM(2, 0, tparam_traits))

#endif // #include guard


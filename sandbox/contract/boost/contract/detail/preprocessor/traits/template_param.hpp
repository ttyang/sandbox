
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_HPP_

// Default value already processed, header included for user to access traits.
#include <boost/contract/detail/preprocessor/traits/template_param/default.hpp>

#include <boost/contract/detail/preprocessor/traits/template_param/kind.hpp>
#include <boost/contract/detail/preprocessor/traits/template_param/requirement.hpp>
#include <boost/contract/detail/preprocessor/traits/template_param/name.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to template parameter traits (inspect with TEMPLATE_PARAM_TRAITS).
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS(tparam_sign) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_NAME( \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_REQUIREMENT( \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_KIND( \
        ( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits at start */ \
        , \
            tparam_sign \
            /* no trailing NIL because always name at end */ \
        ) \
    ))))

#endif // #include guard


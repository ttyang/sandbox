
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_HPP_

// Default value already processed, header included for user to access traits.
#include <boost/contract/detail/preprocessor/traits/func_param/default.hpp>

#include <boost/contract/detail/preprocessor/traits/func_param/classifier.hpp>
#include <boost/contract/detail/preprocessor/traits/func_param/type.hpp>
#include <boost/contract/detail/preprocessor/traits/func_param/name.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to template parameter traits (inspect with FUNC_PARAM_TRAITS).
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS(fparam_sign) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_NAME( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE( \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_CLASSIFIER( \
        ( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits at start */ \
        , \
            fparam_sign \
            /* no trailing NIL because always name at end */ \
        ) \
    ))))

#endif // #include guard


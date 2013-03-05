
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_STATIC_CLASS_INVARIANT_HPP_
#define BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_STATIC_CLASS_INVARIANT_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/subboost/contract/from.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_CONTRACT_comma_class_Base(z, n, unused) \
    , class BOOST_PP_CAT(Base, n)
#define BOOST_CONTRACT_comma_base_param(z, n, unused) \
    , void (* BOOST_PP_CAT(sub_static_class_inv, n)) ( )
#define BOOST_CONTRACT_base_static_class_inv_check(z, n, unused) \
    if(is_subcontracted_from< Class, BOOST_PP_CAT(Base, n) >::value) \
    { \
        (*BOOST_PP_CAT(sub_static_class_inv, n))(); \
    }

namespace boost { namespace contract { namespace aux {

template<
    class Class
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_class_Base, ~)
>
void subcontract_static_class_invariant(
    // NOTE: Even if the class inv func name is known a priori, func must be
    // passed by ptr to avoid error in accessing a private func.
      void (* this_static_class_inv) ( void )
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_base_param, ~)
) {
    // Check all static class inv in short-circuit AND (1st throw stops check).
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_base_static_class_inv_check, ~)
    (*this_static_class_inv)();
}

} } } // namespace

#undef BOOST_CONTRACT_comma_class_Base
#undef BOOST_CONTRACT_comma_base_param
#undef BOOST_CONTRACT_base_static_class_inv_check

#endif // #include guard


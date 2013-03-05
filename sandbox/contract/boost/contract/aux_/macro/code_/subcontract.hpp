
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_HPP_

#include <boost/contract/aux_/subboost/contract/from.hpp>
#include <boost/contract/aux_/subboost/contract/has_class_invariant.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_FUNC_BASE_TYPEDEF_( \
        z, n, id_tpl_f) \
    typedef \
        /* here typename only if enclosing scope is template (tpl = 1) but */ \
        /* not also if f is template (because if f is template no */ \
        /* subcontracting using mpl::false_ which is not type-dependent) */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(3, 1, id_tpl_f), \
            typename \
        ) \
        ::contract::aux::subcontract_from< \
              BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
            , BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n) \
            , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE( \
                    BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_f)), \
                /* NOTE: member func tpl cannot be virtual so no subcontract */\
                ::boost::mpl::false_ \
                BOOST_PP_TUPLE_EAT(3) \
              , \
                BOOST_CONTRACT_AUX_CODE_HAS_VIRTUAL \
              )(BOOST_PP_TUPLE_ELEM(3, 0, id_tpl_f), \
                    BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_f), \
                    BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n)) \
        >::type \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(3, 0, id_tpl_f), n) \
    ;

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_INVARIANT_BASE_TYPEDEF_( \
        z, n, id_tpl_c) \
    typedef \
        BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(BOOST_PP_TUPLE_ELEM( \
                3, 1, id_tpl_c), BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_c)) \
        ::contract::aux::subcontract_from< \
              BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
            , BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n) \
            , ::contract::aux::has_subcontracted_class_invariant< \
                void (BOOST_CONTRACT_AUX_CODE_BASE_TYPE(n)::*) ( ) const \
              > \
        >::type \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(3, 0, id_tpl_c), n) \
    ;

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n) \
    BOOST_CONTRACT_AUX_SYMBOL( (subcontracted_base)(n)(id) )

// Subcontract overriding function pre and post from all bases.
#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_PREPOSTCONDITION_FROM_BASES( \
        id, tpl, k, f) \
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
            BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_FUNC_BASE_TYPEDEF_, \
            (id, tpl, f))

// Subcontract (dynamic, volatile, and static) class inv from all bases.
#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_CLASS_INVARIANT_FROM_BASES( \
        id, tpl, c) \
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
            BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_INVARIANT_BASE_TYPEDEF_, \
                    (id, tpl, c))

#endif // #include guard


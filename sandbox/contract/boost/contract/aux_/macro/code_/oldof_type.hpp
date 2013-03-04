
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE_HPP_
#define BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE_HPP_

#include <boost/contract/aux_/oldof.hpp>
#include <boost/contract/detail/preprocessor/traits/oldof.hpp> // o
#include <boost/typeof/typeof.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPE_(index) \
    BOOST_CONTRACT_AUX_SYMBOL( (Old) (index) )

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES_APPEND_(index, autotypes) \
    BOOST_PP_LIST_APPEND(autotypes, \
            (BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPE_(index), BOOST_PP_NIL))

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES_IDENTITY_(index, autotypes) \
    autotypes

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES_(d, index_autotypes, o) \
    ( \
        BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2, 0, index_autotypes)) \
    , \
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE(o)), \
            BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES_IDENTITY_ \
        , \
            BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES_APPEND_ \
        )(BOOST_PP_TUPLE_ELEM(2, 0, index_autotypes), \
                BOOST_PP_TUPLE_ELEM(2, 1, index_autotypes)) \
    )

#define BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE_AUTO_(typename01, o, index) \
    /* just type name here, aux::oldof_ already applied to typeof deduction */ \
    BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPE_(index)

#define BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE_SPECIFIED_(typename01, o, index) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::contract::aux::oldof_< \
        BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE(o)) \
    >::type

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE(typename01, o, index) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE(o)), \
        BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE_SPECIFIED_ \
    , \
        BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE_AUTO_ \
    )(typename01, o, index)

#define BOOST_CONTRACT_AUX_CODE_OLDOF_DEDUCE_AUTO_TYPE(typename01, o, index) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::contract::aux::oldof_< \
        BOOST_PP_IIF(typename01, \
            /* dependent type context Boost.Typeof (no typename needed) */ \
            BOOST_TYPEOF_TPL \
        , \
            BOOST_TYPEOF \
        )(BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_EXPR(o)) \
    >::type

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES(typename01, oldofs) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES_, (0, BOOST_PP_NIL), \
            oldofs))

#endif // #include guard


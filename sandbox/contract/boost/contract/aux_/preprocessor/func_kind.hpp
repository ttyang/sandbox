
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_PP_FUNC_KIND_HPP_
#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_HPP_

#include <boost/contract/aux_/config.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp> // f
#include <boost/preprocessor/comparison/equal.hpp>

// PUBLIC //

// Kind `k` enumeration.
#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_CONSTRUCTOR 1
#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_DESTRUCTOR  2
#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_FUNCTION    3

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k) \
    BOOST_PP_EQUAL(k, BOOST_CONTRACT_AUX_PP_FUNC_KIND_CONSTRUCTOR)

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k) \
    BOOST_PP_EQUAL(k, BOOST_CONTRACT_AUX_PP_FUNC_KIND_DESTRUCTOR)

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FUNCTION(k) \
    BOOST_PP_EQUAL(k, BOOST_CONTRACT_AUX_PP_FUNC_KIND_FUNCTION)

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
    /* FUTURE: leave this macro here because in the future members could be */ \
    /* detected using special API macros (BOOST_CONTRACT_MEMBER_...) thus */ \
    /* using k instead of access level in f */ \
    BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS(f)))

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f) \
    BOOST_PP_BITAND( \
          BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FUNCTION(k) \
        , BOOST_PP_BITAND( \
              BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
            , BOOST_PP_BITAND( \
                  BOOST_PP_IS_EMPTY( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_STATIC(f)) \
                /* friend members are also contracted as static members */ \
                , BOOST_PP_IS_EMPTY( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_FRIEND(f)) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_STATIC_MEMBER_FUNCTION(k, f) \
    BOOST_PP_BITAND( \
          BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FUNCTION(k) \
        , BOOST_PP_BITAND( \
              BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
            , BOOST_PP_BITOR( \
                  BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_STATIC(f))) \
                /* friend members are also contracted as static members */ \
                , BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_FRIEND(f))) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FREE_FUNCTION(k, f) \
    BOOST_PP_BITAND( \
          BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FUNCTION(k) \
        , BOOST_PP_COMPL(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f)) \
    )

#endif // #include guard


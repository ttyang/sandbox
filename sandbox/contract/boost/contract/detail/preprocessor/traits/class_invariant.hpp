
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/keyword/void.hpp>
#include <boost/contract/detail/preprocessor/keyword/class.hpp>
#include <boost/contract/detail/preprocessor/keyword/volatile.hpp>
#include <boost/contract/detail/preprocessor/keyword/static.hpp>
#include <boost/contract/detail/preprocessor/seq/to_list.hpp>
#include <boost/contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/config.hpp>

// PRIVATE //

#ifndef BOOST_NO_VARIADIC_MACROS
#   define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_TO_SEQ_(...) \
        BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ((void), __VA_ARGS__ )
#else
#   define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_TO_SEQ_(seq) seq
#endif

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_LIST_( \
        remove_macro, assertion) \
    BOOST_CONTRACT_DETAIL_PP_SEQ_TO_LIST( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT, \
        /* cat TO_SEQ_ with class(...) and invoke macro above */ \
        BOOST_PP_EXPAND( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_TO_SEQ_ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
                    remove_macro(assertion)) \
        ) \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC_(s, \
        has_const01, const_invs, has_constvolatile01, constvolatile_invs, \
        has_static01, static_invs, assertion) \
    ( \
        has_const01 \
    , \
        const_invs \
    , \
        has_constvolatile01 \
    , \
        constvolatile_invs \
    , \
        1 /* static class inv specified (still it could be empty) */ \
    , \
        BOOST_PP_LIST_APPEND(static_invs, \
                BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_LIST_( \
                        BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE_FRONT, \
                        assertion)) \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_VOLATILE_(s, \
        has_const01, const_invs, has_constvolatile01, constvolatile_invs, \
        has_static01, static_invs, assertion) \
    ( \
        has_const01 \
    , \
        const_invs \
    , \
        1 /* const volatile class inv specified (still it could be empty) */ \
    , \
        BOOST_PP_LIST_APPEND(constvolatile_invs, \
                BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_LIST_( \
                        BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_FRONT,\
                        assertion)) \
    , \
        has_static01 \
    , \
        static_invs \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_(s, \
        has_const01, const_invs, has_constvolatile01, constvolatile_invs, \
        has_static01, static_invs, assertion) \
    ( \
        1 /* const class inv specified (still it could be empty) */ \
    , \
        BOOST_PP_LIST_APPEND(const_invs, (assertion, BOOST_PP_NIL)) \
    , \
        has_constvolatile01 \
    , \
        constvolatile_invs \
    , \
        has_static01 \
    , \
        static_invs \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_IS_( \
        is_macro, remove_macro, tokens) \
    BOOST_PP_BITAND( \
          BOOST_PP_EXPAND(is_macro(tokens)) /* EXPAND for MSVC */ \
        , BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT( \
                remove_macro(tokens)) \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_( \
        s, const01inv_constvolatile01inv_static01inv, assertion) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_IS_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_FRONT, assertion),\
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_VOLATILE_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_IS_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE_FRONT, assertion), \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_ \
    ))(s \
        , BOOST_PP_TUPLE_ELEM(6, 0, const01inv_constvolatile01inv_static01inv) \
        , BOOST_PP_TUPLE_ELEM(6, 1, const01inv_constvolatile01inv_static01inv) \
        , BOOST_PP_TUPLE_ELEM(6, 2, const01inv_constvolatile01inv_static01inv) \
        , BOOST_PP_TUPLE_ELEM(6, 3, const01inv_constvolatile01inv_static01inv) \
        , BOOST_PP_TUPLE_ELEM(6, 4, const01inv_constvolatile01inv_static01inv) \
        , BOOST_PP_TUPLE_ELEM(6, 5, const01inv_constvolatile01inv_static01inv) \
        , assertion \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_ASSERTIONS_( \
        const01inv_constvolatile01inv_static01inv) \
    ( \
        BOOST_PP_TUPLE_ELEM(6, 0, const01inv_constvolatile01inv_static01inv) \
    , \
        BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS(BOOST_PP_TUPLE_ELEM(6, 1, \
                const01inv_constvolatile01inv_static01inv)) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 2, const01inv_constvolatile01inv_static01inv) \
    , \
        BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS(BOOST_PP_TUPLE_ELEM(6, 3, \
                const01inv_constvolatile01inv_static01inv)) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 4, const01inv_constvolatile01inv_static01inv) \
    , \
        BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS(BOOST_PP_TUPLE_ELEM(6, 5, \
                const01inv_constvolatile01inv_static01inv)) \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_EMPTY_(seq) \
    ( \
        0 /* const class inv not specified */ \
    , \
        BOOST_PP_NIL /* const class inv list */ \
    , \
        0 /* const volatile class inv not specified */ \
    , \
        BOOST_PP_NIL /* const volatile class inv list */ \
    , \
        0 /* static class inv not specified */ \
    , \
        BOOST_PP_NIL /* static class inv list */ \
    )

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_NOT_EMPTY_(seq) \
    BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_ASSERTIONS_( \
            BOOST_PP_SEQ_FOLD_LEFT( \
                    BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_, \
                    /* start empty */ \
                    BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_EMPTY_( \
                            seq), \
                    seq))

// Precondition: size(seq) == 1
#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_MAYBE_EMPTY_(seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT( \
            BOOST_PP_SEQ_HEAD(seq)), \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_EMPTY_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_NOT_EMPTY_ \
    )(seq)

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS(seq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(seq), 1), \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_MAYBE_EMPTY_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_NOT_EMPTY_ \
    )(seq)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HAS_CONST(traits) \
    BOOST_PP_TUPLE_ELEM(6, 0, traits)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST(traits) \
    BOOST_PP_TUPLE_ELEM(6, 1, traits)

// If volatile class(...) specified at all.
#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HAS_CONST_VOLATILE( \
        traits) \
    BOOST_PP_TUPLE_ELEM(6, 2, traits)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_VOLATILE(traits) \
    BOOST_PP_TUPLE_ELEM(6, 3, traits)
    
#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HAS_STATIC(traits) \
    BOOST_PP_TUPLE_ELEM(6, 4, traits)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC(traits) \
    BOOST_PP_TUPLE_ELEM(6, 5, traits)

#endif // #include guard


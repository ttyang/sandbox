#ifndef TUPLE_IMPL_BCON12_VERTICAL_INCLUDE_HPP
#define TUPLE_IMPL_BCON12_VERTICAL_INCLUDE_HPP
//Acknowlegements:
//  The following code was adapted from part of the code in
//    https://github.com/ericniebler/home/blob/master/src/tuple/unrolled_tuple.hpp
//
///////////////////////////////////////////////////////////////////////////////
// unrolled_tuple.hpp
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include "./RETURN_ENABLE_IF_DEFAULTS.hpp"

// Must be greater than or equal to 1. (1 means don't do loop unrolling.)
#ifndef TUPLE_UNROLL_MAX
#define TUPLE_UNROLL_MAX 10
#endif

#define DISABLE_COPY_IF(CLASS, N, T)                                                                \
    BOOST_PP_COMMA_IF(BOOST_PP_EQUAL(N, 1))                                                         \
    BOOST_PP_EXPR_IF(                                                                               \
        BOOST_PP_EQUAL(N, 1)                                                                        \
      , ENABLE_IF(!std::is_same<T, CLASS &>::value)                                                 \
    )                                                                                               \
    /**/

template<typename ...T>
struct tuple_bench;

template<>
struct tuple_bench<>
{
};

#define INIT(Z, N, D) t ## N(static_cast< U ## N && >( u ## N ))
#define MEMBERS(Z, N, D) T ## N t ## N;

#if TUPLE_TEMPLATED_CTOR == 1
  #define TEMPLATED_TUPLE_CTOR_GEN(N)                               \
    DEFAULTS(tuple_bench)                                           \
                                                                    \
    template<BOOST_PP_ENUM_PARAMS(N, typename U)                    \
        DISABLE_COPY_IF(tuple_bench, N, U0)                         \
    >                                                               \
    constexpr tuple_bench(BOOST_PP_ENUM_BINARY_PARAMS(N, U, &&u))   \
      : BOOST_PP_ENUM(N, INIT, ~)                                   \
    {}                                                              \
                                                                    \
  /**/
#else
  #define TEMPLATED_TUPLE_CTOR_GEN(N)
#endif  
  
#define BOOST_PP_LOCAL_MACRO(N)                                     \
template<BOOST_PP_ENUM_PARAMS(N, typename T)>                       \
struct tuple_bench<BOOST_PP_ENUM_PARAMS(N, T)>                      \
{                                                                   \
    TEMPLATED_TUPLE_CTOR_GEN(N)                                     \
    BOOST_PP_REPEAT(N, MEMBERS, ~)                                  \
};                                                                  \
/**/

#define BOOST_PP_LOCAL_LIMITS (1, TUPLE_UNROLL_MAX)
#include BOOST_PP_LOCAL_ITERATE()

#undef TEMPLATED_TUPLE_CTOR_GEN

// A tuple type that can be statically initialized
template<BOOST_PP_ENUM_PARAMS(TUPLE_UNROLL_MAX, typename T), typename ...Tail>
struct tuple_bench<BOOST_PP_ENUM_PARAMS(TUPLE_UNROLL_MAX, T), Tail...>
{
  #if TUPLE_TEMPLATED_CTOR == 1
    DEFAULTS(tuple_bench)

    // Not explicit to allow things like: return {42, "allo"};.
    template<BOOST_PP_ENUM_PARAMS(TUPLE_UNROLL_MAX, typename U), typename ...Rest
      , ENABLE_IF(sizeof...(Rest)==sizeof...(Tail))
        DISABLE_COPY_IF(tuple_bench, TUPLE_UNROLL_MAX, U0)
    >
    constexpr tuple_bench(BOOST_PP_ENUM_BINARY_PARAMS(TUPLE_UNROLL_MAX, U, &&u), Rest &&...rest)
      : BOOST_PP_ENUM(TUPLE_UNROLL_MAX, INIT, ~)
      , tail(static_cast<Rest &&>(rest)...) // std::forward is NOT constexpr!
    {}
  #endif

    BOOST_PP_REPEAT(TUPLE_UNROLL_MAX, MEMBERS, ~)
    tuple_bench<Tail...> tail;
};

#undef INIT
#undef MEMBERS

namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template<int I>
    struct int_{};
    
    // Work-around strange gcc bug
    template<int J>
    struct impl
    {
        #define BOOST_PP_LOCAL_MACRO(N)                                                             \
        template<typename Tuple>                                                                    \
        static inline constexpr auto get_elem(Tuple &&that, int_<N>)                                \
        RETURN(                                                                                     \
            (static_cast<Tuple &&>(that).BOOST_PP_CAT(t, N))  /*extra parens are significant!*/     \
        )                                                                                           \
        /**/

        #define BOOST_PP_LOCAL_LIMITS (0, BOOST_PP_DEC(TUPLE_UNROLL_MAX))
        #include BOOST_PP_LOCAL_ITERATE()

        template<typename Tuple, int I>
        static inline constexpr auto get_elem(Tuple &&that, int_<I>)
        RETURN(
            impl<I-I>::get_elem(static_cast<Tuple &&>(that).tail, int_<I-TUPLE_UNROLL_MAX>())
        )
    };
}

///////////////////////////////////////////////////////////////////////////////
// get
template<int I, typename ...T>
inline constexpr auto get(tuple_bench<T...> &tup)
RETURN(
    detail::impl<I-I>::get_elem(tup, detail::int_<I>())
)

template<int I, typename ...T>
inline constexpr auto get(tuple_bench<T...> const &tup)
RETURN(
    detail::impl<I-I>::get_elem(tup, detail::int_<I>())
)

template<int I, typename ...T>
inline constexpr auto get(tuple_bench<T...> &&tup)
RETURN(
    detail::impl<I-I>::get_elem(static_cast<tuple_bench<T...> &&>(tup), detail::int_<I>())
)

#endif

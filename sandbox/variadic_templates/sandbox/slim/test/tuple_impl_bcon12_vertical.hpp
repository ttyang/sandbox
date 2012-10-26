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

#include <utility>
#include <functional>
#include <type_traits>
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

// Must be greater than or equal to 1. (1 means don't do loop unrolling.)
#ifndef UNROLL_MAX
#define UNROLL_MAX 10
#endif

// C++11 eliminates the need for macros! Oh, wait ...
#define RETURN(...) -> decltype(__VA_ARGS__) { return __VA_ARGS__; }

// New-style enable_if from Matt Calabrese
#define ENABLE_IF(...) typename std::enable_if<(__VA_ARGS__)>::type *& = detail::enabler

// For adding defaulted default, copy and move constructors, and move/copy assign.
#define DEFAULTS(CLASS)                                                                             \
    CLASS() = default; /*required for the type to be trivial!*/                                     \
    CLASS(CLASS const &) = default; /* memberwise copy */                                           \
    CLASS(CLASS &&) = default; /* member-wise move */                                               \
    /* These would otherwise be deleted because we */                                               \
    /* declared a move constructor! */                                                              \
    CLASS &operator=(CLASS const &) = default; /* memberwise copy assign */                         \
    CLASS &operator=(CLASS &&) = default; /* memberwise move assign */                              \
    /**/

#define DISABLE_COPY_IF(CLASS, N, T)                                                                \
    BOOST_PP_COMMA_IF(BOOST_PP_EQUAL(N, 1))                                                         \
    BOOST_PP_EXPR_IF(                                                                               \
        BOOST_PP_EQUAL(N, 1)                                                                        \
      , ENABLE_IF(!std::is_same<T, CLASS &>::value)                                                 \
    )                                                                                               \
    /**/

namespace detail
{
    extern void* enabler;

    ///////////////////////////////////////////////////////////////////////////
    template<int I>
    using int_ = std::integral_constant<int, I>;

    ///////////////////////////////////////////////////////////////////////////
    // unrefwrap
    template<typename T>
    struct unrefwrap
    {
        typedef T type;
    };

    template<typename T>
    struct unrefwrap<std::reference_wrapper<T> >
    {
        typedef T &type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // as_tuple_element
    template<typename T>
    using as_tuple_element = typename unrefwrap<typename std::decay<T>::type>::type;
}

template<typename ...T>
struct tuple_bench;

template<>
struct tuple_bench<>
{
};

#define INIT(Z, N, D) t ## N(static_cast< U ## N && >( u ## N ))
#define MEMBERS(Z, N, D) T ## N t ## N;

#define BOOST_PP_LOCAL_MACRO(N)                                     \
template<BOOST_PP_ENUM_PARAMS(N, typename T)>                       \
struct tuple_bench<BOOST_PP_ENUM_PARAMS(N, T)>                            \
{                                                                   \
    DEFAULTS(tuple_bench)                                                 \
                                                                    \
    template<BOOST_PP_ENUM_PARAMS(N, typename U)                    \
        DISABLE_COPY_IF(tuple_bench, N, U0)                               \
    >                                                               \
    constexpr tuple_bench(BOOST_PP_ENUM_BINARY_PARAMS(N, U, &&u))         \
      : BOOST_PP_ENUM(N, INIT, ~)                                   \
    {}                                                              \
                                                                    \
    BOOST_PP_REPEAT(N, MEMBERS, ~)                                  \
};                                                                  \
/**/

#define BOOST_PP_LOCAL_LIMITS (1, UNROLL_MAX)
#include BOOST_PP_LOCAL_ITERATE()

// A tuple type that can be statically initialized
template<BOOST_PP_ENUM_PARAMS(UNROLL_MAX, typename T), typename ...Tail>
struct tuple_bench<BOOST_PP_ENUM_PARAMS(UNROLL_MAX, T), Tail...>
{
    DEFAULTS(tuple_bench)

    // Not explicit to allow things like: return {42, "allo"};.
    template<BOOST_PP_ENUM_PARAMS(UNROLL_MAX, typename U), typename ...Rest
      , ENABLE_IF(sizeof...(Rest)==sizeof...(Tail))
        DISABLE_COPY_IF(tuple_bench, UNROLL_MAX, U0)
    >
    constexpr tuple_bench(BOOST_PP_ENUM_BINARY_PARAMS(UNROLL_MAX, U, &&u), Rest &&...rest)
      : BOOST_PP_ENUM(UNROLL_MAX, INIT, ~)
      , tail(static_cast<Rest &&>(rest)...) // std::forward is NOT constexpr!
    {}

    BOOST_PP_REPEAT(UNROLL_MAX, MEMBERS, ~)
    tuple_bench<Tail...> tail;
};

#undef INIT
#undef MEMBERS
#undef DEFAULTS

namespace detail
{
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

        #define BOOST_PP_LOCAL_LIMITS (0, BOOST_PP_DEC(UNROLL_MAX))
        #include BOOST_PP_LOCAL_ITERATE()

        template<typename Tuple, int I>
        static inline constexpr auto get_elem(Tuple &&that, int_<I>)
        RETURN(
            impl<I-I>::get_elem(static_cast<Tuple &&>(that).tail, int_<I-UNROLL_MAX>())
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

///////////////////////////////////////////////////////////////////////////////
// make_tuple
template<typename ...T>
inline tuple_bench<detail::as_tuple_element<T>...> make_tuple(T &&...t)
{
    return {t...};
}

#endif

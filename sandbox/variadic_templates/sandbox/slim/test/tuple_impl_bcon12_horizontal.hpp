#ifndef TUPLE_IMPL_BCON12_VERTICAL_INCLUDE_HPP
#define TUPLE_IMPL_BCON12_VERTICAL_INCLUDE_HPP
//Acknowlegements:
//  The following code was adapted from part of the code in
//    https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//
///////////////////////////////////////////////////////////////////////////////
// tuple.cpp
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdio>
#include <utility>
#include <functional>
#include <type_traits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#ifndef BRANCHING_FACTOR
#define BRANCHING_FACTOR 7
#endif

#ifndef DEPTH
#define DEPTH 7
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

namespace detail
{
    extern void* enabler;

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

    ///////////////////////////////////////////////////////////////////////////
    // ints
    template<int ...I>
    struct ints
    {};

    ///////////////////////////////////////////////////////////////////////////
    // indices
    template<int N, typename Ints>
    struct indices_;

    template<int N, int... I>
    struct indices_<N, ints<I...>>
      : indices_<N-1, ints<N-1, I...>>
    {};

    template<int... I>
    struct indices_<0, ints<I...>>
    {
        typedef ints<I...> type;
    };

    template<int I>
    using indices = typename indices_<I, ints<>>::type;

    ///////////////////////////////////////////////////////////////////////////
    // tuple_elem
    template<int I, typename T>
    struct tuple_elem
    {
        DEFAULTS(tuple_elem)

        template<typename U
          , ENABLE_IF(!std::is_same<U, tuple_elem &>::value)>
        explicit constexpr tuple_elem(U &&u)
          : value(static_cast<U &&>(u))
        {}

        typedef T type;
        T value;
    };

    ///////////////////////////////////////////////////////////////////////////
    // tuple_impl
    template<typename Ints, typename ...T>
    struct tuple_impl;

    template<int... Ints, typename H, typename ...T>
    struct tuple_impl<ints<0, Ints...>, H, T...>
        // can't seem to expand two packs in lock step with unrolling. Huh.
      : tuple_elem<0, H>, tuple_elem<Ints, T>...
    {
        DEFAULTS(tuple_impl)

        template<typename U, typename ...V
          , ENABLE_IF(sizeof...(V) != 0 || !std::is_same<U, tuple_impl &>::value)>
        explicit constexpr tuple_impl(U &&u, V &&...v) // HACK around gcc bug #53036
          : tuple_elem<0, H>(static_cast<U &&>(u))
          , tuple_elem<Ints, T>(static_cast<V &&>(v))...
        {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // get
    template<int I, typename T>
    constexpr T &get(tuple_elem<I, T> &t) noexcept
    {
        return t.value;
    }

    template<int I, typename T>
    constexpr T const &get(tuple_elem<I, T> const &t) noexcept
    {
        return t.value;
    }

    template<int I, typename T>
    constexpr T &&get(tuple_elem<I, T> &&t) noexcept
    {
        return static_cast<T &&>(t.value);
    }

    ///////////////////////////////////////////////////////////////////////////
    // get_elem
    template<int I, typename T>
    tuple_elem<I, T> get_elem(tuple_elem<I, T> const &);
}

using detail::get;

///////////////////////////////////////////////////////////////////////////////
// tuple_element
template<int I, typename Tuple>
struct tuple_element
  : decltype(detail::get_elem<I>(std::declval<Tuple>()))
{};

///////////////////////////////////////////////////////////////////////////////
// tuple
template<typename ...T>
struct tuple_bench;

template<>
struct tuple_bench<>
{};

template<typename H, typename ...T>
struct tuple_bench<H, T...>
  : detail::tuple_impl<detail::indices<sizeof...(T) + 1>, H, T...>
{
    typedef detail::tuple_impl<detail::indices<sizeof...(T) + 1>, H, T...> impl_type;

    DEFAULTS(tuple_bench)

    // not explicit to allow things like: return {42, "allo"};
    template<typename U, typename ...V
        , ENABLE_IF(sizeof...(V) == sizeof...(T))
        , ENABLE_IF(sizeof...(V) != 0 || !std::is_same<U, tuple_bench &>::value)>
    constexpr tuple_bench(U &&u, V &&...v)
      : impl_type(static_cast<U &&>(u), static_cast<V &&>(v)...)
    {}
};

///////////////////////////////////////////////////////////////////////////////
// make_tuple
template<typename ...T>
tuple_bench<detail::as_tuple_element<T>...> make_tuple(T &&...t)
{
    return {t...};
}

#endif

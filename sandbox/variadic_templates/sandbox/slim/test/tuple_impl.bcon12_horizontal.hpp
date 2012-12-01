#ifndef TUPLE_IMPL_BCON12_HORIZONTAL_INCLUDE_HPP
#define TUPLE_IMPL_BCON12_HORIZONTAL_INCLUDE_HPP
//Acknowlegements:
//  The following code was adapted from part of the code in
//    https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "./make_indexes.hpp"

#include "./RETURN_ENABLE_IF_DEFAULTS.hpp"

namespace detail
{
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
    struct tuple_impl<detail::int_indexes<0, Ints...>, H, T...>
        // can't seem to expand two packs in lock step with unrolling. Huh.
      : tuple_elem<0, H>, tuple_elem<Ints, T>...
    {
        DEFAULTS(tuple_impl)

      #if TUPLE_TEMPLATED_CTOR == 1
        template<typename U, typename ...V
          , ENABLE_IF(sizeof...(V) != 0 || !std::is_same<U, tuple_impl &>::value)>
        explicit constexpr tuple_impl(U &&u, V &&...v) // HACK around gcc bug #53036
          : tuple_elem<0, H>(static_cast<U &&>(u))
          , tuple_elem<Ints, T>(static_cast<V &&>(v))...
        {}
      #endif
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

}

using detail::get;

///////////////////////////////////////////////////////////////////////////////
// tuple_bench
template<typename ...T>
struct tuple_bench;

template<>
struct tuple_bench<>
{};

template<typename H, typename ...T>
struct tuple_bench<H, T...>
  : detail::tuple_impl
    < typename detail::make_indexes<sizeof...(T)+1>::type
    , H
    , T...
    >
{
    DEFAULTS(tuple_bench)
  
  #if TUPLE_TEMPLATED_CTOR == 1
        typedef 
      detail::tuple_impl
      < typename detail::make_indexes<sizeof...(T)+1>::type
      , H
      , T...
      > 
    impl_type;

    // not explicit to allow things like: return {42, "allo"};
    template<typename U, typename ...V
        , ENABLE_IF(sizeof...(V) == sizeof...(T))
        , ENABLE_IF(sizeof...(V) != 0 || !std::is_same<U, tuple_bench &>::value)>
    constexpr tuple_bench(U &&u, V &&...v)
      : impl_type(static_cast<U &&>(u), static_cast<V &&>(v)...)
    {}
  #endif
};

#endif

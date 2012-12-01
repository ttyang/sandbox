#ifndef TUPLE_IMPL_HORIZONTAL_INCLUDE_HPP
#define TUPLE_IMPL_HORIZONTAL_INCLUDE_HPP
//Acknowlegements:
//  Most of the templated CTOR's code was copied parts of the code in
//    https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//
#include <type_traits>

#if TUPLE_TEMPLATED_CTOR == 1
#include "./RETURN_ENABLE_IF_DEFAULTS.hpp"
#endif

#include "./make_indexes.hpp"

namespace detail
{

  template<int Index, typename Value>
  struct key_value
  {
    #if TUPLE_TEMPLATED_CTOR == 1 
      DEFAULTS(key_value)
      
          template
          < typename U
          , ENABLE_IF(!std::is_same<U, key_value &>::value)
          >
          explicit constexpr
        key_value(U &&u)
          : value(static_cast<U &&>(u))
        {}
    #endif
      Value value;
  };
  
    template
    < typename Indexes
    , typename... Elements
    >
  struct tuple_impl
  ;

    template
    < int... Indices
    , typename Element0
    , typename... Elements
    >
  struct tuple_impl
    < int_indexes<0,Indices...>
    , Element0
    , Elements...
    >
    : key_value<0, Element0>
    , key_value<Indices, Elements>... 
  {
  
    #if TUPLE_TEMPLATED_CTOR == 1
      DEFAULTS(tuple_impl)

        template
        < typename U0
        , typename ...Us
        , ENABLE_IF(sizeof...(Us) != 0 || !std::is_same<U0, tuple_impl &>::value)
        >
        explicit constexpr
      tuple_impl(U0 &&u0, Us &&...us) // HACK around gcc bug #53036
        : key_value< 0      , Element0>(static_cast<U0 &&>(u0))
        , key_value< Indices, Elements>(static_cast<Us &&>(us))...
      {}
    #endif

  };

    template<int Index, typename Value>
      constexpr
    Value&
  get(key_value<Index,Value>& ndx_val)
  {
      return ndx_val.value;
  }
    template<int Index, typename Value>
      constexpr
    Value const&
  get(key_value<Index,Value>const& ndx_val)
  {
      return ndx_val.value;
  }
    template<int Index, typename Value>
      constexpr
    Value&&
  get(key_value<Index,Value>&& ndx_val)
  {
      return static_cast<Value&&>(ndx_val.value);
  }

}//detail namespace 

using detail::get;
 
    template
    < typename... Elements
    >
  struct tuple_bench
  ;
    template
    <
    >
  struct tuple_bench
    <
    >
  {
  };
    template
    < typename Element0
    , typename... Elements
    >
  struct tuple_bench
    < Element0
    , Elements...
    >
    : detail::tuple_impl
      < detail::indices<1+sizeof...(Elements)>
      , Element0
      , Elements...
      > 
  {
   #if TUPLE_TEMPLATED_CTOR == 1
     DEFAULTS(tuple_bench)
      
          typedef 
        detail::tuple_impl
        < detail::indices<1+sizeof...(Elements)>
        , Element0
        , Elements...
        > 
      impl_type
      ;
      // not explicit to allow things like: return {42, "allo"};
        template
        < typename U0
        , typename ...Us
        , ENABLE_IF(sizeof...(Us) == sizeof...(Elements))
        , ENABLE_IF(sizeof...(Us) != 0 || !std::is_same<U0, tuple_bench &>::value)
        >
        constexpr
      tuple_bench(U0 &&u0, Us &&...us)
        : impl_type
          ( static_cast<U0 &&>(u0)
          , static_cast<Us &&>(us)...
          )
      {}
    #endif
  };

#endif//TUPLE_IMPL_HORIZONTAL_INCLUDE_HPP

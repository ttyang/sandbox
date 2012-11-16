#ifndef TUPLE_IMPL_HORIZONTAL_INCLUDE_HPP
#define TUPLE_IMPL_HORIZONTAL_INCLUDE_HPP
#include "make_indexes.hpp"  
  template<typename Key, typename Value>
  struct element
  ;
  template<int Key, typename Value>
  struct element<int_key<Key>,Value>
  {
      Value value;
  };
  template<typename Keys, typename... Args>
  struct tuple_impl
  ;
  template<int... Indices, typename... Args>
  struct tuple_impl<int_indexes<Indices...>, Args...>
    : element<int_key<Indices>, Args>... 
  {};
  
  template<typename... Args>
  struct tuple_bench
    : tuple_impl<typename make_indexes<sizeof...(Args)>::type, Args...> 
  {
  };

  template<int Key, typename Value>
    Value&
  get(element<int_key<Key>,Value>& key_val)
  {
      return key_val.value;
  }
#endif//TUPLE_IMPL_HORIZONTAL_INCLUDE_HPP

#ifndef TUPLE_IMPL_VERTICAL_INCLUDE_HPP
#define TUPLE_IMPL_VERTICAL_INCLUDE_HPP
  template<int Index,typename... Args>
  struct tuple_impl;
  template<int Index>
  struct tuple_impl<Index>
  {
      void at_value(){}
  };
  
#if !defined(TUPLE_CHUNK)
  #define TUPLE_CHUNK 10
#endif  
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#define TUPLE_IMPL_TYPE_NAME H
#define TUPLE_IMPL_MEMB_NAME h
#define TUPLE_IMPL_MEMBER(z_IGNORE,MEMB_NUMB,data_IGNORE)\
	  BOOST_PP_CAT(TUPLE_IMPL_TYPE_NAME,MEMB_NUMB)\
      BOOST_PP_CAT(TUPLE_IMPL_MEMB_NAME,MEMB_NUMB)\
        ;\
	  BOOST_PP_CAT(TUPLE_IMPL_TYPE_NAME,MEMB_NUMB)&\
      at_value\
        ( int_key<Index+MEMB_NUMB>\
        )\
        {\
            return BOOST_PP_CAT(TUPLE_IMPL_MEMB_NAME,MEMB_NUMB);\
        }\
        /**/

#define TUPLE_IMPL_STRUCT_TAIL(z_IGNORE, ARITY, data_IGNORE) \
  template<int Index, BOOST_PP_ENUM_PARAMS(ARITY, typename TUPLE_IMPL_TYPE_NAME)> \
  struct tuple_impl<Index, BOOST_PP_ENUM_PARAMS(ARITY, TUPLE_IMPL_TYPE_NAME)> \
  { \
      BOOST_PP_REPEAT(ARITY,TUPLE_IMPL_MEMBER,~) \
  }; \
  /**/
  
  BOOST_PP_REPEAT_FROM_TO(1,TUPLE_CHUNK,TUPLE_IMPL_STRUCT_TAIL,~)
  
  template<int Index, BOOST_PP_ENUM_PARAMS(TUPLE_CHUNK, typename TUPLE_IMPL_TYPE_NAME), typename... Others>
  struct tuple_impl<Index, BOOST_PP_ENUM_PARAMS(TUPLE_CHUNK, TUPLE_IMPL_TYPE_NAME), Others...>
  : tuple_impl<Index+TUPLE_CHUNK, Others...>
  {
      typedef tuple_impl<Index+TUPLE_CHUNK,Others...> base;
      using base::at_value;
      
      BOOST_PP_REPEAT(TUPLE_CHUNK,TUPLE_IMPL_MEMBER,~)
  };
  
#undef TUPLE_IMPL_TYPE_NAME
#undef TUPLE_IMPL_MEMB_NAME
#undef TUPLE_IMPL_MEMBER
#undef TUPLE_IMPL_STRUCT_TAIL

#ifdef VERT_AMORT
  #include "make_indexes.hpp"
#endif
  
  template<typename... Args>
  struct tuple_bench
  : tuple_impl<0,Args...>
#ifdef VERT_AMORT
  , make_indexes<sizeof...(Args)>::type 
    //This is actually useless for the purpose of VERTICAL tuple.
    //The real purpose is to cause this VERTICAL tuple to incur
    //the same make_indexes overhead as the HORIZONTAL tuple.
    //The justification for this is that the cost of
    //make_indexes should be amortized over the *assumed*
    //many instances of the same make_indexes used in all
    //HORIZONTAL tuples with same size.
#endif
  {};
  
  template< int Index, typename Tuple>
    auto
  get(Tuple& tuple) -> decltype(tuple.at_value(int_key<Index>()))
  {
      return tuple.at_value(int_key<Index>());
  }
#endif//TUPLE_IMPL_VERTICAL_INCLUDE_HPP

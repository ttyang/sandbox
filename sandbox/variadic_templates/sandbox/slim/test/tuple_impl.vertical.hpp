#ifndef TUPLE_IMPL_VERTICAL_INCLUDE_HPP
#define TUPLE_IMPL_VERTICAL_INCLUDE_HPP
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if TUPLE_TEMPLATED_CTOR == 1
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#endif

namespace detail
{
  template<int Key>
  struct int_key
  /**@brief
   *  Provide a means for overloading the
   *  tuple_impl::get_elem methods
   *  to retrieve Key'th element in tuple.
   */
  {};
  
  template<int Index,typename... Elements>
  struct tuple_impl;
  template<int Index>
  struct tuple_impl<Index>
  /**@brief
   *  Dummy tuple_impl to allow:
   *    using tuple_tail::get_elem
   *  in subclasses.
   */
  {
      void get_elem(){}
  };
  
#if !defined(UNROLL_MAX)
  #define UNROLL_MAX 10
#endif

#define TUPLE_IMPL_ELEM_TYPE elem_type
#define TUPLE_IMPL_ELEM_MEMB elem_memb
#if TUPLE_TEMPLATED_CTOR == 1

#define DISABLE_COPY_IF(CLASS, N, T)                                                                \
    BOOST_PP_COMMA_IF(BOOST_PP_EQUAL(N, 1))                                                         \
    BOOST_PP_EXPR_IF(                                                                               \
        BOOST_PP_EQUAL(N, 1)                                                                        \
      , ENABLE_IF(!std::is_same<T, CLASS &>::value)                                                 \
    )                                                                                               \
    /**/
#define TUPLE_CTORS_ENUM(CLASS,ARITY)\
  DEFAULTS(CLASS)\
\
  template<BOOST_PP_ENUM_PARAMS(ARITY, typename U)                    \
      DISABLE_COPY_IF(tuple_bench, ARITY, U0)                               \
  >                                                               \
  constexpr CLASS(BOOST_PP_ENUM_BINARY_PARAMS(ARITY, U, &&u))         \
    : BOOST_PP_ENUM(ARITY, INIT, ~)                                   \
  {}                                                              \
\
  /**/
#define TUPLE_CTORS_TAIL(CLASS,ARITY,ELEMS_TAIL,ARGS_TAIL)\
  DEFAULTS(CLASS)\
\
  template<BOOST_PP_ENUM_PARAMS(ARITY, typename U), typename ...ELEMS_TAIL \
    , ENABLE_IF(sizeof...(ELEMS_TAIL)==sizeof...(ARGS_TAIL)) \
      DISABLE_COPY_IF(CLASS, ARITY, U0) \
  > \
  constexpr CLASS(BOOST_PP_ENUM_BINARY_PARAMS(ARITY, U, &&u), ARGS_TAIL &&...args_tail) \
    : BOOST_PP_ENUM(ARITY, INIT, ~) \
    , tuple_tail(static_cast<ARGS_TAIL &&>(args_tail)...) \
  {} \
  /**/
#else
#define TUPLE_CTORS_ENUM(CLASS,ARITY)\
  /**/
#define TUPLE_CTORS_TAIL(CLASS,ARITY)\
  /**/
#endif

#define TUPLE_IMPL_MEMBER(z_IGNORE,MEMB_NUMB,START_INDEX)\
	  BOOST_PP_CAT(TUPLE_IMPL_ELEM_TYPE,MEMB_NUMB)\
      BOOST_PP_CAT(TUPLE_IMPL_ELEM_MEMB,MEMB_NUMB)\
        ;\
	  BOOST_PP_CAT(TUPLE_IMPL_ELEM_TYPE,MEMB_NUMB)&\
      get_elem\
        ( int_key<START_INDEX+MEMB_NUMB>\
        )\
        {\
            return BOOST_PP_CAT(TUPLE_IMPL_ELEM_MEMB,MEMB_NUMB);\
        }\
        /**/

#define TUPLE_IMPL_STRUCT_ENUM(z_IGNORE, ARITY, data_IGNORE) \
  template<int Index, BOOST_PP_ENUM_PARAMS(ARITY, typename TUPLE_IMPL_ELEM_TYPE)> \
  struct tuple_impl<Index, BOOST_PP_ENUM_PARAMS(ARITY, TUPLE_IMPL_ELEM_TYPE)> \
  { \
      BOOST_PP_REPEAT(ARITY,TUPLE_IMPL_MEMBER,Index) \
      TUPLE_CTORS_ENUM(tuple_impl,ARITY) \
  }; \
  /**/
  
  BOOST_PP_REPEAT_FROM_TO(1,UNROLL_MAX,TUPLE_IMPL_STRUCT_ENUM,~)
  
    template
    < int Index
    , BOOST_PP_ENUM_PARAMS(UNROLL_MAX
    , typename... ElemTail
    >
  struct tuple_impl
    < Index
    , BOOST_PP_ENUM_PARAMS(UNROLL_MAX, TUPLE_IMPL_ELEM_TYPE)
    , ElemTail...
    >
  : tuple_impl<Index+UNROLL_MAX, ElemTail...>
  {
      typedef tuple_impl< ElemTail...> tuple_tail;
      using tuple_tail::get_elem;
      
      BOOST_PP_REPEAT(UNROLL_MAX,TUPLE_IMPL_MEMBER,Index)
      TUPLE_CTORS_TAIL(tuple_impl,UNROLL_MAX,ElemTail)
  };
  
#undef TUPLE_IMPL_ELEM_TYPE
#undef TUPLE_IMPL_ELEM_MEMB
#undef TUPLE_IMPL_MEMBER
#undef TUPLE_IMPL_STRUCT_ENUM
}

#ifdef VERT_AMORT
  #include "make_indexes.hpp"
#endif
  
  template<typename... Elements>
  struct tuple_bench
  : detail::tuple_impl<0,Elements...>
#ifdef VERT_AMORT
  , detail::make_indexes<sizeof...(Elements)>::type 
    //This is actually useless for the purpose of VERTICAL tuple.
    //The real purpose is to cause this VERTICAL tuple to incur
    //the same make_indexes overhead as the HORIZONTAL tuple.
    //The justification for this is that the cost of
    //make_indexes should be amortized over the *assumed*
    //many instances of the same make_indexes used in all
    //HORIZONTAL tuples with same size.
#endif
  {
  };
  
  template< int Index, typename Tuple>
    auto
  get(Tuple& tuple) -> decltype(tuple.get_elem(detail::int_key<Index>()))
  {
      return tuple.get_elem(detail::int_key<Index>());
  }
#endif//TUPLE_IMPL_VERTICAL_INCLUDE_HPP

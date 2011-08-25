//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_ANY_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_ANY_HPP_INCLUDED

//==============================================================================
// Internals for meta::any_
//=============================================================================
#include <boost/mpl/end.hpp>
#include <boost/mpl/not.hpp>
#include <boost/dispatch/meta/na.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_same.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <boost/dispatch/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace boost { namespace dispatch { namespace details
{
  //============================================================================
  // Recursive variadic version
  //============================================================================
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template< class Predicate, class... Args> struct any_impl;

  template< class Pred, class Head, class... Tails>
  struct  any_impl<Pred,Head,Tails...>
        : boost::mpl::or_ < boost::mpl::apply1<Pred,Head>
                          , any_impl<Pred,Tails...>
                          >
  {};

  template< class Pred, class T>
  struct  any_impl<Pred, T>
        : boost::mpl::eval_if_c < boost::mpl::is_sequence<T>::value
                                , boost::mpl::not_<
                                    boost::is_same< typename
                                                    boost::mpl::find_if<T,Pred>::type
                                                  , typename
                                                    boost::mpl::end<T>::type
                                                  >
                                                >
                                , boost::mpl::apply1<Pred,T>
                                >::type
  {};
  #else
  //============================================================================
  // Macro based version
  //============================================================================
  #define M1(z,n,t)                                           \
  || boost::mpl::apply1<Pred,BOOST_PP_CAT(A,n)>::type::value  \
  /**/

  template< class Pred
          , BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_DISPATCH_MAX_META_ARITY
                                        , class A
                                        , = dispatch::meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct  any_impl
        : boost::mpl::bool_<false BOOST_PP_REPEAT(BOOST_DISPATCH_MAX_META_ARITY,M1,~)>
  {};

  template< class Pred, class T>
  struct  any_impl<Pred, T>
        : boost::mpl::
          eval_if_c < boost::mpl::is_sequence<T>::value
                    , boost::mpl::not_<
                        boost::is_same< typename
                                        boost::mpl::find_if<T,Pred>::type
                                      , typename
                                        boost::mpl::end<T>::type
                                      >
                                    >
                    , boost::mpl::apply1<Pred,T>
                    >::type
  {};

  #define M0(z,n,t)                                         \
  template<class Pred, BOOST_PP_ENUM_PARAMS(n,class A)>     \
  struct  any_impl<Pred,BOOST_PP_ENUM_PARAMS(n,A)>          \
        : boost::mpl::bool_<false BOOST_PP_REPEAT(n,M1,~)>  \
  {};                                                       \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_DISPATCH_MAX_META_ARITY,M0,~)

  #undef M1
  #undef M0

  #endif

} } }

#endif

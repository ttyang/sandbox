/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_META_IS_VECTORIZABLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_IS_VECTORIZABLE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/dispatch/meta/na.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T,class Extension>
  struct is_vectorizable
       : boost::mpl::bool_<!boost::is_same< typename as_simd<T,Extension>::type
                                          , boost::dispatch::meta::na_
                                          >::value
                          >
  {};
} } }

#endif

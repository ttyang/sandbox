/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_CATEGORY_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class X>
  struct simd_ : simd_< typename T::parent, X >
  {
    typedef simd_< typename T::parent, X >  parent;
    typedef T                               base;
  };

  template<class T,class X>
  struct  simd_< unspecified_<T>, X >
        : generic_< typename property_of<T>::type >
  {
    typedef generic_< typename property_of<T>::type > parent;
    typedef unspecified_<T>                           base;
  };
} } }

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::simd_;
} } }

#endif

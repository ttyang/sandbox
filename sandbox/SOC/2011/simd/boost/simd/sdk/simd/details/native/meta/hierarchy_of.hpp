//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_HIERARCHY_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class X, class Origin>
  struct hierarchy_of< simd::native<T, X>, Origin>
  {
    typedef typename hierarchy_of<T, Origin>::base  base;
    typedef typename simd::ext::simd_<base, X>      type;
  };
} } }

#endif


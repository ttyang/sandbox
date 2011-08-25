/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_META_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_META_IS_ALIGNED_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/dispatch/error/static_assert.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>

namespace boost { namespace simd {  namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Boolean meta-function checking if a integral constant is aligned on a given
  // power of 2 boundary.
  // Documentation: reference/sdk/aligned/meta/is_aligned_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t V, std::size_t N = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct is_aligned_c : boost::mpl::bool_<!(V & (N-1) )>
  {
    BOOST_DISPATCH_STATIC_ASSERT ( (meta::is_power_of_2_c<N>::value)
                      , INVALID_ALIGNMENT_VALUE
                      , "Alignment detection done on a non-power of two boundary."
                      );
  };

  //////////////////////////////////////////////////////////////////////////////
  // Boolean meta-function checking if a Integral Constant is aligned on a given
  // power of 2 boundary.
  // Documentation: reference/sdk/aligned/meta/is_aligned.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class V, class N = boost::mpl::size_t<BOOST_SIMD_CONFIG_ALIGNMENT> >
  struct is_aligned : is_aligned_c<V::value,N::value> {};

} } }

#endif

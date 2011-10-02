/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_IO_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_IO_HPP_INCLUDED

#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/pack/evaluate.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for pack<T,C>
  ////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t C>
  BOOST_DISPATCH_FORCE_INLINE
  std::ostream& operator<<(std::ostream& os, pack<T,C> const& v )
  {
    return os << evaluate(v);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for SIMD expression
  ////////////////////////////////////////////////////////////////////////////
  template<class X,class T,class C>
  BOOST_DISPATCH_FORCE_INLINE
  std::ostream& operator<<(std::ostream& os, expression<X,T,C> const& v )
  {
    return os << evaluate(v);
  }

} }

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_REALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_REALLOCATE_HPP_INCLUDED

#include <cstring>
#include <cstddef>
#include <boost/simd/sdk/memory/config.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>

namespace boost { namespace simd {  namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Reallocate a raw buffer of bytes to a new size
  //////////////////////////////////////////////////////////////////////////////
  byte* reallocate( byte* ptr, std::size_t nbytes, std::size_t obytes);

  //////////////////////////////////////////////////////////////////////////////
  // Reallocate a raw buffer of bytes to a new size using an allocator
  //////////////////////////////////////////////////////////////////////////////
  template<class Allocator> inline byte*
  reallocate( Allocator& a,  byte* ptr, std::size_t nbytes, std::size_t obytes)
  {
    byte* result;
    if(obytes < nbytes)
    {
      byte* tmp = reinterpret_cast<byte*>(allocate(a,nbytes));
      std::memcpy(tmp,ptr,obytes);
      deallocate(a,ptr,obytes);
      result = tmp;
    }
    else
    {
      result = ptr;
    }

    return result;
  }
} } }

#endif

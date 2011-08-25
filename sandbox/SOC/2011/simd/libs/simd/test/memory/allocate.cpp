/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::memory::allocate and related functions"

#include <boost/simd/sdk/memory/allocate.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/deallocate.hpp>
#include <boost/simd/sdk/memory/reallocate.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


////////////////////////////////////////////////////////////////////////////////
// Test allocating and deallocating
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(allocate)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::memory::is_aligned;

  byte* ptr = 0;
  NT2_TEST( is_aligned(ptr = allocate(5)) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

////////////////////////////////////////////////////////////////////////////////
// Test reallocating and deallocating
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(reallocate)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::reallocate;
  using boost::simd::memory::deallocate;
  using boost::simd::memory::is_aligned;

  byte *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = reallocate(ptr,5,0)) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  // If shrinking, do nothing to pointer
  NT2_TEST( is_aligned(ptr2 = reallocate(ptr,2,5)) );
  NT2_TEST_EQUAL(ptr,ptr2);
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = reallocate(ptr2,7,2)) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

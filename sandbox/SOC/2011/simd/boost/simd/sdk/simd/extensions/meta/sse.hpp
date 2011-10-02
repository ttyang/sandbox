/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

////////////////////////////////////////////////////////////////////////////////
// SSE extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<> struct is_simd_specific<__m128 , tag::sse_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m128d, tag::sse_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m128i, tag::sse_> : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  as_simd<T,tag::sse_>
        : boost::mpl::if_ < boost::is_integral<T>
                          , __m128i
                          , typename  boost::mpl
                            ::if_ < boost::is_same<T,float>
                                  , __m128
                                  , typename  boost::mpl
                                    ::if_ < boost::is_same<T,double>
                                        , __m128d
                                        , dispatch::meta::na_
                                        >::type
                                  >::type
                          >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m128 ,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128d,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128i,X>  { typedef tag::sse_ type; };
} } }

#ifndef BOOST_SIMD_NO_STRICT_ALIASING
////////////////////////////////////////////////////////////////////////////////
// Conversion between vector types
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace details
{
    #if defined(__GNUC__)
        #define BOOST_SIMD_SSE_CONVERT convert_cast
    #else
        #define BOOST_SIMD_SSE_CONVERT union_cast
    #endif

    template<> struct bitwise_cast<__m128 , __m128d> : BOOST_SIMD_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128 , __m128i> : BOOST_SIMD_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128d, __m128 > : BOOST_SIMD_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128d, __m128i> : BOOST_SIMD_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128i, __m128 > : BOOST_SIMD_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128i, __m128d> : BOOST_SIMD_SSE_CONVERT {};

    #undef BOOST_SIMD_SSE_CONVERT
} } }
#endif

#endif

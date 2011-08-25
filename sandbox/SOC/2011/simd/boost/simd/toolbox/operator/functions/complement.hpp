//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/operator/include.hpp>
#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    typedef boost::proto::tag::complement complement_;
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , complement  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , bitwise_not , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , b_not       , 1 )
} }

#endif

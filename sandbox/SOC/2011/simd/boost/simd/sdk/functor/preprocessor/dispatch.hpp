//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED
#define BOOST_SIMD_SDK_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>

#define BOOST_SIMD_REGISTER_DISPATCH(Tag,Site,Types,Seq)                      \
BOOST_DISPATCH_REGISTER_DISPATCH((boost)(simd)(ext),Tag,Site,Types,Seq)

#define BOOST_SIMD_REGISTER_DISPATCH_TPL(Tag,Site,Types,Seq)                  \
BOOST_DISPATCH_REGISTER_DISPATCH_TPL((boost)(simd)(ext),Tag,Site,Types,Seq)

#define BOOST_SIMD_REGISTER_DISPATCH_IF(Tag,Site,Types,Cond,Ret,Seq)          \
BOOST_DISPATCH_REGISTER_DISPATCH_IF((boost)(simd)(ext),Tag,Site,Types,Cond,Ret,Seq)

#define BOOST_SIMD_REGISTER_DISPATCH_IF_TPL(Tag,Site,Types,Cond,Ret,Seq)      \
BOOST_DISPATCH_REGISTER_DISPATCH_IF_TPL((boost)(simd)(ext),Tag,Site,Types,Cond,Ret,Seq)

#endif

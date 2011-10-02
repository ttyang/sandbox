//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_REF_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_REF_HPP_INCLUDED

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct as_ref
  {
    typedef T const& type;
  };
  
  template<class T>
  struct as_ref<T&>
  {
    typedef T& type;
  };
  
  template<class T>
  struct as_ref<T const>
  {
    typedef T const& type;
  };
} } }

#endif

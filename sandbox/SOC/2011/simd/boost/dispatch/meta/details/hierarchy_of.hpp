//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_HIERARCHY_OF_HPP_INCLUDED

#include <boost/dispatch/meta/details/scalar.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace dispatch { namespace details
{
  //============================================================================
  // Overload for fundamental types
  //============================================================================
  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename
                        boost::enable_if< boost::is_fundamental<T> >::type
                      >
  {
    typedef typename meta::property_of<T, Origin>::type  base;
    typedef meta::scalar_<base>                          type;
  };
} } }

#endif

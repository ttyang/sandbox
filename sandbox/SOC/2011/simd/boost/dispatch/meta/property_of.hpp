//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_PROPERTY_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_PROPERTY_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::property_of \metafunction
 */

//////////////////////////////////////////////////////////////////////////////
// Types property is defined on fundamental types as a lattice of classes
// mimicking the type structuration in C++
//////////////////////////////////////////////////////////////////////////////

#include <boost/dispatch/meta/details/hierarchy_base.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Origin = T, class Enable = void>
  struct  property_of
  {
    typedef typename meta::hierarchy_of<T, Origin>::base type;
  };
}
    
namespace meta
{
  template<class T, class Origin = T>
  struct  property_of
        : details::property_of< typename meta::strip<T>::type
                              , typename meta::strip<Origin>::type
                              >
  {};

  template<class T, class Origin>
  struct  property_of<T&, Origin> : property_of<T, typename meta::strip<Origin>::type> {};
  
  template<class T, class Origin>
  struct  property_of<T const, Origin> : property_of<T, typename meta::strip<Origin>::type> {};
} } }

#include <boost/dispatch/meta/details/property_of.hpp>

#endif

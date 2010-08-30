/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829
#define BOOST_ITL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829

#include <boost/itl/type_traits/has_inverse.hpp>
#include <boost/itl/functors.hpp>

namespace boost{ namespace itl
{

template<class Type, class Combiner>
struct adds_inversely
{
    typedef adds_inversely type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_<has_inverse<Type>, is_negative<Combiner> >::value)); 
};

}} // namespace boost itl

#endif // BOOST_ITL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829



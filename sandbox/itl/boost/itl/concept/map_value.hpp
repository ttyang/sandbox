/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ITL_CONCEPT_MAP_VALUE_HPP_JOFA_100924
#define BOOST_ITL_CONCEPT_MAP_VALUE_HPP_JOFA_100924

#include <boost/itl/type_traits/is_map.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Map>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_map<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return it_->first;
}

template<class Type, class Iterator>
inline typename enable_if<is_map<Type>, const typename Type::codomain_type>::type&
co_value(Iterator it_)
{
    return it_->second;
}

template<class Type>
inline typename enable_if<is_map<Type>, typename Type::value_type>::type
make_value(const typename Type::     key_type& key_val, 
           const typename Type::codomain_type&  co_val)
{
    return typename Type::value_type(key_val, co_val);
}


}} // namespace boost icl

#endif



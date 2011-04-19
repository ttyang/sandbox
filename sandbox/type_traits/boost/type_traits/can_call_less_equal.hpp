//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_CAN_CALL_LESS_EQUAL_HPP_INCLUDED
#define BOOST_TT_CAN_CALL_LESS_EQUAL_HPP_INCLUDED

#define BOOST_TT_TRAIT_NAME can_call_less_equal
#define BOOST_TT_TRAIT_OP <=
#define BOOST_TT_FORBIDDEN_IF\
   ::boost::type_traits::ice_or<\
      /* pointer and fundamental */\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< Lhs_noref >::value,\
         ::boost::is_fundamental< Rhs_nocv >::value\
      >::value,\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< Rhs_noref >::value,\
         ::boost::is_fundamental< Lhs_nocv >::value\
      >::value,\
      /* two pointers but no inheritance or no void* */\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< Lhs_noref >::value,\
         ::boost::is_pointer< Rhs_noref >::value,\
         ::boost::type_traits::ice_not<\
            ::boost::type_traits::ice_or<\
               ::boost::is_base_of< Lhs_noptr, Rhs_noptr >::value,\
               ::boost::is_base_of< Rhs_noptr, Lhs_noptr >::value,\
               ::boost::is_same< Lhs_noptr, Rhs_noptr >::value,\
               ::boost::is_void< Lhs_noptr >::value,\
               ::boost::is_void< Rhs_noptr >::value\
            >::value\
         >::value\
      >::value\
   >::value


#include <boost/type_traits/detail/can_call_binary_operator.hpp>

#undef BOOST_TT_TRAIT_NAME
#undef BOOST_TT_TRAIT_OP
#undef BOOST_TT_FORBIDDEN_IF

#endif

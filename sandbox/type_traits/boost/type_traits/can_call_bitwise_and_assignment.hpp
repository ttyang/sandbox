//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_CAN_CALL_BITWISE_AND_ASSIGNMENT_HPP_INCLUDED
#define BOOST_TT_CAN_CALL_BITWISE_AND_ASSIGNMENT_HPP_INCLUDED

#define BOOST_TT_TRAIT_NAME can_call_bitwise_and_assignment
#define BOOST_TT_TRAIT_OP &=
#define BOOST_TT_FORBIDDEN_IF\
   ::boost::type_traits::ice_or<\
      /* two fundamental, one non integral or lhs is const*/\
      ::boost::type_traits::ice_and<\
         ::boost::is_fundamental< Lhs_nocv >::value,\
         ::boost::is_fundamental< Rhs_nocv >::value,\
         ::boost::type_traits::ice_or<\
            ::boost::type_traits::ice_not< ::boost::is_integral< Lhs_noref >::value >::value,\
            ::boost::type_traits::ice_not< ::boost::is_integral< Rhs_noref >::value >::value,\
            ::boost::is_const< Lhs_noref >::value\
         >::value\
      >::value,\
      /* one fundamental, one pointer */\
      ::boost::type_traits::ice_or<\
         ::boost::type_traits::ice_and<\
            ::boost::is_fundamental< Lhs_nocv >::value,\
            ::boost::is_pointer< Rhs_noref >::value\
         >::value,\
         ::boost::type_traits::ice_and<\
            ::boost::is_fundamental< Rhs_nocv >::value,\
            ::boost::is_pointer< Lhs_noref >::value\
         >::value\
      >::value,\
      /* two pointers */\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< Lhs_noref >::value,\
         ::boost::is_pointer< Rhs_noref >::value\
      >::value\
   >::value


#include <boost/type_traits/detail/can_call_binary_operator.hpp>

#undef BOOST_TT_TRAIT_NAME
#undef BOOST_TT_TRAIT_OP
#undef BOOST_TT_FORBIDDEN_IF

#endif
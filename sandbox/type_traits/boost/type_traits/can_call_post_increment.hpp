//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_CAN_CALL_POST_INCREMENT_HPP_INCLUDED
#define BOOST_TT_CAN_CALL_POST_INCREMENT_HPP_INCLUDED

#define BOOST_TT_TRAIT_NAME can_call_post_increment
#define BOOST_TT_TRAIT_OP ++
#define BOOST_TT_FORBIDDEN_IF\
   /* void* or const fundamental */\
   ::boost::type_traits::ice_or<\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< Lhs_noref >::value,\
         ::boost::is_void< Lhs_noptr >::value\
      >::value,\
      ::boost::type_traits::ice_and<\
         ::boost::is_fundamental< Lhs_nocv >::value,\
         ::boost::is_const< Lhs_noref >::value\
     >::value\
   >::value


#include <boost/type_traits/detail/can_call_postfix_operator.hpp>

#undef BOOST_TT_TRAIT_NAME
#undef BOOST_TT_TRAIT_OP
#undef BOOST_TT_FORBIDDEN_IF

#endif
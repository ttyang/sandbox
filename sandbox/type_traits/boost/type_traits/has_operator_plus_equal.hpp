//  (C) Copyright 2009-2011 Frédéric Bron (frederic.bron@m4x.org)
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_plus_equal_HPP_INCLUDED
#define BOOST_TT_plus_equal_HPP_INCLUDED

#define BOOST_TT_TRAIT_NAME has_operator_plus_equal
#define BOOST_TT_TRAIT_OP +=
#define BOOST_TT_DEFAULT_RET void
#define BOOST_TT_FORBIDDEN_IF\
   ::boost::type_traits::ice_or<\
      /* LHS is fundamental and const, RHS is fundamental */\
      ::boost::type_traits::ice_and<\
         ::boost::is_fundamental< lhs_nocv >::value,\
         ::boost::is_const< lhs_noref >::value,\
         ::boost::is_fundamental< rhs_nocv >::value\
      >::value,\
      /* two pointers */\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< lhs_noref >::value,\
         ::boost::is_pointer< rhs_noref >::value\
      >::value,\
      /* void* with fundamental */\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< lhs_noref >::value,\
         ::boost::is_void< typename ::boost::remove_pointer< lhs_noref >::type >::value,\
         ::boost::is_fundamental< rhs_nocv >::value\
      >::value,\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< rhs_noref >::value,\
         ::boost::is_void< typename ::boost::remove_pointer< rhs_noref >::type >::value,\
         ::boost::is_fundamental< lhs_nocv >::value\
      >::value,\
      /* LHS==pointer and RHS==fundamental non integral */\
      ::boost::type_traits::ice_and<\
         ::boost::is_pointer< lhs_noref >::value,\
         ::boost::is_fundamental< rhs_nocv >::value,\
         ::boost::type_traits::ice_not< ::boost::is_integral< rhs_noref >::value >::value\
      >::value,\
      /* LHS==non bool fundamental and RHS==pointer */\
      ::boost::type_traits::ice_and<\
         ::boost::is_fundamental< lhs_nocv >::value,\
         ::boost::type_traits::ice_not< ::boost::is_same< bool, lhs_nocv >::value >::value,\
         ::boost::is_pointer< rhs_noref >::value\
      >::value\
   >::value


#include <boost/type_traits/detail/has_binary_operator.hpp>

#undef BOOST_TT_TRAIT_NAME
#undef BOOST_TT_TRAIT_OP
#undef BOOST_TT_DEFAULT_RET
#undef BOOST_TT_FORBIDDEN_IF

#endif

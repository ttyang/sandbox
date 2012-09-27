/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/strict_weak_order.hpp>

#include <boost/generic/assert.hpp>
#include <functional>

using boost::generic::std_concept::StrictWeakOrder;

BOOST_GENERIC_ASSERT( StrictWeakOrder< bool(int, int), int > );
BOOST_GENERIC_ASSERT( StrictWeakOrder< bool(&)(int, int), int > );
BOOST_GENERIC_ASSERT( StrictWeakOrder< bool(*)(int, int), int > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< void(int, int), int > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< bool(int, int), void > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< bool(int, int), char* > );

BOOST_GENERIC_ASSERT( StrictWeakOrder< std::less< int >, int > );
BOOST_GENERIC_ASSERT( StrictWeakOrder< std::greater< int >, int > );
BOOST_GENERIC_ASSERT( StrictWeakOrder< std::greater_equal< int >, int > );
BOOST_GENERIC_ASSERT( StrictWeakOrder< std::less_equal< int >, int > );

BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< std::less< int >, char* > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< std::greater< int >, char* > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< std::greater_equal< int >, char* > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< std::less_equal< int >, char* > );

struct strict_weak_order_type
{
  bool operator ()( int, int ) const;
};

BOOST_GENERIC_ASSERT( StrictWeakOrder< strict_weak_order_type, int > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< strict_weak_order_type, void* > );

struct not_strict_weak_order_type
{
  void operator ()( int, int ) const;
};

BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< not_strict_weak_order_type, int > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< void, void > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< void, int > );
BOOST_GENERIC_ASSERT_NOT( StrictWeakOrder< int, void > );

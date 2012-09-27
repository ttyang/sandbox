/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_dereference.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasDereference;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasDereference< int* > );
BOOST_GENERIC_ASSERT( HasDereference< long* > );
BOOST_GENERIC_ASSERT( HasDereference< short* > );
BOOST_GENERIC_ASSERT( HasDereference< unsigned* > );

BOOST_GENERIC_ASSERT( SameType< HasDereference< int* >::result_type, int& > );
BOOST_GENERIC_ASSERT( SameType< HasDereference< long* >::result_type, long& > );
BOOST_GENERIC_ASSERT( SameType< HasDereference< short* >::result_type, short& > );
BOOST_GENERIC_ASSERT( SameType< HasDereference< unsigned* >::result_type, unsigned& > );

BOOST_GENERIC_ASSERT_NOT( HasDereference< int > );
BOOST_GENERIC_ASSERT_NOT( HasDereference< long > );
BOOST_GENERIC_ASSERT_NOT( HasDereference< short > );
BOOST_GENERIC_ASSERT_NOT( HasDereference< unsigned > );

struct non_dereference_object {};

BOOST_GENERIC_ASSERT_NOT( HasDereference< non_dereference_object > );

struct dereference_result {};

struct dereference_object
{
  dereference_result operator *() const;
};

BOOST_GENERIC_ASSERT( HasDereference< dereference_object > );

BOOST_GENERIC_ASSERT
( SameType
  < HasDereference< dereference_object >::result_type, dereference_result >
);

struct dereference_void_object
{
  void operator *() const;
};

BOOST_GENERIC_ASSERT( HasDereference< dereference_void_object > );

BOOST_GENERIC_ASSERT
( SameType< HasDereference< dereference_void_object >::result_type, void > );

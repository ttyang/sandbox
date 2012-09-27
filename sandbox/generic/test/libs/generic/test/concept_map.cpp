/*==============================================================================
    Copyright (c) 2010, 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/concept_map.hpp>

#if 0

#define FOO_DETS()\
BOOST_GENERIC_DETAIL_CONCEPT_DETS\
( (Foo)( (class) A )\
, ( typename a )\
, ( typename b )\
, ( (void)(foo)( (A) c ) )\
, ( (void)(bar)( (A) c ) )\
)

#else

#include <utility>

BOOST_GENERIC_CONCEPT_MAP
( (HasPlus)( int )
, ( typedef int value_type )
, ( (value_type)(foo)( (int) lhs, (int) rhs ) )
)

int main()
{
}

#endif

#if 0

#include <boost/generic/ad_hoc_concept.hpp>
#include <boost/generic/assert/assert_concept_may_be_modeled_by.hpp>
#include <boost/generic/type_traits/concept_may_be_modeled_by.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

BOOST_GENERIC_AD_HOC_CONCEPT
( ( TestConcept, ( (class) T, (class) A ) )
, ( for ( (T) x )
        ( (A) y )
  )
, ( try ( x + y )
        ( y + x
  )
, ( if ( boost::is_same< decltype( x + x ), int > )
       ( boost::is_same< decltype( y + y ), int > )
  )
)

struct a {};

// Passes all conditions, no errors produced
BOOST_GENERIC_ASSERT_CONCEPT_MAY_BE_MODELED_BY( (TestConcept)( int, int ) )

// Fails on 3 out of the 4 conditions, only failed conditions appear in errors
BOOST_STATIC_ASSERT
( !BOOST_GENERIC_CONCEPT_MAY_BE_MODELED_BY_C( (TestConcept)( a, int ) ) );

#endif


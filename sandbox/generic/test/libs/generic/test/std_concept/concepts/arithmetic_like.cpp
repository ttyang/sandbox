/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/arithmetic_like.hpp>
#include <boost/generic/assert.hpp>

struct a {};

struct my_type
{
  typedef my_type this_t;

  my_type() = default;
  explicit my_type( long double );

  friend bool operator ==( this_t, this_t );
  friend bool operator !=( this_t, this_t );
  friend bool operator <( this_t, this_t );
  friend bool operator >( this_t, this_t );
  friend bool operator <=( this_t, this_t );
  friend bool operator >=( this_t, this_t );

  friend this_t operator +( this_t );
  friend this_t operator -( this_t );

  friend this_t operator +( this_t, this_t );
  friend this_t operator -( this_t, this_t );
  friend this_t operator *( this_t, this_t );
  friend this_t operator /( this_t, this_t );

  friend this_t& operator ++( this_t );
  friend this_t operator ++( this_t, int );

  friend this_t& operator --( this_t );
  friend this_t operator --( this_t, int );

  friend this_t& operator +=( this_t&, this_t );
  friend this_t& operator -=( this_t&, this_t );
  friend this_t& operator *=( this_t&, this_t );
  friend this_t& operator /=( this_t&, this_t );
};

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( my_type ) )

BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< my_type > );

BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< float > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< double > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< long double > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< signed char > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< short int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< long long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< unsigned char > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< unsigned short int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< unsigned long int > );
BOOST_GENERIC_ASSERT( boost::generic::std_concept::ArithmeticLike< unsigned long long int > );

struct not_arithmetic_like {};

BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::ArithmeticLike< not_arithmetic_like > );
BOOST_GENERIC_ASSERT_NOT( boost::generic::std_concept::ArithmeticLike< void > );

/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/deduction_result.hpp>
#include <boost/generic/detail/dummy_type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost::generic::detail;
using boost::mpl::vector;
using boost::is_same;

static_assert( is_same< deduction_result< vector<> >::type, no_deduction >::value
             , "Empty vector doesn't report as no_deduction."
             );

static_assert( is_same
               < deduction_result< vector< dummy_type< 0 > > >::type
               , no_deduction
               >::value
             , "Vector with only dummies doesn't report as no_deduction."
             );

static_assert
( is_same
  < deduction_result< vector< dummy_type< 0 >, int, dummy_type< 1 > > >::type
  , int
  >::value
, "Vector with a single deduction doesn't report as that deduction."
);

static_assert
( is_same
  < deduction_result< vector< dummy_type<0>, int, dummy_type<1>, int > >::type
  , int
  >::value
, "Vector with the same deduction twice doesn't report as that deduction."
);

static_assert
( is_same
  < deduction_result< vector< int, dummy_type< 0 >, double > >::type
  , ambiguous_deduction
  >::value
, "Vector with ambiguous deduction doesn't report as ambiguous_deduction."
);

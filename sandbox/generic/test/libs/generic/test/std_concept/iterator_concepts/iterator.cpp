/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/iterator_concepts/iterator.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::Iterator;

BOOST_GENERIC_ASSERT_NOT( Iterator< int > );
BOOST_GENERIC_ASSERT( Iterator< int* > );

//#include <array>
//#include <vector>
//#include <deque>
//
//BOOST_GENERIC_ASSERT( Iterator< std::array< int, 10 >::iterator > );
//BOOST_GENERIC_ASSERT( Iterator< std::array< int, 10 >::const_iterator > );
//BOOST_GENERIC_ASSERT( Iterator< std::vector< int >::iterator > );
//BOOST_GENERIC_ASSERT( Iterator< std::vector< int >::const_iterator > );
//BOOST_GENERIC_ASSERT( Iterator< std::deque< int >::iterator > );
//BOOST_GENERIC_ASSERT( Iterator< std::deque< int >::const_iterator > );
//

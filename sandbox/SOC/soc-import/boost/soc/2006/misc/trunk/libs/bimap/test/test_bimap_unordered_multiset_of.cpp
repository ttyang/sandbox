// Boost.Bimap
//
// (C) Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/test for the library home page.

// Boost.Test
#include <boost/test/minimal.hpp>

#include <boost/bimap/unordered_multiset_of.hpp>

int test_main( int, char* [] )
{
    typedef boost::bimap::unordered_multiset_of<int>       set_type;
    typedef boost::bimap::unordered_multiset_of_relation<> set_type_of_relation;

    return 0;
}


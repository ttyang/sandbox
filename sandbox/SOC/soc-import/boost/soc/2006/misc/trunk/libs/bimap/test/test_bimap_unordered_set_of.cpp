// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Boost.Test
#include <boost/test/minimal.hpp>

#include <boost/bimap/unordered_set_of.hpp>

int test_main( int, char* [] )
{
    typedef boost::bimap::unordered_set_of<int>       set_type;
    typedef boost::bimap::unordered_set_of_relation<> set_type_of_relation;

    return 0;
}


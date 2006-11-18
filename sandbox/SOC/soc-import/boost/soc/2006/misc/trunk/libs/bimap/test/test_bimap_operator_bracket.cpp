// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Boost.Test
#include <boost/test/minimal.hpp>

// Boost.Bimap
#include <boost/bimap/support/lambda.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

void test_bimap_operator_bracket()
{
    using namespace boost::bimap;

    typedef bimap< int, unordered_set_of<std::string> > bm;

    bm b;
    b.insert( bm::relation(0,"0") );
    b.insert( bm::relation(1,"1") );
    b.insert( bm::relation(2,"2") );
    b.insert( bm::relation(3,"3") );

    BOOST_CHECK( b.left[1] == "1" );
    BOOST_CHECK( b.left[1] != "3" );
    BOOST_CHECK( b.left[1] <= "2" );
    BOOST_CHECK( b.left[1] <  "2" );
    BOOST_CHECK( b.left[1] >= "0" );
    BOOST_CHECK( b.left[1] >  "0" );

    BOOST_CHECK( "1" == b.left[1] );
    BOOST_CHECK( "3" != b.left[1] );
    BOOST_CHECK( "2" >= b.left[1] );
    BOOST_CHECK( "2" >  b.left[1] );
    BOOST_CHECK( "0" <= b.left[1] );
    BOOST_CHECK( "0" <  b.left[1] );

    BOOST_CHECK( b.left[1] == b.left[1] );
    BOOST_CHECK( b.left[1] != b.left[3] );
    BOOST_CHECK( b.left[1] <= b.left[2] );
    BOOST_CHECK( b.left[1] <  b.left[2] );
    BOOST_CHECK( b.left[1] >= b.left[0] );
    BOOST_CHECK( b.left[1] >  b.left[0] );

    b.left[1] = "one";
    BOOST_CHECK( b.right["one"] == 1 );

    b.left.erase(2);
    BOOST_CHECK( b.left.find(2) == b.left.end() );

    b.right["2"] = 2;
    BOOST_CHECK( b.left[2] == "2" );

    // Duplicated value test
    {
        bool duplicate_value_test_passed = false;

        b.clear();
        b.left[1] = "tomato";

        try
        {
            b.left[2] = "tomato";
        }
        catch( duplicate_value & )
        {
            duplicate_value_test_passed = true;
        }

        BOOST_CHECK( duplicate_value_test_passed );
    }

    // Value not found test
    {
        bool value_not_found_test_passed = false;

        b.clear();
        b.left[1] = "tomato";

        try
        {
            bool comp;
            comp = b.left[2] < "banana";
        }
        catch( value_not_found & )
        {
            value_not_found_test_passed = true;
        }

        BOOST_CHECK( value_not_found_test_passed );
    }

}

int test_main( int, char* [] )
{
    test_bimap_operator_bracket();

    return 0;
}


// Boost.Bimap
//
// (C) Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/test for the library home page.

// std
#include <set>
#include <map>
#include <cstddef>
#include <cassert>
#include <algorithm>

// Boost.Test
#include <boost/test/minimal.hpp>

// std
#include <sstream>
#include <algorithm>
#include <set>

// Boost
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Boost.Bimap
#include <boost/bimap/bimap.hpp>

typedef boost::bimap::bimap<int,double> bm;

void test_bimap_serialization()
{
    std::set< bm::relation > data;
    data.insert( bm::relation(1,0.1) );
    data.insert( bm::relation(2,0.2) );
    data.insert( bm::relation(3,0.3) );
    data.insert( bm::relation(4,0.4) );

    std::ostringstream oss;

    // Save it
    {
        bm b;

        b.insert(data.begin(),data.end());

        boost::archive::text_oarchive oa(oss);
        oa << const_cast<const bm&>(b);
    }

    // Reload it
    {
        bm b;

        std::istringstream iss(oss.str());
        boost::archive::text_iarchive ia(iss);

        ia >> b;

        BOOST_CHECK( std::equal( b.begin(), b.end(), data.begin() ) );
    }
}


int test_main( int, char* [] )
{
    test_bimap_serialization();
    return 0;
}


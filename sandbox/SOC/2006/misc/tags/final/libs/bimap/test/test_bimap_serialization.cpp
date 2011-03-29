// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// This code may be used under either of the following two licences:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE. OF SUCH DAMAGE.
//
// Or:
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// std
#include <set>
#include <map>
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <algorithm>

// Boost.Test
#include <boost/test/minimal.hpp>

// Boost
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Boost.Bimap
#include <boost/bimap/bimap.hpp>


template< class Bimap, class Archive >
void save_bimap(const Bimap & b, Archive & ar)
{
    using namespace boost::bimap;

    ar << b;

    typedef typename const_iterator_type_by< member_at::left, Bimap >::type
        left_const_iterator;

    left_const_iterator left_iter = b.left.begin();
    ar << const_cast< const left_const_iterator& >(left_iter);

    typename Bimap::const_iterator iter = ++b.begin();
    ar << const_cast< const typename Bimap::const_iterator& >(iter);
}




void test_bimap_serialization()
{
    using namespace boost::bimap;

    typedef bimap<int,double> bm;

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

        save_bimap(b,oa);
    }

    // Reload it
    {
        bm b;

        std::istringstream iss(oss.str());
        boost::archive::text_iarchive ia(iss);

        ia >> b;

        BOOST_CHECK( std::equal( b.begin(), b.end(), data.begin() ) );

        const_iterator_type_by< member_at::left, bm >::type left_iter;

        ia >> left_iter;

        BOOST_CHECK( left_iter == b.left.begin() );

        bm::const_iterator iter;

        ia >> iter;

        BOOST_CHECK( iter == ++b.begin() );
    }

}


int test_main( int, char* [] )
{
    test_bimap_serialization();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <iterator>
#include <vector>
#include <list>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/assign/v2/ref/array/csv.hpp>
#include <boost/assign/v2/utility/chain/check.hpp>
#include <boost/assign/v2/utility/chain.hpp>
#include <boost/assign/v2/utility/chain/alias.hpp>
#include <libs/assign/v2/test/utility/chain.h>

namespace test_assign_v2{
namespace xxx_utility{
namespace xxx_chain{


    void test()
    {
        namespace as2 = boost::assign::v2;
        {
            namespace ns = as2::check_chain_aux;
            {    typedef int T; ns::static_<T>(); ns::static_<T>(); }
            {    typedef double T; ns::static_<T>(); ns::static_<T>(); }
        }
        // Non-Boost.Assign.v2 containers
        {
            //[chain_r
            typedef int T;
            boost::array<T, 2> cont1;  cont1[0] = 0; cont1[1] = 1;
            std::list<T> cont2; cont2.push_back( 2 ); cont2.push_back( 3 );
            std::vector<T> joined( boost::begin( cont1 ), boost::end( cont1 ) );
            boost::copy( cont2, std::back_inserter( joined ) );
            BOOST_ASSIGN_V2_CHECK(
                boost::range::equal( joined, cont1 | as2::_chain( cont2 ) )
            );
            //]
        }
        {
            //[chain_w
            typedef int T; std::vector<T> r( 4 );
            r[0] = 1; r[1] = 2; r[2] = 0; r[3] = 5;
            boost::array<T, 2> cont1; 
            std::list<T> cont2( r.size() - cont1.size() );
            boost::copy( r, boost::begin( cont1 | as2::_chain( cont2 ) ) );
            BOOST_ASSIGN_V2_CHECK( cont1[0] == r[0] );
            BOOST_ASSIGN_V2_CHECK( cont1[1] == r[1] );
            BOOST_ASSIGN_V2_CHECK( cont2.front() == r[2] );
            BOOST_ASSIGN_V2_CHECK( cont2.back() == r[3] );
            //]
        }
		// Boost.Assign.v2 containers
        {
            //[chain_ref_array
            /*<< Needed to bring && into scope >>*/ using namespace boost::assign::v2;
            std::vector<int> powers( 3 ); powers[0] = 1;
            for(int i = 1; i < 8; i++){ powers[i] = powers[ i - 1 ] * 2; }
            boost::array<int, 5> first5; int x, y, z;
            boost::copy(
                powers,
                boost::begin(
                    first5 && (/*<< rvalue! >>*/ as2::ref::csv_array( x, y, z ) | as2::ref::_get )
                )
            );

            BOOST_ASSIGN_V2_CHECK( first5.front() == powers.front()          );
            BOOST_ASSIGN_V2_CHECK( first5.back()  == powers[first5.size()-1] );
            BOOST_ASSIGN_V2_CHECK( x              == powers[first5.size()]   );
            BOOST_ASSIGN_V2_CHECK( z              == powers.back()           );
            //]
        }


    }// test

}// xxx_chain
}// xxx_utility
}// test_assign_v2

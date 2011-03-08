//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include <list>
#include <vector>
#include <boost/array.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/stable_partition.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/assign/v2/detail/config/check.hpp>
#include <boost/assign/v2/put/pipe/csv.hpp>
#include <boost/assign/v2/put/pipe/functor.hpp>
#include <boost/assign/v2/put/deque.hpp>
#include <boost/assign/v2/ref/array.hpp>
#include <boost/assign/v2/utility/chain/alias.hpp>
#include <libs/assign/v2/test/mix.h>

namespace test_assign_v2{
namespace xxx_mix{

    // Tests interaction between different functionalities

    void test(){

        namespace as2 = boost::assign::v2;
        namespace lambda = boost::lambda;

        {
            // suggested by JB:
            //[mix_csv_put_csv_array
            std::deque<int> cont;
            boost::range::stable_partition(
                /*<< Calls `cont.push_back( t )` for [^t=0,...,5], and returns `cont` >>*/
                cont | as2::_csv_put( 0, 1, 2, 3, 4, 5 ),
                lambda::_1 % 2
            );
            //]
            //[other_ref_csv_array
            BOOST_ASSIGN_V2_CHECK(boost::range::equal(
                cont,
                /*<< The input [^1, 3, ..., 4] is held by reference (not copies) >>*/
                as2::ref::csv_array(1, 3, 5, 0, 2, 4)
            ));
            //]
        } 
        {
            //[mix_array_csv_array
            const int sz = 3;
    		typedef boost::array<int, sz>  r_;
    		boost::array<r_, sz>  matrix3x3 = /*<<Using `converter` is a good practice, bearing in mind it may work without it>>*/converter(
            	as2::ref::array
                	( converter( as2::ref::csv_array( 1, 2, 3 ) ).type<r_>() )
                	( converter( as2::ref::csv_array( 4, 5, 6 ) ).type<r_>() )
                	( converter( as2::ref::csv_array( 7, 8, 9 ) ).type<r_>() )
            );
            for(int i = 0; i < 9; i++)
            {
            	BOOST_ASSIGN_V2_CHECK( matrix3x3[ i / 3 ][ i % 3 ] == i + 1 );
            }
			//]
        }
		{
        	//[mix_deque_csv_array
            typedef double elem_; typedef std::list<elem_> r_; typedef std::vector<r_> ragged_array_;
            
			ragged_array_ ragged_array = /*<<Using `converter` is a good practice, bearing in mind it may work without it>>*/converter( 
            	as2::deque<r_>
            		( converter( as2::ref::csv_array( 0.71, 0.63, 0.85 ) ).type<r_>() ) 
                	( converter( as2::ref::csv_array( 0.61, 0.69, 0.92, 0.55 ) ).type<r_>() )
					( 1, -99.99 )
                	( )
            );

            BOOST_ASSIGN_V2_CHECK( ragged_array[0].size() == 3 );
            BOOST_ASSIGN_V2_CHECK( ragged_array[1].size() == 4 );
            BOOST_ASSIGN_V2_CHECK( ragged_array[2].size() == 1 );
            BOOST_ASSIGN_V2_CHECK( ragged_array[3].size() == 0 );
            //]
			elem_ eps = boost::numeric::bounds<elem_>::smallest();
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array.front().front() - 0.71 ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array.front().back() - 0.85  ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[2].front() + 99.0      ) < eps ); 
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[2].back() + 99.0       ) < eps ); 
		}
		{
            //[deque_chain_put
            typedef const char state_ [3]; state_ ct = "CT", nj = "NJ", ny = "NY", ca = "CA", /* ore = "OR",*/ wa = "WA";
            typedef int code_; typedef boost::tuple<state_/*<<Notice the reference>>*/&,  code_> area_code_;
            /*<<Brings && for chaining into scope>>*/using namespace boost::assign::v2;
            std::deque<area_code_> pacific; 
            
            //boost::copy(
                as2::deque<area_code_>( nj, 201 )( ct, 203 )( ny, 212 )( ny, 315 )( ny, 347 )( nj, 551 ) 
                	&&  ( pacific | as2::_put( wa, 206 )( ca, 209 )( ca, 213 )( wa, 253 ) );//,
                //std::cout << boost::get<1>( lambda::_1 ) << std::endl;
            //); 
            //]

		}
    }

}// xxx_mix
}// xxx_test_assign
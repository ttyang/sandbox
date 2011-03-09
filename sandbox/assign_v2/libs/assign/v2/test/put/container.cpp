//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <boost/array.hpp>
#include <deque>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <boost/tuple/tuple.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/assign/v2/detail/config/check.hpp>
#include <boost/assign/v2/detail/functor/identity.hpp>
#include <boost/assign/v2/put/container/put.hpp>
#include <boost/assign/v2/put/container/put_range.hpp>
#include <libs/assign/v2/test/put/container.h>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_container{

    void test(){
    
        namespace as2 = boost::assign::v2;
        
        {
            //[put_array
            const int sz = 3;
    		typedef boost::array<int, sz>  r_;
    		boost::array<r_, sz>  matrix3x3;
            {
            	r_ r0, r1, r2;
            	/*<<Calls `r[i] = j` for [^( i, j ) = ( 0, 1 ), ( 1, 2 ), ( 2, 3 )]>>*/as2::put( r0 )( 1 )( 2 )( 3 );
            	as2::put( r1 )( 4 )( 5 )( 6 );
            	as2::put( r2 )( 7 )( 8 )( 9 );
			    /*<<Calls `matrix3x3[i] = r`, for [^( i, r ) = ( 0, r0 ), ( 1, r1 ), ( 2, r2 )]>>*/as2::put( matrix3x3 )( r0 )( r1 )( r2 );
			}
            for(int i = 0; i < 9; i++)
            {
            	BOOST_ASSIGN_V2_CHECK( matrix3x3[ i / 3 ][ i % 3 ] == i + 1 );
            }
			//]
        }
		{
        	//[put_seq_var_args
            typedef double elem_; typedef std::list<elem_> r_; typedef std::vector<r_> ragged_array_;
			r_ a; /* Calls `a.push_back( t )` for [^t = 0.71, 0.63, 0.85] */ as2::put( a )( 0.71 )( 0.63 )( 0.85 );
			r_ b; as2::put( b )( 0.61 )( 0.69 )( 0.92 )( 0.55 );
			ragged_array_ ragged_array; 
            as2::put( ragged_array )
				/*<<Calls `ragged_array.push_back( r_( boost::begin( a ), boost::end( a ) ) )`>>*/( boost::begin( a ), boost::end( a ) )
				/*<<Calls `ragged_array.push_back( r_( b ) )`>>*/( b )
				/*<<Calls `ragged_array.push_back( r_( 1, -99.99 ) )`>>*/( 1, -99.99 )
                /*<<Calls `ragged_array.push_back( r_( ) )`>>*/( );

            BOOST_ASSIGN_V2_CHECK( ragged_array[0].size() == a.size() );
            BOOST_ASSIGN_V2_CHECK( ragged_array[1].size() == b.size() );
            BOOST_ASSIGN_V2_CHECK( ragged_array[2].size() == 1        );
            BOOST_ASSIGN_V2_CHECK( ragged_array[3].size() == 0        );
            //]
			elem_ eps = boost::numeric::bounds<elem_>::smallest();
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[0].front() - a.front() ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[0].back()  - a.back()  ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[1].front() - b.front() ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[1].back()  - b.back()  ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[2].front() + 99.9      ) < eps );
            BOOST_ASSIGN_V2_CHECK( abs( ragged_array[2].back()  + 99.9      ) < eps );
		}
        {
            //[put_adapter
            std::queue<int> fifo; /*<<Calls `fifo.push( t )` for [^t = 72, 31, 48]>>*/as2::put( fifo )( 72 )( 31 )( 48 );

            BOOST_ASSIGN_V2_CHECK( fifo.front() == 72 );
            BOOST_ASSIGN_V2_CHECK( fifo.back() == 48 );
            //]
        }
        {
            using namespace boost;
            //[put_seq_ref_tuple
            typedef const char state_ [3]; state_ ct = "CT", nj = "NJ", ny = "NY";
            typedef int code_; typedef boost::tuple<state_/*<<Notice the reference>>*/&,  code_> area_code_; 
            std::deque< area_code_ > tri_state; /*Calls `tri_state.push_back( area_code_( s, c ) )` for [^( s, c ) = ( nj, 201 )( ct, 203 )( ny, 212 )( ny, 315 )( ny, 347 )( nj, 551 )]*/as2::put( tri_state )( nj, 201 )( ct, 203 )( ny, 212 )( ny, 315 )( ny, 347 )( nj, 551 );

            BOOST_ASSIGN_V2_CHECK( get<0>( tri_state.front() ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<0>( tri_state.back()  ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<1>( tri_state.front() ) == 201 );
            BOOST_ASSIGN_V2_CHECK( get<1>( tri_state.back()  ) == 551 );
            //]
        }
		{
            //[put_range_assign
            typedef const char state_ [3]; state_ ct = "CT", nj = "NJ", ny = "NY", ca = "CA", /*ore = "OR",*/ wa = "WA";
            typedef int code_; typedef boost::tuple<state_/*<<Notice the reference>>*/&,  code_> area_code_; 
            std::deque< area_code_ > tri_state; as2::put( tri_state )( nj, 201 )( ct, 203 )( ny, 212 )( ny, 315 )( ny, 347 )( nj, 551 );
            std::deque< area_code_ > pacific ; as2::put( pacific )( wa, 206 )( ca, 209 )( ca, 213 )( wa, 253 );

			std::deque< area_code_ > states;  as2::put_range( tri_state, states ); as2::put_range( pacific, states );

			using namespace boost;
            BOOST_ASSIGN_V2_CHECK( get<0>( states.front()                                 ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<0>( states[tri_state.size()-1]                     ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<0>( states.front()                                 ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<0>( states[tri_state.size()]                       ) == wa );
            BOOST_ASSIGN_V2_CHECK( get<0>( states[tri_state.size() + pacific.size() - 1 ] ) == wa );
			//]
        }
        {
            //[put_range_constr
            std::vector<int> r( 3 ); r[0] = 72; r[1] = 31; r[2] = 48;

            BOOST_ASSIGN_V2_CHECK( as2::put_range< std:: stack<int> >( r ).top() == 48 );
            //]
        }
        
    }// test()

}// xxx_container
}// xxx_put
}// xxx_test_assign

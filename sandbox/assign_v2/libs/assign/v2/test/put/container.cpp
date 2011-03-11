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
#include <bitset>
#include <cmath>
#include <deque>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <boost/assign/v2/detail/config/check.hpp>
#include <boost/assign/v2/detail/functor/identity.hpp>
#include <boost/assign/v2/put/container/put.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/variant.hpp>
#include <libs/assign/v2/test/put/container.h>

#include <iostream>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_container{

    void test(){
    
        namespace as2 = boost::assign::v2;

		{
         	//[put_bitset
			typedef std::string str_; typedef /*<<`data_( "011" )`, for instance, is not valid, but `data_( str_( "011" ) )` is valid (GCC 4.2)>>*/ std::bitset<3> data_; 
            /*<<Neither `consecutive.push_back( "011" )`, nor `consecutive.push_back( str_( "011" ) )`, for instance, are valid, but `consecutive.push_back( data_( str_( "011" ) ) );` is valid (GCC4.2)>>*/ std::vector<data_> consecutive; /*<<Calls `consecutive.push_back( data_( t ) );` for [^t = str_( "000" ), str_( "001" ), str_( "010" ), str_( "011" ), str_( "100" ), str_( "101" ), str_( "110" ), str_( "111" )]`>>*/as2::put( consecutive )( str_( "000" ) )( str_( "001" ) )( str_( "010" ) )( str_( "011" ) )( str_( "100" ) )( str_( "101" ) )( str_( "110" ) )( str_( "111" ) );
		
            for(int i = 0; i < consecutive.size(); i++)
            {
            	BOOST_ASSIGN_V2_CHECK( consecutive[i].to_ulong() == i );
            }
            //]
        }
        {
         	//[put_as_arg_list
            std::vector<int> numeric( 10 ); boost::iota( numeric, 0 ); typedef std::string str_;
            typedef boost::variant< int, str_ > data_; boost::array<data_, 10 + 4> numeric_kb;
            as2::put( numeric_kb )/*<<Calls `numeric_kb[0] = "+"`>>*/( "+" )/*<<Calls `numeric_kb[1] = "-"`>>*/( "-" )/*<<Calls `numeric_kb[2] = "*"`>>*/( "*" )/*<<Calls `numeric_kb[3] = "/"`>>*/( "/" )/*<<Equivalent to calling `( *( boost::begin( numeric ) ) )( *( 1 + boost::begin( numeric ) ) )`[^...]`( *( 9 + boost::begin( numeric ) ) )`>>*/( as2::as_arg_list( numeric ) );
            
			using namespace boost;
            BOOST_ASSIGN_V2_CHECK( get<str_>( numeric_kb[ 0 ] ) == "+" );
            BOOST_ASSIGN_V2_CHECK( get<str_>( numeric_kb[ 3 ] ) == "/" );
            for(int i = 0; i< numeric.size(); i++){ 
            	BOOST_ASSIGN_V2_CHECK( get<int>( numeric_kb[ i + 4 ] ) == i ); 
            }
            //]
        }
		{
        	//[put_variable_args_size
            typedef double data_; typedef std::vector<data_> variable_size_; 
			variable_size_ a( 3 ); a[0] = 0.71; a[1] = 0.63; a[2] = 0.85;
			variable_size_ b; as2::put( b )( 0.61 )( 0.69 )( 0.92 )( 0.55 );
	        boost::array<variable_size_, 4> ragged; 
            as2::put( ragged )
				/*<<Calls `ragged.push_back( variable_size_( boost::begin( a ), boost::end( a ) ) )`>>*/( boost::begin( a ), boost::end( a ) )
				/*<<Calls `ragged.push_back( variable_size_( b ) )`>>*/( b )
				/*<<Calls `ragged.push_back( variable_size_( 1, -99.99 ) )`>>*/( 1, -99.99 )
                /*<<Calls `ragged.push_back( variable_size_( ) )`>>*/( );

            BOOST_ASSIGN_V2_CHECK( ragged[0].size() == a.size() );
            BOOST_ASSIGN_V2_CHECK( ragged[1].size() == b.size() );
            BOOST_ASSIGN_V2_CHECK( ragged[2].size() == 1        );
            BOOST_ASSIGN_V2_CHECK( ragged[3].size() == 0        );
            //]
			data_ eps = boost::numeric::bounds<data_>::smallest();
            BOOST_ASSIGN_V2_CHECK( fabs( ragged[0].front() - a.front() ) < eps );
            BOOST_ASSIGN_V2_CHECK( fabs( ragged[0].back()  - a.back()  ) < eps );
            BOOST_ASSIGN_V2_CHECK( fabs( ragged[1].front() - b.front() ) < eps );
            BOOST_ASSIGN_V2_CHECK( fabs( ragged[1].back()  - b.back()  ) < eps );
            BOOST_ASSIGN_V2_CHECK( fabs( ragged[2].front() + 99.99     ) < eps );
            BOOST_ASSIGN_V2_CHECK( fabs( ragged[2].back()  + 99.99     ) < eps );
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
			// http://bioinfo.mbb.yale.edu/~mbg/dom/fun3/area-codes/            
            //[put_seq_tuple_ref
            typedef const char us_state_ [3]; us_state_ ct = "CT", nj = "NJ", ny = "NY";
            typedef int area_code_; typedef boost::tuple<us_state_/*<<Notice the reference>>*/&,  area_code_> data_; 
            std::deque< data_ > tri_state_area; /*Calls `tri_state.push_back( data_( s, c ) )` for [^( s, c ) = ( ny, 212 )( ny, 718 )( ny, 516 )( ny, 914 )( nj, 210 )( nj, 908 )( nj, 609 )( ct, 203 ) ]*/
            as2::put( tri_state_area )( ny, 212 )( ny, 718 )( ny, 516 )( ny, 914 )( nj, 210 )( nj, 908 )( nj, 609 )( ct, 203 );

            BOOST_ASSIGN_V2_CHECK( get<0>( tri_state_area.front() ) == ny );
            BOOST_ASSIGN_V2_CHECK( get<1>( tri_state_area.front() ) == 212 );
            BOOST_ASSIGN_V2_CHECK( get<0>( tri_state_area.back()  ) == ct );
            BOOST_ASSIGN_V2_CHECK( get<1>( tri_state_area.back()  ) == 203 );
            //]
        }
    }// test()

}// xxx_container
}// xxx_put
}// xxx_test_assign

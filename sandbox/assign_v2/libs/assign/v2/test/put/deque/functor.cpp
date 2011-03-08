////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                       //
//                                                                        //
//  Copyright (C) 2003-2004 Thorsten Ottosen                              //
//  Copyright (C) 2010 Erwann Rogard                                      //
//  Use, modification and distribution are subject to the                 //
//  Boost Software License, Version 1.0. (See accompanying file           //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)      //
////////////////////////////////////////////////////////////////////////////
#include <string>
#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/assign/v2/put/deque/csv.hpp>
#include <boost/assign/v2/put/deque/functor.hpp>
#include <boost/assign/v2/detail/config/check.hpp>

#include <libs/assign/v2/test/put/deque/functor.h>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_deque{
namespace xxx_functor{

    void test()
    {
        namespace as2 = boost::assign::v2;    
        {
            //[deque_ref_tuple
            typedef const char state_ [3]; state_ ct = "CT", nj = "NJ", ny = "NY";
            typedef int code_; typedef boost::tuple<state_/*<<Notice the reference>>*/&,  code_> area_code_; 
            typedef as2::result_of::deque<area_code_>::type states_;
            states_ tri_state = as2::deque<area_code_>( nj, 201 )( ct, 203 )( ny, 212 );

			using namespace boost;
            BOOST_ASSIGN_V2_CHECK( get<0>( tri_state.front() ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<1>( tri_state.front() ) == 201 );

			states_ tri_state2 = tri_state( ny, 315 )( ny, 347 )( nj, 551 );

            BOOST_ASSIGN_V2_CHECK( get<0>( tri_state2.back()  ) == nj );
            BOOST_ASSIGN_V2_CHECK( get<1>( tri_state2.back()  ) == 551 );
            //]
		}
        {
        	//[deque_str
            typedef std::string str_;
            BOOST_ASSIGN_V2_CHECK(
                str_( as2::deque<const char*>( "x" )( "y" )( "z" )[1] ) == "y"
            );
            //]
        }
    }

}// xxx_functor
}// xxx_deque
}// xxx_put
}// test_assign_v2

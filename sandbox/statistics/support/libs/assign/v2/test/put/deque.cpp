////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                       //
//                                                                        //
//  Copyright (C) 2003-2004 Thorsten Ottosen                              //
//  Copyright (C) 2010 Erwann Rogard                                      //
//  Use, modification and distribution are subject to the                 //
//  Boost Software License, Version 1.0. (See accompanying file           //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)      //
////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <boost/array.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/assign/v2/detail/keyword.hpp>
#include <boost/assign/v2/detail/checking/container.hpp>
#include <boost/assign/v2/detail/checking/constants.hpp>
#include <boost/assign/v2/detail/checking/relational_op.hpp>

#include <boost/assign/v2/put/deque.hpp>

#include <libs/assign/v2/test/put/deque.h>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_deque{

	void test()
    {
    	using namespace boost::assign::v2;
        {
        	// CSV
            using namespace checking::constants;
            using namespace checking::container;
            do_check( csv_deque( a,  b, c, d, e, f, g, h ) );
        }
        {
        	// Operator%
            BOOST_AUTO(tmp, ( deque<int>( _nil ) % ( _repeat = 3 ) ) );
            tmp( 1 );
            BOOST_ASSIGN_V2_CHECK( boost::size( tmp ) == 3 );
            BOOST_ASSIGN_V2_CHECK( tmp.front() == 1 );
            BOOST_ASSIGN_V2_CHECK( tmp.back() == 1 );
        }
        {
        	// string literals
        	typedef std::string str_;
            BOOST_ASSIGN_V2_CHECK( str_( csv_deque("x")[0] ) == "x");
        }
        {
        	// Conversion
        	typedef result_of::deque<int>::type deque_;
            deque_ from;
            {
            	using namespace checking::constants;
            	from = csv_deque( a, b, c, d, e, f, g, h );
            }
        	using namespace checking::container;
#define MACRO do_check( from | put_convert<to_>() );
        	{
                typedef boost::array<int,8> to_;
                MACRO
        	}
        	{
                typedef std::deque<int> to_;
                MACRO
        	}
        	{
                typedef std::list<int> to_;
                MACRO
        	}
        	{
                typedef std::queue<int> to_;
                MACRO
        	}
        	{
                typedef std::set<int> to_;
                MACRO
        	}
        	{
                typedef std::stack<int> to_;
                MACRO
        	}
	        {
                typedef std::vector<int> to_;
                MACRO
        	}
#undef MACRO
        }
/*
        { 	// Relational
            using namespace checking::constants;
            using namespace checking::relational_op;
            do_check(
            	csv_deque( a, b, c, d, e, f, g, h )
            );
        }
*/
    }

}// xxx_deque
}// xxx_put
}// test_assign_v2
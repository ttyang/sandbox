//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <list>
#include <queue>
#include <set>
#include <string>
#include <boost/assign/v2/detail/config/check.hpp>
#include <boost/assign/v2/put/modifier/standard.hpp>
#include <boost/assign/v2/put/container/put.hpp>
#include <boost/assign/v2/put/deque.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/typeof/typeof.hpp>
#include <libs/assign/v2/test/put/modifier/standard.h>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_modifier{
namespace xxx_standard{

    void test()
    {
        namespace as2 = boost::assign::v2;

		// ------------------------------ WARNING ---------------------------- //
        // Don't misconstrue the commands in the tests below as *necessary* to //
        // obtain particular implementation. Most of the time the default is   //
        // already set at that invoked with operator% 	                       //
        // ------------------------------------------------------------------- //

		// PUT
		{
        	//[modifier_meta
        	typedef as2::result_of::put<std::vector<int> >::type put_;
            typedef as2::put_aux::keyword_modifier keyword_;
            typedef as2::modifier_tag::push_front tag_;
            typedef as2::result_of::modulo_modifier<put_> meta1_;
			typedef ::boost::mpl::apply2<meta1_, keyword_, tag_>::type result1_;
            typedef as2::put_aux::replace_modifier_tag<put_> meta2_;
            typedef ::boost::mpl::apply1<meta2_, tag_>::type result2_;
            BOOST_MPL_ASSERT(( boost::is_same<result1_, result2_> ));
        	//]
        }
        {
            //[modifier_push_front
            std::deque<int> powers;
            ( as2::put( powers ) % as2::_push_front )( 16 )( 8 )( 4 )( 2 )( 1 );

            BOOST_ASSIGN_V2_CHECK( powers[0] == 1 );
            BOOST_ASSIGN_V2_CHECK( powers[4] == 16 );
            //]
        }
        {
            //[modifier_push
            std::queue<int> fifo; ( as2::put( fifo ) % as2::_push )( 72 )( 31 )( 48 );
                
            BOOST_ASSIGN_V2_CHECK( fifo.front() == 72 );
            BOOST_ASSIGN_V2_CHECK( fifo.back() == 48 );
            //]
        }
        {
            //[modifier_insert
            std::set<double> sqrt2; ( as2::put( sqrt2 ) % as2::_insert )( 1.414 )( 1.41421 )( 1.41 )( 1.4142 );
        
            BOOST_ASSIGN_V2_CHECK( sqrt2.lower_bound( 1.41 ) == boost::begin( sqrt2 ) );
            BOOST_ASSIGN_V2_CHECK( sqrt2.upper_bound( 1.41421 ) == boost::end( sqrt2 ) );
            //]
        }
        {
            //[modifier_push_back
            typedef int int_; std::list<int> list; 
            ( as2::put( list ) % as2::_push_back )( 72 )( 31 )( 48 );
                
            BOOST_ASSIGN_V2_CHECK( list.front() == 72 );
            BOOST_ASSIGN_V2_CHECK( list.back() == 48 );
            //]
        }
		// DEQUE
		{
        	//[modifier_meta_deque
        	typedef as2::result_of::deque<int>::type put_;
            typedef as2::put_aux::keyword_modifier keyword_;
            typedef as2::modifier_tag::push_front tag_;
            typedef as2::result_of::modulo_modifier<put_> meta1_;
			typedef ::boost::mpl::apply2<meta1_, keyword_, tag_>::type result1_;
            typedef as2::put_aux::replace_modifier_tag<put_> meta2_;
            typedef ::boost::mpl::apply1<meta2_, tag_>::type result2_;

            BOOST_MPL_ASSERT(( boost::is_same<result1_, result2_> ));
        	//]
        }
        {
            //[modifier_push_front_deque
            BOOST_AUTO(
                powers,
                ( as2::deque<int>( as2::_nil ) % as2::_push_front )( 16 )( 8 )( 4 )( 2 )( 1 )
            );

            BOOST_ASSIGN_V2_CHECK( powers[0] == 1 );
            BOOST_ASSIGN_V2_CHECK( powers[4] == 16 );
            //]
        }
    }

}// xxx_standard
}// xxx_modifier
}// xxx_put
}// test_assign_v2

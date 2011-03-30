//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <map>
#include <string>
#include <cmath>
#include <boost/assign/v2/detail/config/check.hpp>
#include <boost/assign/v2/put.hpp>
#include <boost/assign/v2/deque.hpp>
// Options come next
#include <boost/assign/v2/option/data_generator.hpp>
#include <boost/assign/v2/option/modifier/mapped.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tuple/tuple.hpp>
#include <libs/assign/v2/test/option/mapped.h>

namespace test_assign_v2{
namespace xxx_option{
namespace xxx_mapped{

    void test()
    {

        using namespace boost;
        namespace as2 = assign::v2;
        {
            //[test_option_mapped_map
            using namespace lambda;
            typedef std::string str_; typedef std::map<str_, int> C; C year;
            (
                as2::put( year )( "feb", 28 )( "apr", 30 )( "jun", 30 )( "sep", 30 )( "nov", 30 )
                    % (as2::_data = as2::_key) % ( as2::_mapped = ( _1 = 31 ) )
            )/*<<Calls `year["jan"] = 31` etc.>>*/( "jan" )( "mar" )( "may" )( "jul" )( "aug" )( "oct" )( "dec" );

            BOOST_ASSIGN_V2_CHECK( year["jan"] == 31 );
            BOOST_ASSIGN_V2_CHECK( year["dec"] == 31 );
            //]
        }
        {
            //[test_option_mapped_meta_deque
            using namespace lambda;
            typedef BOOST_TYPEOF(_1) arg_;
            typedef as2:: interpreter_aux::keyword_mapped keyword_;
            typedef as2::result_of::deque<int>::type put_;
            typedef as2::result_of::option_mapped<put_, arg_>::type result1_;
            typedef as2::modifier_tag::mapped<arg_> tag1_;
            typedef as2:: interpreter_aux::replace_modifier_tag<put_> meta2_;
            typedef ::boost::mpl::apply1<meta2_, tag1_>::type result2_;
            BOOST_MPL_ASSERT((boost::is_same<result1_, result2_>));
            //]
        }
        {
            //[test_option_mapped_map_deque
            using namespace lambda;
            BOOST_AUTO(
                days_in_first_quater,
                (
                    as2::deque<int>( 31 )( 31 )( 31 ) % ( as2::_mapped = ( _1 -= 3 ) )
                )( 1 )
            );
            BOOST_ASSIGN_V2_CHECK( days_in_first_quater[0] == 31 );
            BOOST_ASSIGN_V2_CHECK( days_in_first_quater[1] == 28 );
            BOOST_ASSIGN_V2_CHECK( days_in_first_quater[2] == 31 );
            //]
        }
    }

}// xxx_mapped
}// xxx_option
}// test_assign_v2

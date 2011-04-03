//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <boost/typeof/typeof.hpp>
#include <boost/assign/v2/detail/config/check.hpp>
#include <boost/assign/v2/put/csv_put.hpp>
// Options come next
#include <boost/assign/v2/option/modifier/std.hpp>
#include <boost/assign/v2/option/modifier/repeat.hpp>
#include <boost/assign/v2/deque.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <libs/assign/v2/test/option/repeat.h>

namespace test_assign_v2{
namespace xxx_option{
namespace xxx_repeat{

    void test()
    {
        using namespace boost;
        namespace as2 = assign::v2;
        {
            //[test_option_repeat_simple
            std::vector<int> cont;
            as2::csv_put( cont, as2::_repeat = 2, 1, 10, 100 );

            BOOST_ASSIGN_V2_CHECK( 
                range::equal( 
                	cont, 
                    as2::csv_deque( 1, 1, 10, 10, 100, 100 ) 
                ) 
            );
            //]
        }
        {
            //[test_option_repeat_compose
            BOOST_AUTO(
                cont, (
                    as2::deque<int>( as2::_nil ) % as2::_push_front % ( as2::_repeat = 2 )
                )( 1 )( 10 )( 100 )
            );
            
            BOOST_ASSIGN_V2_CHECK( 
                range::equal( cont, as2::csv_deque( 100, 100, 10, 10, 1, 1 ) ) 
            );
            //]
        }
    }


}// xxx_repeat
}// xxx_option
}// test_assign_v2

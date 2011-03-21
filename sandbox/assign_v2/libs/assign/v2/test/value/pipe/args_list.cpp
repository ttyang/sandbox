//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <boost/mpl/int.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/assign/v2/detail/check/equal_val.hpp>
#include <boost/assign/v2/detail/check/equal_ref.hpp>

#include <boost/assign/v2/value/modifier/repeat.hpp>
#include <boost/assign/v2/value/pipe/put.hpp> 
#include <boost/assign/v2/utility/csv.hpp>
#include <libs/assign/v2/test/value/pipe/args_list.h>

namespace test_assign_v2{
namespace xxx_value{
namespace xxx_pipe{
namespace xxx_args_list{

    // --User may skip this file-- //
    // It checks internal details. //
    // --------------------------- //        

    void test()
    {
        using namespace boost;
        namespace as2 = assign::v2;
        typedef boost::mpl::int_<0> zero_;
        {
            typedef as2::value_aux::args_list<> args_list_;
            int x = -1;
            BOOST_AUTO( 
                args_list, 
                ( ( args_list_() %  ( as2::_repeat = 3 ) )( x ) ) 
            );
            int n = as2::ref::at<0>( args_list.par_list_cont() ).arg();
            BOOST_ASSIGN_V2_CHECK( n == 3 );
        }
        namespace chk = as2::check_aux;
        namespace aux_ = as2::value_aux;
        typedef chk::equal_ref r_;
        typedef chk::equal_val v_;
        {
// rvalue
#define A -10
#define B 10
            // lvalue
            int a1 = -1, b1 = 0;
            typedef const int cint_;
            cint_ a = 4, b = 5;

            BOOST_AUTO(
                args_list,
                ( as2::_put
                    ( a1, b1 )( a1, b )( a1, B )
                    ( a, b1 )( a, b )( a, B )
                    ( A, b1 )( A, b )( A, B )
                    ( a1 )
                    ( a )
                    ( A )
                    ()
                )
            );

            aux_::check_args_list<0, 0>( args_list, r_(), a1);
            aux_::check_args_list<0, 1>( args_list, r_(), b1);
            aux_::check_args_list<1, 0>( args_list, r_(), a1); aux_::check_args_list<1, 1>( args_list, r_(), b);
            aux_::check_args_list<2, 0>( args_list, r_(), a1); aux_::check_args_list<2, 1>( args_list, v_(), B);

            aux_::check_args_list<3, 0>( args_list, r_(), a ); aux_::check_args_list<3, 1>( args_list, r_(), b1);
            aux_::check_args_list<4, 0>( args_list, r_(), a ); aux_::check_args_list<4, 1>( args_list, r_(), b);
            aux_::check_args_list<5, 0>( args_list, r_(), a ); aux_::check_args_list<5, 1>( args_list, v_(), B);

            aux_::check_args_list<6, 0>( args_list, v_(), A); aux_::check_args_list<6, 1>( args_list, r_(), b1);
            aux_::check_args_list<7, 0>( args_list, v_(), A); aux_::check_args_list<7, 1>( args_list, r_(), b);
            aux_::check_args_list<8, 0>( args_list, v_(), A); aux_::check_args_list<8, 1>( args_list, v_(), B);

            aux_::check_args_list<9, 0>( args_list, r_(), a1);
            aux_::check_args_list<10, 0>( args_list, r_(), a);
            aux_::check_args_list<11, 0>( args_list, v_(), A);
#undef A
#undef B
        }
/*
        {
            // str_literal
            BOOST_AUTO(args_list, as2::_put( "x" ) );
            typedef boost::mpl::int_<0> int_;
            typedef std::string str_;
            #if BOOST_ASSIGN_V2_ENABLE_CPP0X
            using namespace boost::assign::v2::ref;
            #else
            using namespace boost;
            #endif
            aux_::check_args_list<0, 0>( args_list, v_(), str_( "x" ) );
        }
*/
    }


}// xxx_args_list
}// xxx_pipe
}// xxx_value
}// test_assign_v2

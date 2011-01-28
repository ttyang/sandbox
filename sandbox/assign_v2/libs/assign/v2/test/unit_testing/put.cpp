//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef LIBS_ASSIGN_V2_TEST_UNIT_TEST_PUT_ER_2010_CPP
#define LIBS_ASSIGN_V2_TEST_UNIT_TEST_PUT_ER_2010_CPP

#include <iostream> // needed?

#include <boost/test/test_tools.hpp>
#define BOOST_ASSIGN_V2_CHECK( p ) BOOST_CHECK( p )

#include <libs/assign/v2/test/put/deduce.cpp>
#include <libs/assign/v2/test/put/modulo.cpp>
#include <libs/assign/v2/test/put/container/functor.cpp>
#include <libs/assign/v2/test/put/container/csv.cpp>
#include <libs/assign/v2/test/put/container/range.cpp>
#include <libs/assign/v2/test/put/std.cpp>
#include <libs/assign/v2/test/put/ext.cpp>
#include <libs/assign/v2/test/put/ptr.cpp>
#include <libs/assign/v2/test/put/deque.cpp>

#include <libs/assign/v2/test/put/pipe/modulo.cpp>
#include <libs/assign/v2/test/put/pipe/functor/rhs.cpp>
#include <libs/assign/v2/test/put/pipe/functor/forward.cpp>
#include <libs/assign/v2/test/put/pipe/functor/container.cpp>
#include <libs/assign/v2/test/put/pipe/csv/rhs.cpp>
#include <libs/assign/v2/test/put/pipe/csv/container.cpp>
#include <libs/assign/v2/test/put/pipe/ext.cpp>
#include <libs/assign/v2/test/put/pipe/range.cpp>


#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;
test_suite* init_unit_test_suite( int argc, char* argv[] )
{                                            
    test_suite* test = BOOST_TEST_SUITE( "BOOST_ASSIGN_V2" ); 
    using namespace test_assign_v2;  
    {
    	namespace ns = xxx_put;
		test->add( BOOST_TEST_CASE( &ns::xxx_deduce::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_modulo::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_container::xxx_functor::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_container::xxx_csv::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_container::xxx_range::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_std::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_ext::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_ptr::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_deque::test ) );

		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_modulo::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_functor::xxx_rhs::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_functor::xxx_forward::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_functor::xxx_container::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_csv::xxx_rhs::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_csv::xxx_container::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_ext::test ) );
		test->add( BOOST_TEST_CASE( &ns::xxx_pipe::xxx_range::test ) );
    }
    return test;                             
}                                            

#endif
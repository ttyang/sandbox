/* Boost check_implicit_euler.cpp test file

 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky

 This file tests the use of the euler stepper

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#define BOOST_TEST_MODULE odeint_rosenbrock4

#include <utility>

#include <boost/test/unit_test.hpp>

#include <boost/numeric/odeint/stepper/rosenbrock4.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::unit_test;
using namespace boost::numeric::odeint;

typedef double value_type;
typedef boost::numeric::ublas::vector< value_type > state_type;
typedef boost::numeric::ublas::matrix< value_type > matrix_type;


void sys( const state_type &x , state_type &dxdt , const value_type &t )
{
    dxdt( 0 ) = x( 0 ) + 2 * x( 1 );
    dxdt( 1 ) = x( 1 );
}

void jacobi( const state_type &x , matrix_type &jacobi , const value_type &t , state_type &dfdt )
{
    jacobi( 0 , 0 ) = 1;
    jacobi( 0 , 1 ) = 2;
    jacobi( 1 , 0 ) = 0;
    jacobi( 1 , 1 ) = 1;
    dfdt( 0 ) = 0.0;
    dfdt( 1 ) = 0.0;
}

BOOST_AUTO_TEST_SUITE( rosenbrock4_test )

BOOST_AUTO_TEST_CASE( test_rosenbrock4_stepper )
{
	typedef rosenbrock4< value_type > stepper_type;
	stepper_type stepper;

	typedef stepper_type::state_type state_type;
	typedef stepper_type::value_type stepper_value_type;
	typedef stepper_type::deriv_type deriv_type;
	typedef stepper_type::time_type time_type;

	state_type x( 2 ) , xerr( 2 );
	x(0) = 0.0; x(1) = 1.0;



	stepper.do_step( std::make_pair( sys , jacobi ) , x , 0.0 , 0.1 , xerr );

//	using std::abs;
//	value_type eps = 1E-12;
//
//	// compare with analytic solution of above system
//	BOOST_CHECK_SMALL( abs( x(0) - 20.0/81.0 ) , eps );
//	BOOST_CHECK_SMALL( abs( x(1) - 10.0/9.0 ) , eps );

}

BOOST_AUTO_TEST_CASE( test_rosenbrock4_controller )
{
	typedef rosenbrock4_controller< rosenbrock4< value_type > > stepper_type;
	stepper_type stepper;

	typedef stepper_type::state_type state_type;
	typedef stepper_type::value_type stepper_value_type;
	typedef stepper_type::deriv_type deriv_type;
	typedef stepper_type::time_type time_type;

	state_type x( 2 );
	x( 0 ) = 0.0 ; x(1) = 1.0;

	value_type t = 0.0 , dt = 0.01;
	stepper.try_step( std::make_pair( sys , jacobi ) , x , t , dt );
}

BOOST_AUTO_TEST_CASE( test_rosenbrock4_dense_output )
{
	typedef rosenbrock4_dense_output< rosenbrock4_controller< rosenbrock4< value_type > > > stepper_type;
	stepper_type stepper;

	typedef stepper_type::state_type state_type;
	typedef stepper_type::value_type stepper_value_type;
	typedef stepper_type::deriv_type deriv_type;
	typedef stepper_type::time_type time_type;

	state_type x( 2 );
	x( 0 ) = 0.0 ; x(1) = 1.0;
	stepper.initialize( x , 0.0 , 0.1 );
	std::pair< value_type , value_type > tr = stepper.do_step( std::make_pair( sys , jacobi ) );
	stepper.calc_state( 0.5 * ( tr.first + tr.second ) , x );
}



BOOST_AUTO_TEST_SUITE_END()

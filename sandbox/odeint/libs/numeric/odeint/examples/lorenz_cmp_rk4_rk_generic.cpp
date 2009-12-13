/* Boost numeric/odeint/examples/lorenz_cmp_rk4_rk_generic.cpp
 
 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky

 Lorenz Eqquations:
 dx/dt = sigma * ( x - y)
 dy/dt = R*x - y - x*z
 dz/dt = x*y - b*z

 with sigma = 10, r=28, b = 8/3

 Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include <iostream>
#include <vector>
#include <list>
#include <tr1/array>

#include <boost/numeric/odeint.hpp>

#define tab "\t"

using namespace std;
using namespace boost::numeric::odeint;


typedef std::tr1::array< double , 3 > state_type;


const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

void lorenz( state_type &x , state_type &dxdt , double t )
{
    dxdt[0] = sigma * ( x[1] - x[0] );
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = x[0]*x[1] - b * x[2];
}

int main( int argc , char **argv )
{
    const double dt = 0.01;
    const size_t olen = 100000000;
    
    state_type x1 = {{1.0, 0.0, 0.0}};
    state_type x2 = {{1.0, 0.0, 0.0}};
    state_type x3 = {{1.0, 0.0, 0.0}};
    state_type x4 = {{1.0, 0.0, 0.0}};

    stepper_rk4< state_type > stepper_rk4;
    stepper_rk4_classical< state_type > stepper_rk4_classical;

    vector< double > a(3);

    a[0] = 0.5; 
    a[1] = 0.5;
    a[2] = 1;

    vector< vector<double> > b(3);
    b[0].resize(1);
    b[1].resize(2);
    b[2].resize(3);

    b[0][0] = 0.5;
    b[1][0] = 0.0; b[1][1] = 0.5;
    b[2][0] = 0.0; b[2][1] = 0.0; b[2][2] = 1.0;
    
    vector< double > c(4);
    c[0] = 1.0/6.0;
    c[1] = 1.0/3.0;
    c[2] = 1.0/3.0;
    c[3] = 1.0/6.0;

    const double a2[3] = {0.5, 0.5, 1.0 };
    const double b2[6] = {0.5, 0.0, 0.5, 0.0, 0.0, 1.0};
    const double c2[4] = {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0};

    stepper_rk_generic< state_type > stepper_generic4(a, b, c);

    stepper_rk_generic_ptr< state_type > stepper_generic4_ptr(a2, b2, c2, 4);

    clock_t start , end;
    double t;

    cout.precision(16);

    cout << "Hand written Runge Kutta 4"<<endl;

    t = 0.0;
    start= clock();
    for( size_t oi=1 ; oi<olen ; ++oi,t+=dt ) {
        stepper_rk4.do_step( lorenz , x1 , t , dt );
        if( oi < 5 )
            cout << "x after step "<<oi<<": "<<x1[0]<<tab<<x1[1]<<tab<<x1[2]<<endl;

    }
    end = clock();
    cout << "x after "<<olen<<" steps: "<<x1[0]<<tab<<x1[1]<<tab<<x1[2]<<endl;
    cout << "Time for "<<olen<<" steps: " << double ( end - start ) / double( CLOCKS_PER_SEC ) <<"s"<< endl;

    cout << endl << "###########################" << endl << endl;

    cout << "Runge Kutta 4 via generic Runge Kutta implementation"<<endl;
    t = 0.0;
    start= clock();
    for( size_t oi=1 ; oi<olen ; ++oi,t+=dt ) {
        stepper_generic4.do_step( lorenz , x2 , t , dt );
        if( oi < 5 )
            cout << "x after step "<<oi<<":  "<<x2[0]<<tab<<x2[1]<<tab<<x2[2]<<endl;        
    }
    end = clock();
    cout << "x after "<<olen<<" steps: "<<x2[0]<<tab<<x2[1]<<tab<<x2[2]<<endl;
    cout << "Time for "<<olen<<" steps: " << double ( end - start ) / double( CLOCKS_PER_SEC ) << endl;

    cout << endl << "###########################" << endl << endl;
    cout << "Runge Kutta 4 via C-Array styled generic Runge Kutta implementation"<<endl;

    t = 0.0;
    start= clock();
    for( size_t oi=1 ; oi<olen ; ++oi,t+=dt ) {
        stepper_generic4_ptr.do_step( lorenz , x3 , t , dt );
        if( oi < 5 )
            cout << "x after step "<<oi<<":  "<<x3[0]<<tab<<x3[1]<<tab<<x3[2]<<endl;        
    }
    end = clock();
    cout << "x after "<<olen<<" steps: "<<x3[0]<<tab<<x3[1]<<tab<<x3[2]<<endl;
    cout << "Time for "<<olen<<" steps: " << double ( end - start ) / double( CLOCKS_PER_SEC ) << endl;


    cout << endl << "###########################" << endl << endl;

    cout << "Runge Kutta 4 with classical NR-style Runge Kutta implementation"<<endl;
    t = 0.0;
    start= clock();
    for( size_t oi=1 ; oi<olen ; ++oi,t+=dt ) {
        stepper_rk4_classical.do_step( lorenz , x4 , t , dt );
        if( oi < 5 )
            cout << "x after step "<<oi<<":  "<<x4[0]<<tab<<x4[1]<<tab<<x4[2]<<endl;        
    }
    end = clock();
    cout << "x after "<<olen<<" steps: "<<x4[0]<<tab<<x4[1]<<tab<<x4[2]<<endl;
    cout << "Time for "<<olen<<" steps: " << double ( end - start ) / double( CLOCKS_PER_SEC ) << endl;

    return 0;
}

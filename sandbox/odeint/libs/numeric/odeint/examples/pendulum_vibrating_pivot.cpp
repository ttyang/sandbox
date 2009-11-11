/* Boost numeric/odeint/examples/coupled_vdp.cpp
 
 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky

 Shows the usage of odeint by integrating the equations of a 
 pendulum with horizontally vibrating pivot:

 

 Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <tr1/array>

#include <boost/numeric/odeint.hpp>

#define tab "\t"

using namespace std;
using namespace boost::numeric::odeint;


typedef std::tr1::array< double , 2 > state_type;

const double alpha = 0.1;
const double omega = 10;
const double a = 0.1;
const size_t time_points = 1000;

/* 
   Defines the right hand side f(x,t) of the dynamical equations dx/dt = f(x,t) 
   x consists of x=(x, dx/dt) and f has explicit time dependence
*/
void my_system( state_type &x , state_type &dxdt , double t ) 
{
    dxdt[0] = x[1];
    dxdt[1] = -sin(x[0]) - alpha*x[1] + a*omega*omega*sin(omega*t)*cos(x[0]);
}

int main( int argc , char **argv )
{
    state_type x = {{ 1.0, 0.0 }};

    vector<double> times(time_points);
    for( size_t i=0; i<time_points; i++ ) {
        times[i] = 0.1*i;
    }
    vector<state_type> x_t_vec;
    
    stepper_half_step< stepper_rk4< state_type > > stepper;

    size_t steps = integrate( stepper, my_system, x, times, back_inserter(x_t_vec));

        clog << "Steps: " << steps << endl;

    cout.precision(5);
    cout.setf(ios::fixed,ios::floatfield);
    

    for( size_t i=0; i<time_points; i++ ) {
        //cout << "current state: " ;
        cout << times[i] << tab;
        cout << x_t_vec[i][0] << tab << x_t_vec[i][1] << tab << x_t_vec[i][2] << endl;
    }

    return 0;

}

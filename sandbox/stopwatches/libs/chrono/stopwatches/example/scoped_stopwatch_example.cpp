//  example/scoped_stopwatch_example.cpp  ---------------------------------------------------//
//  Copyright 2009/2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#include <boost/chrono/stopwatches/stopwatches.hpp>
#include <cmath>
#include "sleep_for.hpp"
#include <boost/chrono/chrono_io.hpp>
//#include <iostream>

using namespace boost::chrono;

long double res;
void f1(long j)
{
    //stopwatch_reporter<stopwatch<> > _(BOOST_STOPWATCHES_STOPWATCH_FUNCTION_FORMAT);
    //stopwatch<> sw;
    for (long i =0; i< j; i+=1)
        res+=std::sqrt( res+123.456L+i );  // burn some time
    if (j!=0) f1(j-1);
    //stopwatch_reporter<stopwatch<> >::scoped_suspend s(_);
    //std::cout << "f1("<< j <<") Elapsed time: " << sw.elapsed() << std::endl;

}
int main()
{
  //stopwatch_reporter<stopwatch<> > _(BOOST_STOPWATCHES_STOPWATCH_FUNCTION_FORMAT);
    stopwatch<> sw;

    res=0;
    for (long i =1; i< 4; ++i) {
      stopwatch<> sw;
        f1(i*1000);
        {
        stopwatch_suspender<stopwatch<> > _(sw);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
        }
        std::cout << "f1("<< i*1000 <<") Elapsed time: " << sw.elapsed() << std::endl;
    }

    std::cout<< res << std::endl;
    std::cout << "main() Elapsed time: " << sw.elapsed() << std::endl;
  return 0;
}

//  stopwatch_accumulator_example.cpp  ---------------------------------------------------//
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono for documentation.

#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/stopwatches/stopwatches.hpp>
//#include <boost/chrono/process_cpu_clocks.hpp>
#include <cmath>


using namespace boost::chrono;
using namespace boost;



//typedef stopwatch_accumulator<process_real_cpu_clock> swa;
typedef stopwatch_accumulator<high_resolution_clock> swa;
int f1(long j, swa& sw)
{
  //static stopwatch_reporter<stopwatch_accumulator<high_resolution_clock> > acc(BOOST_STOPWATCHES_ACCUMULATOR_FUNCTION_FORMAT);
  //stopwatch_reporter<stopwatch_accumulator<high_resolution_clock> >::scoped_run r_(acc);
  //static stopwatch_reporter<stopwatch_accumulator<process_real_cpu_clock> > acc2(BOOST_STOPWATCHES_ACCUMULATOR_FUNCTION_FORMAT);
  //stopwatch_reporter<stopwatch_accumulator<process_real_cpu_clock> >::scoped_run r2_(acc2);

  stopwatch_runner<swa > _(sw);

  for ( long i = 0; i < j; ++i )
    std::sqrt( 123.456L );  // burn some time

  return 0;
}
int main()
{
  swa sw;

  f1(10000000,sw);
  f1(20000000,sw);
  f1(30000000,sw);

  swa::accumulator_set& acc = sw.get_storage();
  std::cout << "f1() Lifetime: " << sw.lifetime() << std::endl;
  std::cout << "f1() Elapsed: " << sw.elapsed() << std::endl;
  std::cout << "f1() Count: " << accumulators::count(acc) << std::endl;
  std::cout << "f1() Sum: " << accumulators::sum(acc) << std::endl;
  std::cout << "f1() Sum/Count: " << accumulators::sum(acc)/accumulators::count(acc) << std::endl;
  std::cout << "f1() Mean: " << accumulators::mean(acc) << std::endl;
  std::cout << "f1() Min: " << (accumulators::min)(acc) << std::endl;
  std::cout << "f1() Max: " << (accumulators::max)(acc) << std::endl;
  return 0;
}

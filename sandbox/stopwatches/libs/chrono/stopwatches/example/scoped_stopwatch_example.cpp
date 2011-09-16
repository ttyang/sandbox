//  example/scoped_stopwatch_example.cpp  ---------------------------------------------------//
//  Copyright 2009/2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.
#include <iostream>

#include <boost/chrono/stopwatches/stopwatches.hpp>
#include <boost/chrono/stopwatches/simple_stopwatch.hpp>
#include <boost/chrono/stopwatches/formatters/elapsed_formatter.hpp>
#include <boost/chrono/stopwatches/formatters/oneshot_formatter.hpp>
#include <boost/chrono/stopwatches/reporters/stopwatch_reporter.hpp>
#include <cmath>
#include <string>
#include "sleep_for.hpp"
#include <boost/chrono/chrono_io.hpp>
#include <boost/format.hpp>

namespace boost { namespace chrono  {
  template <>
  struct stopwatch_reporter2_default_formatter<stopwatch<system_clock> > {
      typedef elapsed_formatter type;
  };
  template <>
  struct stopwatch_reporter2_default_formatter<stopwatch<high_resolution_clock> > {
      typedef elapsed_formatter type;
  };
  template <>
  struct stopwatch_reporter2_default_formatter<simple_stopwatch<high_resolution_clock> > {
      typedef elapsed_formatter type;
  };
}}

using namespace boost::chrono;
using namespace boost;


long double res;
void f0(long j)
{
  stopwatch_reporter2<simple_stopwatch<high_resolution_clock> > sw;
  for (long i =0; i< j; i+=1)
    res+=std::sqrt( res+123.456L+i );  // burn some time
}
void f1(long j)
{
  boost::format fmt("%1%[%2%] f1(%3%) - Elapsed time: %4%");
  fmt % __FILE__ % __LINE__ % j;
  stopwatch_reporter2<stopwatch<high_resolution_clock> > sw(fmt);
  for (long i =0; i< j; i+=1)
    res+=std::sqrt( res+123.456L+i );  // burn some time
}

void f2(long j)
{
  boost::format fmt("%1%[%2%] %3% - Elapsed time: %4%");
  fmt % __FILE__ % __LINE__ % BOOST_CURRENT_FUNCTION;
  stopwatch_reporter2<stopwatch<high_resolution_clock> > sw(fmt);
  for (long i =0; i< j; i+=1)
    res+=std::sqrt( res+123.456L+i );  // burn some time
  stopwatch_suspender< stopwatch_reporter2<stopwatch<high_resolution_clock> > > _(sw);
  boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
}
void f3(long j)
{
  typedef basic_elapsed_formatter<milli > formatter;
  formatter fmt("Elapsed time: %1%",std::cerr);
  fmt.set_duration_style(duration_style::prefix_text);
  fmt.set_precision(6);

  stopwatch_reporter2<stopwatch<high_resolution_clock>, formatter> sw(fmt);
  for (long i =0; i< j; i+=1)
    res+=std::sqrt( res+123.456L+i );  // burn some time
}

int main()
{
  std::cout << __FILE__ << "[" << __LINE__ <<"]"<< std::endl;
  stopwatch_reporter2<stopwatch<> > sw(BOOST_CHRONO_STOPWATCHES_ELAPSED_FUNCTION_FORMAT);

  res=0;
    f0(1000000);
    f1(1000000);
    f2(1000000);
    f3(3000000);

  std::cout<< res << std::endl;
  return 0;
}




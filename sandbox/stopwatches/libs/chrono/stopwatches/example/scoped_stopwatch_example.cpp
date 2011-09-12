//  example/scoped_stopwatch_example.cpp  ---------------------------------------------------//
//  Copyright 2009/2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#include <boost/chrono/stopwatches/stopwatches.hpp>
#include <cmath>
#include <string>
#include "sleep_for.hpp"
#include <boost/chrono/chrono_io.hpp>
#include <boost/format.hpp>

using namespace boost::chrono;

template <typename Stopwatch>
class stopwatch_reporter : public Stopwatch
{
  public:
  stopwatch_reporter( )
  : internal_fmt_("%1%"), fmt_(internal_fmt_) {}
  stopwatch_reporter(const char* str )
  : internal_fmt_(str), fmt_(internal_fmt_) {}
  stopwatch_reporter(std::string const& str )
  : internal_fmt_(str), fmt_(internal_fmt_) {}
  stopwatch_reporter(boost::format & fmt )
  : fmt_(fmt) {}
  ~stopwatch_reporter() {
    std::cout << fmt_ % this->elapsed() << std::endl;
  }
  private:
  boost::format internal_fmt_;
  boost::format& fmt_;
};

long double res;
void f1(long j)
{
  //stopwatch_reporter<stopwatch<> > _(BOOST_STOPWATCHES_STOPWATCH_FUNCTION_FORMAT);
  boost::format fmt("f1(%1%): Elapsed time: %2%");
  fmt % j;
  ::stopwatch_reporter<stopwatch<> > sw(fmt);
  for (long i =0; i< j; i+=1)
    res+=std::sqrt( res+123.456L+i );  // burn some time
  stopwatch_suspender< ::stopwatch_reporter<stopwatch<> > > _(sw);
  boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
}

int main()
{
  //stopwatch_reporter<stopwatch<> > _(BOOST_STOPWATCHES_STOPWATCH_FUNCTION_FORMAT);
  ::stopwatch_reporter<stopwatch<> > _("main(): Elapsed time: %1%");

  res=0;
  for (long i =1; i< 4; ++i) {
    f1(i*1000000);
  }

  std::cout<< res << std::endl;
  return 0;
}

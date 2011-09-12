//  stopwatch_accumulator_example.cpp  ---------------------------------------------------//
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono for documentation.

#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/stopwatches/stopwatches.hpp>
//#include <boost/chrono/process_cpu_clocks.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
#include <boost/format/group.hpp>
#include <boost/chrono/chrono_io.hpp>


using namespace boost::chrono;
using namespace boost;

std::ostream&
my_duration_short(std::ostream& os)
{
  return boost::chrono::duration_short(os);
}

template <typename Stopwatch, typename Ratio=boost::ratio<1> >
class stopwatch_reporter : public Stopwatch
{
  public:
  stopwatch_reporter( )
  : internal_fmt_("times=%1%, sum=%2%, min=%3%, max=%4%, mean=%5%, frequency=%6% Hz, lifetime=%7%, time=%8% %%"),
    fmt_(internal_fmt_),
    os_(std::cout)
  {}
  stopwatch_reporter(const char* str )
  : internal_fmt_(str),
    fmt_(internal_fmt_),
    os_(std::cout)
  {}
  stopwatch_reporter(std::string const& str )
  : internal_fmt_(str),
    fmt_(internal_fmt_),
    os_(std::cout)
  {}
  stopwatch_reporter(boost::format & fmt )
  : fmt_(fmt),
    os_(std::cout)
  {}
  ~stopwatch_reporter() {
    typename Stopwatch::accumulator_set& acc = this->get_storage();
    typedef typename Stopwatch::duration duration_t;
    int precision_=3;

    os_ << fmt_
        % boost::accumulators::count(acc)
        % io::group(std::fixed, std::setprecision(precision_),my_duration_short, boost::chrono::duration<double,Ratio>(duration_t(boost::accumulators::sum(acc))))
        % io::group(std::fixed, std::setprecision(precision_),my_duration_short, boost::chrono::duration<double,Ratio>(duration_t((boost::accumulators::min)(acc))))
        % io::group(std::fixed, std::setprecision(precision_),my_duration_short, boost::chrono::duration<double,Ratio>(duration_t((boost::accumulators::max)(acc))))
        % io::group(std::fixed, std::setprecision(precision_),my_duration_short,((boost::accumulators::count(acc)>0)
            ? boost::chrono::duration<double,Ratio>(duration_t(boost::accumulators::sum(acc)/boost::accumulators::count(acc)))
            : boost::chrono::duration<double,Ratio>(duration_t(0))))
        % io::group(std::fixed, std::setprecision(precision_),
            ((boost::accumulators::count(acc)>0)
            ? boost::accumulators::count(acc)/boost::chrono::duration<double>(this->lifetime())
            : 0))
        % io::group(std::fixed, std::setprecision(precision_),my_duration_short, boost::chrono::duration<double,Ratio>(this->lifetime()))
        % io::group(std::fixed, std::setprecision(precision_),boost::chrono::duration<double>(duration_t(accumulators::sum(acc))).count()*100/boost::chrono::duration<double>(this->lifetime()).count())
    << std::endl;
  }
  private:
  boost::format internal_fmt_;
  boost::format& fmt_;
  std::ostream& os_;
};

//typedef stopwatch_accumulator<process_real_cpu_clock> swa;
typedef stopwatch_accumulator<high_resolution_clock> swa;
int f1(long j, swa& sw)
{
  //static stopwatch_reporter<stopwatch_accumulator<high_resolution_clock> > acc(BOOST_STOPWATCHES_ACCUMULATOR_FUNCTION_FORMAT);
  //stopwatch_reporter<stopwatch_accumulator<high_resolution_clock> >::scoped_run r_(acc);
  static ::stopwatch_reporter<stopwatch_accumulator<high_resolution_clock>, boost::micro> acc;
  stopwatch_runner<
    ::stopwatch_reporter<
       stopwatch_accumulator<high_resolution_clock>, boost::micro
    >
  > r_(acc);
  //static stopwatch_reporter<stopwatch_accumulator<process_real_cpu_clock> > acc2(BOOST_STOPWATCHES_ACCUMULATOR_FUNCTION_FORMAT);
  //stopwatch_reporter<stopwatch_accumulator<process_real_cpu_clock> >::scoped_run r2_(acc2);

  //stopwatch_runner<swa > _(sw);

  for ( long i = 0; i < j; ++i )
    std::sqrt( 123.456L );  // burn some time

  return 0;
}
int main()
{
  swa sw;

  std::cout << duration_short << nanoseconds(10) << std::endl;

  f1(10000000,sw);
  f1(20000000,sw);
  f1(30000000,sw);

//  swa::accumulator_set& acc = sw.get_storage();
//  std::cout << "f1() Lifetime: " << sw.lifetime() << std::endl;
//  std::cout << "f1() Elapsed: " << sw.elapsed() << std::endl;
//  std::cout << "f1() Count: " << accumulators::count(acc) << std::endl;
//  std::cout << "f1() Sum: " << accumulators::sum(acc) << std::endl;
//  std::cout << "f1() Sum/Count: " << accumulators::sum(acc)/accumulators::count(acc) << std::endl;
//  std::cout << "f1() Mean: " << accumulators::mean(acc) << std::endl;
//  std::cout << "f1() Min: " << (accumulators::min)(acc) << std::endl;
//  std::cout << "f1() Max: " << (accumulators::max)(acc) << std::endl;
  return 1;
}

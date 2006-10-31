//#define BOOST_PROFILER_DISABLE
//#define _SCL_SECURE_NO_DEPRECATE
#include <boost/profiler.hpp>
#include <iostream>
#include <fstream>
#include <cmath>

BOOST_PROFILER_CONTEXT ( ctx1,"ctx1");
BOOST_PROFILER_CONTEXT ( ctx2,"ctx2");

inline void busy_delay(double seconds)
{
    using namespace boost::profiler;
    tick_t t = boost::profiler::ticks();
    const timer_metrics &tm = get_timer_metrics();
    tick_t n = t + static_cast<tick_t>(floor(seconds * tm.ticks_per_second + 0.5));
    while (boost::profiler::ticks() < n)
        ;
}

int fact(int n)
{
    BOOST_PROFILER_SET_CONTEXT(ctx2);
    BOOST_PROFILER_SCOPE("scope");
    BOOST_PROFILER_START("fact");
    int r = n > 1 ? n * fact(n - 1) : 1;
    BOOST_PROFILER_STOP();
    return r;
}

extern int fact2(int);

void delay(boost::profiler::tick_t d)
{
    boost::profiler::tick_t t = boost::profiler::ticks();
    while (boost::profiler::ticks() < t + d)
        ;
}

int main()
{
    fact2(10);
    fact(10);

    BOOST_PROFILER_SET_CONTEXT(BOOST_PROFILER_GET_DEFAULT_CONTEXT());

    {
        BOOST_PROFILER_SCOPE("bd");     
        busy_delay(1);
        BOOST_PROFILER_START("bd2");
        busy_delay(1);
        BOOST_PROFILER_START("bd3");
        busy_delay(1);
        BOOST_PROFILER_STOP();
        busy_delay(1);
        BOOST_PROFILER_STOP();
    }
    
    BOOST_PROFILER_DUMP_ALL("out.txt");
    BOOST_PROFILER_DUMP_ALL(std::cout);
	BOOST_PROFILER_DUMP_CONTEXT(BOOST_PROFILER_GET_DEFAULT_CONTEXT(),"out2.txt");
}

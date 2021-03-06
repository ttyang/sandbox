//  stopwatch_accumulator_example.cpp  ---------------------------------------------------//
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/stopwatches for documentation.

#include <boost/stopwatches.hpp>
#include <cmath>
//#include <boost/thread.hpp>
#include "sleep_for.hpp"

using namespace boost::chrono;
using namespace boost::stopwatches;

#define BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR \
    static stopclock_accumulator<> BOOST_JOIN(_boost_chrono_stopclock_accumulator_, __LINE__)( \
        std::string(__FILE__) + "[" + BOOST_STRINGIZE(__LINE__) + "] " + stopwatch_accumulator_formatter::default_format() \
    ); \
    stopclock_accumulator<>::scoped_run BOOST_JOIN(_boost_chrono_stopclock_accumulator_run_, __LINE__)(BOOST_JOIN(_boost_chrono_stopclock_accumulator_, __LINE__))

#define BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR_FCT \
    static stopclock_accumulator<> BOOST_JOIN(_boost_chrono_stopclock_accumulator_, __LINE__)( \
        std::string(BOOST_CURRENT_FUNCTION) + ":  " + stopwatch_accumulator_formatter::default_format() \
    ); \
    stopclock_accumulator<>::scoped_run BOOST_JOIN(_boost_chrono_stopclock_accumulator_run_, __LINE__)(BOOST_JOIN(_boost_chrono_stopclock_accumulator_, __LINE__))

#define BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR_FCT_REVERSE \
    static stopclock_accumulator<> BOOST_JOIN(_boost_chrono_stopclock_accumulator_, __LINE__)( \
        std::string(BOOST_CURRENT_FUNCTION) + "(between calls):  " + stopwatch_accumulator_formatter::default_format() \
    ); \
    stopclock_accumulator<>::scoped_stop BOOST_JOIN(_boost_chrono_stopclock_accumulator_stop_, __LINE__)(BOOST_JOIN(_boost_chrono_stopclock_accumulator_, __LINE__))

void f1()
{
    //~ static stopclock_accumulator<> acc(
        //~ std::string(__FILE__) + "[" + BOOST_STRINGIZE(__LINE__) + "] " + stopwatch_accumulator_formatter::default_format()
    //~ );
    //~ stopclock_accumulator<>::scoped_run _(acc);
    BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR_FCT;
    //BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR_FCT_REVERSE;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    {
        BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR;
        //~ static stopclock_accumulator<> acc(
            //~ std::string(__FILE__) + "[" + BOOST_STRINGIZE(__LINE__) + "] " + stopwatch_accumulator_formatter::default_format()
        //~ );
        //~ stopclock_accumulator<>::scoped_run _(acc);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
    }

}
int main()
{
    BOOST_STOPWATCHES_STOPCLOCK_ACCUMULATOR_FCT;
    //~ static stopclock_accumulator<> acc(
        //~ std::string(__FILE__) + "[" + BOOST_STRINGIZE(__LINE__) + "] " + stopwatch_accumulator_formatter::default_format()
    //~ );
    //~ stopclock_accumulator<>::scoped_run _(acc);

    boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    f1();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    f1();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(50));
    f1();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
    return 0;
}

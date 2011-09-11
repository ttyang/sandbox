//  boost/chrono/stopwatches/stopwatch_accumulator.hpp  ------------------------------------------------------------//
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_STOPWATCHES_STOPWATCH_ACCUMULATOR_HPP
#define BOOST_STOPWATCHES_STOPWATCH_ACCUMULATOR_HPP

#include <utility>

#include <boost/chrono/chrono.hpp>
#include <boost/chrono/stopwatches/stopwatch_scoped.hpp>
#include <boost/system/error_code.hpp>
#include <boost/chrono/stopwatches/lightweight_stopwatch.hpp>
#include <boost/utility/base_from_member.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>

namespace boost
{
  namespace chrono
  {

    template <typename Features, typename Weight=void>
    struct lightweight_stopwatch_accumulator_set_traits {
        template <typename D>
        struct apply {
            struct type {
                typedef accumulators::accumulator_set<typename D::rep, Features, Weight> storage_type;
                typedef D duration_type;
                static duration_type get_duration(storage_type& acc_) { return duration_type(accumulators::sum(acc_)); }
                static void set_duration(storage_type& acc_, duration_type d) { acc_(d.count()); }
                static void reset(storage_type& acc_) { acc_=storage_type(); }
            };
        };
    };

//--------------------------------------------------------------------------------------//
//                                    stopwatch_accumulator
//
//~ A stopwatch accumulator is a class designed to measure the amount of time elapsed from a particular time
//~ when activated to when it is deactivated.

//~ Calling start starts the stopwatch_accumulator running, and calling stop stops it.
//~ A call to reset resets the stopwatch_accumulator to zero.
//~ A stopwatch_accumulator can also be used to record split times or lap times.
//~ The elapsed time since the last start is available through the elapsed function.
//--------------------------------------------------------------------------------------//

    // forward declaration
    template <class Clock=chrono::high_resolution_clock,
        typename Features=accumulators::features<
                        accumulators::tag::count,
                        accumulators::tag::sum,
                        accumulators::tag::min,
                        accumulators::tag::max,
                        accumulators::tag::mean >,
        typename Weight=void
    >
    class stopwatch_accumulator;


//--------------------------------------------------------------------------------------//

    template <class Clock, typename Features, typename Weight>
    class stopwatch_accumulator
        : private base_from_member<
            typename accumulators::accumulator_set<typename Clock::duration::rep, Features, Weight> 
                //~ typename lightweight_stopwatch_accumulator_set_traits<Features,Weight>::template apply<Clock::duration>::storage_type
            >,
          public lightweight_stopwatch<Clock,lightweight_stopwatch_accumulator_set_traits<Features,Weight> >
    {
    public:
        typedef base_from_member<typename accumulators::accumulator_set<typename Clock::duration::rep, Features, Weight> > pbase_type;
        typedef typename accumulators::accumulator_set<typename Clock::duration::rep, Features, Weight> accumulator_set;

        stopwatch_accumulator( )
        : pbase_type(), 
          lightweight_stopwatch<Clock,lightweight_stopwatch_accumulator_set_traits<Features,Weight> >(pbase_type::member, dont_start)
        { }
    };

//--------------------------------------------------------------------------------------//
    typedef boost::chrono::stopwatch_accumulator< boost::chrono::system_clock > system_stopwatch_accumulator;
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
    typedef boost::chrono::stopwatch_accumulator< boost::chrono::steady_clock > steady_stopwatch_accumulator;
#endif
    typedef boost::chrono::stopwatch_accumulator< boost::chrono::high_resolution_clock > high_resolution_stopwatch_accumulator;

//--------------------------------------------------------------------------------------//


  } // namespace chrono
} // namespace boost

#endif

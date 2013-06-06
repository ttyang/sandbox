// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_STATS_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_STATS_HPP

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/stats.hpp>

namespace boost { namespace accumulators {

    typedef stats<> no_stats;
}}  // namespace boost::accumulators

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::no_stats)

#define BOOST_TYPEOF_REGISTER_BOOST_ACCUMULATORS_TEMPLATE(z, n, Type)        \
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::Type, BOOST_PP_INC(n)) \
//

BOOST_PP_REPEAT(
    BOOST_PP_DEC(BOOST_ACCUMULATORS_MAX_FEATURES)
  , BOOST_TYPEOF_REGISTER_BOOST_ACCUMULATORS_TEMPLATE
  , stats
)

#undef BOOST_TYPEOF_REGISTER_BOOST_ACCUMULATORS_TEMPLATE

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_STATS_HPP


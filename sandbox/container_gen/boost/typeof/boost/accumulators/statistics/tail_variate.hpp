// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/tail_variate.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::tail_variate_impl
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::tail_variate
  , 3
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::abstract_tail_variate)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::tail_weights
  , 1
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::abstract_tail_weights)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_HPP


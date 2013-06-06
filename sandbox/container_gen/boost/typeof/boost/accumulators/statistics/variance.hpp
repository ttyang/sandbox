// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::lazy_variance_impl
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::variance_impl
  , 3
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::lazy_variance)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::variance)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP


// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::this_feature_has_no_error_calculation
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::impl::error_of_impl, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::error_of, 1)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP


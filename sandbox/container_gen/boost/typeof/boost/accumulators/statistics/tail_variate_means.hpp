// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/tail_variate_means.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::tail_variate_means_impl
  , 4
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::absolute_tail_variate_means
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::relative_tail_variate_means
  , 3
)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::accumulators::tag::abstract_absolute_tail_variate_means
)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::accumulators::tag::abstract_relative_tail_variate_means
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP


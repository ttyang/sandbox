// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_COVARIANCE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_COVARIANCE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/covariance.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::numeric::functional::outer_product_base
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::numeric::functional::outer_product_base
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::numeric::functional::outer_product, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::numeric::functional::outer_product, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::numeric::functional::outer_product, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::numeric::op::outer_product)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::impl::covariance_impl, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::covariance, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::abstract_covariance)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_COVARIANCE_HPP


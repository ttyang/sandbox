// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::detail::tail_range, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::stat_assign_visitor
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::is_tail_variate_feature
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::impl::tail_impl, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tail_cache_size_named_arg
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::tail, 1)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::abstract_tail)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_TAIL_HPP


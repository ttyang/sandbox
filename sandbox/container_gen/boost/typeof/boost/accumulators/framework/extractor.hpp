// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_EXTRACTOR_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_EXTRACTOR_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::accumulator_set_result
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::argument_pack_result
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::extractor_result
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::extractor, 1)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_EXTRACTOR_HPP


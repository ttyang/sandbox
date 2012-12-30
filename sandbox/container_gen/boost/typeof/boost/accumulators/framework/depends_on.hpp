// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_DEPENDS_ON_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_DEPENDS_ON_HPP

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/framework/depends_on.hpp>

namespace boost { namespace accumulators {

    typedef depends_on<> depends_on_nothing;
}}

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::as_feature, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::as_weighted_feature, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::feature_of, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::detail::feature_tag, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::detail::undroppable, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::is_dependent_on
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::dependencies_of
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::set_insert_range
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::collect_abstract_features
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::depends_on_base
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::matches_feature
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::contains_feature_of
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::contains_feature_of_
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::build_acc_list
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::build_acc_list
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::meta::make_acc_list
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::checked_as_weighted_feature
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::as_feature_list
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::accumulator_wrapper
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::to_accumulator
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::insert_feature
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::insert_dependencies
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::insert_sequence
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::make_accumulator_tuple
  , 3
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::depends_on_nothing)

#define BOOST_TYPEOF_REGISTER_BOOST_ACCUMULATORS_TEMPLATE(z, n, Type)        \
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::Type, BOOST_PP_INC(n)) \
//

BOOST_PP_REPEAT(
    BOOST_PP_DEC(BOOST_ACCUMULATORS_MAX_FEATURES)
  , BOOST_TYPEOF_REGISTER_BOOST_ACCUMULATORS_TEMPLATE
  , depends_on
)

#undef BOOST_TYPEOF_REGISTER_BOOST_ACCUMULATORS_TEMPLATE

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_DEPENDS_ON_HPP


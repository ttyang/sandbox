//=======================================================================
// Copyright (C) 2011 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_HAS_STABLE_ITERS_SELECTOR_HPP_INCLUDED
#define BOOST_UTILITY_HAS_STABLE_ITERS_SELECTOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/utility/container_selector.hpp>

//[reference__has_stable_iterators_selector
namespace boost {

    template <typename Selector>
    struct has_stable_iterators_selector : ::boost::mpl::true_
    {
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_unique_associative_selector
          , (Selector)
        )
        //->
    };

    //<-
    template <>
    struct has_stable_iterators_selector<vecS> : ::boost::mpl::false_
    {
    };

    template <>
    struct has_stable_iterators_selector<dequeS> : ::boost::mpl::true_
    {
    };

    template <>
    struct has_stable_iterators_selector<flat_setS> : ::boost::mpl::false_
    {
    };

    template <>
    struct has_stable_iterators_selector<flat_mapS> : ::boost::mpl::false_
    {
    };

    template <>
    struct has_stable_iterators_selector<flat_multisetS>
      : ::boost::mpl::false_
    {
    };

    template <>
    struct has_stable_iterators_selector<flat_multimapS>
      : ::boost::mpl::false_
    {
    };
    //->
}  // namespace boost
//]

#endif  // BOOST_UTILITY_HAS_STABLE_ITERS_SELECTOR_HPP_INCLUDED


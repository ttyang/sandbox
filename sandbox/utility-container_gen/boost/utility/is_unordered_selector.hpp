//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_IS_UNORDERED_SELECTOR_HPP_INCLUDED
#define BOOST_UTILITY_IS_UNORDERED_SELECTOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/utility/container_selector.hpp>

//[reference__is_unordered_selector
namespace boost {

    template <typename Selector>
    struct is_unordered_selector : ::boost::mpl::false_
    {
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_unordered_selector,(Selector))
        //->
    };

    //<-
    template <>
    struct is_unordered_selector<hash_setS> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_unordered_selector<hash_mapS> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_unordered_selector<hash_multisetS> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_unordered_selector<hash_multimapS> : ::boost::mpl::true_
    {
    };
    //->
}  // namespace boost
//]

#endif  // BOOST_UTILITY_IS_UNORDERED_SELECTOR_HPP_INCLUDED


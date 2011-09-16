//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED
#define BOOST_UTILITY_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/utility/container_selector.hpp>

//[reference__is_random_access_selector
namespace boost {

    template <typename Selector>
    struct is_random_access_selector : ::boost::mpl::false_
    {
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_selector,(Selector))
        //->
    };

    //<-
    template <>
    struct is_random_access_selector<vecS> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_random_access_selector<dequeS> : ::boost::mpl::true_
    {
    };
    //->
}  // namespace boost
//]

#endif  // BOOST_UTILITY_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED


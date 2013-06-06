//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_STD_HEAP_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_STD_HEAP_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/selectors.hpp>

//[reference__is_std_heap_selector
namespace boost {

    template <typename Selector>
    struct is_std_heap_selector
        //<-
      : ::boost::mpl::false_
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_std_heap_selector, (Selector))
        //->
    };
}  // namespace boost
//]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <>
    struct is_std_heap_selector<std_heap_selector_base> : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename CompareSelector, typename SequenceSelector>
    struct is_std_heap_selector<
        std_heap_selector<CompareSelector,SequenceSelector>
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_IS_STD_HEAP_SELECTOR_HPP_INCLUDED


//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_HAS_FRONT_NOT_TOP_MFUNC_SEL_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_HAS_FRONT_NOT_TOP_MFUNC_SEL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/selectors.hpp>

//[reference__has_front_not_top_member_function_selector
namespace boost {

    template <typename Selector>
    struct has_front_not_top_member_function_selector
      : ::boost::mpl::false_
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , has_front_not_top_member_function_selector
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <>
    struct has_front_not_top_member_function_selector<
        queue_selector_base
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename ContainerSelector>
    struct has_front_not_top_member_function_selector<
        queue_selector<ContainerSelector>
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_HAS_FRONT_NOT_TOP_MFUNC_SEL_HPP_INCLUDED


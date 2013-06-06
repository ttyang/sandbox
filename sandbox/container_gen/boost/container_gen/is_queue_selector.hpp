//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_QUEUE_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_QUEUE_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/bool.hpp>

#if defined BOOST_NO_SFINAE || defined BOOST_MPL_CFG_NO_HAS_XXX

namespace boost {

    template <typename Selector>
    struct is_queue_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_queue_selector, (Selector))
    };
}  // namespace boost

#include <boost/container_gen/selectors.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <>
    struct is_queue_selector<queue_selector_base> : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename SequenceSelector>
    struct is_queue_selector<queue_selector<SequenceSelector> >
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_NO_SFINAE && !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_queue.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename Selector>
    struct is_queue_selector_impl
      : ::boost::detail::metafunction::is_queue<
            typename container_gen<Selector,int>::type
        >
    {
    };
}}}  // namespace boost::detail::metafunction

//[reference__is_queue_selector
namespace boost {

    template <typename Selector>
    struct is_queue_selector
        //<-
      : ::boost::mpl::if_<
            typename ::boost::mpl::aux::has_type<
                container_gen<Selector,int>
            >::type
          , detail::metafunction::is_queue_selector_impl<Selector>
          , ::boost::mpl::false_
        >::type
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_queue_selector, (Selector))
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_NO_SFINAE, BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_QUEUE_SELECTOR_HPP_INCLUDED


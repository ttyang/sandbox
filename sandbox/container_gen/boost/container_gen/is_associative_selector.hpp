//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_IS_ASSOCIATIVE_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_ASSOCIATIVE_SELECTOR_HPP_INCLUDED

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/or.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include <boost/container_gen/is_multiple_assoc_selector.hpp>

namespace boost {

    template <typename Selector>
    struct is_associative_selector
      : ::boost::mpl::or_<
            is_unique_associative_selector<Selector>
          , is_multiple_associative_selector<Selector>
        >
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_associative_selector
          , (Selector)
        )
    };
}  // namespace boost

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>

//[reference__is_associative_selector
namespace boost {

    template <typename Selector>
    struct is_associative_selector
        //<-
      : ::boost::detail::metafunction::is_associative_container<
            typename container_gen<Selector,int>::type
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_associative_selector
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_ASSOCIATIVE_SELECTOR_HPP_INCLUDED


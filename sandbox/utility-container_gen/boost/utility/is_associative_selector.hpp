//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_IS_ASSOCIATIVE_SELECTOR_HPP_INCLUDED
#define BOOST_UTILITY_IS_ASSOCIATIVE_SELECTOR_HPP_INCLUDED

#include <boost/mpl/or.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/utility/is_unique_assoc_selector.hpp>
#include <boost/utility/is_multiple_assoc_selector.hpp>

//[reference__is_associative_selector
namespace boost {

    template <typename Selector>
    struct is_associative_selector
      : ::boost::mpl::or_<
            is_unique_associative_selector<Selector>
          , is_multiple_associative_selector<Selector>
        >
    {
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

#endif  // BOOST_UTILITY_IS_ASSOCIATIVE_SELECTOR_HPP_INCLUDED


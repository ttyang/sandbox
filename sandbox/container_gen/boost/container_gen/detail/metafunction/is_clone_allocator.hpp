//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_DETAIL_METAFUNCTION_IS_CLONE_ALLOCATOR_HPP
#define BOOST_CONTAINER_GEN_DETAIL_METAFUNCTION_IS_CLONE_ALLOCATOR_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/is_compare_selector.hpp>
#include <boost/container_gen/is_hasher_selector.hpp>
#include <boost/detail/metafunction/is_allocator.hpp>

namespace boost { namespace detail { namespace metafunction {

    // Without the ability to detect the presence of static member function
    // templates, this hack relies on process of elimination to facilitate
    // template argument deduction.
    template <typename T>
    struct is_clone_allocator
      : ::boost::mpl::eval_if<
            is_allocator<T>
          , ::boost::mpl::false_
          , ::boost::mpl::eval_if<
                is_compare_selector<T>
              , ::boost::mpl::false_
              , ::boost::mpl::if_<
                    is_hasher_selector<T>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
            >
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_clone_allocator,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_CONTAINER_GEN_DETAIL_METAFUNCTION_IS_CLONE_ALLOCATOR_HPP


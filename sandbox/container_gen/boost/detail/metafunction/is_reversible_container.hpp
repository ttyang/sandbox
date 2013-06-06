// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_REVERSIBLE_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_REVERSIBLE_CONTAINER_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_mfunc_rbegin_rend.hpp>
#include <boost/detail/metafunction/has_rvrs_container_typedefs.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/metafunction/is_ptr_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_reversible_container_impl
      : ::boost::mpl::and_<
            typename has_member_function_rbegin<
                T
              , typename T::const_reverse_iterator
              , ::boost::mpl::vector0<>
              , ::boost::function_types::const_qualified
            >::type
          , typename has_member_function_rend<
                T
              , typename T::const_reverse_iterator
              , ::boost::mpl::vector0<>
              , ::boost::function_types::const_qualified
            >::type
        >
    {
    };

    template <typename T>
    struct is_reversible_container
      : ::boost::mpl::eval_if<
            has_reversible_container_typedefs<T>
          , ::boost::mpl::if_<
                is_reversible_container_impl<T>
              , is_container<T>
              , is_ptr_container<T>
            >
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_reversible_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_REVERSIBLE_CONTAINER_HPP_INCLUDED


// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_WITH_EMPLACE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_WITH_EMPLACE_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>
#include <boost/deatil/metafunction/has_mfunc_emplace.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_sequence_with_emplace
      : ::boost::mpl::or_<
            typename has_member_function_emplace_front<
                T
              , void
              , ::boost::mpl::vector0<>
              , ::boost::function_types::non_const
            >::type
          , typename has_member_function_emplace_back<
                T
              , void
              , ::boost::mpl::vector0<>
              , ::boost::function_types::non_const
            >::type
        >
    {
    };

    template <typename T>
    struct is_associative_container_with_emplace
      : has_member_function_emplace<
            T
          , typename T::iterator
          , ::boost::mpl::vector1<typename T::key_type>
          , ::boost::function_types::non_const
        >
    {
    };

    template <typename T>
    struct is_container_with_emplace
      : ::boost::mpl::if_<
            typename is_reversible_container<T>::type
          , is_container_with_emplace_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_container_with_emplace,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_WITH_EMPLACE_HPP_INCLUDED


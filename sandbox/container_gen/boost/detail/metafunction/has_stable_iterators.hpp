// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_STABLE_ITERATORS_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_STABLE_ITERATORS_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/metafunction/is_random_access_iterator.hpp>
#include <boost/detail/metafunction/is_hashed_assoc_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct has_stable_iterators_impl
      : ::boost::mpl::eval_if<
            is_random_access_iterator<typename T::iterator>
          , ::boost::mpl::false_
          , ::boost::mpl::not_<is_hashed_associative_container<T> >
        >
    {
    };

    template <typename T>
    struct has_stable_iterators
      : ::boost::mpl::eval_if<
            is_container<T>
          , has_stable_iterators_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_stable_iterators,(T))
    };
}}}  // namespace boost::detail::metafunction

#include <boost/config.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/container/stable_vector.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename ValueType, typename Allocator>
    struct has_stable_iterators<
        ::boost::container::stable_vector<ValueType,Allocator>
    > : ::boost::mpl::true_
    {
    };
}}}  // namespace boost::detail::metafunction

#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_STABLE_ITERATORS_HPP_INCLUDED


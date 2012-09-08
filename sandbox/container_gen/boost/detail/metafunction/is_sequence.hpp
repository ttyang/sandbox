// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_SEQUENCE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_iterator_category.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    // Major assumption:
    // A Sequence is a Container that is neither Associative
    // nor with an Iterator that is a raw pointer (e.g. boost::array).
    template <typename T>
    struct is_sequence_impl
      : ::boost::mpl::if_<
            typename has_iterator_category< typename T::iterator >::type
          , ::boost::mpl::not_<is_associative_container<T> >
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_sequence
      : ::boost::mpl::eval_if<
            is_container<T>
          , is_sequence_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_sequence,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_SEQUENCE_HPP_INCLUDED


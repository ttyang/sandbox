// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_BACK_INSERTION_SEQUENCE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_BACK_INSERTION_SEQUENCE_HPP_INCLUDED

#include <iterator>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/detail/metafunction/is_sequence.hpp>

namespace boost { namespace detail { namespace metafunction {

    // Major assumption:
    // A Back Insertion Sequence is a Sequence with Bidirectional Iterators.
    template <typename T>
    struct is_back_insertion_sequence_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_convertible<
                typename ::boost::BOOST_ITERATOR_CATEGORY<
                    typename T::iterator
                >::type
              , ::std::bidirectional_iterator_tag
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_back_insertion_sequence
      : ::boost::mpl::eval_if<
            is_sequence<T>
          , is_back_insertion_sequence_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_back_insertion_sequence,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_BACK_INSERTION_SEQUENCE_HPP_INCLUDED


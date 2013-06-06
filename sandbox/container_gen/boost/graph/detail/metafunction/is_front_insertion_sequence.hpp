// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_METAFUNCTION_IS_FRONT_INSERTION_SEQUENCE_HPP
#define BOOST_GRAPH_DETAIL_METAFUNCTION_IS_FRONT_INSERTION_SEQUENCE_HPP

#include <iterator>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/detail/metafunction/is_sequence.hpp>

namespace boost { namespace graph_detail {

    // Major BGL assumption:
    // A Front Insertion Sequence is a Sequence without
    // Bidirectional Iterators.
    template <typename T>
    struct is_front_insertion_sequence_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_convertible<
                typename ::boost::BOOST_ITERATOR_CATEGORY<
                    typename T::iterator
                >::type
              , ::std::bidirectional_iterator_tag
            >
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >
    {
    };

    template <typename T>
    struct is_front_insertion_sequence
      : ::boost::mpl::eval_if<
            ::boost::detail::metafunction::is_sequence<T>
          , is_front_insertion_sequence_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_front_insertion_sequence,(T))
    };
}}  // namespace boost::graph_detail

#endif  // BOOST_GRAPH_DETAIL_METAFUNCTION_IS_FRONT_INSERTION_SEQUENCE_HPP


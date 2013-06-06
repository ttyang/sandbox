// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_RANDOM_ACCESS_ITERATOR_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_RANDOM_ACCESS_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/detail/metafunction/has_iterator_category.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_random_access_iterator_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_convertible<
                typename ::boost::BOOST_ITERATOR_CATEGORY<T>::type
              , ::std::random_access_iterator_tag
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_random_access_iterator
      : ::boost::mpl::eval_if<
            typename has_iterator_category< ::std::iterator_traits<T> >::type
          , is_random_access_iterator_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_iterator,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_RANDOM_ACCESS_ITERATOR_HPP_INCLUDED


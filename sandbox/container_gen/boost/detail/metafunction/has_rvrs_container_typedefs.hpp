// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_HAS_RVRS_CONTAINER_TYPEDEFS_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_HAS_RVRS_CONTAINER_TYPEDEFS_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/is_bidirectional_iterator.hpp>
#include <boost/detail/metafunction/has_iterator.hpp>
#include <boost/detail/metafunction/has_const_iterator.hpp>
#include <boost/detail/metafunction/has_reverse_iterator.hpp>
#include <boost/detail/metafunction/has_const_reverse_iterator.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct has_reversible_container_typedefs_impl
      : ::boost::mpl::if_<
            ::boost::mpl::or_<
                ::std::tr1::is_void<typename T::reverse_iterator>
              , ::std::tr1::is_void<typename T::const_reverse_iterator>
            >
          , ::boost::mpl::false_
          , ::boost::mpl::and_<
                ::boost::mpl::and_<
                    is_bidirectional_iterator<typename T::iterator>
                  , is_bidirectional_iterator<typename T::const_iterator>
                >
              , ::boost::mpl::and_<
                    is_bidirectional_iterator<typename T::reverse_iterator>
                  , is_bidirectional_iterator<
                        typename T::const_reverse_iterator
                    >
                >
            >
        >
    {
    };

    template <typename T>
    struct has_reversible_container_typedefs
      : ::boost::mpl::eval_if<
            ::boost::mpl::and_<
                ::boost::mpl::and_<
                    typename has_iterator<T>::type
                  , typename has_const_iterator<T>::type
                >
              , ::boost::mpl::and_<
                    typename has_reverse_iterator<T>::type
                  , typename has_const_reverse_iterator<T>::type
                >
            >
          , has_reversible_container_typedefs_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_reversible_container_typedefs,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_HAS_RVRS_CONTAINER_TYPEDEFS_HPP_INCLUDED


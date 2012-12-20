// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_MULTI_ASSOC_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_MULTI_ASSOC_CONTAINER_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/utility/get_reference.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>
#include <boost/detail/metafunction/is_ptr_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_multiple_associative_container_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_same<
                BOOST_TYPEOF_TPL(
                    T().insert(::boost::get_reference<typename T::key_type>())
                )
              , typename T::iterator
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T>
    struct is_multiple_associative_ptr_container_impl
      : ::boost::mpl::if_<
            ::std::tr1::is_same<
                BOOST_TYPEOF_TPL(
                    T().insert(&::boost::get_reference<typename T::key_type>())
                )
              , typename T::iterator
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T>
    struct is_multiple_associative_container
      : ::boost::mpl::eval_if<
            is_associative_container<T>
          , ::boost::mpl::if_<
                is_ptr_container<T>
              , is_multiple_associative_ptr_container_impl<T>
              , is_multiple_associative_container_impl<T>
            >
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_multiple_associative_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_MULTI_ASSOC_CONTAINER_HPP_INCLUDED


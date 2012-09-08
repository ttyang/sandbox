// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_value_type.hpp>
#include <boost/detail/metafunction/has_difference_type.hpp>
#include <boost/detail/metafunction/has_size_type.hpp>
#include <boost/detail/metafunction/has_iterator.hpp>
#include <boost/detail/metafunction/has_const_iterator.hpp>
#include <boost/detail/metafunction/has_pointer.hpp>
#include <boost/detail/metafunction/has_const_pointer.hpp>
#include <boost/detail/metafunction/has_reference.hpp>
#include <boost/detail/metafunction/has_const_reference.hpp>
#include <boost/detail/metafunction/is_input_iterator.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct has_container_typedefs
      : ::boost::mpl::and_<
            ::boost::mpl::and_<
                typename has_value_type<T>::type
              , typename has_difference_type<T>::type
              , typename has_size_type<T>::type
              , typename has_iterator<T>::type
              , typename has_const_iterator<T>::type
            >
          , ::boost::mpl::and_<
                typename has_reference<T>::type
              , typename has_const_reference<T>::type
//              , typename has_pointer<T>::type
//              , typename has_const_pointer<T>::type
            >
        >
    {
    };

    template <typename T>
    struct is_container_impl
      : is_input_iterator<typename T::const_iterator>::type
    {
    };

    template <typename T>
    struct is_container
      : ::boost::mpl::if_<
            has_container_typedefs<T>
          , is_container_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_HPP_INCLUDED


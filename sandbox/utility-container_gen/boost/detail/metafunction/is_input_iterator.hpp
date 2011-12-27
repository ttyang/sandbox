// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_INPUT_ITERATOR_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_INPUT_ITERATOR_HPP_INCLUDED

#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/type_traits/has_dereference.hpp>
#include <boost/type_traits/has_pre_increment.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/detail/metafunction/has_value_type.hpp>
#include <boost/detail/metafunction/has_difference_type.hpp>
#include <boost/detail/metafunction/has_pointer.hpp>
#include <boost/detail/metafunction/has_reference.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct is_input_iterator_impl
      : ::boost::is_signed<typename T::difference_type>
    {
    };

    template <typename T>
    struct is_input_iterator
      : ::boost::mpl::if_<
            ::boost::mpl::and_<
                typename has_value_type<T>::type
              , typename has_difference_type<T>::type
              , typename has_pointer<T>::type
              , typename has_reference<T>::type
            >
          , ::boost::mpl::and_<
                ::boost::has_equal_to<T>
              , ::boost::has_dereference<T>
              , ::boost::has_pre_increment<T>
              , ::boost::has_post_increment<T>
              , is_input_iterator_impl<T>
            >
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_input_iterator,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_IS_INPUT_ITERATOR_HPP_INCLUDED


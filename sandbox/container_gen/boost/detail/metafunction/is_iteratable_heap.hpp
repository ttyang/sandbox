// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_ITERATABLE_HEAP_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_ITERATABLE_HEAP_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_mfunc_begin_end.hpp>
#include <boost/detail/metafunction/has_iterator.hpp>
#include <boost/detail/metafunction/has_const_iterator.hpp>
#include <boost/detail/metafunction/has_input_const_iterator.hpp>
#include <boost/detail/metafunction/is_heap.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_iteratable_heap_impl
      : ::boost::mpl::and_<
            typename has_member_function_begin<
                T
              , typename T::iterator
              , ::boost::mpl::vector0<>
              , ::boost::function_types::const_qualified
            >::type
          , typename has_member_function_end<
                T
              , typename T::iterator
              , ::boost::mpl::vector0<>
              , ::boost::function_types::const_qualified
            >::type
        >
    {
    };

    template <typename T>
    struct is_iteratable_heap
      : ::boost::mpl::if_<
            ::boost::mpl::and_<
                is_heap<T>
              , ::boost::mpl::and_<
                    typename has_iterator<T>::type
                  , typename has_const_iterator<T>::type
                >
            >
          , ::boost::mpl::and_<
                has_input_const_iterator<T>
              , is_iteratable_heap_impl<T>
            >
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_iteratable_heap,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_ITERATABLE_HEAP_HPP_INCLUDED


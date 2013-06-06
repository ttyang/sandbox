// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_STACK_OR_STD_HEAP_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_STACK_OR_STD_HEAP_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_mfunc_empty.hpp>
#include <boost/detail/metafunction/has_mfunc_size.hpp>
#include <boost/detail/metafunction/has_mfunc_top.hpp>
#include <boost/detail/metafunction/has_mfunc_push.hpp>
#include <boost/detail/metafunction/has_mfunc_pop.hpp>
#include <boost/detail/metafunction/has_value_type.hpp>
#include <boost/detail/metafunction/has_size_type.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_stack_or_std_heap_impl
      : ::boost::mpl::and_<
            ::boost::mpl::and_<
                ::boost::mpl::and_<
                    typename has_member_function_empty<
                        T
                      , bool
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::const_qualified
                    >::type
                  , typename has_member_function_size<
                        T
                      , typename T::size_type
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::const_qualified
                    >::type
                >
              , typename has_member_function_top<
                    T
                  , typename T::value_type const&
                  , ::boost::mpl::vector0<>
                  , ::boost::function_types::const_qualified
                >::type
            >
          , ::boost::mpl::and_<
                typename has_member_function_push<
                    T
                  , void
                  , ::boost::mpl::vector1<typename T::value_type const&>
                  , ::boost::function_types::non_const
                >::type
              , typename has_member_function_pop<
                    T
                  , void
                  , ::boost::mpl::vector0<>
                  , ::boost::function_types::non_const
                >::type
            >
        >
    {
    };

    template <typename T>
    struct is_stack_or_std_heap
      : ::boost::mpl::if_<
            ::boost::mpl::and_<
                typename has_value_type<T>::type
              , typename has_size_type<T>::type
            >
          , is_stack_or_std_heap_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_stack_or_std_heap,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_STACK_OR_STD_HEAP_HPP_INCLUDED


// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_MUTABLE_HEAP_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_MUTABLE_HEAP_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_mfunc_update.hpp>
#include <boost/detail/metafunction/has_mfunc_increase.hpp>
#include <boost/detail/metafunction/has_mfunc_decrease.hpp>
#include <boost/detail/metafunction/has_mfunc_merge.hpp>
#include <boost/detail/metafunction/has_mfunc_push.hpp>
#include <boost/detail/metafunction/has_handle_type.hpp>
#include <boost/detail/metafunction/is_heap.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_mutable_heap_with_increase
      : ::boost::mpl::eval_if<
            typename has_member_function_increase<
                T
              , void
              , ::boost::mpl::vector1<typename T::handle_type>
              , ::boost::function_types::non_const
            >::type
          , has_member_function_increase<
                T
              , void
              , ::boost::mpl::vector2<
                    typename T::handle_type
                  , typename T::const_reference
                >
              , ::boost::function_types::non_const
            >
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_mutable_heap_with_decrease
      : ::boost::mpl::eval_if<
            typename has_member_function_decrease<
                T
              , void
              , ::boost::mpl::vector1<typename T::handle_type>
              , ::boost::function_types::non_const
            >::type
          , has_member_function_decrease<
                T
              , void
              , ::boost::mpl::vector2<
                    typename T::handle_type
                  , typename T::const_reference
                >
              , ::boost::function_types::non_const
            >
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T>
    struct is_mutable_heap_with_push_and_merge
#if 1
      : has_member_function_push<
            T
          , typename T::handle_type
          , ::boost::mpl::vector1<typename T::const_reference>
          , ::boost::function_types::non_const
        >
#else
      : ::boost::mpl::eval_if<
            typename has_member_function_push<
                T
              , typename T::handle_type
              , ::boost::mpl::vector1<typename T::const_reference>
              , ::boost::function_types::non_const
            >::type
          , has_member_function_merge<
                T
              , void
              , ::boost::mpl::vector1<T const&>
              , ::boost::function_types::non_const
            >
          , ::boost::mpl::false_
        >
#endif
    {
    };

    template <typename T>
    struct is_mutable_heap_impl
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::eval_if<
                    typename has_member_function_update<
                        T
                      , void
                      , ::boost::mpl::vector1<typename T::handle_type>
                      , ::boost::function_types::non_const
                    >::type
                  , has_member_function_update<
                        T
                      , void
                      , ::boost::mpl::vector2<
                            typename T::handle_type
                          , typename T::const_reference
                        >
                      , ::boost::function_types::non_const
                    >
                  , ::boost::mpl::false_
                >::type
              , is_mutable_heap_with_increase<T>
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::eval_if<
                is_mutable_heap_with_decrease<T> 
              , is_mutable_heap_with_push_and_merge<T>
              , ::boost::mpl::false_
            >
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_mutable_heap
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
                is_heap<T>
              , has_handle_type<T>
              , ::boost::mpl::false_
            >::type
          , is_mutable_heap_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_mutable_heap,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_MUTABLE_HEAP_HPP_INCLUDED


// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_ASSOCIATIVE_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_ASSOCIATIVE_CONTAINER_HPP_INCLUDED

#include <utility>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_key_type.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/metafunction/is_ptr_container.hpp>

#if 0
#include <boost/detail/metafunction/has_mfunc_erase.hpp>
#include <boost/detail/metafunction/has_mfunc_clear.hpp>
#include <boost/detail/metafunction/has_mfunc_find.hpp>
#include <boost/detail/metafunction/has_mfunc_count.hpp>
#include <boost/detail/metafunction/has_mfunc_equal_range.hpp>
#endif

namespace boost { namespace detail { namespace metafunction {

#if 0
    template <typename T>
    struct is_associative_container_impl
      : ::boost::mpl::and_<
            ::boost::mpl::and_<
                ::boost::mpl::and_<
                    typename has_member_function_erase<
                        T
                      , typename T::iterator
                      , ::boost::mpl::vector1<typename T::iterator>
                      , ::boost::function_types::non_const
                    >::type
                  , typename has_member_function_clear<
                        T
                      , void
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::non_const
                    >::type
                >
              , ::boost::mpl::and_<
                    typename has_member_function_find<
                        T
                      , typename T::const_iterator
                      , ::boost::mpl::vector1<typename T::key_type const&>
                      , ::boost::function_types::const_qualified
                    >::type
                  , typename has_member_function_find<
                        T
                      , typename T::iterator
                      , ::boost::mpl::vector1<typename T::key_type const&>
                      , ::boost::function_types::non_const
                    >::type
                >
            >
          , ::boost::mpl::and_<
                typename has_member_function_count<
                    T
                  , typename T::size_type
                  , ::boost::mpl::vector1<typename T::key_type const&>
                  , ::boost::function_types::non_const
                >::type
              , ::boost::mpl::and_<
                    typename has_member_function_equal_range<
                        T
                      , ::std::pair<
                            typename T::const_iterator
                          , typename T::const_iterator
                        >
                      , ::boost::mpl::vector1<typename T::key_type const&>
                      , ::boost::function_types::const_qualified
                    >::type
                  , typename has_member_function_equal_range<
                        T
                      , ::std::pair<
                            typename T::iterator
                          , typename T::iterator
                        >
                      , ::boost::mpl::vector1<typename T::key_type const&>
                      , ::boost::function_types::non_const
                    >::type
                >
            >
        >
    {
    };
#endif

    template <typename T>
    struct is_associative_container
      : ::boost::mpl::eval_if<
            typename has_key_type<T>::type
          , ::boost::mpl::if_<
                is_container<T>
//              , is_associative_container_impl<T>
              , ::boost::mpl::true_
              , is_ptr_container<T>
            >
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_associative_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_ASSOCIATIVE_CONTAINER_HPP_INCLUDED


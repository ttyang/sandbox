// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_SEQUENCE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_iterator_category.hpp>
#include <boost/detail/metafunction/has_mfunc_insert.hpp>
#include <boost/detail/metafunction/has_mfunc_erase.hpp>
#include <boost/detail/metafunction/has_mfunc_clear.hpp>
#include <boost/detail/metafunction/has_mfunc_resize.hpp>
#include <boost/detail/metafunction/is_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_sequence_impl
      : ::boost::mpl::and_<
            ::boost::mpl::and_<
                typename has_iterator_category< typename T::iterator >::type
              , ::boost::mpl::or_<
                    typename has_member_function_insert<
                        T
                      , typename T::iterator
                      , ::boost::mpl::vector2<
                            typename T::const_iterator
                          , typename T::value_type const&
                        >
                      , ::boost::function_types::non_const
                    >::type
                  , typename has_member_function_insert<
                        T
                      , typename T::iterator
                      , ::boost::mpl::vector2<
                            typename T::iterator
                          , typename T::value_type const&
                        >
                      , ::boost::function_types::non_const
                    >::type
                >
            >
          , ::boost::mpl::and_<
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
                    typename has_member_function_resize<
                        T
                      , void
                      , ::boost::mpl::vector1<typename T::size_type>
                      , ::boost::function_types::non_const
                    >::type
                  , typename has_member_function_resize<
                        T
                      , void
                      , ::boost::mpl::vector2<
                            typename T::size_type
                          , typename T::value_type const&
                        >
                      , ::boost::function_types::non_const
                    >::type
                >
            >
        >
    {
    };

    template <typename T>
    struct is_sequence
      : ::boost::mpl::if_<
            is_container<T>
          , is_sequence_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_sequence,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_SEQUENCE_HPP_INCLUDED


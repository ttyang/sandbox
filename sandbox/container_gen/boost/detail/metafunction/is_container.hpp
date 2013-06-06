// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_CONTAINER_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_mfunc_begin_end.hpp>
#include <boost/detail/metafunction/has_mfunc_size.hpp>
#include <boost/detail/metafunction/has_mfunc_empty.hpp>
#include <boost/detail/metafunction/has_container_typedefs.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_container_impl
      : ::boost::mpl::and_<
            ::boost::mpl::and_<
                ::boost::mpl::and_<
                    typename has_member_function_begin<
                        T
                      , typename T::const_iterator
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::const_qualified
                    >::type
                  , typename has_member_function_end<
                        T
                      , typename T::const_iterator
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::const_qualified
                    >::type
                >
              , ::boost::mpl::and_<
                    typename has_member_function_size<
                        T
                      , typename T::size_type
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::const_qualified
                    >::type
                  , typename has_member_function_max_size<
                        T
                      , typename T::size_type
                      , ::boost::mpl::vector0<>
                      , ::boost::function_types::const_qualified
                    >::type
                >
            >
          , typename has_member_function_empty<
                T
              , bool
              , ::boost::mpl::vector0<>
              , ::boost::function_types::const_qualified
            >::type
        >
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


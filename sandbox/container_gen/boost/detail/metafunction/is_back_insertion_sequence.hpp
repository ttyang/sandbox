// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_BACK_INSERTION_SEQUENCE_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_BACK_INSERTION_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/detail/metafunction/has_mfunc_back.hpp>
#include <boost/detail/metafunction/is_sequence.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_back_insertion_sequence_impl
      : ::boost::mpl::and_<
            ::boost::mpl::and_<
                typename has_member_function_back<
                    T
                  , typename T::const_reference
                  , ::boost::mpl::vector0<>
                  , ::boost::function_types::const_qualified
                >::type
              , typename has_member_function_back<
                    T
                  , typename T::reference
                  , ::boost::mpl::vector0<>
                  , ::boost::function_types::non_const
                >::type
            >
          , ::boost::mpl::and_<
                typename has_member_function_push_back<
                    T
                  , void
                  , ::boost::mpl::vector1<typename T::value_type const&>
                  , ::boost::function_types::non_const
                >::type
              , typename has_member_function_pop_back<
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
    struct is_back_insertion_sequence
      : ::boost::mpl::eval_if<
            is_sequence<T>
          , is_back_insertion_sequence_impl<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_back_insertion_sequence,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_BACK_INSERTION_SEQUENCE_HPP_INCLUDED


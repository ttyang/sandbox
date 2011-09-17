/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DETAIL_SEGMENTED_EQUAL_TO_IMPL_HPP
#define BOOST_FUSION_ITERATOR_DETAIL_SEGMENTED_EQUAL_TO_IMPL_HPP

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
              , result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >
            >
        {};

        template <>
        struct segmented_equal_to<fusion::nil, fusion::nil>
          : mpl::true_
        {};
    }
}}

#endif

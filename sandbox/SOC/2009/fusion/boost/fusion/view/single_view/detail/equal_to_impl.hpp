/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_SINGLE_VIEW_DETAIL_EQUAL_TO_IMPL_HPP
#define BOOST_FUSION_VIEW_SINGLE_VIEW_DETAIL_EQUAL_TO_IMPL_HPP

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct equal_to_impl;

    template<>
    struct equal_to_impl<single_view_iterator_tag>
    {
        template<typename It1, typename It2>
        struct apply
          : is_same<
                typename detail::identity<
                    typename detail::remove_reference<It1>::type::view_type
                >::type
              , typename detail::identity<
                    typename detail::remove_reference<It2>::type::view_type
                >::type
            >
        {};
    };
}}}

#endif

/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_NEXT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_NEXT_IMPL_HPP

#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <>
    struct next_impl<reverse_view_iterator_tag>
    {
        template <typename ItRef>
        struct apply
        {
            typedef
                reverse_view_iterator<
                    typename result_of::prior<
                        typename detail::remove_reference<
                            ItRef
                        >::type::first_type
                    >::type
                >
            type;

            static type
            call(ItRef it)
            {
                return type(fusion::prior(it.first));
            }
        };
    };
}}}

#endif

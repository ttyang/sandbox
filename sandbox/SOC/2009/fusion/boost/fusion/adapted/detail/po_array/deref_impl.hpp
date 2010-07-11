/*==============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_PO_ARRAY_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_PO_ARRAY_DEREF_IMPL_HPP

#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct deref_impl;

    template<>
    struct deref_impl<po_array_iterator_tag>
    {
        template<typename It>
        struct apply
        {
            typedef typename detail::remove_reference<It>::type it;

            typedef typename
                detail::add_lref<
                    typename remove_extent<
                        typename detail::remove_reference<
                            typename it::seq_type
                        >::type
                    >::type
                >::type
            type;

            static type
            call(It it)
            {
                return (*it.seq)[it::index::value];
            }
        };
    };
}}}

#endif

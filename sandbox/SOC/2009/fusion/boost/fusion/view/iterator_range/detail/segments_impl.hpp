/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_RANGE_DETAIL_SEGMENTED_IMPL_HPP
#define BOOST_FUSION_ITERATOR_RANGE_DETAIL_SEGMENTED_IMPL_HPP

#include <boost/fusion/sequence/intrinsic/segments.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/view/iterator_range/detail/segmented_iterator_range.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct segments_impl;

        template <>
        struct segments_impl<iterator_range_tag>
        {
            template <typename Seq>
            struct apply
            {
                typedef typename detail::remove_reference<Seq>::type seq;
                typedef
                    detail::make_segmented_range<
                        typename seq::begin_type
                      , typename seq::end_type
                    >
                impl;

                BOOST_FUSION_MPL_ASSERT((traits::is_segmented<typename impl::type>))

                typedef
                    typename result_of::segments<typename impl::type>::type
                type;

                static type call(Seq seq)
                {
                    return fusion::segments(impl::call(seq.first, seq.last));
                }
            };
        };
    }
}}

#endif

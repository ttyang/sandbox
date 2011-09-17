/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DETAIL_SEGMENT_SEQUENECE_HPP
#define BOOST_FUSION_ITERATOR_DETAIL_SEGMENT_SEQUENECE_HPP

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion { namespace traits
{
    template<typename>
    struct category_of;
}}}

namespace boost { namespace fusion { namespace detail
{
    struct segment_sequence_tag {};

    // Here, Sequence is a sequence of ranges (which may or may not be
    // segmented).
    template<typename Sequence>
    struct segment_sequence
    {
        typedef fusion_sequence_tag tag;
        typedef segment_sequence_tag fusion_tag;
        typedef typename traits::is_view<Sequence>::type is_view;
        typedef typename traits::category_of<Sequence>::type category;
        typedef Sequence sequence_type;
        sequence_type sequence;

        explicit segment_sequence(Sequence const & seq)
            : sequence(seq)
        {}
    };
}

namespace extension
{
    template<typename Tag>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
            : mpl::true_
        {};
    };

    template<typename Tag>
    struct is_segmented_impl;

    template<>
    struct is_segmented_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
            : mpl::true_
        {};
    };

    template<typename Tag>
    struct segments_impl;

    template<>
    struct segments_impl<detail::segment_sequence_tag>
    {
        template<typename Seq>
        struct apply
        {
            typedef typename detail::remove_reference<Seq>::type seq;
            typedef typename seq::sequence_type type;

            static type call(Seq seq)
            {
                return seq.sequence;
            }
        };
    };
}}}

#endif

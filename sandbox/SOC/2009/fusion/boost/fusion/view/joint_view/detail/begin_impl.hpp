/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename Tag>
    struct begin_impl;

    template <>
    struct begin_impl<joint_view_tag>
    {
        template <typename SeqRef>
        struct apply
        {
            typedef typename detail::remove_reference<SeqRef>::type seq;
            typedef typename
                result_of::begin<typename seq::seq1_type>::type
            first_type;
            typedef typename
                result_of::end<typename seq::seq1_type>::type
            last_type;
            typedef typename
                result_of::begin<typename seq::seq2_type>::type
            concat_type;
            typedef typename
                result_of::equal_to<first_type, last_type>::type
            equal_to;

            typedef typename
                mpl::if_<
                    equal_to
                  , concat_iterator<concat_type>
                  , joint_view_iterator<first_type, last_type, concat_type>
                >::type
            type;

            static type
            call(SeqRef seq, mpl::true_)
            {
                return type(fusion::begin(seq.seq2.get()));
            }

            static type
            call(SeqRef seq, mpl::false_)
            {
                return type(
                        fusion::begin(seq.seq1.get())
                      , fusion::begin(seq.seq2.get()));
            }

            static type
            call(SeqRef seq)
            {
                return call(seq, equal_to());
            }
        };
    };
}}}

#endif

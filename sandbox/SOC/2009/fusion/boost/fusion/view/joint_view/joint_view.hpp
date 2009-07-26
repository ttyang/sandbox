/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_JOINT_VIEW_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_JOINT_VIEW_HPP

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/ref.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/view/detail/view_storage.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/fusion/view/joint_view/detail/joint_view_fwd.hpp>
#include <boost/fusion/view/joint_view/detail/joint_view_iterator.hpp>
#include <boost/fusion/view/joint_view/detail/begin_impl.hpp>
#include <boost/fusion/view/joint_view/detail/deref_impl.hpp>
#include <boost/fusion/view/joint_view/detail/end_impl.hpp>
#include <boost/fusion/view/joint_view/detail/equal_to_impl.hpp>
#include <boost/fusion/view/joint_view/detail/next_impl.hpp>
#include <boost/fusion/view/joint_view/detail/value_of_impl.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Seq1, typename Seq2>
    struct joint_view
      : sequence_base<joint_view<Seq1, Seq2> >
    {
        typedef joint_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef forward_traversal_tag category;
        typedef mpl::true_ is_view;

        typedef detail::view_storage<Seq1> storage1_type;
        typedef typename storage1_type::type seq1_type;
        typedef detail::view_storage<Seq2> storage2_type;
        typedef typename storage2_type::type seq2_type;

        typedef typename
            mpl::plus<
                result_of::size<seq1_type>
              , result_of::size<seq2_type>
            >::type
        size;

        template<typename OtherJointView>
        joint_view(BOOST_FUSION_R_ELSE_CLREF(OtherJointView) other_view)
          : seq1(BOOST_FUSION_FORWARD(OtherJointView,other_view).seq1)
          , seq2(BOOST_FUSION_FORWARD(OtherJointView,other_view).seq2)
        {}

#ifdef BOOST_NO_RVALUE_REFERENCES
        joint_view(typename storage1_type::call_param seq1,
               typename storage2_type::call_param seq2)
          : seq1(seq1)
          , seq2(seq2)
        {}
#else
        template<typename OtherSeq1, typename OtherSeq2>
        joint_view(BOOST_FUSION_R_ELSE_CLREF(OtherSeq1) other_seq1,
                BOOST_FUSION_R_ELSE_CLREF(OtherSeq2) other_seq2)
          : seq1(BOOST_FUSION_FORWARD(OtherSeq1,other_seq1))
          , seq2(BOOST_FUSION_FORWARD(OtherSeq2,other_seq2))
        {}
#endif

        template<typename OtherJointView>
        OtherJointView&
        operator=(BOOST_FUSION_R_ELSE_CLREF(OtherJointView) other_view)
        {
            seq1=BOOST_FUSION_FORWARD(OtherJointView,other_view).seq1;
            seq2=BOOST_FUSION_FORWARD(OtherJointView,other_view).seq2;
            return *this;
        }

        storage1_type seq1;
        storage2_type seq2;
    };
}}

#endif

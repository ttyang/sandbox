/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_REVERSE_VIEW_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_REVERSE_VIEW_HPP

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/ref.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/assert.hpp>
#include <boost/fusion/view/detail/view_storage.hpp>

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/fusion/view/reverse_view/detail/reverse_view_fwd.hpp>
#include <boost/fusion/view/reverse_view/detail/reverse_view_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/begin_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/end_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/deref_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/next_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/prior_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/advance_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/distance_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/equal_to_impl.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    template <typename Seq>
    struct reverse_view
      : sequence_base<reverse_view<Seq> >
    {
        typedef reverse_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef detail::view_storage<Seq> storage_type;
        typedef typename storage_type::type seq_type;
        typedef typename traits::category_of<seq_type>::type category;
        typedef typename result_of::size<seq_type>::type size;

        //BOOST_FUSION_STATIC_ASSERT(
        //    (is_base_of<bidirectional_traversal_tag,
        //            typename traits::category_of<first_type>::type>::value),
        //    "underlying iterator must be bidirectional");

#define REVERSE_VIEW_CTOR(COMBINATION,_)\
        template<typename OtherSeq>\
        reverse_view(reverse_view<OtherSeq> COMBINATION view)\
          : seq(BOOST_FUSION_FORWARD(\
                reverse_view<OtherSeq> COMBINATION,view).seq)\
        {}

        BOOST_FUSION_ALL_CV_REF_COMBINATIONS(REVERSE_VIEW_CTOR,_)

#undef REVERSE_VIEW_CTOR

#ifdef BOOST_NO_RVALUE_REFERENCES
        explicit reverse_view(typename storage_type::call_param seq)
          : seq(seq)
        {}
#else
        template<typename OtherSeq>
        explicit reverse_view(OtherSeq&& seq)
          : seq(std::forward<OtherSeq>(seq))
        {}
#endif

        template<typename OtherReverseView>
        OtherReverseView&
        operator=(BOOST_FUSION_R_ELSE_CLREF(OtherReverseView) other_view)
        {
            seq=BOOST_FUSION_FORWARD(OtherReverseView,other_view).seq;
            return *this;
        }

        detail::view_storage<Seq> seq;
    };
}}

#endif

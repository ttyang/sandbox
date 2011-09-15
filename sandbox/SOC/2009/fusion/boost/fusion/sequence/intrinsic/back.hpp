/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SEQUENCE_INTRINSIC_BACK_HPP
#define BOOST_FUSION_SEQUENCE_INTRINSIC_BACK_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq>
        struct back
          : deref<typename prior<typename end<Seq>::type>::type>
        {
            BOOST_FUSION_MPL_ASSERT((traits::is_sequence<Seq>))
            BOOST_FUSION_MPL_ASSERT((traits::is_forward<Seq>))
            BOOST_FUSION_MPL_ASSERT_NOT((empty<Seq>))
        };
    }

    template<typename Seq>
    typename result_of::back<BOOST_FUSION_R_ELSE_CLREF(Seq)>::type
    back(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
    {
        return fusion::deref(fusion::prior(fusion::end(
            BOOST_FUSION_FORWARD(Seq,seq))));
    }

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename Seq>
    typename result_of::back<Seq&>::type
    back(Seq& seq)
    {
        return fusion::deref(fusion::prior(fusion::end(seq)));
    }
#endif
}}

#endif

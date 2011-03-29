/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_TRANSFORMATION_POP_BACK_HPP
#define BOOST_FUSION_ALGORITHM_TRANSFORMATION_POP_BACK_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq>
        struct pop_back
        {
            BOOST_FUSION_MPL_ASSERT((traits::is_sequence<Seq>))
            BOOST_FUSION_MPL_ASSERT((traits::is_forward<Seq>))
            BOOST_FUSION_MPL_ASSERT_NOT((empty<Seq>))

            typedef 
                iterator_range<
                    typename begin<Seq>::type
                  , typename prior<typename end<Seq>::type>::type
                > 
            type;
        };
    }

    template<typename Seq>
    inline typename result_of::pop_back<BOOST_FUSION_R_ELSE_CLREF(Seq)>::type
    pop_back(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
    {
        return typename
            result_of::pop_back<BOOST_FUSION_R_ELSE_CLREF(Seq)>::type(
                    fusion::begin(BOOST_FUSION_FORWARD(Seq,seq))
                  , fusion::prior(fusion::end(BOOST_FUSION_FORWARD(Seq,seq))));
    }

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename Seq>
    inline typename result_of::pop_back<Seq&>::type
    pop_back(Seq& seq)
    {
        return typename
            result_of::pop_back<Seq&>::type(
                    fusion::begin(BOOST_FUSION_FORWARD(Seq,seq))
                  , fusion::prior(fusion::end(BOOST_FUSION_FORWARD(Seq,seq))));
    }
#endif
}}

#endif
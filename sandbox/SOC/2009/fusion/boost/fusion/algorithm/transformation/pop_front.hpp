/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_TRANSFORMATION_POP_FRONT_HPP
#define BOOST_FUSION_ALGORITHM_TRANSFORMATION_POP_FRONT_HPP

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#ifdef BOOST_FUSION_ENABLE_STATIC_ASSERTS
#   include <boost/fusion/sequence/intrinsic/size.hpp>
#endif
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/support/internal/ref.hpp>
#include <boost/fusion/support/internal/assert.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Seq>
        struct pop_front
        {
            //BOOST_FUSION_MPL_ASSERT((traits_is_sequence<Seq>));
            BOOST_FUSION_MPL_ASSERT((traits::is_forward<Seq>));
            BOOST_FUSION_MPL_ASSERT((size<Seq>));

            typedef 
                iterator_range<
                    typename next<typename begin<Seq>::type>::type
                  , typename end<Seq>::type
                > 
            type;
        };
    }

    template <typename Seq>
    inline typename result_of::pop_front<BOOST_FUSION_R_ELSE_CLREF(Seq)>::type
    pop_front(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
    {
        return typename
            result_of::pop_front<
                BOOST_FUSION_R_ELSE_CLREF(Seq)
            >::type(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }

#ifdef BOOST_NO_RVALUE_REFERENCES
    template <typename Seq>
    inline typename result_of::pop_front<Seq&>::type
    pop_front(Seq& seq)
    {
        return typename
            result_of::pop_front<Seq&>::type(
                fusion::next(fusion::begin(seq)), fusion::end(seq));
    }
#endif
}}

#endif

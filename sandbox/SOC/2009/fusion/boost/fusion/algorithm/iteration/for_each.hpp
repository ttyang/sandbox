/*==============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_FOR_EACH_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_FOR_EACH_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/algorithm/iteration/detail/for_each.hpp>
#include <boost/fusion/algorithm/iteration/detail/for_each_segmented.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename>
        struct for_each
        {
            BOOST_FUSION_MPL_ASSERT((traits::is_sequence<Seq>))
            BOOST_FUSION_MPL_ASSERT((
                mpl::or_<traits::is_forward<Seq>,traits::is_segmented<Seq> >))

            typedef void type;
        };
    }

    template<typename Seq, typename F>
    void
    for_each(BOOST_FUSION_R_ELSE_CLREF(Seq) seq,
        BOOST_FUSION_RREF_ELSE_OBJ(F) f)
    {
        detail::for_each<BOOST_FUSION_R_ELSE_CLREF(Seq)>(
            BOOST_FUSION_FORWARD(Seq,seq),
            BOOST_FUSION_FORWARD(F,f),
            typename traits::is_segmented<
                BOOST_FUSION_R_ELSE_CLREF(Seq)
            >::type());
    }

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename Seq, typename F>
    void
    for_each(Seq& seq,F f)
    {
        detail::for_each<Seq&>(
            seq,
            f,
            typename traits::is_segmented<Seq&>::type());
    }
#endif
}}

#endif

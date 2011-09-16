/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009-2011 Christopher Schmidt
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_QUERY_FIND_HPP
#define BOOST_FUSION_ALGORITHM_QUERY_FIND_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/internal/workaround.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/find_segmented.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename T>
        struct find
          : mpl::if_<
                traits::is_segmented<Seq>
              , detail::find_segmented<Seq, T>
              , detail::find<Seq, T>
            >::type
        {
            BOOST_FUSION_MPL_ASSERT((traits::is_sequence<Seq>))
            BOOST_FUSION_MPL_ASSERT((
                mpl::or_<traits::is_forward<Seq>, traits::is_segmented<Seq> >))
        };
    }

    template<typename T, typename Seq>
    typename result_of::find<BOOST_FUSION_R_ELSE_CLREF(Seq), T>::type
    find(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
    {
        return result_of::find<BOOST_FUSION_R_ELSE_CLREF(Seq), T>::call(
            BOOST_FUSION_FORWARD(Seq,seq));
    }

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename T, typename Seq>
    BOOST_FUSION_EXPLICIT_TEMPLATE_NON_CONST_ARG_OVERLOAD(
        result_of::find<,Seq,&, T>)
    find(Seq& seq)
    {
        return result_of::find<Seq&, T>::call(seq);
    }
#endif
}}

#endif

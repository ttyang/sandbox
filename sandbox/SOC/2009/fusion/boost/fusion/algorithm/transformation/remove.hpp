/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_TRANSFORMATION_REMOVE_HPP
#define BOOST_FUSION_ALGORITHM_TRANSFORMATION_REMOVE_HPP

#include <boost/fusion/view/filter_view/filter_view.hpp>

#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Seq, typename T>
        struct remove
        {
            typedef
                filter_view<Seq, mpl::not_<is_same<mpl::_, T> > >
            type;
        };
    }

    template <typename T, typename Seq>
    inline typename result_of::remove<BOOST_FUSION_R_ELSE_CLREF(Seq), T>::type
    remove(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
    {
        return typename
            result_of::remove<BOOST_FUSION_R_ELSE_CLREF(Seq), T>::type(
                BOOST_FUSION_FORWARD(Seq,seq));
    }

#ifdef BOOST_NO_RVALUE_REFERENCES
    template <typename T, typename Seq>
    inline typename result_of::remove<Seq&, T>::type
    remove_if(Seq& seq)
    {
        return typename result_of::remove<Seq&, T>::type(seq);
    }
#endif
}}

#endif

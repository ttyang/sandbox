/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_TRANSFORMATION_CLEAR_HPP
#define BOOST_FUSION_ALGORITHM_TRANSFORMATION_CLEAR_HPP

#include <boost/fusion/sequence/convert.hpp>
#ifdef BOOST_NO_VARIADIC_TEMPLATES
#   include <boost/fusion/container/vector/vector.hpp>
#else
#   include <boost/fusion/container/vector/vector10.hpp>
#endif
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/ref.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        //TODO doc!!!

        template <typename Seq>
        struct clear
        {
#ifdef BOOST_NO_VARIADIC_TEMPLATES
            typedef vector0<> vec;
#else
            typedef vector<> vec;
#endif

            typedef typename
                mpl::eval_if<
                    traits::is_view<Seq>
                  , mpl::identity<vec>
                  , result_of::convert<
                        typename traits::tag_of<Seq>::type
                      , vec
                    >
                >::type
            type;
        };
    }

    template <typename Seq>
    inline typename result_of::clear<BOOST_FUSION_R_ELSE_CLREF(Seq)>::type
    clear(BOOST_FUSION_R_ELSE_CLREF(Seq) seq)
    {
        return typename
            result_of::clear<BOOST_FUSION_R_ELSE_CLREF(Seq)>::type();
    }
}}

#endif

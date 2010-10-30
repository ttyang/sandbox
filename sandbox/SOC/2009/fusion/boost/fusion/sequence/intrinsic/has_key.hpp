/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SEQUENCE_INTRINSIC_HAS_KEY_HPP
#define BOOST_FUSION_SEQUENCE_INTRINSIC_HAS_KEY_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/algorithm/query/find_key.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/tag_of.hpp>

#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct has_key_impl
        {
            template<typename Seq, typename Key>
            struct apply
              : mpl::not_<
                    typename result_of::equal_to<
                        typename result_of::find_key<Seq, Key>::type
                      , typename result_of::end<Seq>::type
                    >::type
                >::type
            {};
        };
    }

    namespace result_of
    {
        template<typename Seq, typename Key>
        struct has_key
          : extension::has_key_impl<typename traits::tag_of<Seq>::type>::
                template apply<Seq, Key>
        {
            BOOST_FUSION_MPL_ASSERT((traits::is_sequence<Seq>))
            BOOST_FUSION_MPL_ASSERT((traits::is_associative<Seq>))
        };
    }

    template<typename Key, typename Seq>
    inline typename result_of::has_key<Seq const&, Key>::type
    has_key(Seq const& seq)
    {
        return typename result_of::has_key<Seq const&, Key>::type();
    }
}}

#endif

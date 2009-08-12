/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SEQUENCE_INTRINSIC_VALUE_AT_KEY_HPP
#define BOOST_FUSION_SEQUENCE_INTRINSIC_VALUE_AT_KEY_HPP

#ifdef BOOST_FUSION_ENABLE_STATIC_ASSERTS
#   include <boost/fusion/sequence/intrinsic/has_key.hpp>
#endif
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/algorithm/query/find_key.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/ref.hpp>
#include <boost/fusion/support/assert.hpp>

#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct sequence_facade_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl
        {
            template <typename SeqRef, typename Key>
            struct apply
            {
                typedef typename
                    result_of::value_of_data<
                        typename result_of::find_key<SeqRef, Key>::type
                    >::type
                type;
            };
        };

        template <>
        struct value_at_key_impl<sequence_facade_tag>
        {
            template <typename SeqRef, typename Key>
            struct apply
              : detail::remove_reference<SeqRef>::type::
                    template value_at_key<SeqRef, Key>
            {};
        };
    }

    namespace result_of
    {
        template <typename Seq, typename Key>
        struct value_at_key
          : extension::value_at_key_impl<typename traits::tag_of<Seq>::type>::
                template apply<typename detail::add_lref<Seq>::type, Key>
        {
            //BOOST_FUSION_MPL_ASSERT((traits_is_sequence<Seq>));
            BOOST_FUSION_MPL_ASSERT((traits::is_associative<Seq>));
            BOOST_FUSION_MPL_ASSERT((has_key<Seq,Key>));
        };
    }
}}

#endif

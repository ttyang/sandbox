
/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SEQUENCE_INTRINSIC_SIZE_HPP
#define BOOST_FUSION_SEQUENCE_INTRINSIC_SIZE_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_size.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template<typename Seq>
        struct size
          : remove_reference<Seq>::type::size
        {};
    }

    namespace extension
    {
        template<typename>
        struct size_impl
        {
            template<typename Seq>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Seq>
                  , detail::segmented_size<Seq>
                  , detail::size<Seq>
                >::type
            {};
        };
    }

    namespace result_of
    {
        template<typename Seq>
        struct size
          : extension::size_impl<typename traits::tag_of<Seq>::type>::
                template apply<Seq>::type
        {
            BOOST_FUSION_MPL_ASSERT((traits::is_sequence<Seq>))
        };
    }

    template<typename Seq>
    typename result_of::size<Seq const&>::type
    size(Seq const&)
    {
        return typename result_of::size<Seq const&>::type();
    }
}}

#endif

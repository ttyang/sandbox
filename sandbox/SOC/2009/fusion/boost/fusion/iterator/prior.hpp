/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_PRIOR_HPP
#define BOOST_FUSION_ITERATOR_PRIOR_HPP

#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<iterator_facade_tag>
        {
            template <typename ItRef>
            struct apply
              : detail::remove_reference<ItRef>::type::template prior<ItRef>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct prior
          : extension::prior_impl<typename traits::tag_of<It>::type>::
                template apply<typename detail::add_lref<It>::type>
        {};
    }

    template <typename It>
    typename result_of::prior<It const&>::type const
    prior(It const& it)
    {
        return result_of::prior<It const&>::call(it);
    }
}}

#endif

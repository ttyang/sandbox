/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template<>
    struct begin_impl<map_tag>
    {
        template<typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , map_category
                  , typename detail::add_lref<Seq>::type
                  , 0
                >
            type;

            static type
            call(Seq seq)
            {
                return type(&seq);
            }
        };
    };
}}}

#endif

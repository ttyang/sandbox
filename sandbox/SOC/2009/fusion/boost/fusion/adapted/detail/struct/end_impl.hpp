/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_END_IMPL_HPP

#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct end_impl;

    template<>
    struct end_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , typename detail::add_lref<Seq>::type
                  , struct_size<typename detail::identity<Seq>::type>::value
                >
            type;

            static type
            call(Seq seq)
            {
                return type(&seq);
            }
        };
    };

    template<>
    struct end_impl<assoc_struct_tag>
    {
        template<typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , typename detail::add_lref<Seq>::type
                  , struct_size<typename detail::identity<Seq>::type>::value
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
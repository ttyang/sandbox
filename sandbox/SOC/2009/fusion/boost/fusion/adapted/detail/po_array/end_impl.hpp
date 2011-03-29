/*==============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_PO_ARRAY_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_PO_ARRAY_END_IMPL_HPP

#include <boost/fusion/iterator/basic_iterator.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct end_impl;

    template<>
    struct end_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
        {
            typedef typename detail::remove_reference<Seq>::type seq;

            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , typename detail::add_lref<Seq>::type
                  , extent<seq,rank<seq>::value-1>::value
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
/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_DETAIL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_DETAIL_SIZE_IMPL_HPP

namespace boost { namespace fusion {

    struct array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<array_tag>
        {
            template<typename Sequence>
            struct apply
              : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

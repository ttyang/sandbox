/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_MPL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_MPL_SIZE_IMPL_HPP

#include <boost/mpl/size.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template <>
        struct size_impl<mpl_sequence_tag>
        {
            template <typename SeqRef>
            struct apply
              : mpl::size<typename detail::identity<SeqRef>::type>
            {};
        };
    }
}}

#endif

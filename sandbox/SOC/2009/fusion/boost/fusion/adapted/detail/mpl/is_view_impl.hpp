/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_MPL_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_MPL_IS_VIEW_IMPL_HPP

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename Tag>
    struct is_view_impl;

    template<>
    struct is_view_impl<mpl_sequence_tag>
    {
        template<typename SeqRef>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

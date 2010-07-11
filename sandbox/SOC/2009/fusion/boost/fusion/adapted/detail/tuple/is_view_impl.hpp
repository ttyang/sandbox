/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_TUPLE_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_TUPLE_IS_VIEW_IMPL_HPP

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<boost_tuple_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };

    template<>
    struct is_view_impl<std_tuple_tag>
      : is_view_impl<boost_tuple_tag>
    {};
}}}

#endif

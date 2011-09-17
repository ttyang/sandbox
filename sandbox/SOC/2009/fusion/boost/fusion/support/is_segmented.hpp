/*==============================================================================
    Copyright (c) 2006 Eric Niebler
    Copyright (c) 2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SUPPORT_IS_SEGMENTED_HPP
#define BOOST_FUSION_SUPPORT_IS_SEGMENTED_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct is_segmented_impl
        {
            template<typename>
            struct apply
              : mpl::false_
            {};
        };
    }

    namespace traits
    {
        template<typename T>
        struct is_segmented
          : extension::is_segmented_impl<
                typename traits::tag_of<T>::type
            >::template apply<T>
        {};
    }
}}

#endif

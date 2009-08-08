/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_MPL_PRIOR_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_MPL_PRIOR_IMPL_HPP

#include <boost/mpl/prior.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename Tag>
    struct prior_impl;

    template <>
    struct prior_impl<mpl_iterator_tag>
    {
        template <typename ItRef>
        struct apply
        {
            typedef
                mpl_iterator<
                    typename mpl::prior<
                        typename detail::identity<ItRef>::type
                    >::type
                >
            type;

            template<typename ItRef2>
            static type
            call(ItRef2)
            {
                return type();
            }
        };
    };
}}}

#endif

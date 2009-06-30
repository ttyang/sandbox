/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_DETAIL_STRICTEST_TRAVERSAL_HPP
#define BOOST_FUSION_VIEW_DETAIL_STRICTEST_TRAVERSAL_HPP

#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/mpl.hpp>

#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>

#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    namespace detail
    {
        template<typename Tag1, typename Tag2>
        struct stricter_traversal
        {
            typedef typename
                mpl::if_<
                    is_convertible<Tag2,Tag1>
                  , Tag1
                  , Tag2
                >::type
            type;
        };

        struct strictest_traversal_impl
        {
            template<typename Sig>
            struct result;

            template<typename Next, typename StrictestSoFar>
            struct result<strictest_traversal_impl(Next, StrictestSoFar)>
            {
                typedef typename traits::category_of<Next>::type next_tag;

                typedef typename
                    stricter_traversal<StrictestSoFar,next_tag>::type
                type;
            };
        };

        template<typename Sequence>
        struct strictest_traversal
          : result_of::fold<
                Sequence
              , fusion::random_access_traversal_tag
              , strictest_traversal_impl
            >
        {};
    }
}}

#endif

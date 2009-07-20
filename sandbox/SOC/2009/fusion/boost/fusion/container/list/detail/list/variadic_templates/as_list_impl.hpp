// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FUSION_CONTAINER_LIST_DETAIL_LIST_VARIADIC_TEMPLATES_AS_LIST_IMPL_HPP
#define BOOST_FUSION_CONTAINER_LIST_DETAIL_LIST_VARIADIC_TEMPLATES_AS_LIST_IMPL_HPP

#include <boost/fusion/container/list.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/support/variadic_templates/variadic_quote.hpp>
#include <boost/fusion/support/to_random_access_mpl_seq.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/unpack_args.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename SeqRef>
    struct as_list_impl
    {
        struct apply
        {
            typedef typename
                mpl::apply<
                    mpl::unpack_args<variadic_quote<list> >
                  , typename detail::to_random_access_mpl_seq<
                        typename detail::remove_reference<SeqRef>::type
                    >::type
                >::type
            type;
        };

        static typename apply::type
        call(SeqRef seq)
        {
            return typename apply::type(
                    sequence_assign(BOOST_FUSION_FORWARD(SeqRef,seq)));
        }
    };
}}}

#endif

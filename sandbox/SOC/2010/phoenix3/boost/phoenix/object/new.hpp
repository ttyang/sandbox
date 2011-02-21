/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_NEW_HPP
#define BOOST_PHOENIX_OBJECT_NEW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(new_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , BOOST_PHOENIX_COMPOSITE_LIMIT
)

namespace boost { namespace phoenix
{

    //template <typename T>
    struct new_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context, typename A0>
        struct result<This(Context, A0)>
        {
            typedef typename detail::result_of::target<A0> target_type;
            typedef typename target_type::type  construct_type;
            typedef typename target_type::type * type;
        };

        template <typename Context, typename Target>
        typename detail::result_of::target<Target>::type *
        operator()(Context const&, Target) const
        {
            return new typename detail::result_of::target<Target>::type;
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/new_eval.hpp>
    };

    template <typename Dummy>
    struct default_actions::when<rule::new_, Dummy>
        : call<new_eval, Dummy>
    {};

    template <typename T>
    typename expression::new_<detail::target<T> >::type const
    new_()
    {
        return
            expression::
                new_<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/new.hpp>
}}

#endif


/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP
#define BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(reinterpret_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    
    struct reinterpret_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context, typename Target, typename Source>
        struct result<This(Context, Target const &, Source const&)>
            : detail::result_of::target<Target>
        {
        };

        template <typename Context, typename Target, typename Source>
        typename detail::result_of::target<Target>::type
        operator()(Context const& ctx, Target, Source const& u) const
        {
            return
                reinterpret_cast<
                    typename detail::result_of::target<Target>::type
                >(eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::reinterpret_cast_, Dummy>
        : call<reinterpret_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    typename expression::reinterpret_cast_<detail::target<T>, U>::type const
    reinterpret_cast_(U const& u)
    {
        return
            expression::
                reinterpret_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
    
    template <typename T, typename U>
    typename expression::reinterpret_cast_<detail::target<T>, U>::type const
    reinterpret_cast_(U & u)
    {
        return
            expression::
                reinterpret_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }

}}

#endif

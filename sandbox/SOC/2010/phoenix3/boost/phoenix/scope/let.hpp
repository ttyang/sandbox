/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_SCOPE_LET_HPP
#define PHOENIX_SCOPE_LET_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost { namespace phoenix
{
    PHOENIX_DEFINE_EXPRESSION(
        let
      , (rule::local_var_def_list)
        (meta_grammar)
    )

    struct let_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Context, typename Locals, typename Let>
        struct result<This(Context, Locals &, Let &)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::actions<Context>::type
                >::type
                actions_type;

            typedef
                typename proto::detail::uncvref<
                    typename boost::result_of<
                        rule::local_var_def_list(
                            Locals const &
                          , Context
                        )
                    >::type
                >::type
                locals_type;

            typedef
                typename evaluator::impl<
                    Let const &
                  , typename result_of::context<
                        scoped_environment<
                            typename result_of::env<Context>::type
                          , typename result_of::env<Context>::type
                          , locals_type
                        >
                      , actions_type
                    >::type
                  , int
                >::result_type
                type;
        };

        template <typename Context, typename Locals, typename Let>
        typename result<let_eval(Context&, Locals const &, Let const &)>::type
        operator()(Context & ctx, Locals const & locals, Let const & let) const
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;

            typedef
                typename proto::detail::uncvref<
                    typename result_of::actions<Context>::type
                >::type
                actions_type;

            typedef
                typename proto::detail::uncvref<
                    typename boost::result_of<
                        rule::local_var_def_list(
                            Locals &
                          , Context &
                        )
                    >::type
                >::type
                locals_type;
            
            typedef scoped_environment<env_type, env_type, locals_type> scoped_env_type;

            locals_type l = 
                   rule::local_var_def_list()(
                      locals
                    , ctx
                    );


            scoped_env_type
                scoped_env(
                    env(ctx)
                  , env(ctx)
                  , l
                );

            typename result_of::context<
                scoped_env_type &
              , actions_type
            >::type new_ctx(scoped_env, actions(ctx));

            return eval(let, new_ctx);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::let, Dummy>
        : proto::call<let_eval(_context, proto::_child_c<0>, proto::_child_c<1>)>
    {};

    template <typename Locals = void, typename Dummy = void>
    struct let_actor_gen;

    template <>
    struct let_actor_gen<void, void>
    {
        template <typename Expr>
        Expr const &
        operator[](Expr const & expr) const
        {
            return expr;
        }
    };

    template <typename Locals>
    struct let_actor_gen<Locals>
    {
        let_actor_gen(Locals const & locals)
            : locals(locals)
        {}

        template <typename Expr>
        typename expression::let<
            Locals
          , Expr
        >::type const
        operator[](Expr const & expr) const
        {
            return expression::let<Locals, Expr>::make(locals, expr);
        }

        Locals locals;
    };


    struct let_local_gen
    {
        let_actor_gen<> const
        operator()() const
        {
            return let_actor_gen<>();
        }

        template <typename Expr0>
        let_actor_gen<Expr0> const
        operator()(Expr0 const& expr0) const
        {
            return expr0;
        }

        #include <boost/phoenix/scope/detail/let_local_gen.hpp>
    };

    let_local_gen const let = {};
    
    template <typename Dummy>
    struct is_nullary::when<rule::let, Dummy>
        : proto::make<
            mpl::and_<
                detail::local_var_def_is_nullary(proto::_child_c<0>, _context, int())
              , evaluator(
                    proto::_child_c<1>
                  , fusion::vector2<
                        mpl::true_
                      , detail::scope_is_nullary_actions
                    >()
                  , int()
                )
            >()
        >
    {};

}}

#endif

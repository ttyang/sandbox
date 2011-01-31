/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_CORE_ACTOR_HPP
#define PHOENIX_CORE_ACTOR_HPP

#include <boost/phoenix/core/limits.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/proto/extends.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/void.hpp>
#include <cstring>

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct actor;

    namespace detail
    {
        struct error_expecting_arguments
        {
            template <typename T>
            error_expecting_arguments(T const&) {}
        };
        
        struct error_invalid_lambda_expr
        {
            template <typename T>
            error_invalid_lambda_expr(T const&) {}
        };

        struct do_assign
        {
            BOOST_PROTO_CALLABLE()

            typedef void result_type;

            template <typename T1, typename T2>
            void operator()(T1 & t1, T2 const & t2) const
            {
                proto::value(t1) = proto::value(t2);
            }
        };


    #define PHOENIX_ACTOR_ASSIGN_CHILD(Z, N, D)                                 \
        assign(proto::_child_c<N>, proto::_child_c<N>(proto::_state))           \
    /**/
    #define PHOENIX_ACTOR_ASSIGN_CALL(Z, N, D)                                  \
            proto::when<                                                        \
                proto::nary_expr<proto::_ ,                                     \
                  BOOST_PP_ENUM_PARAMS(N, proto::_ BOOST_PP_INTERCEPT)          \
                >                                                               \
               , proto::and_<                                                   \
                  BOOST_PP_ENUM(                                                \
                        N                                                       \
                      , PHOENIX_ACTOR_ASSIGN_CHILD                              \
                      , _                                                       \
                    )                                                           \
                >                                                               \
            >                                                                   \
      /**/

        struct assign
            : proto::or_<
                BOOST_PP_ENUM_SHIFTED(
                    PHOENIX_LIMIT
                  , PHOENIX_ACTOR_ASSIGN_CALL
                  , _
                )
              , proto::when<
                    proto::terminal<proto::_>
                  , do_assign(proto::_, proto::_state)
                >
            >
        {};
    #undef PHOENIX_ACTOR_ASSIGN_CALL
    #undef PHOENIX_ACTOR_ASSIGN_CHILD
    }

    // Bring in the result_of::actor<>
    #include <boost/phoenix/core/detail/actor_result_of.hpp>

    ////////////////////////////////////////////////////////////////////////////
    //
    //  actor
    //
    //      The actor class. The main thing! In phoenix, everything is an actor
    //      This class is responsible for full function evaluation. Partial
    //      function evaluation involves creating a hierarchy of actor objects.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct actor
    {
        BOOST_PROTO_BASIC_EXTENDS(Expr, actor<Expr>, phoenix_domain)

        // providing operator= to be assignable
        actor& operator=(actor const& other)
        {
            detail::assign()(*this, other);
            return *this;
        }
        actor& operator=(actor & other)
        {
            detail::assign()(*this, other);
            return *this;
        }
        BOOST_PROTO_EXTENDS_ASSIGN_()
        BOOST_PROTO_EXTENDS_SUBSCRIPT()

        template <typename Sig>
        struct result;

        typename result_of::actor<Expr>::type
        operator()()
        {
            typedef fusion::vector1<const actor<Expr> *> args_type;
            args_type args(this);
            fusion::vector2<args_type&, default_actions> env(args, default_actions());
            
            return eval(*this, env);
        }

        typename result_of::actor<Expr>::type
        operator()() const
        {
            typedef fusion::vector1<const actor<Expr> *> args_type;
            args_type args(this);
            fusion::vector2<args_type&, default_actions> env(args, default_actions());

            return eval(*this, env);
        }
        
        // Bring in the rest
        #include <boost/phoenix/core/detail/actor_operator.hpp>
    };

}}

namespace boost
{
    // specialize boost::result_of to return the proper result type
    template <typename Expr>
    struct result_of<phoenix::actor<Expr>()>
        : phoenix::result_of::actor<Expr>
    {};
    
    template <typename Expr>
    struct result_of<phoenix::actor<Expr> const()>
        : result_of<phoenix::actor<Expr>()>
    {};
}

#endif


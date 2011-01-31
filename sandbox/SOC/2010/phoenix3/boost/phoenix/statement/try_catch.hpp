/*==============================================================================
    Copyright (c) 2005-2007 Dan Marsden
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_STATEMENT_TRY_CATCH_HPP
#define PHOENIX_STATEMENT_TRY_CATCH_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/functional/fusion/pop_front.hpp>

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct try_catch_actor;

    template <typename Exception>
    struct catch_exception
    {
        typedef Exception type;
    };

    namespace tag
    {
        struct try_catch {};
        struct catch_ {};
        struct catch_all {};
    }

    namespace expression
    {
        template <
            typename Try
          , PHOENIX_typename_A_void(PHOENIX_CATCH_LIMIT)
          , typename Dummy = void
        >
        struct try_catch;

        // bring in the expression definitions
        #include <boost/phoenix/statement/detail/try_catch_expression.hpp>

        template <typename A0, typename A1>
        struct catch_
            : proto::binary_expr<tag::catch_, A0, A1>
        {};
        
        template <typename A0>
        struct catch_all
            : proto::unary_expr<tag::catch_all, A0>
        {};
    }

    namespace rule
    {
        struct catch_
            : expression::catch_<
                proto::terminal<catch_exception<proto::_> >
              , meta_grammar
            >
        {};
        
        struct catch_all
            : expression::catch_all<
                meta_grammar
            >
        {};

        struct try_catch
            : proto::or_<
                expression::try_catch<
                     meta_grammar
                   , proto::vararg<rule::catch_>
                >
              , expression::try_catch<
                     meta_grammar
                   , rule::catch_all
                >
              , expression::try_catch<
                     meta_grammar
                   , proto::vararg<rule::catch_>
                   , rule::catch_all
                >
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<tag::try_catch, Dummy>
        : proto::when<rule::try_catch, proto::external_transform>
    {};

    struct try_catch_eval
    {
        BOOST_PROTO_CALLABLE()

        typedef void result_type;

        // bring in the operator overloads
        #include <boost/phoenix/statement/detail/try_catch_eval.hpp>
    };

#define PHOENIX_TRY_CATCH_CHILD(Z, N, D) proto::_child_c<N>
#define PHOENIX_TRY_CATCH_CALL(Z, N, D)                                         \
            proto::when<                                                        \
                expression::try_catch<                                          \
                  BOOST_PP_ENUM_PARAMS(N, proto::_ BOOST_PP_INTERCEPT)          \
                >                                                               \
               , try_catch_eval(                                                \
                    _context                                                        \
                  , BOOST_PP_ENUM(                                              \
                        N                                                       \
                      , PHOENIX_TRY_CATCH_CHILD                                 \
                      , _                                                       \
                    )                                                           \
                )                                                               \
            >                                                                   \
        /**/

    template <typename Dummy>
    struct default_actions::when<rule::try_catch, Dummy>
        : proto::or_<
            BOOST_PP_ENUM_SHIFTED(
                BOOST_PP_INC(PHOENIX_CATCH_LIMIT)
              , PHOENIX_TRY_CATCH_CALL
              , _
            )
        >   
    {};

#undef PHOENIX_TRY_CATCH_CHILD
#undef PHOENIX_TRY_CATCH_CALL

    namespace detail
    {
        struct try_catch_is_nullary
            : proto::or_<
                proto::when<
                    rule::catch_all
                  , evaluator(proto::_child_c<0>, proto::_data, int())
                >
              , proto::when<
                    rule::catch_
                  , evaluator(proto::_child_c<1>, proto::_data, int())
                >
              , proto::when<
                    rule::try_catch
                  , mpl::and_<
                        evaluator(proto::_child_c<0>, proto::_data, int())
                      , proto::fold<
                            proto::functional::pop_front(proto::_)
                          , mpl::true_()
                          , mpl::and_<
                                proto::_state
                              , try_catch_is_nullary(
                                    proto::_
                                  , int()
                                  , proto::_data
                                )
                            >()
                        >
                    >()
                >
            >
        {};

        template <
            typename TryCatch
          , typename Exception
          , typename Expr
          , long Arity = proto::arity_of<TryCatch>::value
        >
        struct catch_push_back;

        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, Expr, 1>
        {
            typedef
                typename proto::result_of::make_expr<
                    tag::catch_
                  , default_domain_with_basic_expr
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            
            typedef
                expression::try_catch<
                    TryCatch
                  , catch_expr
                >
                gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const & try_catch, Expr const & catch_)
            {
                return
                    gen_type::make(
                        try_catch
                      , proto::make_expr<
                            tag::catch_
                          , default_domain_with_basic_expr
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        
        template <
            typename TryCatch
          , typename Expr
          , long Arity = proto::arity_of<TryCatch>::value
        >
        struct catch_all_push_back;

        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 1>
        {
            typedef
                typename proto::result_of::make_expr<
                    tag::catch_all
                  , default_domain_with_basic_expr
                  , Expr
                >::type
                catch_expr;
            
            typedef
                expression::try_catch<
                    TryCatch
                  , catch_expr
                >
                gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const& try_catch, Expr const& catch_)
            {
                return
                    gen_type::make(
                        try_catch
                      , proto::make_expr<
                            tag::catch_all
                          , default_domain_with_basic_expr
                        >(catch_)
                    );
            }
        };
        #include <boost/phoenix/statement/detail/catch_push_back.hpp>
    }

    template <typename Dummy>
    struct is_nullary::when<rule::try_catch, Dummy>
        : proto::call<detail::try_catch_is_nullary(proto::_, int(), _context)>
    {};

    template <typename TryCatch, typename Exception>
    struct catch_gen
    {
        catch_gen(TryCatch const& try_catch) : try_catch(try_catch) {}

        template <typename Expr>
        typename boost::disable_if<
            proto::matches<
                typename proto::result_of::child_c<
                    TryCatch
                  , proto::arity_of<TryCatch>::value - 1
                >::type
              , rule::catch_all
            >
          , typename detail::catch_push_back<TryCatch, Exception, Expr>::type
        >::type
        operator[](Expr const& expr) const
        {
            return
                detail::catch_push_back<TryCatch, Exception, Expr>::make(
                    try_catch, expr
                );
        }

        TryCatch const & try_catch;
    };

    template <typename TryCatch>
    struct catch_all_gen
    {
        catch_all_gen(TryCatch const& try_catch) : try_catch(try_catch) {}

        template <typename Expr>
        typename boost::disable_if<
            proto::matches<
                typename proto::result_of::child_c<
                    TryCatch
                  , proto::arity_of<TryCatch>::value - 1
                >::type
              , rule::catch_all
            >
          , typename detail::catch_all_push_back<TryCatch, Expr>::type
        >::type
        operator[](Expr const& expr) const
        {
            return detail::catch_all_push_back<TryCatch, Expr>::make(
                try_catch, expr
            );
        }

        TryCatch const & try_catch;
    };

    template <
        typename Expr
    >
    struct try_catch_actor;

    template <typename Expr>
    struct try_catch_actor
        : actor<Expr>
    {
        typedef try_catch_actor<Expr> that_type;
        typedef actor<Expr> base_type;

        try_catch_actor(base_type const& expr)
            : base_type(expr)
            , catch_all(*this)
        {
        }

        template <typename Exception>
        catch_gen<that_type, Exception> const
        catch_() const
        {
            return catch_gen<that_type, Exception>(*this);
        }

        catch_all_gen<that_type> const catch_all;
    };

    struct try_gen
    {
        template <typename Try>
        typename expression::try_catch<Try>::type const
        operator[](Try const & try_) const
        {
            return expression::try_catch<Try>::make(try_);
        }
    };

    try_gen const try_ = {};
}}

#endif

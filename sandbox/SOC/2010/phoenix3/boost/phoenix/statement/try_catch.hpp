/*==============================================================================
    Copyright (c) 2005-2007 Dan Marsden
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !PHOENIX_IS_ITERATING

#ifndef PHOENIX_STATEMENT_TRY_CATCH_HPP
#define PHOENIX_STATEMENT_TRY_CATCH_HPP

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct try_catch_actor;

    template <typename>
    struct catch_exception {};

    PHOENIX_DEFINE_EXPRESSION_EXT(
        try_catch_actor
      , try_
      , (meta_grammar)
    )
    
    PHOENIX_DEFINE_EXPRESSION(
        catch_
      , (proto::terminal<catch_exception<proto::_> >)
        (meta_grammar)
    )
    
    /*
    PHOENIX_DEFINE_EXPRESSION(
        catch_all
      , (proto::terminal<catch_exception<mpl::na> >)
    )

    namespace tag
    {
        struct try_catch;
    }

    namespace detail
    {
        struct try_catch_grammar
            : proto::nary_expr<
              , tag::try_catch
              , rule::try_
              , proto::vararg<rule::catch_>
              , proto::or_<
                    rule::catch_
                  , rule::catch_all
                >
            >
        {};
    }
    */
    
    PHOENIX_DEFINE_EXPRESSION_EXT_VARARG(
        try_catch_actor
      , try_catch
      , (proto::_)
      , PHOENIX_CATCH_LIMIT
    )

    template <typename TryCatch>
    struct catch_all_gen
    {
        template <typename Expr>
        void
        operator[](Expr const & expr)
        {
        }
    };

    namespace detail
    {
        template <typename TryCatch, typename Exception, typename Expr, long Arity = proto::arity_of<TryCatch>::value>
        struct catch_push_back;

        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, Expr, 1>
        {
            typedef expression::catch_<catch_exception<Exception>, Expr> catch_expr;
            
            typedef expression::try_catch<
                TryCatch//typename proto::result_of::child_c<TryCatch, 0>::type
              , typename catch_expr::type> gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const& try_catch, Expr const& catch_)
            {
                std::cout << typeid(TryCatch).name() << "\n\n";
                std::cout << typeid(type).name() << "\n\n";
                return
                    gen_type::make(
                        try_catch//proto::child_c<0>(try_catch)
                      , catch_expr::make(catch_exception<Exception>(), catch_)
                    );
            }
        };

        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, Expr, 2>
        {
            typedef expression::catch_<catch_exception<Exception>, Expr> catch_expr;

            typedef expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type
              , typename proto::result_of::child_c<TryCatch, 1>::type
              , typename catch_expr::type> gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const& try_catch, Expr const& catch_)
            {
                std::cout << typeid(TryCatch).name() << "\n\n";
                std::cout << typeid(type).name() << "\n";
                return
                    gen_type::make(
                        proto::child_c<0>(try_catch)
                      , proto::child_c<1>(try_catch)
                      , catch_expr::make(catch_exception<Exception>(), catch_)
                    );
            }
        };
        
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, Expr, 3>
        {
            typedef expression::catch_<catch_exception<Exception>, Expr> catch_expr;

            typedef expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type
              , typename proto::result_of::child_c<TryCatch, 1>::type
              , typename proto::result_of::child_c<TryCatch, 2>::type
              , typename catch_expr::type> gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const& try_catch, Expr const& catch_)
            {
                return
                    gen_type::make(
                        proto::child_c<0>(try_catch)
                      , proto::child_c<1>(try_catch)
                      , proto::child_c<2>(try_catch)
                      , catch_expr::make(catch_exception<Exception>(), catch_)
                    );
            }
        };
    }

    template <typename TryCatch, typename Exception>
    struct catch_gen
    {
        catch_gen(TryCatch const& try_catch) : try_catch(try_catch) {}

        template <typename Expr>
        typename detail::catch_push_back<TryCatch, Exception, Expr>::type
        operator[](Expr const& expr) const
        {
            return detail::catch_push_back<TryCatch, Exception, Expr>::make(try_catch, expr);
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

        try_catch_actor(base_type const& expr) : base_type(expr) {};

        template <typename Exception>
        catch_gen<that_type, Exception> const
        catch_() const
        {
            return catch_gen<that_type, Exception>(*this);
        }

        catch_all_gen<that_type> catch_all;
    };

    struct try_gen
    {
        template <typename Try>
        typename expression::try_<Try>::type const
        operator[](Try const & try_) const
        {
            return expression::try_<Try>::make(try_);
        }
    };

    try_gen const try_ = {};
    /*
    namespace result_of
    {
        template <typename Env, PHOENIX_typename_A_void(PHOENIX_CATCH_LIMIT)>
        struct try_catch
        {
            typedef void type;
        };
    }

    template <PHOENIX_typename_A_void(PHOENIX_CATCH_LIMIT),
        typename Dummy = void>
    struct try_catch_eval;

    template <PHOENIX_typename_A_void(PHOENIX_CATCH_LIMIT),
        typename Dummy = void>
    struct try_catch_all_eval;

    template<>
    struct try_catch_all_eval<>
    {
        typedef void result_type;

        template <typename Env, typename Try, typename CatchAll>
        result_type
        operator()(
            Env& env, Try const& try_block, CatchAll const& catch_all) const
        {
            try
            {
                eval(try_block, env);
            }
            catch(...)
            {
                eval(catch_all, env);
            }
        }
    };

#define CATCH_EXCEPTION(_, n, __)                                               \
    BOOST_PP_COMMA_IF(n)                                                        \
    typename CatchBlock ## n = void, typename Exception ## n = void

    template <
        typename Try
      , BOOST_PP_REPEAT(PHOENIX_CATCH_LIMIT, CATCH_EXCEPTION, _)
      , typename Dummy = void>
    struct make_try_catch;
    
    template <
        typename Try
      , BOOST_PP_REPEAT(PHOENIX_CATCH_LIMIT, CATCH_EXCEPTION, _)
      , typename CatchAll = void
      , typename Dummy = void>
    struct make_try_catch_all;

    template <
        typename Exception
      , typename Try
      , BOOST_PP_REPEAT(BOOST_PP_DEC(PHOENIX_CATCH_LIMIT), CATCH_EXCEPTION, _)
      , typename Dummy = void>
    struct catch_gen;

    template <
        typename Try
      , BOOST_PP_REPEAT(PHOENIX_CATCH_LIMIT, CATCH_EXCEPTION, _)
      , typename Dummy = void>
    struct catch_all_gen;

#undef CATCH_EXCEPTION

    template<typename Expr>
    struct try_catch_actor0;

    template <typename Try>
    struct make_try_catch<Try>
        : compose_ex<try_catch_eval<>, try_catch_actor0, Try> {};

    template <typename Try, typename CatchAll>
    struct make_try_catch_all<Try, CatchAll>
        : compose<try_catch_all_eval<>, Try, CatchAll> {};

    template <typename Exception, typename Try>
    struct catch_gen<Exception, Try>
    {
        catch_gen(Try const& try_block) : try_block(try_block) {}

        template <typename CatchBlock>
        typename make_try_catch<Try, CatchBlock, Exception>::type const
        operator[](CatchBlock const& catch_block) const
        {
            return make_try_catch<
                Try, CatchBlock, Exception>()(try_block, catch_block);
        };

        Try const& try_block;
    };

    template <typename Try>
    struct catch_all_gen<Try>
    {
        catch_all_gen(Try const& try_block) : try_block(try_block) {}

        template <typename CatchAll>
        typename make_try_catch_all<Try, CatchAll>::type const
        operator[](CatchAll const& catch_all) const
        {
            return make_try_catch_all<Try, CatchAll>()(try_block, catch_all);
        }
        
        Try const& try_block;
    };

#define PHOENIX_ITERATION_PARAMS                                                \
        (3, (1, PHOENIX_CATCH_LIMIT,                                            \
        <boost/phoenix/statement/try_catch.hpp>))
#include PHOENIX_ITERATE()

    template <typename Expr>
    struct try_catch_actor0
        : actor<Expr>
    {
        typedef actor<Expr> base_type;

        try_catch_actor0(base_type const& base)
            : base_type(base)
            , catch_all(element_at_c<0>(*this))
        {}
        
        typedef typename result_of::element_value_at_c<Expr, 0>::type try_type;

        template <typename Exception>
        catch_gen<Exception, try_type> const
        catch_() const
        {
            return catch_gen<Exception, try_type>(element_at_c<0>(*this));
        }

        const catch_all_gen<try_type> catch_all;
    };

    template <typename Expr>
    struct BOOST_PP_CAT(try_catch_actor, BOOST_PP_INC(PHOENIX_CATCH_LIMIT))
    {
        typedef actor<Expr> base_type;

        BOOST_PP_CAT(try_catch_actor, BOOST_PP_INC(PHOENIX_CATCH_LIMIT))(
            base_type const& base)
            : base_type(base)
            , catch_all(element_at_c<0>(*this))
        {}
        
        typedef typename result_of::element_value_at_c<Expr, 0>::type try_type;

        const catch_all_gen<try_type> catch_all;
    };

    struct try_gen
    {
        template <typename Try>
        typename make_try_catch<Try>::type const
        operator[](Try const& try_block) const
        {
            return make_try_catch<Try>()(try_block);
        }
    };

    try_gen const try_ = try_gen();
*/

}}

#endif

#else

#define PHOENIX_typename_Exception                                              \
    BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, typename Exception)
#define PHOENIX_Exception                                                       \
    BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, Exception)
#define PHOENIX_Exception_ref                                                   \
    BOOST_PP_ENUM_BINARY_PARAMS(                                                \
        PHOENIX_ITERATION, Exception, & BOOST_PP_INTERCEPT)

#define INIT_a(_,n,__) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(a,n)(BOOST_PP_CAT(a,n))
#define CATCH_BLOCK(_, n, __) A ## n const& a ## n;

    template <typename Exception, typename Try, PHOENIX_typename_A>
    struct catch_gen<Exception, Try, PHOENIX_A>
    {
        catch_gen(Try const& try_block, PHOENIX_A_const_ref_a)
            : try_block(try_block)
            , BOOST_PP_REPEAT(PHOENIX_ITERATION, INIT_a, _)
        {}

        template <typename CatchBlock>
        typename make_try_catch<
            Try, PHOENIX_A, CatchBlock, Exception>::type const
        operator[](CatchBlock const& catch_block) const
        {
            return make_try_catch<
                Try, PHOENIX_A, CatchBlock, Exception>()(
                    try_block, PHOENIX_a, catch_block);
        };

        Try const& try_block;
        BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH_BLOCK, _)
    };

    template <typename Try, PHOENIX_typename_A>
    struct catch_all_gen<Try, PHOENIX_A>
    {
        catch_all_gen(Try const& try_block, PHOENIX_A_const_ref_a)
            : try_block(try_block)
            , BOOST_PP_REPEAT(PHOENIX_ITERATION, INIT_a, _)
        {}

        template <typename CatchAll>
        typename make_try_catch_all<Try, PHOENIX_A, CatchAll>::type const
        operator[](CatchAll const& catch_all) const
        {
            return make_try_catch_all<
                Try, PHOENIX_A, CatchAll>()(try_block, PHOENIX_a, catch_all);
        }
        
        Try const& try_block;
        BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH_BLOCK, _)
    };
#undef CATCH_BLOCK
#undef INIT_a

#define CATCH(_, n, __)                                                         \
            catch(Exception ## n &)                                             \
            {                                                                   \
                eval(a ## n, env);                                              \
            }

    template <PHOENIX_typename_Exception>
    struct try_catch_eval<PHOENIX_Exception>
    {
        typedef void result_type;

        template <typename Env, typename Try, PHOENIX_typename_A>
        result_type
        operator()(Env& env, Try const& try_, PHOENIX_A_const_ref_a) const
        {
            try
            {
                eval(try_, env);
            }
            BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH, _)
        }
    };

    template <PHOENIX_typename_Exception>
    struct try_catch_all_eval<PHOENIX_Exception>
    {
        typedef void result_type;

        template <typename Env, typename Try, PHOENIX_typename_A, typename CatchAll>
        result_type
        operator()(
            Env& env,
            Try const& try_,
            PHOENIX_A_const_ref_a,
            CatchAll const& catch_all) const
        {
            try
            {
                eval(try_, env);
            }
            BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH, _)
            catch(...)
            {
                eval(catch_all, env);
            }
        }
    };

#undef CATCH

    template <typename Expr>
    struct BOOST_PP_CAT(try_catch_actor, PHOENIX_ITERATION);

#define CATCH_EXCEPTION_typename(_, n, __)                                      \
    BOOST_PP_COMMA_IF(n) typename CatchBlock ## n, typename Exception ## n

#define CATCH_EXCEPTION(_, n, __)                                               \
    BOOST_PP_COMMA_IF(n) CatchBlock ## n, Exception ## n

    template <typename Try,
        BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH_EXCEPTION_typename, _)>
    struct make_try_catch<Try,
        BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH_EXCEPTION, _)>
        : compose_ex<
            try_catch_eval<BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, Exception)>
          , BOOST_PP_CAT(try_catch_actor, PHOENIX_ITERATION)
          , Try
          , BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, CatchBlock)
          > {};

    template <typename Try,
        BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH_EXCEPTION_typename, _),
        typename CatchAll>
    struct make_try_catch_all<Try,
        BOOST_PP_REPEAT(PHOENIX_ITERATION, CATCH_EXCEPTION, _), CatchAll>
        : compose_ex<
            try_catch_eval<BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, Exception)>
          , BOOST_PP_CAT(try_catch_actor, PHOENIX_ITERATION)
          , Try
          , BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, CatchBlock)
          , CatchAll
          > {};

    template <typename Expr>
    struct BOOST_PP_CAT(try_catch_actor, PHOENIX_ITERATION)
        : actor<Expr>
    {
        typedef actor<Expr> base_type;

        BOOST_PP_CAT(try_catch_actor, PHOENIX_ITERATION)(base_type const& base)
            : base_type(base)
            , catch_all(element_at_c<0>(*this))
        {}

#undef CATCH_EXCEPTION
#undef CATCH_EXCEPTION_typename
        
#define TRY_CATCH_BLOCK_TYPES(_, n, __)                                         \
        typedef typename                                                        \
            result_of::element_value_at_c<Expr, n>::type try_catch_type ## n;
        BOOST_PP_REPEAT(PHOENIX_ITERATION, TRY_CATCH_BLOCK_TYPES, _)
#undef TRY_CATCH_BLOCK_TYPES


        template <typename Exception>
        catch_gen<Exception,
            BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, try_catch_type)> const
        catch_() const
        {
#define ELEMENT_AT_C(_,n,__) BOOST_PP_COMMA_IF(n) element_at_c<  n >(*this)

            return catch_gen<
                Exception
              , BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, try_catch_type)
            >(BOOST_PP_REPEAT(PHOENIX_ITERATION, ELEMENT_AT_C, _));
#undef ELEMENT_AT_C
        }

        const catch_all_gen<
            BOOST_PP_ENUM_PARAMS(PHOENIX_ITERATION, try_catch_type)> catch_all;
    };

#undef PHOENIX_typename_Exception
#undef PHOENIX_Exception
#undef PHOENIX_Exception_ref

#endif

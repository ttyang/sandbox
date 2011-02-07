/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
namespace boost { namespace phoenix { namespace tag { struct mem_fun_ptr {}; } namespace expression { template < typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename Dummy = void > struct mem_fun_ptr; template < typename A0 > struct mem_fun_ptr< A0 > : expr< tag:: mem_fun_ptr , A0 > {}; template < typename A0 , typename A1 > struct mem_fun_ptr< A0 , A1 > : expr< tag:: mem_fun_ptr , A0 , A1 > {}; template < typename A0 , typename A1 , typename A2 > struct mem_fun_ptr< A0 , A1 , A2 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 > {}; template < typename A0 , typename A1 , typename A2 , typename A3 > struct mem_fun_ptr< A0 , A1 , A2 , A3 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 , A3 > {}; template < typename A0 , typename A1 , typename A2 , typename A3 , typename A4 > struct mem_fun_ptr< A0 , A1 , A2 , A3 , A4 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 , A3 , A4 > {}; template < typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 > struct mem_fun_ptr< A0 , A1 , A2 , A3 , A4 , A5 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 , A3 , A4 , A5 > {}; template < typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 > struct mem_fun_ptr< A0 , A1 , A2 , A3 , A4 , A5 , A6 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 , A3 , A4 , A5 , A6 > {}; template < typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 > struct mem_fun_ptr< A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 > {}; template < typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 > struct mem_fun_ptr< A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 > : expr< tag:: mem_fun_ptr , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 > {}; } namespace rule { struct mem_fun_ptr : expression:: mem_fun_ptr < proto::vararg< meta_grammar > > {}; } } } namespace boost { namespace phoenix { template <typename Dummy> struct meta_grammar::case_< boost :: phoenix :: tag:: mem_fun_ptr , Dummy > : enable_rule< boost :: phoenix :: rule:: mem_fun_ptr > {}; } }
namespace boost { namespace phoenix
{
    namespace rule { struct mem_ptr : proto::binary_expr<proto::tag::mem_ptr, proto::_, proto::_> {}; } template <typename Dummy> struct meta_grammar::case_<proto::tag::mem_ptr, Dummy> : enable_rule<rule::mem_ptr> {};
    template <typename Object, typename MemPtr>
    typename enable_if<
        is_member_function_pointer<MemPtr>
      , detail::mem_fun_ptr_gen<actor<Object>, MemPtr> const
      >::type
    operator->*(actor<Object> const& obj, MemPtr ptr)
    {
        return detail::mem_fun_ptr_gen<actor<Object>, MemPtr>(obj, ptr);
    }
    namespace result_of
    {
        template <
            typename Context
          , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void
          , typename Dummy = void
        >
        struct mem_fun_ptr_eval;
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1>
        struct mem_fun_ptr_eval<Context, A0 , A1>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1;
            typedef
                typename boost::result_of<
                    child1(
                        child1
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3; typedef typename evaluator::impl< A4 , Context , int >::result_type child4;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3; typedef typename evaluator::impl< A4 , Context , int >::result_type child4; typedef typename evaluator::impl< A5 , Context , int >::result_type child5;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3; typedef typename evaluator::impl< A4 , Context , int >::result_type child4; typedef typename evaluator::impl< A5 , Context , int >::result_type child5; typedef typename evaluator::impl< A6 , Context , int >::result_type child6;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3; typedef typename evaluator::impl< A4 , Context , int >::result_type child4; typedef typename evaluator::impl< A5 , Context , int >::result_type child5; typedef typename evaluator::impl< A6 , Context , int >::result_type child6; typedef typename evaluator::impl< A7 , Context , int >::result_type child7;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3; typedef typename evaluator::impl< A4 , Context , int >::result_type child4; typedef typename evaluator::impl< A5 , Context , int >::result_type child5; typedef typename evaluator::impl< A6 , Context , int >::result_type child6; typedef typename evaluator::impl< A7 , Context , int >::result_type child7; typedef typename evaluator::impl< A8 , Context , int >::result_type child8;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
        {
            typedef typename evaluator::impl< A0 , Context , int >::result_type child0; typedef typename evaluator::impl< A1 , Context , int >::result_type child1; typedef typename evaluator::impl< A2 , Context , int >::result_type child2; typedef typename evaluator::impl< A3 , Context , int >::result_type child3; typedef typename evaluator::impl< A4 , Context , int >::result_type child4; typedef typename evaluator::impl< A5 , Context , int >::result_type child5; typedef typename evaluator::impl< A6 , Context , int >::result_type child6; typedef typename evaluator::impl< A7 , Context , int >::result_type child7; typedef typename evaluator::impl< A8 , Context , int >::result_type child8; typedef typename evaluator::impl< A9 , Context , int >::result_type child9;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9
                    )
                >::type
                type;
        };
    }
    struct mem_fun_ptr_eval
        : proto::callable
    {
        template<typename Sig>
        struct result;
        
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1>
        struct result<This(Context, A0 , A1)>
            : result<This(Context, A0 const& , A1 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1>
        struct result<This(Context, A0 & , A1 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1>
        {};
        template <typename Context, typename A0 , typename A1>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2>
        struct result<This(Context, A0 , A1 , A2)>
            : result<This(Context, A0 const& , A1 const& , A2 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2>
        struct result<This(Context, A0 & , A1 & , A2 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(Context, A0 , A1 , A2 , A3)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 & , A4 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 & , A4 & , A5 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx)
                );
        }
        
    
    
    
    
    
    
    
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
            : result<This(Context, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&)>
        {};
        template <typename This, typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(Context, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &)>
            : result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
        {};
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename result_of::mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type
        operator()(
            Context const & ctx, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    eval(a2, ctx) , eval(a3, ctx) , eval(a4, ctx) , eval(a5, ctx) , eval(a6, ctx) , eval(a7, ctx) , eval(a8, ctx) , eval(a9, ctx)
                );
        }
        
    };
    template <typename Dummy>
    struct default_actions::when<rule::mem_fun_ptr, Dummy>
    
        : call<mem_fun_ptr_eval>
    {};
}}

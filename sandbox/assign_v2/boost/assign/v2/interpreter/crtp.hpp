//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_INTERPRETER_CRTP_ER_2010_HPP
#define BOOST_ASSIGN_V2_INTERPRETER_CRTP_ER_2010_HPP
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#include <boost/assign/v2/detail/pp/forward.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#include <boost/assign/v2/detail/traits/container.hpp>
#include <boost/assign/v2/interpreter/as_arg_list.hpp>
#include <boost/assign/v2/interpreter/fwd.hpp>
#include <boost/assign/v2/interpreter/modifier.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/ref.hpp>
#include <boost/utility/enable_if.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#else
#include <boost/assign/v2/detail/config/limit_arity.hpp>
#include <boost/assign/v2/detail/config/limit_csv_arity.hpp>
#include <boost/assign/v2/detail/functor/crtp_unary_and_up.hpp>
#include <boost/preprocessor/arithmetic.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition.hpp>
#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X

namespace boost{
namespace assign{
namespace v2{
namespace interpreter_aux{

    template<typename F>
    struct data_gen_holder{

        typedef F fun_type;

        data_gen_holder(){}
        data_gen_holder(fun_type const& f) : fun( f ){}

        fun_type fun;

    };

    template<typename Tag>
    struct modifier_holder{

        typedef Tag modifier_tag;
        typedef interpreter_aux::interpreter_modifier<Tag> modifier_type;

        modifier_holder(){}
        modifier_holder(modifier_type const& m) : modifier( m ){}

        modifier_type modifier;

    };

    template<typename D>
    struct wrapper
    {

        wrapper(D const& d):d_( d ){}

        operator D const&()const{ return this->d_; }

        typedef wrapper const& result_type;

#if BOOST_ASSIGN_V2_ENABLE_CPP0X
        template<typename T>
        result_type operator()( T&& t )const
        {
            this->d_( std::forward<T>(t) ); return (*this);
        }
#else

        template<typename T>
        result_type operator()(T& t)const
        {
            this->d_( t ); return (*this);
        }

        template<typename T>
        result_type operator()(T const & t)const
        {
            this->d_( t ); return (*this);
        }
#endif

        private:
        D const& d_;

    };
}// interpreter_aux
//[syntax_interpreter_crtp
namespace interpreter_aux{

    template<typename C, typename D>
    struct ConceptDerivedInterpreter1{

        BOOST_CONCEPT_USAGE(ConceptDerivedInterpreter1)
        {
            D derived( cont );
            C& ref = derived.container();
        }

        private:
        static C& cont;

    };

    template<typename C, typename F, typename MTag, typename D>
    struct ConceptDerivedInterpreter2 : ConceptDerivedInterpreter1<C, D>{

        typedef interpreter_aux::interpreter_modifier<MTag> modifier_;

        BOOST_CONCEPT_USAGE(ConceptDerivedInterpreter2)
        {
            D derived( cont, f, m );
        }

        private:
        static C& cont;
        static F const &f;
        static modifier_ m;

    };

    template<
        typename C              // Container, 
        , typename F            // Data generator
        , typename MTag         // Modifier tag
        , typename DTag         // Data tag
        , typename D            // Derived
    >
    class interpreter_crtp
//<-
        : public data_gen_holder<F>
        , public modifier_holder<MTag>
#if !BOOST_ASSIGN_V2_ENABLE_CPP0X
        , public functor_aux::crtp_unary_and_up<
            interpreter_crtp<C, F, MTag, DTag, D>,
            ::boost::mpl::always< D const& >
        >
#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X
//->
    {
//<-
        public:
        D & derived(){ return static_cast<D&>(*this); }
        D const& derived()const{ return static_cast<D const&>(*this); }

        protected:

        typedef data_gen_holder<F> data_gen_holder_;
        typedef modifier_holder<MTag> modifier_holder_;
//->

        public:

        typedef /*<-*/ typename modifier_holder_::modifier_type 
            BOOST_ASSIGN_V2_IGNORE(/*->*/ interpreter_modifier<Tag> /*<-*/)/*->*/
        modifier_type;

        interpreter_crtp(){}
        explicit interpreter_crtp( F const& f )/*<-*/ 
            : data_gen_holder_( f )
        {}BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        explicit interpreter_crtp( F const& f, modifier_type const& m )/*<-*/
            : data_gen_holder_( f ), modifier_holder_( m )
        {}BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

        typedef D const& result_type;

        template<typename R>
        result_type
        operator()( as_arg_list_adapter<R> range )const/*<-*/
        {
             return ::boost::for_each( range(), wrapper<D>( this->derived() ) );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

//<-
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
//->

        template<typename...Args>
        result_type operator()( Args&&...args )const/*<-*/
        {
            return  this->modify(
                /*Instance of F*/ this->fun( std::forward<Args>(args)... )
            );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

//<-
#else
        protected:
        typedef functor_aux::crtp_unary_and_up<
            interpreter_crtp,
            ::boost::mpl::always<result_type>
        > super_t;

        public:
        using super_t::operator();

        result_type operator()()const
        {
            return this->modify( this->fun() );
        }

#define BOOST_ASSIGN_V2_MACRO(z, N, data) \
    template<BOOST_PP_ENUM_PARAMS(N, typename T)> \
    result_type \
    impl( BOOST_PP_ENUM_BINARY_PARAMS(N, T, & _) )const \
    { \
        return this->modify( this->fun(BOOST_PP_ENUM_PARAMS(N,_)) ); \
    } \
/**/
BOOST_PP_REPEAT_FROM_TO(
    1,
    BOOST_PP_INC(BOOST_ASSIGN_V2_LIMIT_ARITY),
    BOOST_ASSIGN_V2_MACRO,
    ~
)
#undef BOOST_ASSIGN_V2_MACRO
#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X

        // must be mutable
        C& container()const{ return this->derived().container(); }

        protected:

        template<typename T>
        void check_modifier( BOOST_ASSIGN_V2_FORWARD_PARAM(T, t) )const
        {
            typedef ConceptModifier<MTag, DTag, C,
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
                T&&
#else
                T&
#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X
            > concept_;
            BOOST_CONCEPT_ASSERT(( concept_ ));
        }

#if BOOST_ASSIGN_V2_ENABLE_CPP0X

        template<typename T>
        result_type modify(T&& t)const
        {
            check_modifier( t );
            
            this->modifier.impl(
                this->derived().container(),
                std::forward<T>( t ),
                DTag()
            );
            return this->derived();
        }
#else
        template<typename T>
        result_type modify(T& t)const
        {
            check_modifier( t );
            this->modifier.impl( this->derived().container(), t, DTag() );
            return this->derived();
        }

        template<typename T>
        result_type modify(T const& t)const
        {
            check_modifier( t );
            this->modifier.impl( this->derived().container(), t, DTag() );
            return this->derived();
        }

#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X

//->
    };

}// interpreter_aux
//]
}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_INTERPRETER_CRTP_ER_2010_HPP

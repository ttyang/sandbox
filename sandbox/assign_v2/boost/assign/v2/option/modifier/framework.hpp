//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_OPTION_MODIFIER_FRAMEWORK_ER_2010_HPP
#define BOOST_ASSIGN_V2_OPTION_MODIFIER_FRAMEWORK_ER_2010_HPP
#include <boost/assign/v2/detail/keyword/ignore.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#include <boost/assign/v2/interpreter/fwd.hpp>
#include <boost/assign/v2/interpreter/modifier.hpp>
#include <boost/assign/v2/interpreter/replace.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost{
namespace assign{
namespace v2{
//[syntax_option_modifier
namespace interpreter_aux{

    template<
        typename Keyword // A class of modifiers
        , typename Arg /*<-*/= keyword_aux::ignore/*->*/ // Specifies an aspect of the implementation
    >
    struct option_modifier
    {
        
        option_modifier(){}
        option_modifier(Arg arg)/*<-*/
            :arg_( arg )
        {}BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        
        Arg const& arg()const/*<-*/
        { 
            return this->arg_; 
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

        template<typename Arg1>
        option_modifier<Keyword, Arg1>
        operator=(const Arg1& arg1)const/*<-*/{
            return option_modifier<Keyword, Arg1>( arg1 );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        
//<-
        protected:
        Arg arg_;
//->
    };

    // Specialize on Keyword
    template<typename Keyword, typename Arg>
    struct meta_modifier_tag
    {
        template<
            typename D // Inherits interpreter_crtp<>
        >
        struct apply;
    };

namespace result_of{
        
    template<typename D>
    struct option_modifier{

//<-            
        typedef interpreter_aux::replace_modifier_tag<D> meta_;
//->
            
        template<typename Keyword, typename Arg>
        struct apply 
//<-
            : ::boost::mpl::apply1<
                meta_, 
                typename ::boost::mpl::apply1<
                    interpreter_aux::meta_modifier_tag<Keyword, Arg>, 
                    D
                >::type
            >
//->
        {};
        
    };
            
}// result_of

    template<typename C, typename F, typename ModifierTag, typename DataTag, typename D, 
        typename Keyword, typename Arg>
    typename ::boost::mpl::apply2<
        result_of::option_modifier<D>, Keyword, Arg
    >::type
    operator%(
        interpreter_crtp<C, F, ModifierTag, DataTag, D> const& lhs,
        option_modifier<Keyword, Arg> const& rhs
    )/*<-*/
    {
        typedef interpreter_aux::meta_modifier_tag<Keyword, Arg> meta_;
        typedef typename ::boost::mpl::apply1<meta_, D>::type modifier_tag;
        typedef interpreter_aux::interpreter_modifier<modifier_tag> modifier_;
    
        typedef typename ::boost::mpl::apply2<
            result_of::option_modifier<D>, 
            Keyword, Arg
        >::type result_;
    
        return result_(
            lhs.container(),
            lhs.fun,
            modifier_( lhs.modifier, rhs.arg() )
        );
    }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

}// interpreter_aux

/*<-*/BOOST_ASSIGN_V2_IGNORE(/*->*/#define BOOST_ASSIGN_V2_OPTION_MODIFIER_KEYWORD(NAME) unspecified/*<-*/)/*->*/
/*<-*/BOOST_ASSIGN_V2_IGNORE(/*->*/#define BOOST_ASSIGN_V2_OPTION_MODIFIER_META_MODIFIER_TAG(NAME, Result) unspecified/*<-*/)/*->*/

//]
namespace result_of{

    template<typename D>
    struct option_modifier 
        : interpreter_aux::result_of::option_modifier<D>
    {};

}// result_of

#ifdef BOOST_ASSIGN_V2_OPTION_MODIFIER_META_MODIFIER_TAG
#error
#else
#define BOOST_ASSIGN_V2_OPTION_MODIFIER_META_MODIFIER_TAG(NAME, Result)\
namespace interpreter_aux{\
\
    template<typename Arg>\
    struct meta_modifier_tag<BOOST_PP_CAT(keyword_,NAME), Arg>\
    {\
        template<typename D>\
        struct apply{ typedef Result type; };\
    };\
}\
/**/
#endif

#ifdef BOOST_ASSIGN_V2_OPTION_MODIFIER_KWD_TYPE
#error
#else
#define BOOST_ASSIGN_V2_OPTION_MODIFIER_KWD_TYPE(NAME)\
    interpreter_aux::option_modifier<interpreter_aux::BOOST_PP_CAT(keyword_,NAME)>\
/**/
#endif

#ifdef BOOST_ASSIGN_V2_OPTION_MODIFIER_KEYWORD
#error
#else
#define BOOST_ASSIGN_V2_OPTION_MODIFIER_KEYWORD(NAME)\
namespace interpreter_aux{\
    struct BOOST_PP_CAT(keyword_,NAME){\
\
        BOOST_PP_CAT(keyword_,NAME)(){}\
\
    };\
}\
namespace {\
    BOOST_ASSIGN_V2_OPTION_MODIFIER_KWD_TYPE(NAME) const BOOST_PP_CAT(_,NAME)\
        = BOOST_ASSIGN_V2_OPTION_MODIFIER_KWD_TYPE(NAME)();\
}\
/**/
#endif

}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_OPTION_MODIFIER_FRAMEWORK_ER_2010_HPP
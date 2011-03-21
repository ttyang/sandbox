//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_ER_2010_HPP
#define BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_ER_2010_HPP
#include <boost/assign/v2/detail/keyword/ignore.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#include <boost/assign/v2/interpreter/fwd.hpp>
#include <boost/assign/v2/interpreter/modifier.hpp>
#include <boost/assign/v2/interpreter/replace_parameter.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost{
namespace assign{
namespace v2{
//[syntax_put_modifier_modulo
namespace aux{

    template<typename /*<<A class of modifiers>>*/ Keyword, typename /*<<A part of the modifier's implementation>>*/Arg = keyword_aux::ignore>
    struct optional_modifier
    {
        
        optional_modifier(){}
        optional_modifier(Arg arg)/*<-*/
            :arg_( arg )
        {}BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        
        Arg const& arg()const/*<-*/
        { 
            return this->arg_; 
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

        template<typename Arg1>
        optional_modifier<Keyword, Arg1>
        operator=(const Arg1& arg1)const/*<-*/{
            return optional_modifier<Keyword, Arg1>( arg1 );
        }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/
        
//<-
        protected:
        Arg arg_;
//->
    };

    template<typename Keyword, typename Arg>
    struct /*<<Meta-function class to be specialized on Keyword>>*/ meta_modifier_tag
    {
        template<typename /*<<Inherits `interpreter_crtp<>` >>*/ D> 
        struct /*<<Returns a modifier-tag>>*/ apply;
    };

namespace result_of{
        
    template<typename D>
    struct optional_modifier{

//<-            
        typedef aux::replace_modifier_tag<D> meta_;
//->
            
        template<typename Keyword, typename Arg>
        struct apply 
//<-
            : ::boost::mpl::apply1<
                meta_, 
                typename ::boost::mpl::apply1<
                    aux::meta_modifier_tag<Keyword, Arg>, 
                    D
                >::type
            >
//->
        {};
        
    };
            
}// result_of

    template<typename C, typename F, typename Tag, typename D, 
        typename Keyword, typename Arg>
    typename ::boost::mpl::apply2<
        result_of::optional_modifier<D>, 
        Keyword, Arg
    >::type
    operator%(
        interpreter_crtp<C, F, Tag, D> const& lhs,
        optional_modifier<Keyword, Arg> const& rhs
    )/*<-*/
    {
        typedef aux::meta_modifier_tag<Keyword, Arg> meta_;
        typedef typename ::boost::mpl::apply1<meta_, D>::type modifier_tag;
        typedef aux::adapter_modifier<modifier_tag> modifier_;
    
        typedef typename ::boost::mpl::apply2<
            result_of::optional_modifier<D>, 
            Keyword, Arg
        >::type result_;
    
        return result_(
            lhs.container(),
            lhs.fun,
            modifier_( lhs.modifier, rhs.arg() )
        );
    }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

}// aux
//]
namespace result_of{

    template<typename D>
    struct optional_modifier 
        : aux::result_of::optional_modifier<D>
    {};

}// result_of
}// v2
}// assign
}// boost

#ifdef BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_META_MODIFIER_TAG
#error
#else
#define BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_META_MODIFIER_TAG(NAME, Result)\
namespace boost{\
namespace assign{\
namespace v2{\
namespace aux{\
\
    template<typename Arg>\
    struct meta_modifier_tag<BOOST_PP_CAT(keyword_,NAME), Arg>\
    {\
        template<typename D>\
        struct apply{ typedef Result type; };\
    };\
\
}\
}\
}\
}\
/**/
#endif

#ifdef BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_PARAM
#error
#else
#define BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_PARAM(NAME)\
    aux::optional_modifier<aux::BOOST_PP_CAT(keyword_,NAME)>\
/**/
#endif

#ifdef BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_KEYWORD
#error
#else
#define BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_KEYWORD(NAME)\
namespace boost{\
namespace assign{\
namespace v2{\
namespace aux{\
\
    struct BOOST_PP_CAT(keyword_,NAME){\
\
        BOOST_PP_CAT(keyword_,NAME)(){}\
\
    };\
\
}\
namespace {\
    BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_PARAM(NAME) const BOOST_PP_CAT(_,NAME)\
        = BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_PARAM(NAME)();\
}\
}\
}\
}\
/**/
#endif

// The default
BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_KEYWORD(standard_modifier)    
BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_META_MODIFIER_TAG(standard_modifier, Arg)

#endif // BOOST_ASSIGN_V2_OPTIONAL_MODIFIER_ER_2010_HPP

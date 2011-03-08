//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_MODULO_MODIFIER_META_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_MODULO_MODIFIER_META_ER_2010_HPP
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/assign/v2/put/frame/replace.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace put_aux{
    
	template<typename Keyword, typename Arg>
	struct /*<<Meta-function class to be specialized on Keyword>>*/ meta_modifier_tag
	{
        template<typename /*<<Inherits crtp\<\> >>*/ D> 
    	struct apply;
	};
        
}// put_aux
#ifndef BOOST_ASSIGN_V2_PUT_MODULO_MODIFIER_META_MODIFIER_TAG
#define BOOST_ASSIGN_V2_PUT_MODULO_MODIFIER_META_MODIFIER_TAG(NAME, Result)\
namespace boost{\
namespace assign{\
namespace v2{\
namespace put_aux{\
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
namespace result_of{
        
    template<typename /*<<Inherits crtp\<\> >>*/D>
    struct /*<<Meta-function class>>*/ modulo_modifier{
            
        typedef put_aux::replace_modifier_tag<D> meta_;
            
        template<typename Keyword, typename Arg>
        struct apply : ::boost::mpl::apply1<
        	meta_, 
            typename ::boost::mpl::apply1<
                put_aux::meta_modifier_tag<Keyword, Arg>, 
                D
            >::type
        >{};
        
    };
            
}// result_of
}// v2
}// assign
}// boost

#endif

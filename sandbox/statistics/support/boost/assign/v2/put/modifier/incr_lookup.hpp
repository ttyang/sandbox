//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_MODIFIER_INCR_LOOKUP_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_MODIFIER_INCR_LOOKUP_ER_2010_HPP
#include <boost/assign/v2/put/modifier/def.hpp>
#include <boost/assign/v2/detail/type_traits/value.hpp>

namespace boost{
namespace assign{ 
namespace v2{

// lookup_key
namespace put_tag{ struct incr_lookup{}; }
namespace put_aux{

	template<>
    struct modifier<v2::put_tag::incr_lookup>{

		modifier(){};
    
    	template<typename V,typename T>
        void impl(V& v,T& t)const{ 
        	++ v[ t ]; 
        }
    };

}// assign_aux
}// v2
}// assign
}// boost

#endif

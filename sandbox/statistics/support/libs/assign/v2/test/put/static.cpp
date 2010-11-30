//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <boost/array.hpp>

#include <boost/ptr_container/ptr_array.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/assign/v2/detail/checking/assert.hpp>
#include <boost/assign/v2/put/modifier.hpp>
#include <libs/assign/v2/test/put/static.h>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_static{

#define MACRO( V, T0, T1, n )\
	{ \
    	typedef V< T0 BOOST_PP_COMMA_IF(n) BOOST_PP_EXPR_IF(n, T1) > cont_; \
        typedef put_aux::deduce_modifier<cont_>::type found_; \
        checking::do_assert_is_same<found_,wanted_>(); \
    } \
/**/

    void test()
    {
    	using namespace boost::assign::v2;
        {
        	typedef modifier_tag::push_back wanted_;
        	MACRO( std::list, int, , 0 )
        	MACRO( std::vector, int, ,	0 )
            MACRO( std::deque, int, , 0 )

            MACRO( boost::ptr_deque, int, , 0 )
            MACRO( boost::ptr_list, int, ,	0 )
            MACRO( boost::ptr_vector, int, , 0 )
        }
        {
        	typedef modifier_tag::at_next wanted_;
            MACRO( boost::array, int, 1, 1 )
            MACRO( boost::ptr_array, int, 1, 1 )
        }
        {
        	typedef modifier_tag::push wanted_;
            MACRO( std::queue, int, , 0 )
            MACRO( std::stack, int, ,0 )
        }
        {
        	typedef modifier_tag::insert wanted_;
        	MACRO( std::set, int, , 0 )
            MACRO( std::map, const char* , int, 1 )
        }
        
    }

#undef MACRO

}// xxx_static
}// xxx_put
}// test_assign_v2


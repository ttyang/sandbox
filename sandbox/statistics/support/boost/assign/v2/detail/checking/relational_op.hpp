//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_CHECKING_RELATIONAL_OP_ER_2010_HPP
#define BOOST_ASSIGN_V2_CHECKING_RELATIONAL_OP_ER_2010_HPP
#include <boost/array.hpp>
#include <boost/assign/v2/detail/checking/constants.hpp>
#include <boost/assign/v2/detail/checking/check_equal.hpp>

namespace boost{                                                               
namespace assign{ 
namespace v2{
namespace checking{ 
namespace relational_op{

	// R must derive from relational_op_aux::crtp<> and r contain the checking
    // constants.
    template<typename R>
    void do_check(R const& r)
		{
    		typedef boost::array<int,8> ar_;
			ar_ ar;
        	{
            	using namespace constants;
    			ar[0] = a; ar[1] = b; ar[2] = c;
    			ar[3] = d; ar[4] = e; ar[5] = f;
    			ar[6] = g; ar[7] = h; 
    		}
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  ==  r), true );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  !=  r), false );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  <  r), false );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  >  r), false );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  <=  r), true );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  >=  r), true );
        	++ar[2];
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  ==  r), false );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  !=  r), true );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  <  r), false );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  >  r), true );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  <=  r), false );
        	BOOST_ASSIGN_V2_CHECK_EQUAL( (ar  >=  r), true );

		}

}// relational_op
}// checking
}// v2
}// assign
}// boost    
    
#endif

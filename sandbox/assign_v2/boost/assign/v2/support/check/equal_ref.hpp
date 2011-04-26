//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_SUPPORT_CHECK_EQUAL_REF_ER_2010_HPP
#define BOOST_ASSIGN_V2_SUPPORT_CHECK_EQUAL_REF_ER_2010_HPP
#include <boost/assign/v2/support/config/check.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace check_aux{

    struct equal_ref{

        equal_ref(){}
        template<typename T, typename U>
        void operator()(T const& t, U const& u)const
        {
            BOOST_ASSIGN_V2_CHECK( &t == &u );
        }
    };

}// check_aux
}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_SUPPORT_CHECK_EQUAL_REF_ER_2010_HPP

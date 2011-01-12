//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <libs/assign/v2/test/detail/traits/has_push.h>
#include <libs/assign/v2/test/detail/traits/has_static_size.h>
#include <libs/assign/v2/test/detail/traits/has_value_type.h>
#include <libs/assign/v2/test/detail/traits.h>

namespace test_assign_v2{
namespace xxx_detail{
namespace xxx_traits{

    void test(){
        xxx_has_push::test();
        xxx_has_static_size::test();
        xxx_has_value_type::test();
    }

}// xxx_traits
}// xxx_detail    
}// xxx_test_assign


//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <libs/assign/v2/test/put/pipe/functor/container.h>
#include <libs/assign/v2/test/put/pipe/functor/forward.h>
#include <libs/assign/v2/test/put/pipe/functor/rhs.h>
#include <libs/assign/v2/test/put/pipe/functor.h>

namespace test_assign_v2{
namespace xxx_put{
namespace xxx_pipe{
namespace xxx_functor{

    void test(){
        xxx_container::test();
        xxx_forward::test();
        xxx_rhs::test();
    }

}// xxx_functor
}// xxx_pipe
}// xxx_put
}// xxx_test_assign
//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <libs/assign/v2/test/put/modulo.h>
#include <libs/assign/v2/test/put/ptr.h>
#include <libs/assign/v2/test/put/static.h>
#include <libs/assign/v2/test/put/stl.h>
#include <libs/assign/v2/test/put/tuple_refs.h>
#include <libs/assign/v2/test/put/pipe.h>
#include <libs/assign/v2/test/put/deque.h>
#include <libs/assign/v2/test/put.h>

namespace test_assign_v2{
namespace xxx_put{

    void test(){
    
    	xxx_modulo::test();
    	xxx_ptr::test();
    	xxx_static::test();
    	xxx_stl::test();
    	xxx_tuple_refs::test();
    	xxx_deque::test();
    	xxx_pipe::test();        

    }
    
}// xxx_put
}// test_assign_v2


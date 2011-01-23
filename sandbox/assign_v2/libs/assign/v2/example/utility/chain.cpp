//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <list>
#include <boost/array.hpp>
#include <boost/assign/v2/utility/chain.hpp>
#include <boost/assign/v2/ref/array.hpp>
#include <boost/assign/v2/ref/wrapper/adaptor_get.hpp>
#include <boost/assign/v2/put/deque.hpp>
#include <libs/assign/v2/example/include.h>
#include <libs/assign/v2/example/utility/chain.h>

namespace example_assign_v2{
namespace xxx_utility{
namespace xxx_chain{

    void run(std::ostream& os)
    {
        os << "* xxx_chain" << std::endl;
        {
            //[chain_r
            boost::array<int, 2> ar; ar[0] = 0; ar[1] = 1;
            std::list<int> list( 1, 2 );
            std::vector<int> vec( 2 ); vec[0] = 3; vec[1] = 4;
            boost::for_each(
                ar | as2::_chain( list ) | as2::_chain( vec ),
                os << bl::_1 << ' '
            ); // outputs 0, 1, 2, 3, 4
            //]
	        os << std::endl;
        }
        {
        	//[chain_w
            std::vector<int> v( 3 ); v[0] = -1; v[1] = 0; v[2] = 1;
            boost::array<int, 2> ar; int z; 
            boost::copy(
                v,
                boost::begin(
                    ar /* lvalue */ | as2::_chain(
                        as2::ref::csv_array( 
                        	z /* lvalue */ 
                        )  /* rvalue */ | as2::ref::_get 
                    ) 
                )
            );
            assert( ar[0] == -1 );
            assert( ar[1] == 0 );
            assert( z == 1 );
            //]
        }
    }

}// xxx_chain
}// xxx_utility
}// example_assign_v2
//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/list.hpp>
#include <boost/mpl/for_each.hpp>


#include <boost/detail/lightweight_test.hpp>  // for main, BOOST_TEST
#include <boost/assert.hpp>
#include <boost/type_traits.hpp>
#include "test_type_list.hpp"
#include <boost/integer/high_low_bits.hpp>

using namespace boost;




template <typename T>
void test_function() {

    // making sure that the value type is transfered correctly.
    BOOST_TEST((is_same< typename low_bits<T, 3>::value_type, T >::value));


    BOOST_TEST(( boost::low_bits<T,1>::value == 1));
    BOOST_TEST(( boost::low_bits<T,2>::value == 3));
    BOOST_TEST(( boost::low_bits<T,3>::value == 7));
    BOOST_TEST(( boost::low_bits<T,4>::value == 15));
    BOOST_TEST(( boost::low_bits<T,5>::value == 31));
    BOOST_TEST(( boost::low_bits<T,6>::value == 63));
    BOOST_TEST(( boost::low_bits<T,7>::value == 127));
    BOOST_TEST(( boost::low_bits<T,8>::value == 255));

    // assert that type returns the correct typedef.
    BOOST_TEST(( is_same< 
                    typename low_bits<T, 3>::type,
                    low_bits<T, 3> >::value
              ));
}


struct type_tester {
    template< typename U >
    void operator()(U) {
        test_function<U>();

    }
};


int main( ) {   
    mpl::for_each< test_types   >( type_tester() ); 
    mpl::for_each< test_types_2 >( type_tester() ); 
    mpl::for_each< test_types_3 >( type_tester() ); 
    return 0;
}

//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)



#include "test_type_list.hpp"
#include <boost/integer/high_low_bits.hpp>



// Testing for operator overloads.
using namespace boost;

// this test is to ensure that the overloads
// provide the exact same functionality as their underlying operators.


template <typename T>
void test_function() {

    T mask_value(high_bits_mask<T, 1>::value);
    // operator &(T, high_bits_mask)
    T bit_result = T(0) & high_bits_mask<T, 1>();
    BOOST_ASSERT(( bit_result == (T(0) &  mask_value) ));

    // operator &(high_bits_mask, T)
    bit_result = high_bits_mask<T, 1>() & T(0);
    BOOST_ASSERT(( bit_result == (mask_value & T(0)) ));
    
    // operator |(T, high_bits_mask)
    bit_result = T(0) | high_bits_mask<T, 1>();
    BOOST_ASSERT(( bit_result == ( T(0) | mask_value) ));
    
    // operator |(high_bits_mask, T)
    bit_result = high_bits_mask<T,1>() | T(0);
    BOOST_ASSERT(( bit_result == (mask_value  | T(0)) ));

    // operator ^(high_bits_mask, T)
    bit_result = T(0) ^ high_bits_mask<T,1>();
    BOOST_ASSERT(( bit_result == (T(0) ^ mask_value) ));

    // operator ^(T, high_bits_mask)
    bit_result = high_bits_mask<T,1>() ^ T(0);
    BOOST_ASSERT(( bit_result == ( mask_value ^ T(0)) ));

    // operator ~(high_bits_mask)
    bit_result = ~ (high_bits_mask<T,1>());

    // this is causing errors with unsigned types.
    mask_value = ~( mask_value );
    BOOST_ASSERT(( bit_result == mask_value ));
}


struct type_tester {
    template< typename U >
    void operator()(U) {
        test_function<U>();
    }
};


int main() {
    mpl::for_each< test_types   >( type_tester() ); 
    mpl::for_each< test_types_2 >( type_tester() ); 
    mpl::for_each< test_types_3 >( type_tester() ); 

    return 0;
}

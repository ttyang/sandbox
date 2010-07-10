//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)



#include <boost/integer/high_low_bits.hpp>
#include <boost/detail/lightweight_test.hpp>
#include "test_type_list.hpp"
#include <iostream>
#include <typeinfo>
#include <iomanip>



// tesitng for bit width.
using namespace boost;

template <typename T>
void test_function() {

    using namespace std;


    cout << "Starting test. Test Type = " << typeid(T).name() << endl;
    // making sure that the value type is transfered correctly.
    BOOST_TEST((is_same< typename high_bits_mask<T, 3>::value_type, T >::value));  
    BOOST_TEST(( boost::high_bits_mask<T,1>::value ==
    static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 1)) ));
    BOOST_TEST(( boost::high_bits_mask<T,2>::value == 
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 2)) ));
    BOOST_TEST(( boost::high_bits_mask<T,3>::value ==
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 3)) ));
    BOOST_TEST(( boost::high_bits_mask<T,4>::value ==
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 4)) ));
    BOOST_TEST(( boost::high_bits_mask<T,5>::value ==
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 5)) ));
    BOOST_TEST(( boost::high_bits_mask<T,6>::value ==
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 6)) ));
    BOOST_TEST(( boost::high_bits_mask<T,7>::value ==
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 7)) ));
    BOOST_TEST(( boost::high_bits_mask<T,8>::value ==
        static_cast<T>( ~(~(typename make_unsigned<T>::type(0)) >> 8)) ));

    // assert that type returns the correct typedef.
    BOOST_TEST(( is_same< 
                    typename high_bits_mask<T, 3>::type,
                    high_bits_mask<T, 3> >::value
              ));
}


struct type_tester {
    template< typename U >
    void operator()(U) {
        test_function<U>();
    }
    void operator() (wchar_t)
    {
        using namespace std;
        cout << "can't use wchar_t" << endl;
    }
};


int main() {
    mpl::for_each< test_types   >( type_tester() ); 
    mpl::for_each< test_types_2 >( type_tester() ); 
    mpl::for_each< test_types_3 >( type_tester() );

    return boost::report_errors();
}

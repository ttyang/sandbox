
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/local_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestGccStore
#include <boost/test/unit_test.hpp>

void intermediate(boost::function<void (int, int)> store_func, int size) {
    store_func(size - 1, -1);
}

void hack(int* array, int size) {
    void BOOST_LOCAL_FUNCTION(bind array, int index, int value) {
        array[index] = value;
    } BOOST_LOCAL_FUNCTION_NAME(store)
    
    intermediate(store, size);
}

BOOST_AUTO_TEST_CASE( test_gcc_store ) {
    int nums[] = {1, 2, 3};
    hack(nums, 3);

    BOOST_CHECK( nums[0] ==  1 );
    BOOST_CHECK( nums[1] ==  2 );
    BOOST_CHECK( nums[2] == -1 );
}


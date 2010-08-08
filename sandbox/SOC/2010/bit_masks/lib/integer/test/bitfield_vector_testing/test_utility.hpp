//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <cstring>

#if defined(__GNUC__)
#include <cxxabi.h>
#endif

#ifndef BOOST_BITFIELD_VECTOR_TESTING_UTILITYIES_HPP
#define BOOST_BITFIELD_VECTOR_TESTING_UTILITYIES_HPP



template <typename T>
std::string typestr() {
#if defined(__GNUC__)
    std::size_t const BUFSIZE = 8192;
    std::size_t n = BUFSIZE;
    char buf[BUFSIZE];
    abi::__cxa_demangle(typeid(T).name(), buf, &n, 0);
    return std::string(buf, ::strlen(buf));
#else
    return std::string(typeid(T).name());
#endif
}

template <typename T>
inline std::string typestr(T const&)
{ return typestr<T>(); }


#define BOOST_PRINT_ON_TEST_FAILURE(P1, P2) \
    if(P1 != P2 ) { \
        std::cout << #P1 << ": " << std::hex << std::size_t(P1) << std::endl; \
        std::cout << #P2 << ": " << std::hex << std::size_t(P2) << std::endl; \
    }\
    BOOST_TEST( P1 == P2);


struct print_mpl_values {
    template<typename T>
    void operator()(T x) {
        std::cout<< x << " ";
    }
};

#endif

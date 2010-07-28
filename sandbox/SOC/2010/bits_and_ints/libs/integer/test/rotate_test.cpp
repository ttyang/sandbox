//  Boost integer/rotate.hpp test program  ----------------------//
//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


#include <iostream>
#include <boost/cstdint.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/integer/rotate.hpp>

#define ROTATE_L_TEST(x, n, y) \
BOOST_TEST((::boost::rotate_left(x, n) == y))

#define ROTATE_R_TEST(x, n, y) \
BOOST_TEST((::boost::rotate_right(x, n) == y)); \
std::cout << "aah " << std::hex << ::boost::rotate_right(x, n) << std::endl

int main()
{
    ROTATE_L_TEST(0x0, 1, 0);
	ROTATE_L_TEST(0x0, 30, 0);
	ROTATE_L_TEST(0xF0000000, 4, 0xF);
	ROTATE_L_TEST(0xFF000000, 4, 0xF000000F);
	ROTATE_L_TEST(0xFF000000, 8, 0xFF);
	ROTATE_L_TEST(0xA0000000, 1, 0x40000001);
	ROTATE_L_TEST(0xA0000000, 2, 0x80000002);
	ROTATE_L_TEST(0xA0000000, 3, 0x5);
	ROTATE_L_TEST(0xC, 8, 0xC00);
	ROTATE_L_TEST(0xFFFFFFFF, 4, 0xFFFFFFFF);
	ROTATE_L_TEST(0xFFFFFFFF, 31, 0xFFFFFFFF);
	ROTATE_L_TEST(0x00000002, 31, 0x1);
	ROTATE_L_TEST(0x12345678, 4, 0x23456781);
	
	ROTATE_R_TEST(0x0, 1, 0);
	ROTATE_R_TEST(0x0, 31, 0);
	ROTATE_R_TEST(0xFU, 3, 0xE0000001U);
	ROTATE_R_TEST(0xFU, 1, 0x80000007U);
	ROTATE_R_TEST(0x8, 3, 0x1);
	ROTATE_R_TEST(0x9, 3, 0x20000001);
	ROTATE_R_TEST((int32_t)0xFFFF, 8, (int32_t)0xFF0000FF);
	ROTATE_R_TEST(0xFFFFFFFF, 1, 0xFFFFFFFF);
	ROTATE_R_TEST(0xFFFFFFFF, 30, 0xFFFFFFFF);
	ROTATE_R_TEST(0x12345678, 8, 0x78123456);	
	
#ifndef BOOST_HAS_NO_INT64_T
	
    ROTATE_L_TEST(0x0ULL, 1, 0ULL);
	ROTATE_L_TEST(0x0ULL, 30, 0ULL);
	ROTATE_L_TEST(0xF000000000000000ULL, 4, 0xFULL);
	ROTATE_L_TEST(0xFF00000000000000ULL, 4, 0xF00000000000000FULL);
	ROTATE_L_TEST(0xFF00000000000000ULL, 8, 0xFFULL);
	ROTATE_L_TEST(0xA000000000000000ULL, 1, 0x4000000000000001ULL);
	ROTATE_L_TEST(0xA000000000000000LL, 2, 0x8000000000000002ULL);
	ROTATE_L_TEST(0xA000000000000000LL, 3, 0x5LL);
	ROTATE_L_TEST(0xCLL, 8, 0xC00LL);
	ROTATE_L_TEST(0xFFFFFFFFFFFFFFFFLL, 4, 0xFFFFFFFFFFFFFFFFLL);
	ROTATE_L_TEST(0xFFFFFFFFFFFFFFFFLL, 63, 0xFFFFFFFFFFFFFFFFLL);
	ROTATE_L_TEST(0x0000000000000002LL, 63, 0x1LL);
	ROTATE_L_TEST(0x123456789ABCDEF0LL, 4, 0x23456789ABCDEF01LL);
	ROTATE_R_TEST(0x0ULL, 1, 0ULL);
	ROTATE_R_TEST(0x0ULL, 63, 0ULL);
	ROTATE_R_TEST(0xFULL, 3, 0xE000000000000001ULL);
	ROTATE_R_TEST(0xFULL, 1, 0x8000000000000007ULL);
	ROTATE_R_TEST(0x8ULL, 3, 0x1ULL);
	ROTATE_R_TEST(0x9LL, 3, 0x2000000000000001LL);
	ROTATE_R_TEST((int64_t)0xFFFFLL, 8, (int64_t)0xFF000000000000FFLL);
	ROTATE_R_TEST((uint64_t)0xFFFFFFFFLL, 1, (uint64_t)0x800000007FFFFFFFLL);
	ROTATE_R_TEST(0xFFFFFFFFFFFFFFFFLL, 30, 0xFFFFFFFFFFFFFFFFLL);

#endif
	
	return boost::report_errors();
}

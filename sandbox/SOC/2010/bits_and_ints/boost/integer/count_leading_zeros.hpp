//  Boost integer/count_leading_zeros.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_COUNT_LEADING_ZEROS_INCLUDED
#define BOOST_COUNT_LEADING_ZEROS_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/integer/pop_count.hpp>

/*
 *	count_leading_zeros counts the number of consecutive 0's 
 *		from the most significant bit of an integral value.
 *
 *	For example:
 *	
 *              leading zeros: vvvv vvv
 *	unsigned value = 0xF080; // 0000 0001 1111 0000 1000 0000
 *  int x = count_leading_zeros(value); // x = 7 
 * 
 */

namespace boost {
#ifdef __GNUC__

template <typename T>
inline int count_leading_zeros(T value)
{
	if (value == 0) {
		return sizeof(T) << 3;
	}
	
	return __builtin_clz(value) - (32 - (sizeof(T) << 3));
}

inline int count_leading_zeros(unsigned int value)
{
	if (value == 0) {
		return sizeof(unsigned int) << 3;
	}
	
	return __builtin_clz(value);
}

inline int count_leading_zeros(unsigned long int value)
{
	if (value == 0) {
		return sizeof(unsigned long int) << 3;
	}
	
	return __builtin_clzl(value);
}

#ifndef BOOST_HAS_NO_INT64_T
inline int count_leading_zeros(unsigned long long int value)
{	
	if (value == 0) {
		return sizeof(unsigned long long int) << 3;
	}
	
	return __builtin_clzll(value);
}
#endif	

#else

template <typename T>
typename enable_if_c<sizeof(T) == 1, int>::type
count_leading_zeros(T value)
{
	value = value | (value >> 1);
	value = value | (value >> 2);
	value = value | (value >> 4);
	
	return pop_count(T(~value));
}

template <typename T>
typename enable_if_c<sizeof(T) == 2, int>::type
count_leading_zeros(T value)
{
	value = value | (value >> 1);
	value = value | (value >> 2);
	value = value | (value >> 4);
	value = value | (value >> 8);
	
	return pop_count(T(~value));
}

template <typename T>
typename enable_if_c<sizeof(T) == 4, int>::type
count_leading_zeros(T value)
{
	value = value | (value >> 1);
	value = value | (value >> 2);
	value = value | (value >> 4);
	value = value | (value >> 8);
	value = value | (value >> 16);

	return pop_count(T(~value));
}

template <typename T>
typename enable_if_c<sizeof(T) == 8, int>::type
count_leading_zeros(T value)
{
	value = value | (value >> 1);
	value = value | (value >> 2);
	value = value | (value >> 4);
	value = value | (value >> 8);
	value = value | (value >> 16);
	value = value | (value >> 32);
	
	return pop_count(T(~value));
}

#endif

} // boost

#endif

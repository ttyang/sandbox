//  Boost integer/count_trailing_zeros.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_COUNT_TRAILING_ZEROS_INCLUDED
#define BOOST_COUNT_TRAILING_ZEROS_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/integer/pop_count.hpp>

/*
 *	count_trailing_zeros counts the number of consecutive 0's 
 *		from the least significant bit of an integral value.
 *
 *	For example:
 *	
 *                                   trailing zeros: vvv vvvv
 *	unsigned value = 0xF080; // 0000 0000 1111 0000 1000 0000
 *  int x = count_trailing_zeros(value); // x = 7 
 * 
 */

namespace boost {

#ifdef __GNUC__
	
template <typename T>
inline typename enable_if<is_unsigned<T>, int>::type
count_trailing_zeros(T value)
{
	if (value == 0) {
		return sizeof(T) << 3;
	}
	
	return __builtin_ctz(unsigned(value));
}

inline int count_trailing_zeros(unsigned int value)
{
	if (value == 0) { 
		return sizeof(unsigned int) << 3;
	}
	
	return __builtin_ctz(value);
}
	
inline int count_trailing_zeros(unsigned long int value)
{
	if (value == 0) { 
		return sizeof(unsigned long int) << 3;
	}
	
	return __builtin_ctzl(value);
}

#ifndef BOOST_HAS_NO_INT64_T
inline int count_trailing_zeros(unsigned long long int value)
{
	if (value == 0) { 
		return sizeof(unsigned long long int) << 3;
	}
	
	return __builtin_ctzll(value);
}
#endif
	

#else

inline int count_trailing_zeros(uintmax_t value)
{
	return pop_count(~value & (value - 1));
}

#endif // __GNUC__	
	
} // boost

#endif

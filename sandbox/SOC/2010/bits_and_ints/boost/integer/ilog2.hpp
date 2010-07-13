//  Boost integer/count_leading_zeros.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_ILOG2_INCLUDED
#define BOOST_ILOG2_INCLUDED

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/integer/count_leading_zeros.hpp>

namespace boost {

/*
 *	This function returns the integer value of 
 *		logarithm in base 2 of an unsigned integral `value`
 *
 *	If `value` is equal to 0, the value returned is -1
 *
 *	`value` must be unsigned.
 */
template <typename T>
inline T ilog2(T value)
{
	BOOST_STATIC_ASSERT((is_unsigned<T>::value));
	
	return (sizeof(T) * 8) - count_leading_zeros(value) - 1;
}
	
}

#endif

//  Boost integer/detail/sign_extend.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_SIGN_EXTEND_INCLUDED
#define BOOST_SIGN_EXTEND_INCLUDED

#include <boost/cstdint.hpp> // for intmax_t
#include <boost/assert.hpp>

namespace boost 
{

//	Extend data represented in `bits' bits to 
//		sizeof(IntegralType) * 8 bits
template <typename IntegralType>
inline IntegralType sign_extend(IntegralType data, std::size_t bits)
{
	data = data & ((IntegralType(1) << bits) - 1);
	IntegralType const mask = (IntegralType(1) << (bits - 1));
	return (data ^ mask) - mask;
}
	
} // boost

#endif
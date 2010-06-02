//  Boost integer/detail/static_sign_extend.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_STATIC_SIGN_EXTEND_INCLUDED
#define BOOST_STATIC_SIGN_EXTEND_INCLUDED

#include <boost/cstdint.hpp>

namespace boost 
{

// Compile-time version of sign_extend
template<typename IntegralType, IntegralType raw, std::size_t Bits>
struct static_sign_extend 
{
private:
    BOOST_STATIC_CONSTANT(IntegralType, shift = (IntegralType(1) << (Bits - 1)));
	BOOST_STATIC_CONSTANT(IntegralType, mask = ((IntegralType(1) << Bits) - 1));
public:
	BOOST_STATIC_CONSTANT(IntegralType, value = ((raw & mask) ^ shift) - shift); 
}; // boost::static_sign_extend

} // boost

#endif
//  Boost integer/static_gcd.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  (C) Copyright Vicente J. Botet Escribá 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STATIC_GCD_INCLUDED
#define BOOST_STATIC_GCD_INCLUDED

#include <boost/mpl/and.hpp>
#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/math/common_factor_ct.hpp>
#include <boost/integer/static_abs.hpp>
#include <boost/integer/is_integral_constant.hpp>

namespace boost {
	
/*
 *	This header defines mpl::gcd<> metafunction wich calculates
 *		the greatest common divisor of two given mpl::integral_c<> 
 *		ICT1 and ICT2.
 */

namespace mpl {

template <typename ICT1, typename ICT2
	, class Enable = typename enable_if<
		and_<
			is_integral_constant<ICT1>,
			is_integral_constant<ICT2>
		>
	>::type
>
struct gcd : integral_c<uintmax_t,
	math::static_gcd<
		mpl::abs<ICT1>::value,
		mpl::abs<ICT2>::value
	>::value
> 
{};
	
}

} // boost

#endif
//  Boost integer/static_sign.hpp header file  ------------------------------//

//  (C) Copyright Murilo Adriano Vasconcelos 2010.
//  (C) Copyright Vicente J. Botst Escriba 2010.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STATIC_SIGN_INCLUDED
#define BOOST_STATIC_SIGN_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/make_signed.hpp>
#include <boost/integer/is_integral_constant.hpp>

namespace boost {

/*
 *	This header defines mpl::sign<> and static_sign<> metafunctions.
 */
	
namespace mpl {

template <typename IC>
struct sign : 
	integral_c<
		typename make_signed<
			typename IC::value_type
		>::type,
		(IC::value == 0 ? 0 : (IC::value > 0 ? 1 : -1))
	>
{
	BOOST_STATIC_ASSERT((is_integral_constant<IC>::value));
};

}

template <typename T, T Value>
struct static_sign : mpl::sign<mpl::integral_c<T, Value> >
{
	BOOST_STATIC_ASSERT((is_integral<T>::value));
};

} // boost

#endif
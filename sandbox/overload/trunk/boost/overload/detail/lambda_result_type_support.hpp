/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_LAMBDA_RESULT_TYPE_SUPPORT_HPP_
#define _BOOST_OVERLOAD_LAMBDA_RESULT_TYPE_SUPPORT_HPP_

#include <boost/tuple/tuple.hpp>
#include "result_type.hpp"


#define BOOST_OVERLOAD_KET(z, n, text) >
// end macro BOOST_OVERLOAD_KET

#define BOOST_OVERLOAD_SIG(z, n, unused) \
template< typename F BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A) > \
struct sig< boost::tuples::cons<F BOOST_PP_ENUM_TRAILING_PARAMS(n, boost::tuples::cons<A), boost::tuples::null_type> BOOST_PP_REPEAT(n, BOOST_OVERLOAD_KET, unused) > \
    : public result<F ( BOOST_PP_ENUM_PARAMS(n, A) )> \
{ \
};
// end macro BOOST_OVERLOAD_SIG

namespace boost{ namespace overloads{ namespace detail{

///////////////////////////////////////////////////////////////////////////////
// metafunction:  sig<Args>
// requires:      Args is a tuple< F, A0, A1, ..., AN> where F is an instantiation
//                of the boost::overload class template
// returns:       the result type of the call signature supported by F that
//                owns the same argument list as Args or undefined if there
//                is no supported call signature with the same argument list
// provides:      support for Boost.Lambda result type deduction

template< typename Args>
struct sig
{};


BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_OVERLOAD_MAX_NUM_ARGS), BOOST_OVERLOAD_SIG, unused)

} } } // end namespaces

#undef BOOST_OVERLOAD_SIG


#endif // _BOOST_OVERLOAD_LAMBDA_RESULT_TYPE_SUPPORT_HPP_

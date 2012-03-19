/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_CHANGE_RESULT_TYPE_HPP_
#define _BOOST_OVERLOAD_CHANGE_RESULT_TYPE_HPP_

#include <boost/type_traits/function_traits.hpp>

///////////////////////////////////////////////////////////////////////////////
// utility:   change_result_type<ResultType, Signature>
// requires:  Signature is a function type (e.g. R (A0, A1, ...,AN))
// returns:   a call signature with the same parameter types of Signature and
//            with result type ResultType

#define BOOST_OVERLOAD_CHANGE_RESULT_TYPE(z, n, unused) \
template<typename ResultType, typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A) > \
struct change_result_type<ResultType, R ( BOOST_PP_ENUM_PARAMS(n, A) )> \
{ \
   typedef ResultType type ( BOOST_PP_ENUM_PARAMS(n, A) ); \
};
// end macro BOOST_OVERLOAD_CHANGE_RESULT_TYPE

namespace boost{ namespace overloads{ namespace detail{

template<typename ResultType, typename Signature>
struct change_result_type
{};


BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_OVERLOAD_MAX_NUM_ARGS), BOOST_OVERLOAD_CHANGE_RESULT_TYPE, unused)

} } } // end namespaces

#undef BOOST_OVERLOAD_CHANGE_RESULT_TYPE

#endif // _BOOST_OVERLOAD_CHANGE_RESULT_TYPE_HPP_

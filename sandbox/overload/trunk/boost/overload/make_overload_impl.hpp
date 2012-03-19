/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_MAKE_OVERLOAD_IMPL_HPP_
#define _BOOST_MAKE_OVERLOAD_IMPL_HPP_


#include "overload_impl.hpp"
#include "detail/get_signature.hpp"


namespace boost{ namespace overloads{

namespace detail {

struct no_function {};

template<>
struct get_signature<no_function, function_obj_tag>
{
    typedef no_signature type;
};


template<
    typename F0,
    BOOST_OVERLOAD_ENUM_SHIFTED_PARAMS_WITH_A_DEFAULT(BOOST_OVERLOAD_LIMIT, typename F, no_function)
>
struct make_overload_type
{
    typedef overload< BOOST_OVERLOAD_ENUM_CALLS_TPL(BOOST_OVERLOAD_LIMIT, typename get_signature, F, type) >
            type;
};

} // end namespace detail


BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_OVERLOAD_LIMIT), BOOST_OVERLOAD_MAKE_NTH_MAKE_OVERLOAD, unused)

using detail::make_overload_type;

} // end overloads namespace

using overloads::make_overload;

} // end boost namespace


#endif // _BOOST_MAKE_OVERLOAD_IMPL_HPP_

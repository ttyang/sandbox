/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_DETAIL_FINAL_OVERLOAD_BASE_HPP_
#define _BOOST_DETAIL_FINAL_OVERLOAD_BASE_HPP_

//#include <limits>
#include <boost/function.hpp>


namespace boost{ namespace overloads{ namespace detail{

///////////////////////////////////////////////////////////////////////////////
// stop recursion structs

struct no_signature {};

struct final_overload_base
{
    BOOST_STATIC_CONSTANT( unsigned int, index = UINT_MAX );
    typedef final_overload_base base_type;
    typedef BOOST_OVERLOAD_WRAPPED_FUNC<no_signature> function_type;
    typedef no_signature signature_type;
    struct final;
    void operator()(final*) const {}
};

} } } // end namespaces

#endif // _BOOST_DETAIL_FINAL_OVERLOAD_BASE_HPP_


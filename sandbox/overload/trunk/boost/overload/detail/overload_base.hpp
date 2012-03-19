/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_DETAIL_OVERLOAD_BASE_HPP_
#define _BOOST_DETAIL_OVERLOAD_BASE_HPP_

#include <boost/function.hpp>

#include "final_overload_base.hpp"

namespace boost{ namespace overloads{ namespace detail{

///////////////////////////////////////////////////////////////////////////////
// overload_base class

template< 
    unsigned int N,
    typename Sig0, 
    BOOST_OVERLOAD_ENUM_SHIFTED_PARAMS_WITH_A_DEFAULT(BOOST_OVERLOAD_LIMIT, typename Sig, detail::no_signature)
>
struct overload_base
    : public BOOST_OVERLOAD_WRAPPED_FUNC<Sig0>
    , public overload_base<N+1, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
{
        BOOST_STATIC_CONSTANT( unsigned int, index = N );

    typedef Sig0                                 signature_type;
    typedef BOOST_OVERLOAD_WRAPPED_FUNC<Sig0>    function_type;
    typedef 
        overload_base<N+1, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)> 
        base_type;

// Workaround for MSVC < 8.0 tested on MSVC 7.1 
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400) 
    using function_type::operator();
    using base_type::operator();
#endif
// Workaround for masking result_type inherited from boost::function
// that leads to a problem for result_of support
#if BOOST_WORKAROUND(BOOST_MSVC, < 1500) || BOOST_WORKAROUND(__INTEL_COMPILER, < 1220)
  private:
    template<typename T>
    struct result_type;
#endif
};

template< unsigned int N, typename Sig0 >
struct overload_base<N, Sig0>
    : public BOOST_OVERLOAD_WRAPPED_FUNC<Sig0>
    , public final_overload_base
{
    BOOST_STATIC_CONSTANT( unsigned int, index = N );

    typedef Sig0                                 signature_type;
    typedef BOOST_OVERLOAD_WRAPPED_FUNC<Sig0>    function_type;
    typedef final_overload_base                  base_type;

// Workaround for MSVC < 8.0 tested on MSVC 7.1 
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)  
    using function_type::operator();
#endif
};

} } } // end namespaces


#endif // _BOOST_DETAIL_OVERLOAD_BASE_HPP_


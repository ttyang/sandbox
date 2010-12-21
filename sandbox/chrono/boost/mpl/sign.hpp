////////////////////////////////////////////////////////////////////
//
// Copyright Vicente J. Botet Escriba 2010
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.
//
////////////////////////////////////////////////////////////////////
#ifndef BOOST_MPL_SIGN_HPP_INCLUDED
#define BOOST_MPL_SIGN_HPP_INCLUDED

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct sign_impl;

template< typename T > struct sign_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct sign
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : sign_impl<
          typename sign_tag<N>::type
        >::template apply<N>::type
#else
    : aux::msvc_eti_base< typename apply_wrap1<
          sign_impl< typename sign_tag<N>::type >
        , N
        >::type >::type
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, sign, (N))
};

BOOST_MPL_AUX_NA_SPEC(1, sign)


#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2)
namespace aux {
template< typename T, T n > struct sign_wknd
{
    BOOST_STATIC_CONSTANT(T, value = (n == 0 ? 0 : (n < 0 ? -1 : 1)));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct sign_impl<integral_c_tag>
{
#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2)
    template< typename N > struct apply
        : aux::sign_wknd< typename N::value_type, N::value >
#else
    template< typename N > struct apply
        : integral_c< typename N::value_type, (N::value == 0 ? 0 : (N::value < 0 ? -1 : 1)) >
#endif    
    {
    };
};

}}

#endif // BOOST_MPL_SIGN_HPP_INCLUDED

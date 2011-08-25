/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_DOWNGRADE_HPP_INCLUDED

#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>

namespace boost { namespace dispatch
{
    namespace details { namespace simd
    {
        template<typename T, typename U>
        struct downgrade;
        
        template< class Type
                , std::size_t Cardinal
                >
        struct downgrade< boost::simd::pack<Type, Cardinal>, Type >
        {
            typedef boost::simd::pack<Type, Cardinal> type;
        };
        
        template< class Type
                , std::size_t Cardinal
                , class DownType
                >
        struct downgrade< boost::simd::pack<Type, Cardinal>, DownType >
        {
            typedef boost::simd::pack<DownType, Cardinal*2> type;
        };
    } }
    
    namespace meta
    {
        template< class Type
                , std::size_t Cardinal
                >
        struct downgrade< boost::simd::pack<Type, Cardinal> >
        {
            typedef typename boost::dispatch::details::simd::downgrade<
                boost::simd::pack<Type, Cardinal>
              , typename downgrade<Type>::type
            >::type type;
        };
    }
} }

#endif

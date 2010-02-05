//Copyright (c) 2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LA_CUSTOM_VECTOR_MAGNITUDE2_4_HPP_INCLUDED
#define BOOST_LA_CUSTOM_VECTOR_MAGNITUDE2_4_HPP_INCLUDED

//This file was generated by a program. Do not edit manually.

#include <boost/la/config.hpp>
#include <boost/la/math.hpp>
#include <boost/la/vector_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace
boost
    {
    namespace
    la
        {
        template <class A>
        BOOST_LA_INLINE_OPERATIONS
        typename enable_if_c<
            is_vector<A>::value && vector_traits<A>::dim==4,
            typename vector_traits<A>::scalar_type>::type
        magnitude2( A const & a )
            {
            typedef typename vector_traits<A>::scalar_type T;
            T const a0=vector_traits<A>::template r<0>(a);
            T const a1=vector_traits<A>::template r<1>(a);
            T const a2=vector_traits<A>::template r<2>(a);
            T const a3=vector_traits<A>::template r<3>(a);
            T const mag2=a0*a0+a1*a1+a2*a2+a3*a3;
            return mag2;
            }

        namespace
        la_detail
            {
            template <int D>
            struct vector_magnitude2_defined;

            template <>
            struct
            vector_magnitude2_defined<4>
                {
                static bool const value=true;
                };
            }
        }
    }

#endif

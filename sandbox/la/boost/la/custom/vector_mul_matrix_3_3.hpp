//Copyright (c) 2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LA_CUSTOM_VECTOR_MUL_MATRIX_3_3_HPP_INCLUDED
#define BOOST_LA_CUSTOM_VECTOR_MUL_MATRIX_3_3_HPP_INCLUDED

//This file was generated by a program. Do not edit manually.

#include <boost/la/config.hpp>
#include <boost/la/deduce_vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>

namespace
boost
    {
    namespace
    la
        {
        template <class A,class B>
        BOOST_LA_INLINE_OPERATIONS
        typename lazy_enable_if_c<
            matrix_traits<B>::rows==3 && matrix_traits<B>::cols==3 &&
            vector_traits<A>::dim==3,
            deduce_vector2<A,B,3> >::type
        operator*( A const & a, B const & b )
            {
            typedef typename vector_traits<A>::scalar_type Ta;
            typedef typename matrix_traits<B>::scalar_type Tb;
            Ta const a0 = vector_traits<A>::template r<0>(a);
            Ta const a1 = vector_traits<A>::template r<1>(a);
            Ta const a2 = vector_traits<A>::template r<2>(a);
            Tb const b00 = matrix_traits<B>::template r<0,0>(b);
            Tb const b01 = matrix_traits<B>::template r<0,1>(b);
            Tb const b02 = matrix_traits<B>::template r<0,2>(b);
            Tb const b10 = matrix_traits<B>::template r<1,0>(b);
            Tb const b11 = matrix_traits<B>::template r<1,1>(b);
            Tb const b12 = matrix_traits<B>::template r<1,2>(b);
            Tb const b20 = matrix_traits<B>::template r<2,0>(b);
            Tb const b21 = matrix_traits<B>::template r<2,1>(b);
            Tb const b22 = matrix_traits<B>::template r<2,2>(b);
            typedef typename deduce_vector2<A,B,3>::type R;
            BOOST_STATIC_ASSERT(vector_traits<R>::dim==3);
            R r;
            vector_traits<R>::template w<0>(r)=a0*b00+a1*b10+a2*b20;
            vector_traits<R>::template w<1>(r)=a0*b01+a1*b11+a2*b21;
            vector_traits<R>::template w<2>(r)=a0*b02+a1*b12+a2*b22;
            return r;
            }

        namespace
        la_detail
            {
            template <int M,int N>
            struct vector_mul_matrix_defined;

            template <>
            struct
            vector_mul_matrix_defined<3,3>
                {
                static bool const value=true;
                };
            }
        }
    }

#endif
//Copyright (c) 2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LA_CUSTOM_MATRIX_MUL_MATRIX_2_2_1_HPP_INCLUDED
#define BOOST_LA_CUSTOM_MATRIX_MUL_MATRIX_2_2_1_HPP_INCLUDED

//This file was generated by a program. Do not edit manually.

#include <boost/la/config.hpp>
#include <boost/la/deduce_matrix.hpp>
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
            matrix_traits<A>::rows==2 && matrix_traits<B>::rows==2 &&
            matrix_traits<A>::cols==2 && matrix_traits<B>::cols==1,
            deduce_matrix2<A,B,2,1> >::type
        operator*( A const & a, B const & b )
            {
            typedef typename matrix_traits<A>::scalar_type Ta;
            typedef typename matrix_traits<B>::scalar_type Tb;
            Ta const a00 = matrix_traits<A>::template r<0,0>(a);
            Ta const a01 = matrix_traits<A>::template r<0,1>(a);
            Ta const a10 = matrix_traits<A>::template r<1,0>(a);
            Ta const a11 = matrix_traits<A>::template r<1,1>(a);
            Tb const b00 = matrix_traits<B>::template r<0,0>(b);
            Tb const b10 = matrix_traits<B>::template r<1,0>(b);
            typedef typename deduce_matrix2<A,B,2,1>::type R;
            BOOST_STATIC_ASSERT(matrix_traits<R>::rows==2);
            BOOST_STATIC_ASSERT(matrix_traits<R>::cols==1);
            R r;
            matrix_traits<R>::template w<0,0>(r)=a00*b00+a01*b10;
            matrix_traits<R>::template w<1,0>(r)=a10*b00+a11*b10;
            return r;
            }

        namespace
        la_detail
            {
            template <int M,int N,int P>
            struct matrix_mul_matrix_defined;

            template <>
            struct
            matrix_mul_matrix_defined<2,2,1>
                {
                static bool const value=true;
                };
            }
        }
    }

#endif

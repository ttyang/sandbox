//Copyright (c) 2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LA_CUSTOM_MATRIX_DIV_EQ_SCALAR_3_3_HPP_INCLUDED
#define BOOST_LA_CUSTOM_MATRIX_DIV_EQ_SCALAR_3_3_HPP_INCLUDED

//This file was generated by a program. Do not edit manually.

#include <boost/la/config.hpp>
#include <boost/la/matrix_traits.hpp>
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
            matrix_traits<A>::rows==3 && matrix_traits<A>::cols==3,
            A &>::type
        operator/=( A & a, typename matrix_traits<A>::scalar_type b )
            {
            matrix_traits<A>::template w<0,0>(a)/=b;
            matrix_traits<A>::template w<0,1>(a)/=b;
            matrix_traits<A>::template w<0,2>(a)/=b;
            matrix_traits<A>::template w<1,0>(a)/=b;
            matrix_traits<A>::template w<1,1>(a)/=b;
            matrix_traits<A>::template w<1,2>(a)/=b;
            matrix_traits<A>::template w<2,0>(a)/=b;
            matrix_traits<A>::template w<2,1>(a)/=b;
            matrix_traits<A>::template w<2,2>(a)/=b;
            return a;
            }

        namespace
        la_detail
            {
            template <int M,int N>
            struct matrix_div_eq_scalar_defined;

            template <>
            struct
            matrix_div_eq_scalar_defined<3,3>
                {
                static bool const value=true;
                };
            }
        }
    }

#endif

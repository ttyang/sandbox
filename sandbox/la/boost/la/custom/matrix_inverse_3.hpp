//Copyright (c) 2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LA_CUSTOM_MATRIX_INVERSE_3_HPP_INCLUDED
#define BOOST_LA_CUSTOM_MATRIX_INVERSE_3_HPP_INCLUDED

//This file was generated by a program. Do not edit manually.

#include <boost/la/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/la/deduce_matrix.hpp>
#include <boost/la/scalar_traits.hpp>
#include <boost/assert.hpp>

namespace
boost
    {
    namespace
    la
        {
        template <class A>
        BOOST_LA_INLINE_OPERATIONS
        typename lazy_enable_if_c<
            matrix_traits<A>::rows==3 && matrix_traits<A>::cols==3,
            deduce_matrix<A> >::type
        inverse( A const & a, typename matrix_traits<A>::scalar_type det )
            {
            typedef typename matrix_traits<A>::scalar_type T;
            BOOST_ASSERT(det!=scalar_traits<T>::zero());
            T const a00=matrix_traits<A>::template r<0,0>(a);
            T const a01=matrix_traits<A>::template r<0,1>(a);
            T const a02=matrix_traits<A>::template r<0,2>(a);
            T const a10=matrix_traits<A>::template r<1,0>(a);
            T const a11=matrix_traits<A>::template r<1,1>(a);
            T const a12=matrix_traits<A>::template r<1,2>(a);
            T const a20=matrix_traits<A>::template r<2,0>(a);
            T const a21=matrix_traits<A>::template r<2,1>(a);
            T const a22=matrix_traits<A>::template r<2,2>(a);
            T const f=scalar_traits<T>::one()/det;
            typedef typename deduce_matrix<A>::type R;
            R r;
            matrix_traits<R>::template w<0,0>(r)= f*(a11*a22-a12*a21);
            matrix_traits<R>::template w<0,1>(r)=-f*(a01*a22-a02*a21);
            matrix_traits<R>::template w<0,2>(r)= f*(a01*a12-a02*a11);
            matrix_traits<R>::template w<1,0>(r)=-f*(a10*a22-a12*a20);
            matrix_traits<R>::template w<1,1>(r)= f*(a00*a22-a02*a20);
            matrix_traits<R>::template w<1,2>(r)=-f*(a00*a12-a02*a10);
            matrix_traits<R>::template w<2,0>(r)= f*(a10*a21-a11*a20);
            matrix_traits<R>::template w<2,1>(r)=-f*(a00*a21-a01*a20);
            matrix_traits<R>::template w<2,2>(r)= f*(a00*a11-a01*a10);
            return r;
            }

        namespace
        la_detail
            {
            template <int D>
            struct matrix_inverse_defined;

            template <>
            struct
            matrix_inverse_defined<3>
                {
                static bool const value=true;
                };
            }
        }
    }

#endif

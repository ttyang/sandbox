//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_SUPPORT_MATH_HPP )
#define BOOST_MAPS_SUPPORT_MATH_HPP

#include <boost/maps/generic/array.hpp>
#include <boost/maps/generic/array_.hpp>

namespace boost { namespace maps {

//--

    template< class T, std::size_t N, bool I, class A >
    struct vector_type
    {
        typedef array_< T,1,N,I,A > type;
    };

//--

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    struct matrix_type
    {
        typedef array< T,bounds2< M,N >,I,A > type;
    };

//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct tensor_type
    {
        typedef array_< T,N,D,I,A > type;
    };

//--

    template< class T > class scalar;
    template< class T, std::size_t N, bool I = true, class A = null::allocator > class vector;
    template< class T, std::size_t M, std::size_t N, bool I = true, class A = null::allocator > class matrix;
    template< class T, std::size_t N, std::size_t D, bool I = true, class A = null::allocator > class tensor;

//--

    template< class T1, class T2 >
    struct matrix_vector_type
    {
        typedef typename common_type< T1,T2 >::type type;
    };

    template< class T1, std::size_t N, bool I1, class A1, class T2, bool I2, class A2 >
    struct matrix_vector_type< vector< T1,N,I1,A1 >,vector< T2,N,I2,A2 > >
    {
        typedef matrix< typename common_type< T1,T2 >::type,N,N,I1,A1 > type;
    };

    template< class T1, std::size_t N, bool I1, class A1, class T2, std::size_t M, bool I2, class A2 >
    struct matrix_vector_type< vector< T1,N,I1,A1 >,matrix< T2,N,M,I2,A2 > >
    {
        typedef matrix< typename common_type< T1,T2 >::type,N,M,I2,A2 > type;
    };

    template< class T1, std::size_t M, std::size_t N, bool I1, class A1, class T2, bool I2, class A2 >
    struct matrix_vector_type< matrix< T1,M,N,I1,A1 >,vector< T2,N,I2,A2 > >
    {
        typedef matrix< typename common_type< T1,T2 >::type,M,N,I1,A1 > type;
    };

    template< class T1, std::size_t N1, bool I1, class A1, std::size_t N, bool I2, class A2, class T2, bool I3, class A3, bool I4, class A4 >
    struct matrix_vector_type< vector< vector< T1,N1,I1,A1 >,N,I2,A2 >,vector< vector< T2,N1,I3,A3 >,N,I4,A4 > >
    {
        typedef matrix< typename matrix_vector_type< vector< T1,N1,I1,A1 >,vector< T2,N1,I3,A3 > >::type,N1,N1,I1,A1 > type;
    };

    template< class T1, std::size_t N1, bool I1, class A1, std::size_t N, bool I2, class A2, class T2, std::size_t M1, bool I3, class A3, std::size_t M, bool I4, class A4 >
    struct matrix_vector_type< vector< vector< T1,N1,I1,A1 >,N,I2,A2 >,matrix< matrix< T2,N1,M1,I3,A3 >,N,M,I4,A4 > >
    {
        typedef matrix< typename matrix_vector_type< vector< T1,N1,I1,A1 >,matrix< T2,N1,M1,I3,A3 > >::type,N1,M1,I3,A3 > type;
    };

    template< class T1, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I2, class A2, class T2, bool I3, class A3, bool I4, class A4 >
    struct matrix_vector_type< matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 >,vector< vector< T2,N1,I3,A3 >,N,I4,A4 > >
    {
        typedef matrix< typename matrix_vector_type< matrix< T1,M1,N1,I1,A1 >,vector< T2,N1,I3,A3 > >::type,M1,N1,I1,A1 > type;
    };

//--

    template< class T1, class T2 >
    struct vector_matrix_type
    {
        typedef typename common_type< T1,T2 >::type type;
    };

    template< class T1, std::size_t N1, bool I1, class A1, class T2, std::size_t N2, bool I2, class A2 >
    struct vector_matrix_type< vector< T1,N1,I1,A1 >,matrix< T2,N1,N2,I2,A2 > >
    {
        typedef vector< T1,N2,I1,A1 > type;
    };

    template< class T1, std::size_t N1, bool I1, class A1, class T2, std::size_t N2, bool I2, class A2 >
    struct vector_matrix_type< matrix< T2,N1,N2,I2,A2 >,vector< T1,N2,I1,A1 > >
    {
        typedef vector< T1,N1,I1,A1 > type;
    };

    template< class T1, std::size_t N1, bool I1, class A1, std::size_t N, bool I2, class A2, class T2, std::size_t N2, bool I3, class A3, std::size_t M, bool I4, class A4 >
    struct vector_matrix_type< vector< vector< T1,N1,I1,A1 >,N,I2,A2 >,matrix< matrix< T2,N1,N2,I3,A3 >,N,M,I4,A4 > >
    {
        typedef vector< typename vector_matrix_type< vector< T1,N1,I1,A1 >,matrix< T2,N1,N2,I3,A3 > >::type,M,I2,A2 > type;
    };

    template< class T1, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I2, class A2, class T2, bool I3, class A3, bool I4, class A4 >
    struct vector_matrix_type< matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 >,vector< vector< T2,N1,I3,A3 >,N,I4,A4 > >
    {
        typedef vector< typename vector_matrix_type< matrix< T1,M1,N1,I1,A1 >,vector< T2,N1,I3,A3 > >::type,M,I4,A4 > type;
    };

//--

    template< class T1, class T2 >
    struct matrix_scalar_type
    {
        typedef typename common_type< T1,T2 >::type type;
    };

    template< class T1, class T2, std::size_t M, std::size_t N, bool I, class A >
    struct matrix_scalar_type< T1,matrix< T2,M,N,I,A > >
    {
        typedef matrix< typename common_type< T1,T2 >::type,M,N,I,A > type;
    };

    template< class T1, std::size_t M, std::size_t N, bool I, class A, class T2 >
    struct matrix_scalar_type< matrix< T1,M,N,I,A >,T2 >
    {
        typedef matrix< typename common_type< T1,T2 >::type,M,N,I,A > type;
    };

    template< class T1, class T2, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I2, class A2 >
    struct matrix_scalar_type< T1,matrix< matrix< T2,M1,N1,I1,A1 >,M,N,I2,A2 > >
    {
        typedef matrix< matrix< T2,M1,N1,I1,A1 >,M,N,I2,A2 > type;
    };

    template< class T1, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I2, class A2, class T2 >
    struct matrix_scalar_type< matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 >,T2 >
    {
        typedef matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 > type;
    };

//--

    template< class T1, class T2 >
    struct vector_scalar_type
    {
        typedef typename common_type< T1,T2 >::type type;
    };

    template< class T1, class T2, std::size_t N, bool I, class A >
    struct vector_scalar_type< T1,vector< T2,N,I,A > >
    {
        typedef vector< typename common_type< T1,T2 >::type,N,I,A > type;
    };

    template< class T1, std::size_t N, bool I, class A, class T2 >
    struct vector_scalar_type< vector< T1,N,I,A >,T2 >
    {
        typedef vector< typename common_type< T1,T2 >::type,N,I,A > type;
    };

    template< class T1, class T2, std::size_t N1, bool I1, class A1, std::size_t N, bool I2, class A2 >
    struct vector_scalar_type< T1,vector< vector< T2,N1,I1,A1 >,N,I2,A2 > >
    {
        typedef vector< vector< T2,N1,I1,A1 >,N,I2,A2 > type;
    };

    template< class T1, std::size_t N1, bool I1, class A1, std::size_t N, bool I2, class A2, class T2 >
    struct vector_scalar_type< vector< vector< T1,N1,I1,A1 >,N,I2,A2 >,T2 >
    {
        typedef vector< vector< T1,N1,I1,A1 >,N,I2,A2 > type;
    };

//--

    template< class T1, class T2 >
    struct matrix_product_type
    {
        typedef typename common_type< T1,T2 >::type type;
    };

    template< class T1, std::size_t M, std::size_t P, bool I1, class A1, class T2, std::size_t N, bool I2, class A2 >
    struct matrix_product_type< matrix< T1,M,P,I1,A1 >,matrix< T2,P,N,I2,A2 > >
    {
        typedef matrix< typename common_type< T1,T2 >::type,M,N,true,A1 > type;
    };

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t P, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N, bool I4, class A4 >
    struct matrix_product_type< matrix< matrix< T1,M1,P1,I1,A1 >,M,P,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,P,N,I4,A4 > >
    {
        typedef matrix< typename matrix_product_type< matrix< T1,M1,P1,I1,A1 >,matrix< T2,P1,N1,I3,A3 > >::type,M,N,true,A2 > type;
    };

//--

    template< class T >
    struct matrix_transpose_type
    {
        typedef T type;
    };

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    struct matrix_transpose_type< matrix< T,M,N,I,A > >
    {
        typedef matrix< T,N,M,I,A > type;
    };

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A >
    struct matrix_transpose_type< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >
    {
        typedef matrix< typename matrix_transpose_type< matrix< T,M1,N1,I1,A1 > >::type,N,M,I,A > type;
    };

//--

    template< class T >
    struct is_matrix
    {
        typedef mpl::bool_< false > type;
    };

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    struct is_matrix< matrix< T,M,N,I,A > >
    {
        typedef mpl::bool_< true > type;
    };

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_SUPPORT_MATH_HPP

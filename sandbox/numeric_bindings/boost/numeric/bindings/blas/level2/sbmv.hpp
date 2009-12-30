//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_SBMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_SBMV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_order.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The BLAS-backend is selected by defining a pre-processor variable,
//  which can be one of
// * for CBLAS, define BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
// * for CUBLAS, define BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
// * netlib-compatible BLAS is the default
//
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
#include <boost/numeric/bindings/blas/detail/cblas.h>
#include <boost/numeric/bindings/blas/detail/cblas_option.hpp>
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
#include <boost/numeric/bindings/blas/detail/cublas.h>
#include <boost/numeric/bindings/blas/detail/blas_option.hpp>
#else
#include <boost/numeric/bindings/blas/detail/blas.h>
#include <boost/numeric/bindings/blas/detail/blas_option.hpp>
#endif

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end BLAS-routine.
//
namespace detail {

#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void sbmv( Order, UpLo, const std::ptrdiff_t n, const std::ptrdiff_t k,
        const float alpha, const float* a, const std::ptrdiff_t lda,
        const float* x, const std::ptrdiff_t incx, const float beta, float* y,
        const std::ptrdiff_t incy ) {
    cblas_ssbmv( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            k, alpha, a, lda, x, incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void sbmv( Order, UpLo, const std::ptrdiff_t n, const std::ptrdiff_t k,
        const double alpha, const double* a, const std::ptrdiff_t lda,
        const double* x, const std::ptrdiff_t incx, const double beta,
        double* y, const std::ptrdiff_t incy ) {
    cblas_dsbmv( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            k, alpha, a, lda, x, incx, beta, y, incy );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void sbmv( Order, UpLo, const std::ptrdiff_t n, const std::ptrdiff_t k,
        const float alpha, const float* a, const std::ptrdiff_t lda,
        const float* x, const std::ptrdiff_t incx, const float beta, float* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasSsbmv( blas_option< UpLo >::value, n, k, alpha, a, lda, x, incx,
            beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void sbmv( Order, UpLo, const std::ptrdiff_t n, const std::ptrdiff_t k,
        const double alpha, const double* a, const std::ptrdiff_t lda,
        const double* x, const std::ptrdiff_t incx, const double beta,
        double* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void sbmv( Order, UpLo, const std::ptrdiff_t n, const std::ptrdiff_t k,
        const float alpha, const float* a, const std::ptrdiff_t lda,
        const float* x, const std::ptrdiff_t incx, const float beta, float* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_SSBMV( &blas_option< UpLo >::value, &n, &k, &alpha, a, &lda, x,
            &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void sbmv( Order, UpLo, const std::ptrdiff_t n, const std::ptrdiff_t k,
        const double alpha, const double* a, const std::ptrdiff_t lda,
        const double* x, const std::ptrdiff_t incx, const double beta,
        double* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_DSBMV( &blas_option< UpLo >::value, &n, &k, &alpha, a, &lda, x,
            &incx, &beta, y, &incy );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to sbmv.
//
template< typename Value >
struct sbmv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type invoke( const std::ptrdiff_t k, const real_type alpha,
            const MatrixA& a, const VectorX& x, const real_type beta,
            VectorY& y ) {
        typedef typename result_of::data_order< MatrixA >::type order;
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorY >::value ) );
        detail::sbmv( order(), uplo(), size_column(a), k, alpha,
                begin_value(a), stride_major(a), begin_value(x), stride(x),
                beta, begin_value(y), stride(y) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the sbmv_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for sbmv. Its overload differs for
// * VectorY&
//
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename sbmv_impl< typename value< MatrixA >::type >::return_type
sbmv( const std::ptrdiff_t k, const typename remove_imaginary<
        typename value< MatrixA >::type >::type alpha, const MatrixA& a,
        const VectorX& x, const typename remove_imaginary< typename value<
        MatrixA >::type >::type beta, VectorY& y ) {
    sbmv_impl< typename value< MatrixA >::type >::invoke( k, alpha, a,
            x, beta, y );
}

//
// Overloaded function for sbmv. Its overload differs for
// * const VectorY&
//
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename sbmv_impl< typename value< MatrixA >::type >::return_type
sbmv( const std::ptrdiff_t k, const typename remove_imaginary<
        typename value< MatrixA >::type >::type alpha, const MatrixA& a,
        const VectorX& x, const typename remove_imaginary< typename value<
        MatrixA >::type >::type beta, const VectorY& y ) {
    sbmv_impl< typename value< MatrixA >::type >::invoke( k, alpha, a,
            x, beta, y );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

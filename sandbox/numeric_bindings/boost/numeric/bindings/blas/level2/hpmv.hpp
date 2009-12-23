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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPMV_HPP

#include <boost/assert.hpp>
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
// * CBLAS backend
// * complex<float> value-type
//
template< typename Order, typename UpLo >
inline void hpmv( Order, UpLo, const std::ptrdiff_t n,
        const std::complex<float> alpha, const std::complex<float>* ap,
        const std::complex<float>* x, const std::ptrdiff_t incx,
        const std::complex<float> beta, std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    cblas_chpmv( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            &alpha, ap, x, incx, &beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend
// * complex<double> value-type
//
template< typename Order, typename UpLo >
inline void hpmv( Order, UpLo, const std::ptrdiff_t n,
        const std::complex<double> alpha, const std::complex<double>* ap,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double> beta, std::complex<double>* y,
        const std::ptrdiff_t incy ) {
    cblas_zhpmv( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            &alpha, ap, x, incx, &beta, y, incy );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend
// * complex<float> value-type
//
template< typename Order, typename UpLo >
inline void hpmv( Order, UpLo, const std::ptrdiff_t n,
        const std::complex<float> alpha, const std::complex<float>* ap,
        const std::complex<float>* x, const std::ptrdiff_t incx,
        const std::complex<float> beta, std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasChpmv( blas_option< UpLo >::value, n, alpha, ap, x, incx, beta, y,
            incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend
// * complex<double> value-type
//
template< typename Order, typename UpLo >
inline void hpmv( Order, UpLo, const std::ptrdiff_t n,
        const std::complex<double> alpha, const std::complex<double>* ap,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double> beta, std::complex<double>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default)
// * complex<float> value-type
//
template< typename Order, typename UpLo >
inline void hpmv( Order, UpLo, const std::ptrdiff_t n,
        const std::complex<float> alpha, const std::complex<float>* ap,
        const std::complex<float>* x, const std::ptrdiff_t incx,
        const std::complex<float> beta, std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_CHPMV( &blas_option< UpLo >::value, &n, &alpha, ap, x, &incx, &beta,
            y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default)
// * complex<double> value-type
//
template< typename Order, typename UpLo >
inline void hpmv( Order, UpLo, const std::ptrdiff_t n,
        const std::complex<double> alpha, const std::complex<double>* ap,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double> beta, std::complex<double>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_ZHPMV( &blas_option< UpLo >::value, &n, &alpha, ap, x, &incx, &beta,
            y, &incy );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hpmv.
//
template< typename Value >
struct hpmv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename VectorX, typename VectorY >
    static return_type invoke( const value_type alpha, const MatrixAP& ap,
            const VectorX& x, const value_type beta, VectorY& y ) {
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixAP >::type >::type, typename remove_const<
                typename value< VectorX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixAP >::type >::type, typename remove_const<
                typename value< VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorY >::value ) );
        typedef typename result_of::data_order< MatrixAP >::type order;
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        detail::hpmv( order(), uplo(), size_column(ap), alpha,
                begin_value(ap), begin_value(x), stride(x), beta,
                begin_value(y), stride(y) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the hpmv_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hpmv. Its overload differs for
// * VectorY&
//
template< typename MatrixAP, typename VectorX, typename VectorY >
inline typename hpmv_impl< typename value<
        MatrixAP >::type >::return_type
hpmv( const typename value< MatrixAP >::type alpha, const MatrixAP& ap,
        const VectorX& x, const typename value< MatrixAP >::type beta,
        VectorY& y ) {
    hpmv_impl< typename value< MatrixAP >::type >::invoke( alpha, ap, x,
            beta, y );
}

//
// Overloaded function for hpmv. Its overload differs for
// * const VectorY&
//
template< typename MatrixAP, typename VectorX, typename VectorY >
inline typename hpmv_impl< typename value<
        MatrixAP >::type >::return_type
hpmv( const typename value< MatrixAP >::type alpha, const MatrixAP& ap,
        const VectorX& x, const typename value< MatrixAP >::type beta,
        const VectorY& y ) {
    hpmv_impl< typename value< MatrixAP >::type >::invoke( alpha, ap, x,
            beta, y );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

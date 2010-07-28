//
// Copyright (c) 2002--2010
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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPR2_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPR2_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_order.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
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
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const float alpha, const float* x, const int incx, const float* y,
        const int incy, float* ap ) {
    cblas_sspr2( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            alpha, x, incx, y, incy, ap );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const double alpha, const double* x, const int incx, const double* y,
        const int incy, double* ap ) {
    cblas_dspr2( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            alpha, x, incx, y, incy, ap );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const std::complex<float> alpha, const std::complex<float>* x,
        const int incx, const std::complex<float>* y, const int incy,
        std::complex<float>* ap ) {
    cblas_chpr2( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            &alpha, x, incx, y, incy, ap );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const std::complex<double> alpha, const std::complex<double>* x,
        const int incx, const std::complex<double>* y, const int incy,
        std::complex<double>* ap ) {
    cblas_zhpr2( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            &alpha, x, incx, y, incy, ap );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const float alpha, const float* x, const int incx, const float* y,
        const int incy, float* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasSspr2( blas_option< UpLo >::value, n, alpha, x, incx, y, incy, ap );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const double alpha, const double* x, const int incx, const double* y,
        const int incy, double* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const std::complex<float> alpha, const std::complex<float>* x,
        const int incx, const std::complex<float>* y, const int incy,
        std::complex<float>* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasChpr2( blas_option< UpLo >::value, n, alpha, x, incx, y, incy, ap );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const int n,
        const std::complex<double> alpha, const std::complex<double>* x,
        const int incx, const std::complex<double>* y, const int incy,
        std::complex<double>* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const fortran_int_t n,
        const float alpha, const float* x, const fortran_int_t incx,
        const float* y, const fortran_int_t incy, float* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_SSPR2( &blas_option< UpLo >::value, &n, &alpha, x, &incx, y, &incy,
            ap );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const fortran_int_t n,
        const double alpha, const double* x, const fortran_int_t incx,
        const double* y, const fortran_int_t incy, double* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_DSPR2( &blas_option< UpLo >::value, &n, &alpha, x, &incx, y, &incy,
            ap );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const fortran_int_t n,
        const std::complex<float> alpha, const std::complex<float>* x,
        const fortran_int_t incx, const std::complex<float>* y,
        const fortran_int_t incy, std::complex<float>* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_CHPR2( &blas_option< UpLo >::value, &n, &alpha, x, &incx, y, &incy,
            ap );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline void hpr2( const Order order, const UpLo uplo, const fortran_int_t n,
        const std::complex<double> alpha, const std::complex<double>* x,
        const fortran_int_t incx, const std::complex<double>* y,
        const fortran_int_t incy, std::complex<double>* ap ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_ZHPR2( &blas_option< UpLo >::value, &n, &alpha, x, &incx, y, &incy,
            ap );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hpr2.
//
template< typename Value >
struct hpr2_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void result_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorViewX, typename VectorViewY, typename MatrixAP >
    static result_type invoke( const value_type alpha, const VectorViewX& x,
            const VectorViewY& y, MatrixAP& ap ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_order< MatrixAP >::type order;
        typedef typename result_of::uplo_tag< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const<
                typename bindings::value_type< VectorViewX >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorViewY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_same< typename remove_const<
                typename bindings::value_type< VectorViewX >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixAP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAP >::value) );
        detail::hpr2( order(), uplo(), bindings::size_column(ap), alpha,
                bindings::begin_value(x), bindings::stride(x),
                bindings::begin_value(y), bindings::stride(y),
                bindings::begin_value(ap) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the hpr2_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hpr2. Its overload differs for
// * MatrixAP&
//
template< typename VectorViewX, typename VectorViewY, typename MatrixAP >
inline typename hpr2_impl< typename bindings::value_type<
        VectorViewX >::type >::result_type
hpr2( const typename bindings::value_type< VectorViewX >::type alpha,
        const VectorViewX& x, const VectorViewY& y, MatrixAP& ap ) {
    hpr2_impl< typename bindings::value_type<
            VectorViewX >::type >::invoke( alpha, x, y, ap );
}

//
// Overloaded function for hpr2. Its overload differs for
// * const MatrixAP&
//
template< typename VectorViewX, typename VectorViewY, typename MatrixAP >
inline typename hpr2_impl< typename bindings::value_type<
        VectorViewX >::type >::result_type
hpr2( const typename bindings::value_type< VectorViewX >::type alpha,
        const VectorViewX& x, const VectorViewY& y, const MatrixAP& ap ) {
    hpr2_impl< typename bindings::value_type<
            VectorViewX >::type >::invoke( alpha, x, y, ap );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

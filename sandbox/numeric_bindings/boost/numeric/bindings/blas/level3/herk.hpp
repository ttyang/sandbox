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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_HERK_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_HERK_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_order.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
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
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const float alpha, const float* a,
        const int lda, const float beta, float* c, const int ldc ) {
    cblas_ssyrk( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, n, k, alpha, a, lda, beta, c, ldc );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const double alpha, const double* a,
        const int lda, const double beta, double* c, const int ldc ) {
    cblas_dsyrk( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, n, k, alpha, a, lda, beta, c, ldc );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const float alpha,
        const std::complex<float>* a, const int lda, const float beta,
        std::complex<float>* c, const int ldc ) {
    cblas_cherk( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, n, k, alpha, a, lda, beta, c, ldc );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const double alpha,
        const std::complex<double>* a, const int lda, const double beta,
        std::complex<double>* c, const int ldc ) {
    cblas_zherk( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, n, k, alpha, a, lda, beta, c, ldc );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const float alpha, const float* a,
        const int lda, const float beta, float* c, const int ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasSsyrk( blas_option< UpLo >::value, blas_option< Trans >::value, n,
            k, alpha, a, lda, beta, c, ldc );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const double alpha, const double* a,
        const int lda, const double beta, double* c, const int ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasDsyrk( blas_option< UpLo >::value, blas_option< Trans >::value, n,
            k, alpha, a, lda, beta, c, ldc );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const float alpha,
        const std::complex<float>* a, const int lda, const float beta,
        std::complex<float>* c, const int ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasCherk( blas_option< UpLo >::value, blas_option< Trans >::value, n,
            k, alpha, a, lda, beta, c, ldc );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const int n, const int k, const double alpha,
        const std::complex<double>* a, const int lda, const double beta,
        std::complex<double>* c, const int ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const fortran_int_t n, const fortran_int_t k, const float alpha,
        const float* a, const fortran_int_t lda, const float beta, float* c,
        const fortran_int_t ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_SSYRK( &blas_option< UpLo >::value, &blas_option< Trans >::value, &n,
            &k, &alpha, a, &lda, &beta, c, &ldc );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const fortran_int_t n, const fortran_int_t k, const double alpha,
        const double* a, const fortran_int_t lda, const double beta,
        double* c, const fortran_int_t ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_DSYRK( &blas_option< UpLo >::value, &blas_option< Trans >::value, &n,
            &k, &alpha, a, &lda, &beta, c, &ldc );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const fortran_int_t n, const fortran_int_t k, const float alpha,
        const std::complex<float>* a, const fortran_int_t lda,
        const float beta, std::complex<float>* c, const fortran_int_t ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_CHERK( &blas_option< UpLo >::value, &blas_option< Trans >::value, &n,
            &k, &alpha, a, &lda, &beta, c, &ldc );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans >
inline void herk( const Order order, const UpLo uplo, const Trans trans,
        const fortran_int_t n, const fortran_int_t k, const double alpha,
        const std::complex<double>* a, const fortran_int_t lda,
        const double beta, std::complex<double>* c, const fortran_int_t ldc ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_ZHERK( &blas_option< UpLo >::value, &blas_option< Trans >::value, &n,
            &k, &alpha, a, &lda, &beta, c, &ldc );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to herk.
//
template< typename Value >
struct herk_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void result_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixC >
    static result_type invoke( const real_type alpha, const MatrixA& a,
            const real_type beta, MatrixC& c ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_order< MatrixC >::type order;
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::uplo_tag< MatrixC >::type uplo;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixC >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixC >::value) );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(c) == 1 ||
                bindings::stride_minor(c) == 1 );
        detail::herk( order(), uplo(), trans(),
                bindings::size_column(c), bindings::size_column(a), alpha,
                bindings::begin_value(a), bindings::stride_major(a), beta,
                bindings::begin_value(c), bindings::stride_major(c) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the herk_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for herk. Its overload differs for
// * MatrixC&
//
template< typename MatrixA, typename MatrixC >
inline typename herk_impl< typename bindings::value_type<
        MatrixA >::type >::result_type
herk( const typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type alpha, const MatrixA& a,
        const typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type beta, MatrixC& c ) {
    herk_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( alpha, a, beta, c );
}

//
// Overloaded function for herk. Its overload differs for
// * const MatrixC&
//
template< typename MatrixA, typename MatrixC >
inline typename herk_impl< typename bindings::value_type<
        MatrixA >::type >::result_type
herk( const typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type alpha, const MatrixA& a,
        const typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type beta, const MatrixC& c ) {
    herk_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( alpha, a, beta, c );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

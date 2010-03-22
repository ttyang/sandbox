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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_TRMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_TRMV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/blas/detail/default_order.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
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
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const float* a, const int lda, float* x,
        const int incx ) {
    cblas_strmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, a,
            lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const double* a, const int lda,
        double* x, const int incx ) {
    cblas_dtrmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, a,
            lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const std::complex<float>* a,
        const int lda, std::complex<float>* x, const int incx ) {
    cblas_ctrmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, a,
            lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const std::complex<double>* a,
        const int lda, std::complex<double>* x, const int incx ) {
    cblas_ztrmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, a,
            lda, x, incx );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const float* a, const int lda, float* x,
        const int incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasStrmv( blas_option< UpLo >::value, blas_option< Trans >::value,
            blas_option< Diag >::value, n, a, lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const double* a, const int lda,
        double* x, const int incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const std::complex<float>* a,
        const int lda, std::complex<float>* x, const int incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const int n, const std::complex<double>* a,
        const int lda, std::complex<double>* x, const int incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const fortran_int_t n, const float* a,
        const fortran_int_t lda, float* x, const fortran_int_t incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_STRMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, a, &lda, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const fortran_int_t n, const double* a,
        const fortran_int_t lda, double* x, const fortran_int_t incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_DTRMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, a, &lda, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const fortran_int_t n, const std::complex<float>* a,
        const fortran_int_t lda, std::complex<float>* x,
        const fortran_int_t incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_CTRMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, a, &lda, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void trmv( const Order order, const UpLo uplo, const Trans trans,
        const Diag diag, const fortran_int_t n, const std::complex<double>* a,
        const fortran_int_t lda, std::complex<double>* x,
        const fortran_int_t incx ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_ZTRMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, a, &lda, x, &incx );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trmv.
//
template< typename Value >
struct trmv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void result_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorX >
    static result_type invoke( const MatrixA& a, VectorX& x ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename detail::default_order< MatrixA >::type order;
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::uplo_tag< MatrixA, trans >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorX >::value) );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        detail::trmv( order(), uplo(), trans(), diag(),
                bindings::size_column_op(a, trans()),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(x), bindings::stride(x) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the trmv_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trmv. Its overload differs for
// * VectorX&
//
template< typename MatrixA, typename VectorX >
inline typename trmv_impl< typename bindings::value_type<
        MatrixA >::type >::result_type
trmv( const MatrixA& a, VectorX& x ) {
    trmv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, x );
}

//
// Overloaded function for trmv. Its overload differs for
// * const VectorX&
//
template< typename MatrixA, typename VectorX >
inline typename trmv_impl< typename bindings::value_type<
        MatrixA >::type >::result_type
trmv( const MatrixA& a, const VectorX& x ) {
    trmv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, x );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

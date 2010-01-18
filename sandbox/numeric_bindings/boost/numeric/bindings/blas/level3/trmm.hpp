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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_TRMM_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_TRMM_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_order.hpp>
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
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const float alpha, const float* a, const int lda,
        float* b, const int ldb ) {
    cblas_strmm( cblas_option< Order >::value, cblas_option< Side >::value,
            cblas_option< UpLo >::value, cblas_option< TransA >::value,
            cblas_option< Diag >::value, m, n, alpha, a, lda, b, ldb );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const double alpha, const double* a, const int lda,
        double* b, const int ldb ) {
    cblas_dtrmm( cblas_option< Order >::value, cblas_option< Side >::value,
            cblas_option< UpLo >::value, cblas_option< TransA >::value,
            cblas_option< Diag >::value, m, n, alpha, a, lda, b, ldb );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const std::complex<float> alpha,
        const std::complex<float>* a, const int lda, std::complex<float>* b,
        const int ldb ) {
    cblas_ctrmm( cblas_option< Order >::value, cblas_option< Side >::value,
            cblas_option< UpLo >::value, cblas_option< TransA >::value,
            cblas_option< Diag >::value, m, n, &alpha, a, lda, b, ldb );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const std::complex<double> alpha,
        const std::complex<double>* a, const int lda, std::complex<double>* b,
        const int ldb ) {
    cblas_ztrmm( cblas_option< Order >::value, cblas_option< Side >::value,
            cblas_option< UpLo >::value, cblas_option< TransA >::value,
            cblas_option< Diag >::value, m, n, &alpha, a, lda, b, ldb );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const float alpha, const float* a, const int lda,
        float* b, const int ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasStrmm( side, blas_option< UpLo >::value, blas_option<
            TransA >::value, blas_option< Diag >::value, m, n, alpha, a, lda,
            b, ldb );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const double alpha, const double* a, const int lda,
        double* b, const int ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasDtrmm( side, blas_option< UpLo >::value, blas_option<
            TransA >::value, blas_option< Diag >::value, m, n, alpha, a, lda,
            b, ldb );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const std::complex<float> alpha,
        const std::complex<float>* a, const int lda, std::complex<float>* b,
        const int ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasCtrmm( side, blas_option< UpLo >::value, blas_option<
            TransA >::value, blas_option< Diag >::value, m, n, alpha, a, lda,
            b, ldb );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag, const int m,
        const int n, const std::complex<double> alpha,
        const std::complex<double>* a, const int lda, std::complex<double>* b,
        const int ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag,
        const fortran_int_t m, const fortran_int_t n, const float alpha,
        const float* a, const fortran_int_t lda, float* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_STRMM( &side, &blas_option< UpLo >::value, &blas_option<
            TransA >::value, &blas_option< Diag >::value, &m, &n, &alpha, a,
            &lda, b, &ldb );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag,
        const fortran_int_t m, const fortran_int_t n, const double alpha,
        const double* a, const fortran_int_t lda, double* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_DTRMM( &side, &blas_option< UpLo >::value, &blas_option<
            TransA >::value, &blas_option< Diag >::value, &m, &n, &alpha, a,
            &lda, b, &ldb );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag,
        const fortran_int_t m, const fortran_int_t n,
        const std::complex<float> alpha, const std::complex<float>* a,
        const fortran_int_t lda, std::complex<float>* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_CTRMM( &side, &blas_option< UpLo >::value, &blas_option<
            TransA >::value, &blas_option< Diag >::value, &m, &n, &alpha, a,
            &lda, b, &ldb );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename TransA, typename Diag >
inline void trmm( Order, const char side, UpLo, TransA, Diag,
        const fortran_int_t m, const fortran_int_t n,
        const std::complex<double> alpha, const std::complex<double>* a,
        const fortran_int_t lda, std::complex<double>* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_ZTRMM( &side, &blas_option< UpLo >::value, &blas_option<
            TransA >::value, &blas_option< Diag >::value, &m, &n, &alpha, a,
            &lda, b, &ldb );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trmm.
//
template< typename Value >
struct trmm_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB >
    static return_type invoke( const char side, const value_type alpha,
            const MatrixA& a, MatrixB& b ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_order< MatrixB >::type order;
        typedef typename result_of::trans_tag< MatrixA, order >::type transa;
        typedef typename result_of::uplo_tag< MatrixA, trans >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( side == 'L' || side == 'R' );
        detail::trmm( order(), side, uplo(), transa(), diag(),
                bindings::size_row(b), bindings::size_column(b), alpha,
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(b), bindings::stride_major(b) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the trmm_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trmm. Its overload differs for
// * MatrixB&
//
template< typename MatrixA, typename MatrixB >
inline typename trmm_impl< typename bindings::value_type<
        MatrixA >::type >::return_type
trmm( const char side, const typename bindings::value_type<
        MatrixA >::type alpha, const MatrixA& a, MatrixB& b ) {
    trmm_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( side, alpha, a, b );
}

//
// Overloaded function for trmm. Its overload differs for
// * const MatrixB&
//
template< typename MatrixA, typename MatrixB >
inline typename trmm_impl< typename bindings::value_type<
        MatrixA >::type >::return_type
trmm( const char side, const typename bindings::value_type<
        MatrixA >::type alpha, const MatrixA& a, const MatrixB& b ) {
    trmm_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( side, alpha, a, b );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

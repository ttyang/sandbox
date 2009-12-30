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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_TBMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_TBMV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/blas/detail/default_order.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
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
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const float* a, const std::ptrdiff_t lda,
        float* x, const std::ptrdiff_t incx ) {
    cblas_stbmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, k,
            a, lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const double* a, const std::ptrdiff_t lda,
        double* x, const std::ptrdiff_t incx ) {
    cblas_dtbmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, k,
            a, lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const std::complex<float>* a,
        const std::ptrdiff_t lda, std::complex<float>* x,
        const std::ptrdiff_t incx ) {
    cblas_ctbmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, k,
            a, lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const std::complex<double>* a,
        const std::ptrdiff_t lda, std::complex<double>* x,
        const std::ptrdiff_t incx ) {
    cblas_ztbmv( cblas_option< Order >::value, cblas_option< UpLo >::value,
            cblas_option< Trans >::value, cblas_option< Diag >::value, n, k,
            a, lda, x, incx );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const float* a, const std::ptrdiff_t lda,
        float* x, const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasStbmv( blas_option< UpLo >::value, blas_option< Trans >::value,
            blas_option< Diag >::value, n, k, a, lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const double* a, const std::ptrdiff_t lda,
        double* x, const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    // NOT FOUND();
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const std::complex<float>* a,
        const std::ptrdiff_t lda, std::complex<float>* x,
        const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasCtbmv( blas_option< UpLo >::value, blas_option< Trans >::value,
            blas_option< Diag >::value, n, k, a, lda, x, incx );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const std::complex<double>* a,
        const std::ptrdiff_t lda, std::complex<double>* x,
        const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const float* a, const std::ptrdiff_t lda,
        float* x, const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_STBMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, &k, a, &lda, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const double* a, const std::ptrdiff_t lda,
        double* x, const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_DTBMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, &k, a, &lda, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const std::complex<float>* a,
        const std::ptrdiff_t lda, std::complex<float>* x,
        const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_CTBMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, &k, a, &lda, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo, typename Trans, typename Diag >
inline void tbmv( Order, UpLo, Trans, Diag, const std::ptrdiff_t n,
        const std::ptrdiff_t k, const std::complex<double>* a,
        const std::ptrdiff_t lda, std::complex<double>* x,
        const std::ptrdiff_t incx ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_ZTBMV( &blas_option< UpLo >::value, &blas_option< Trans >::value,
            &blas_option< Diag >::value, &n, &k, a, &lda, x, &incx );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tbmv.
//
template< typename Value >
struct tbmv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorX >
    static return_type invoke( const std::ptrdiff_t k, const MatrixA& a,
            VectorX& x ) {
        typedef typename detail::default_order< MatrixA >::type order;
        typedef typename result_of::data_side< MatrixA >::type uplo;
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorX >::value ) );
        detail::tbmv( order(), uplo(), trans(), diag(),
                size_column_op(a, trans()), k, begin_value(a),
                stride_major(a), begin_value(x), stride(x) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the tbmv_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tbmv. Its overload differs for
// * VectorX&
//
template< typename MatrixA, typename VectorX >
inline typename tbmv_impl< typename value< MatrixA >::type >::return_type
tbmv( const std::ptrdiff_t k, const MatrixA& a, VectorX& x ) {
    tbmv_impl< typename value< MatrixA >::type >::invoke( k, a, x );
}

//
// Overloaded function for tbmv. Its overload differs for
// * const VectorX&
//
template< typename MatrixA, typename VectorX >
inline typename tbmv_impl< typename value< MatrixA >::type >::return_type
tbmv( const std::ptrdiff_t k, const MatrixA& a, const VectorX& x ) {
    tbmv_impl< typename value< MatrixA >::type >::invoke( k, a, x );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

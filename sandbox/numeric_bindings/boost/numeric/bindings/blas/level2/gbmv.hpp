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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GBMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GBMV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/blas/detail/default_order.hpp>
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
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku, float alpha,
        const float* a, int lda, const float* x, int incx, float beta,
        float* y, int incy ) {
    cblas_sgbmv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, kl, ku, alpha, a, lda, x, incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku, double alpha,
        const double* a, int lda, const double* x, int incx, double beta,
        double* y, int incy ) {
    cblas_dgbmv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, kl, ku, alpha, a, lda, x, incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku,
        std::complex<float> alpha, const std::complex<float>* a, int lda,
        const std::complex<float>* x, int incx, std::complex<float> beta,
        std::complex<float>* y, int incy ) {
    cblas_cgbmv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, kl, ku, &alpha, a, lda, x, incx, &beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku,
        std::complex<double> alpha, const std::complex<double>* a, int lda,
        const std::complex<double>* x, int incx, std::complex<double> beta,
        std::complex<double>* y, int incy ) {
    cblas_zgbmv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, kl, ku, &alpha, a, lda, x, incx, &beta, y, incy );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku, float alpha,
        const float* a, int lda, const float* x, int incx, float beta,
        float* y, int incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasSgbmv( blas_option< Trans >::value, m, n, kl, ku, alpha, a, lda, x,
            incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku, double alpha,
        const double* a, int lda, const double* x, int incx, double beta,
        double* y, int incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku,
        std::complex<float> alpha, const std::complex<float>* a, int lda,
        const std::complex<float>* x, int incx, std::complex<float> beta,
        std::complex<float>* y, int incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasCgbmv( blas_option< Trans >::value, m, n, kl, ku, alpha, a, lda, x,
            incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, int m, int n, int kl, int ku,
        std::complex<double> alpha, const std::complex<double>* a, int lda,
        const std::complex<double>* x, int incx, std::complex<double> beta,
        std::complex<double>* y, int incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, fortran_int_t m, fortran_int_t n,
        fortran_int_t kl, fortran_int_t ku, float alpha, const float* a,
        fortran_int_t lda, const float* x, fortran_int_t incx, float beta,
        float* y, fortran_int_t incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_SGBMV( &blas_option< Trans >::value, &m, &n, &kl, &ku, &alpha, a,
            &lda, x, &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, fortran_int_t m, fortran_int_t n,
        fortran_int_t kl, fortran_int_t ku, double alpha, const double* a,
        fortran_int_t lda, const double* x, fortran_int_t incx, double beta,
        double* y, fortran_int_t incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_DGBMV( &blas_option< Trans >::value, &m, &n, &kl, &ku, &alpha, a,
            &lda, x, &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, fortran_int_t m, fortran_int_t n,
        fortran_int_t kl, fortran_int_t ku, std::complex<float> alpha,
        const std::complex<float>* a, fortran_int_t lda,
        const std::complex<float>* x, fortran_int_t incx,
        std::complex<float> beta, std::complex<float>* y,
        fortran_int_t incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_CGBMV( &blas_option< Trans >::value, &m, &n, &kl, &ku, &alpha, a,
            &lda, x, &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename Trans >
inline void gbmv( Order, Trans, fortran_int_t m, fortran_int_t n,
        fortran_int_t kl, fortran_int_t ku, std::complex<double> alpha,
        const std::complex<double>* a, fortran_int_t lda,
        const std::complex<double>* x, fortran_int_t incx,
        std::complex<double> beta, std::complex<double>* y,
        fortran_int_t incy ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_ZGBMV( &blas_option< Trans >::value, &m, &n, &kl, &ku, &alpha, a,
            &lda, x, &incx, &beta, y, &incy );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gbmv.
//
template< typename Value >
struct gbmv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type invoke( const value_type alpha, const MatrixA& a,
            const VectorX& x, const value_type beta, VectorY& y ) {
        typedef typename detail::default_order< MatrixA >::type order;
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorY >::value) );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        detail::gbmv( order(), trans(), size_row_op(a, trans()),
                size_column_op(a, trans()), bandwidth_lower_op(a, trans()),
                bandwidth_upper_op(a, trans()), alpha, begin_value(a),
                stride_major(a), begin_value(x), stride(x), beta,
                begin_value(y), stride(y) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the gbmv_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gbmv. Its overload differs for
// * VectorY&
//
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename gbmv_impl< typename value< MatrixA >::type >::return_type
gbmv( const typename value< MatrixA >::type alpha, const MatrixA& a,
        const VectorX& x, const typename value< MatrixA >::type beta,
        VectorY& y ) {
    gbmv_impl< typename value< MatrixA >::type >::invoke( alpha, a, x,
            beta, y );
}

//
// Overloaded function for gbmv. Its overload differs for
// * const VectorY&
//
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename gbmv_impl< typename value< MatrixA >::type >::return_type
gbmv( const typename value< MatrixA >::type alpha, const MatrixA& a,
        const VectorX& x, const typename value< MatrixA >::type beta,
        const VectorY& y ) {
    gbmv_impl< typename value< MatrixA >::type >::invoke( alpha, a, x,
            beta, y );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

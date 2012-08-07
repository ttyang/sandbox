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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_SYR_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_SYR_HPP

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
inline void syr( const Order, const UpLo, const int n, const float alpha,
        const float* x, const int incx, float* a, const int lda ) {
    cblas_ssyr( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            alpha, x, incx, a, lda );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void syr( const Order, const UpLo, const int n, const double alpha,
        const double* x, const int incx, double* a, const int lda ) {
    cblas_dsyr( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            alpha, x, incx, a, lda );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void syr( const Order, const UpLo, const int n, const float alpha,
        const float* x, const int incx, float* a, const int lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasSsyr( blas_option< UpLo >::value, n, alpha, x, incx, a, lda );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void syr( const Order, const UpLo, const int n, const double alpha,
        const double* x, const int incx, double* a, const int lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasDsyr( blas_option< UpLo >::value, n, alpha, x, incx, a, lda );
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo >
inline void syr( const Order, const UpLo, const fortran_int_t n,
        const float alpha, const float* x, const fortran_int_t incx, float* a,
        const fortran_int_t lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_SSYR( &blas_option< UpLo >::value, &n, &alpha, x, &incx, a, &lda );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo >
inline void syr( const Order, const UpLo, const fortran_int_t n,
        const double alpha, const double* x, const fortran_int_t incx,
        double* a, const fortran_int_t lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_DSYR( &blas_option< UpLo >::value, &n, &alpha, x, &incx, a, &lda );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to syr.
//
template< typename Value >
struct syr_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void result_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX, typename MatrixA >
    static result_type invoke( const real_type alpha, const VectorX& x,
            MatrixA& a ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_order< MatrixA >::type order;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const<
                typename bindings::value_type< VectorX >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixA >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        detail::syr( order(), uplo(), bindings::size_column(a), alpha,
                bindings::begin_value(x), bindings::stride(x),
                bindings::begin_value(a), bindings::stride_major(a) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the syr_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for syr. Its overload differs for
//
template< typename VectorX, typename MatrixA >
inline typename syr_impl< typename bindings::value_type<
        VectorX >::type >::result_type
syr( const typename remove_imaginary< typename bindings::value_type<
        VectorX >::type >::type alpha, const VectorX& x, MatrixA& a ) {
    syr_impl< typename bindings::value_type<
            VectorX >::type >::invoke( alpha, x, a );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

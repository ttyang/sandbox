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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GERC_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GERC_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_order.hpp>
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
// * complex<float> value-type.
//
template< typename Order >
inline void gerc( Order, const int m, const int n,
        const std::complex<float> alpha, const std::complex<float>* x,
        const int incx, const std::complex<float>* y, const int incy,
        std::complex<float>* a, const int lda ) {
    cblas_cgerc( cblas_option< Order >::value, m, n, &alpha, x, incx, y, incy,
            a, lda );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order >
inline void gerc( Order, const int m, const int n,
        const std::complex<double> alpha, const std::complex<double>* x,
        const int incx, const std::complex<double>* y, const int incy,
        std::complex<double>* a, const int lda ) {
    cblas_zgerc( cblas_option< Order >::value, m, n, &alpha, x, incx, y, incy,
            a, lda );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order >
inline void gerc( Order, const int m, const int n,
        const std::complex<float> alpha, const std::complex<float>* x,
        const int incx, const std::complex<float>* y, const int incy,
        std::complex<float>* a, const int lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    cublasCgerc( m, n, alpha, x, incx, y, incy, a, lda );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order >
inline void gerc( Order, const int m, const int n,
        const std::complex<double> alpha, const std::complex<double>* x,
        const int incx, const std::complex<double>* y, const int incy,
        std::complex<double>* a, const int lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order >
inline void gerc( Order, const fortran_int_t m, const fortran_int_t n,
        const std::complex<float> alpha, const std::complex<float>* x,
        const fortran_int_t incx, const std::complex<float>* y,
        const fortran_int_t incy, std::complex<float>* a,
        const fortran_int_t lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_CGERC( &m, &n, &alpha, x, &incx, y, &incy, a, &lda );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order >
inline void gerc( Order, const fortran_int_t m, const fortran_int_t n,
        const std::complex<double> alpha, const std::complex<double>* x,
        const fortran_int_t incx, const std::complex<double>* y,
        const fortran_int_t incy, std::complex<double>* a,
        const fortran_int_t lda ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    BLAS_ZGERC( &m, &n, &alpha, x, &incx, y, &incy, a, &lda );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gerc.
//
template< typename Value >
struct gerc_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX, typename VectorY, typename MatrixA >
    static return_type invoke( const value_type alpha, const VectorX& x,
            const VectorY& y, MatrixA& a ) {
        typedef typename result_of::data_order< MatrixA >::type order;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                VectorX >::type >::type, typename remove_const<
                typename value< VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                VectorX >::type >::type, typename remove_const<
                typename value< MatrixA >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        detail::gerc( order(), size_row(a), size_column(a), alpha,
                begin_value(x), stride(x), begin_value(y), stride(y),
                begin_value(a), stride_major(a) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the gerc_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gerc. Its overload differs for
// * MatrixA&
//
template< typename VectorX, typename VectorY, typename MatrixA >
inline typename gerc_impl< typename value< VectorX >::type >::return_type
gerc( const typename value< VectorX >::type alpha, const VectorX& x,
        const VectorY& y, MatrixA& a ) {
    gerc_impl< typename value< VectorX >::type >::invoke( alpha, x, y,
            a );
}

//
// Overloaded function for gerc. Its overload differs for
// * const MatrixA&
//
template< typename VectorX, typename VectorY, typename MatrixA >
inline typename gerc_impl< typename value< VectorX >::type >::return_type
gerc( const typename value< VectorX >::type alpha, const VectorX& x,
        const VectorY& y, const MatrixA& a ) {
    gerc_impl< typename value< VectorX >::type >::invoke( alpha, x, y,
            a );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

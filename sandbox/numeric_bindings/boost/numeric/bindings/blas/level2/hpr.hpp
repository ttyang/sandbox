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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPR_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPR_HPP

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
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline void hpr( Order, UpLo, int n, float alpha,
        const std::complex<float>* x, int incx, std::complex<float>* ap ) {
    cblas_chpr( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            alpha, x, incx, ap );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline void hpr( Order, UpLo, int n, double alpha,
        const std::complex<double>* x, int incx, std::complex<double>* ap ) {
    cblas_zhpr( cblas_option< Order >::value, cblas_option< UpLo >::value, n,
            alpha, x, incx, ap );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline void hpr( Order, UpLo, int n, float alpha,
        const std::complex<float>* x, int incx, std::complex<float>* ap ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasChpr( blas_option< UpLo >::value, n, alpha, x, incx, ap );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline void hpr( Order, UpLo, int n, double alpha,
        const std::complex<double>* x, int incx, std::complex<double>* ap ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline void hpr( Order, UpLo, fortran_int_t n, float alpha,
        const std::complex<float>* x, fortran_int_t incx,
        std::complex<float>* ap ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_CHPR( &blas_option< UpLo >::value, &n, &alpha, x, &incx, ap );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline void hpr( Order, UpLo, fortran_int_t n, double alpha,
        const std::complex<double>* x, fortran_int_t incx,
        std::complex<double>* ap ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_ZHPR( &blas_option< UpLo >::value, &n, &alpha, x, &incx, ap );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hpr.
//
template< typename Value >
struct hpr_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX, typename MatrixAP >
    static return_type invoke( const real_type alpha, const VectorX& x,
            MatrixAP& ap ) {
        typedef typename result_of::data_order< MatrixAP >::type order;
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                VectorX >::type >::type, typename remove_const<
                typename value< MatrixAP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAP >::value) );
        BOOST_ASSERT( size_minor(ap) == 1 || stride_minor(ap) == 1 );
        detail::hpr( order(), uplo(), size_column(ap), alpha,
                begin_value(x), stride(x), begin_value(ap) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the hpr_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hpr. Its overload differs for
// * MatrixAP&
//
template< typename VectorX, typename MatrixAP >
inline typename hpr_impl< typename value< VectorX >::type >::return_type
hpr( const typename remove_imaginary< typename value<
        VectorX >::type >::type alpha, const VectorX& x, MatrixAP& ap ) {
    hpr_impl< typename value< VectorX >::type >::invoke( alpha, x, ap );
}

//
// Overloaded function for hpr. Its overload differs for
// * const MatrixAP&
//
template< typename VectorX, typename MatrixAP >
inline typename hpr_impl< typename value< VectorX >::type >::return_type
hpr( const typename remove_imaginary< typename value<
        VectorX >::type >::type alpha, const VectorX& x, const MatrixAP& ap ) {
    hpr_impl< typename value< VectorX >::type >::invoke( alpha, x, ap );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_SCAL_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_SCAL_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
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
// * float value-type.
//
inline void scal( const std::ptrdiff_t n, const float a, float* x,
        const std::ptrdiff_t incx ) {
    cblas_sscal( n, a, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
inline void scal( const std::ptrdiff_t n, const double a, double* x,
        const std::ptrdiff_t incx ) {
    cblas_dscal( n, a, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
inline void scal( const std::ptrdiff_t n, const std::complex<float> a,
        std::complex<float>* x, const std::ptrdiff_t incx ) {
    cblas_cscal( n, &a, x, incx );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
inline void scal( const std::ptrdiff_t n, const std::complex<double> a,
        std::complex<double>* x, const std::ptrdiff_t incx ) {
    cblas_zscal( n, &a, x, incx );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
inline void scal( const std::ptrdiff_t n, const float a, float* x,
        const std::ptrdiff_t incx ) {
    cublasSscal( n, a, x, incx );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
inline void scal( const std::ptrdiff_t n, const double a, double* x,
        const std::ptrdiff_t incx ) {
    cublasDscal( n, a, x, incx );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
inline void scal( const std::ptrdiff_t n, const std::complex<float> a,
        std::complex<float>* x, const std::ptrdiff_t incx ) {
    cublasCscal( n, a, x, incx );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
inline void scal( const std::ptrdiff_t n, const std::complex<double> a,
        std::complex<double>* x, const std::ptrdiff_t incx ) {
    cublasZscal( n, a, x, incx );
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
inline void scal( const std::ptrdiff_t n, const float a, float* x,
        const std::ptrdiff_t incx ) {
    BLAS_SSCAL( &n, &a, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
inline void scal( const std::ptrdiff_t n, const double a, double* x,
        const std::ptrdiff_t incx ) {
    BLAS_DSCAL( &n, &a, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
inline void scal( const std::ptrdiff_t n, const std::complex<float> a,
        std::complex<float>* x, const std::ptrdiff_t incx ) {
    BLAS_CSCAL( &n, &a, x, &incx );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
inline void scal( const std::ptrdiff_t n, const std::complex<double> a,
        std::complex<double>* x, const std::ptrdiff_t incx ) {
    BLAS_ZSCAL( &n, &a, x, &incx );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to scal.
//
template< typename Value >
struct scal_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX >
    static return_type invoke( const value_type a, VectorX& x ) {
        BOOST_STATIC_ASSERT( (is_mutable< VectorX >::value ) );
        detail::scal( size(x), a, begin_value(x), stride(x) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the scal_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for scal. Its overload differs for
// * VectorX&
//
template< typename VectorX >
inline typename scal_impl< typename value< VectorX >::type >::return_type
scal( const typename value< VectorX >::type a, VectorX& x ) {
    scal_impl< typename value< VectorX >::type >::invoke( a, x );
}

//
// Overloaded function for scal. Its overload differs for
// * const VectorX&
//
template< typename VectorX >
inline typename scal_impl< typename value< VectorX >::type >::return_type
scal( const typename value< VectorX >::type a, const VectorX& x ) {
    scal_impl< typename value< VectorX >::type >::invoke( a, x );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

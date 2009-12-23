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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_DOTC_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_DOTC_HPP

#include <boost/assert.hpp>
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
// * CBLAS backend
// * complex<float> value-type
//
template< typename Order >
inline void dotc( Order, const std::ptrdiff_t n, const std::complex<float>* x,
        const std::ptrdiff_t incx, const std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    return cblas_cdotc_sub( cblas_option< Order >::value, n, x, incx, y,
            incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend
// * complex<double> value-type
//
template< typename Order >
inline void dotc( Order, const std::ptrdiff_t n,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double>* y, const std::ptrdiff_t incy ) {
    return cblas_zdotc_sub( cblas_option< Order >::value, n, x, incx, y,
            incy );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend
// * complex<float> value-type
//
template< typename Order >
inline void dotc( Order, const std::ptrdiff_t n, const std::complex<float>* x,
        const std::ptrdiff_t incx, const std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    return cublasCdotc( n, x, incx, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend
// * complex<double> value-type
//
template< typename Order >
inline void dotc( Order, const std::ptrdiff_t n,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double>* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    return // NOT FOUND();
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default)
// * complex<float> value-type
//
template< typename Order >
inline void dotc( Order, const std::ptrdiff_t n, const std::complex<float>* x,
        const std::ptrdiff_t incx, const std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    return BLAS_CDOTC( &n, x, &incx, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default)
// * complex<double> value-type
//
template< typename Order >
inline void dotc( Order, const std::ptrdiff_t n,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double>* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    return BLAS_ZDOTC( &n, x, &incx, y, &incy );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to dotc.
//
template< typename Value >
struct dotc_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef value_type return_type;

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX, typename VectorY >
    static return_type invoke( const VectorX& x, const VectorY& y ) {
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                VectorX >::type >::type, typename remove_const<
                typename value< VectorY >::type >::type >::value) );
        
        return detail::dotc( size(x), begin_value(x), stride(x),
                begin_value(y), stride(y) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the dotc_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for dotc. Its overload differs for
//
template< typename VectorX, typename VectorY >
inline typename dotc_impl< typename value< VectorX >::type >::return_type
dotc( const VectorX& x, const VectorY& y ) {
    return dotc_impl< typename value< VectorX >::type >::invoke( x, y );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

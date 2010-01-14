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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_LARGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_LARGV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for largv is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
inline std::ptrdiff_t largv( const fortran_int_t n, float* x,
        const fortran_int_t incx, float* y, const fortran_int_t incy,
        float* c, const fortran_int_t incc ) {
    fortran_int_t info(0);
    LAPACK_SLARGV( &n, x, &incx, y, &incy, c, &incc );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t largv( const fortran_int_t n, double* x,
        const fortran_int_t incx, double* y, const fortran_int_t incy,
        double* c, const fortran_int_t incc ) {
    fortran_int_t info(0);
    LAPACK_DLARGV( &n, x, &incx, y, &incy, c, &incc );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t largv( const fortran_int_t n, std::complex<float>* x,
        const fortran_int_t incx, std::complex<float>* y,
        const fortran_int_t incy, float* c, const fortran_int_t incc ) {
    fortran_int_t info(0);
    LAPACK_CLARGV( &n, x, &incx, y, &incy, c, &incc );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t largv( const fortran_int_t n, std::complex<double>* x,
        const fortran_int_t incx, std::complex<double>* y,
        const fortran_int_t incy, double* c, const fortran_int_t incc ) {
    fortran_int_t info(0);
    LAPACK_ZLARGV( &n, x, &incx, y, &incy, c, &incc );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to largv.
//
template< typename Value, typename Enable = void >
struct largv_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct largv_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX, typename VectorY, typename VectorC >
    static std::ptrdiff_t invoke( const fortran_int_t n, VectorX& x,
            VectorY& y, VectorC& c ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorX >::type >::type,
                typename remove_const< typename value<
                VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorX >::type >::type,
                typename remove_const< typename value<
                VectorC >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorY >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorC >::value) );
        BOOST_ASSERT( bindings::size(c) >= 1+(n-1)*bindings::stride(c) );
        BOOST_ASSERT( bindings::size(x) >= 1+(n-1)*bindings::stride(x) );
        BOOST_ASSERT( bindings::size(y) >= 1+(n-1)*bindings::stride(y) );
        return detail::largv( n, bindings::begin_value(x),
                bindings::stride(x), bindings::begin_value(y),
                bindings::stride(y), bindings::begin_value(c),
                bindings::stride(c) );
    }

};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct largv_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorX, typename VectorY, typename VectorC >
    static std::ptrdiff_t invoke( const fortran_int_t n, VectorX& x,
            VectorY& y, VectorC& c ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorX >::type >::type,
                typename remove_const< typename value<
                VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorX >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorY >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorC >::value) );
        BOOST_ASSERT( bindings::size(c) >= 1+(n-1)*bindings::stride(c) );
        BOOST_ASSERT( bindings::size(x) >= 1+(n-1)*bindings::stride(x) );
        BOOST_ASSERT( bindings::size(y) >= 1+(n-1)*bindings::stride(y) );
        return detail::largv( n, bindings::begin_value(x),
                bindings::stride(x), bindings::begin_value(y),
                bindings::stride(y), bindings::begin_value(c),
                bindings::stride(c) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the largv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for largv. Its overload differs for
// * VectorX&
// * VectorY&
// * VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, VectorX& x,
        VectorY& y, VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * const VectorX&
// * VectorY&
// * VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, const VectorX& x,
        VectorY& y, VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * VectorX&
// * const VectorY&
// * VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, VectorX& x,
        const VectorY& y, VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * const VectorX&
// * const VectorY&
// * VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, const VectorX& x,
        const VectorY& y, VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * VectorX&
// * VectorY&
// * const VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, VectorX& x,
        VectorY& y, const VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * const VectorX&
// * VectorY&
// * const VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, const VectorX& x,
        VectorY& y, const VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * VectorX&
// * const VectorY&
// * const VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, VectorX& x,
        const VectorY& y, const VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

//
// Overloaded function for largv. Its overload differs for
// * const VectorX&
// * const VectorY&
// * const VectorC&
//
template< typename VectorX, typename VectorY, typename VectorC >
inline std::ptrdiff_t largv( const fortran_int_t n, const VectorX& x,
        const VectorY& y, const VectorC& c ) {
    return largv_impl< typename value< VectorX >::type >::invoke( n, x,
            y, c );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GTSV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GTSV_HPP

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
// The LAPACK-backend for gtsv is the netlib-compatible backend.
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
inline std::ptrdiff_t gtsv( const fortran_int_t n, const fortran_int_t nrhs,
        float* dl, float* d, float* du, float* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_SGTSV( &n, &nrhs, dl, d, du, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gtsv( const fortran_int_t n, const fortran_int_t nrhs,
        double* dl, double* d, double* du, double* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_DGTSV( &n, &nrhs, dl, d, du, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t gtsv( const fortran_int_t n, const fortran_int_t nrhs,
        std::complex<float>* dl, std::complex<float>* d,
        std::complex<float>* du, std::complex<float>* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_CGTSV( &n, &nrhs, dl, d, du, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t gtsv( const fortran_int_t n, const fortran_int_t nrhs,
        std::complex<double>* dl, std::complex<double>* d,
        std::complex<double>* du, std::complex<double>* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_ZGTSV( &n, &nrhs, dl, d, du, b, &ldb, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gtsv.
//
template< typename Value >
struct gtsv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename MatrixB >
    static std::ptrdiff_t invoke( const fortran_int_t n, VectorDL& dl,
            VectorD& d, VectorDU& du, MatrixB& b ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorDL >::type >::type,
                typename remove_const< typename value<
                VectorD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorDL >::type >::type,
                typename remove_const< typename value<
                VectorDU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorDL >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorDL >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorDU >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(d) >= n );
        BOOST_ASSERT( size(dl) >= n-1 );
        BOOST_ASSERT( size(du) >= n-1 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        return detail::gtsv( n, size_column(b), begin_value(dl),
                begin_value(d), begin_value(du), begin_value(b),
                stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gtsv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * VectorD&
// * VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        VectorD& d, VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * VectorD&
// * VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, VectorD& d, VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * const VectorD&
// * VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        const VectorD& d, VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * const VectorD&
// * VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, const VectorD& d, VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * VectorD&
// * const VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        VectorD& d, const VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * VectorD&
// * const VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, VectorD& d, const VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * const VectorD&
// * const VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        const VectorD& d, const VectorDU& du, MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * const VectorD&
// * const VectorDU&
// * MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, const VectorD& d, const VectorDU& du,
        MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * VectorD&
// * VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        VectorD& d, VectorDU& du, const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * VectorD&
// * VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, VectorD& d, VectorDU& du, const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * const VectorD&
// * VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        const VectorD& d, VectorDU& du, const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * const VectorD&
// * VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, const VectorD& d, VectorDU& du,
        const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * VectorD&
// * const VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        VectorD& d, const VectorDU& du, const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * VectorD&
// * const VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, VectorD& d, const VectorDU& du,
        const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * VectorDL&
// * const VectorD&
// * const VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n, VectorDL& dl,
        const VectorD& d, const VectorDU& du, const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

//
// Overloaded function for gtsv. Its overload differs for
// * const VectorDL&
// * const VectorD&
// * const VectorDU&
// * const MatrixB&
//
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline std::ptrdiff_t gtsv( const fortran_int_t n,
        const VectorDL& dl, const VectorD& d, const VectorDU& du,
        const MatrixB& b ) {
    return gtsv_impl< typename value< VectorDL >::type >::invoke( n, dl,
            d, du, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

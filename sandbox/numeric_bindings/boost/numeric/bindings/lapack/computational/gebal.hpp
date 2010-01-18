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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBAL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBAL_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for gebal is the netlib-compatible backend.
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
inline std::ptrdiff_t gebal( const char job, const fortran_int_t n, float* a,
        const fortran_int_t lda, fortran_int_t& ilo, fortran_int_t& ihi,
        float* scale ) {
    fortran_int_t info(0);
    LAPACK_SGEBAL( &job, &n, a, &lda, &ilo, &ihi, scale, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gebal( const char job, const fortran_int_t n, double* a,
        const fortran_int_t lda, fortran_int_t& ilo, fortran_int_t& ihi,
        double* scale ) {
    fortran_int_t info(0);
    LAPACK_DGEBAL( &job, &n, a, &lda, &ilo, &ihi, scale, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t gebal( const char job, const fortran_int_t n,
        std::complex<float>* a, const fortran_int_t lda, fortran_int_t& ilo,
        fortran_int_t& ihi, float* scale ) {
    fortran_int_t info(0);
    LAPACK_CGEBAL( &job, &n, a, &lda, &ilo, &ihi, scale, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t gebal( const char job, const fortran_int_t n,
        std::complex<double>* a, const fortran_int_t lda, fortran_int_t& ilo,
        fortran_int_t& ihi, double* scale ) {
    fortran_int_t info(0);
    LAPACK_ZGEBAL( &job, &n, a, &lda, &ilo, &ihi, scale, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gebal.
//
template< typename Value, typename Enable = void >
struct gebal_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct gebal_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorSCALE >
    static std::ptrdiff_t invoke( const char job, MatrixA& a,
            fortran_int_t& ilo, fortran_int_t& ihi,
            VectorSCALE& scale ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorSCALE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorSCALE >::value) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        return detail::gebal( job, bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a), ilo, ihi,
                bindings::begin_value(scale) );
    }

};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct gebal_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorSCALE >
    static std::ptrdiff_t invoke( const char job, MatrixA& a,
            fortran_int_t& ilo, fortran_int_t& ihi,
            VectorSCALE& scale ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorSCALE >::value) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        return detail::gebal( job, bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a), ilo, ihi,
                bindings::begin_value(scale) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gebal_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gebal. Its overload differs for
// * MatrixA&
// * VectorSCALE&
//
template< typename MatrixA, typename VectorSCALE >
inline std::ptrdiff_t gebal( const char job, MatrixA& a,
        fortran_int_t& ilo, fortran_int_t& ihi, VectorSCALE& scale ) {
    return gebal_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( job, a, ilo, ihi, scale );
}

//
// Overloaded function for gebal. Its overload differs for
// * const MatrixA&
// * VectorSCALE&
//
template< typename MatrixA, typename VectorSCALE >
inline std::ptrdiff_t gebal( const char job, const MatrixA& a,
        fortran_int_t& ilo, fortran_int_t& ihi, VectorSCALE& scale ) {
    return gebal_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( job, a, ilo, ihi, scale );
}

//
// Overloaded function for gebal. Its overload differs for
// * MatrixA&
// * const VectorSCALE&
//
template< typename MatrixA, typename VectorSCALE >
inline std::ptrdiff_t gebal( const char job, MatrixA& a,
        fortran_int_t& ilo, fortran_int_t& ihi,
        const VectorSCALE& scale ) {
    return gebal_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( job, a, ilo, ihi, scale );
}

//
// Overloaded function for gebal. Its overload differs for
// * const MatrixA&
// * const VectorSCALE&
//
template< typename MatrixA, typename VectorSCALE >
inline std::ptrdiff_t gebal( const char job, const MatrixA& a,
        fortran_int_t& ilo, fortran_int_t& ihi,
        const VectorSCALE& scale ) {
    return gebal_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( job, a, ilo, ihi, scale );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

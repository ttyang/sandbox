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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBTRF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBTRF_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for gbtrf is the netlib-compatible backend.
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
inline std::ptrdiff_t gbtrf( const fortran_int_t m, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku, float* ab,
        const fortran_int_t ldab, fortran_int_t* ipiv ) {
    fortran_int_t info(0);
    LAPACK_SGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gbtrf( const fortran_int_t m, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku, double* ab,
        const fortran_int_t ldab, fortran_int_t* ipiv ) {
    fortran_int_t info(0);
    LAPACK_DGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t gbtrf( const fortran_int_t m, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        std::complex<float>* ab, const fortran_int_t ldab,
        fortran_int_t* ipiv ) {
    fortran_int_t info(0);
    LAPACK_CGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t gbtrf( const fortran_int_t m, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        std::complex<double>* ab, const fortran_int_t ldab,
        fortran_int_t* ipiv ) {
    fortran_int_t info(0);
    LAPACK_ZGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gbtrf.
//
template< typename Value >
struct gbtrf_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorIPIV >
    static std::ptrdiff_t invoke( MatrixAB& ab, VectorIPIV& ipiv ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIPIV >::value) );
        BOOST_ASSERT( bindings::bandwidth_lower(ab) >= 0 );
        BOOST_ASSERT( bindings::bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( bindings::size(ipiv) >= std::min<
                std::ptrdiff_t >(bindings::size_row(ab),
                bindings::size_column(ab)) );
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::size_row(ab) >= 0 );
        BOOST_ASSERT( bindings::stride_major(ab) >= 2 );
        return detail::gbtrf( bindings::size_row(ab),
                bindings::size_column(ab), bindings::bandwidth_lower(ab),
                bindings::bandwidth_upper(ab), bindings::begin_value(ab),
                bindings::stride_major(ab), bindings::begin_value(ipiv) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gbtrf_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gbtrf. Its overload differs for
// * MatrixAB&
// * VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( MatrixAB& ab, VectorIPIV& ipiv ) {
    return gbtrf_impl< typename bindings::value_type<
            MatrixAB >::type >::invoke( ab, ipiv );
}

//
// Overloaded function for gbtrf. Its overload differs for
// * const MatrixAB&
// * VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( const MatrixAB& ab, VectorIPIV& ipiv ) {
    return gbtrf_impl< typename bindings::value_type<
            MatrixAB >::type >::invoke( ab, ipiv );
}

//
// Overloaded function for gbtrf. Its overload differs for
// * MatrixAB&
// * const VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( MatrixAB& ab, const VectorIPIV& ipiv ) {
    return gbtrf_impl< typename bindings::value_type<
            MatrixAB >::type >::invoke( ab, ipiv );
}

//
// Overloaded function for gbtrf. Its overload differs for
// * const MatrixAB&
// * const VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( const MatrixAB& ab, const VectorIPIV& ipiv ) {
    return gbtrf_impl< typename bindings::value_type<
            MatrixAB >::type >::invoke( ab, ipiv );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

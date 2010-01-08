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
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

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
// Overloaded function for dispatching to float value-type.
//
inline void gbtrf( fortran_int_t m, fortran_int_t n, fortran_int_t kl,
        fortran_int_t ku, float* ab, fortran_int_t ldab, fortran_int_t* ipiv,
        fortran_int_t& info ) {
    LAPACK_SGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
inline void gbtrf( fortran_int_t m, fortran_int_t n, fortran_int_t kl,
        fortran_int_t ku, double* ab, fortran_int_t ldab, fortran_int_t* ipiv,
        fortran_int_t& info ) {
    LAPACK_DGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
inline void gbtrf( fortran_int_t m, fortran_int_t n, fortran_int_t kl,
        fortran_int_t ku, std::complex<float>* ab, fortran_int_t ldab,
        fortran_int_t* ipiv, fortran_int_t& info ) {
    LAPACK_CGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
inline void gbtrf( fortran_int_t m, fortran_int_t n, fortran_int_t kl,
        fortran_int_t ku, std::complex<double>* ab, fortran_int_t ldab,
        fortran_int_t* ipiv, fortran_int_t& info ) {
    LAPACK_ZGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
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
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorIPIV >
    static void invoke( MatrixAB& ab, VectorIPIV& ipiv,
            fortran_int_t& info ) {
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorIPIV >::value) );
        BOOST_ASSERT( bandwidth_lower(ab) >= 0 );
        BOOST_ASSERT( bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( size(ipiv) >= std::min< std::ptrdiff_t >(size_row(ab),
                size_column(ab)) );
        BOOST_ASSERT( size_column(ab) >= 0 );
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( size_row(ab) >= 0 );
        BOOST_ASSERT( stride_major(ab) >= 2 );
        detail::gbtrf( size_row(ab), size_column(ab), bandwidth_lower(ab),
                bandwidth_upper(ab), begin_value(ab), stride_major(ab),
                begin_value(ipiv), info );
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
    fortran_int_t info(0);
    gbtrf_impl< typename value< MatrixAB >::type >::invoke( ab, ipiv,
            info );
    return info;
}

//
// Overloaded function for gbtrf. Its overload differs for
// * const MatrixAB&
// * VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( const MatrixAB& ab, VectorIPIV& ipiv ) {
    fortran_int_t info(0);
    gbtrf_impl< typename value< MatrixAB >::type >::invoke( ab, ipiv,
            info );
    return info;
}

//
// Overloaded function for gbtrf. Its overload differs for
// * MatrixAB&
// * const VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( MatrixAB& ab, const VectorIPIV& ipiv ) {
    fortran_int_t info(0);
    gbtrf_impl< typename value< MatrixAB >::type >::invoke( ab, ipiv,
            info );
    return info;
}

//
// Overloaded function for gbtrf. Its overload differs for
// * const MatrixAB&
// * const VectorIPIV&
//
template< typename MatrixAB, typename VectorIPIV >
inline std::ptrdiff_t gbtrf( const MatrixAB& ab,
        const VectorIPIV& ipiv ) {
    fortran_int_t info(0);
    gbtrf_impl< typename value< MatrixAB >::type >::invoke( ab, ipiv,
            info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

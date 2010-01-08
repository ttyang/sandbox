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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SPTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SPTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
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
inline void sptrs( char uplo, fortran_int_t n, fortran_int_t nrhs,
        const float* ap, const fortran_int_t* ipiv, float* b,
        fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_SSPTRS( &uplo, &n, &nrhs, ap, ipiv, b, &ldb, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
inline void sptrs( char uplo, fortran_int_t n, fortran_int_t nrhs,
        const double* ap, const fortran_int_t* ipiv, double* b,
        fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_DSPTRS( &uplo, &n, &nrhs, ap, ipiv, b, &ldb, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
inline void sptrs( char uplo, fortran_int_t n, fortran_int_t nrhs,
        const std::complex<float>* ap, const fortran_int_t* ipiv,
        std::complex<float>* b, fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_CSPTRS( &uplo, &n, &nrhs, ap, ipiv, b, &ldb, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
inline void sptrs( char uplo, fortran_int_t n, fortran_int_t nrhs,
        const std::complex<double>* ap, const fortran_int_t* ipiv,
        std::complex<double>* b, fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_ZSPTRS( &uplo, &n, &nrhs, ap, ipiv, b, &ldb, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to sptrs.
//
template< typename Value >
struct sptrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename VectorIPIV, typename MatrixB >
    static void invoke( const char uplo, const fortran_int_t n,
            const MatrixAP& ap, const VectorIPIV& ipiv, MatrixB& b,
            fortran_int_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(ap) >= n*(n+1)/2 );
        BOOST_ASSERT( size(ipiv) >= n );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        detail::sptrs( uplo, n, size_column(b), begin_value(ap),
                begin_value(ipiv), begin_value(b), stride_major(b), info );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the sptrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for sptrs. Its overload differs for
// * MatrixB&
//
template< typename MatrixAP, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t sptrs( const char uplo, const fortran_int_t n,
        const MatrixAP& ap, const VectorIPIV& ipiv, MatrixB& b ) {
    fortran_int_t info(0);
    sptrs_impl< typename value< MatrixAP >::type >::invoke( uplo, n, ap,
            ipiv, b, info );
    return info;
}

//
// Overloaded function for sptrs. Its overload differs for
// * const MatrixB&
//
template< typename MatrixAP, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t sptrs( const char uplo, const fortran_int_t n,
        const MatrixAP& ap, const VectorIPIV& ipiv, const MatrixB& b ) {
    fortran_int_t info(0);
    sptrs_impl< typename value< MatrixAP >::type >::invoke( uplo, n, ap,
            ipiv, b, info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

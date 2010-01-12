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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for gbtrs is the netlib-compatible backend.
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
template< typename Trans >
inline std::ptrdiff_t gbtrs( Trans, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        const fortran_int_t nrhs, const float* ab, const fortran_int_t ldab,
        const fortran_int_t* ipiv, float* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_SGBTRS( &lapack_option< Trans >::value, &n, &kl, &ku, &nrhs, ab,
            &ldab, ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Trans >
inline std::ptrdiff_t gbtrs( Trans, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        const fortran_int_t nrhs, const double* ab, const fortran_int_t ldab,
        const fortran_int_t* ipiv, double* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_DGBTRS( &lapack_option< Trans >::value, &n, &kl, &ku, &nrhs, ab,
            &ldab, ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Trans >
inline std::ptrdiff_t gbtrs( Trans, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        const fortran_int_t nrhs, const std::complex<float>* ab,
        const fortran_int_t ldab, const fortran_int_t* ipiv,
        std::complex<float>* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_CGBTRS( &lapack_option< Trans >::value, &n, &kl, &ku, &nrhs, ab,
            &ldab, ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Trans >
inline std::ptrdiff_t gbtrs( Trans, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        const fortran_int_t nrhs, const std::complex<double>* ab,
        const fortran_int_t ldab, const fortran_int_t* ipiv,
        std::complex<double>* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_ZGBTRS( &lapack_option< Trans >::value, &n, &kl, &ku, &nrhs, ab,
            &ldab, ipiv, b, &ldb, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gbtrs.
//
template< typename Value >
struct gbtrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorIPIV, typename MatrixB >
    static std::ptrdiff_t invoke( const MatrixAB& ab, const VectorIPIV& ipiv,
            MatrixB& b ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bandwidth_lower(ab) >= 0 );
        BOOST_ASSERT( bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( size(ipiv) >= size_column(ab) );
        BOOST_ASSERT( size_column(ab) >= 0 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(ab) >= 2 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,
                size_column(ab)) );
        return detail::gbtrs( trans(), size_column(ab), bandwidth_lower(ab),
                bandwidth_upper(ab), size_column(b), begin_value(ab),
                stride_major(ab), begin_value(ipiv), begin_value(b),
                stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gbtrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gbtrs. Its overload differs for
// * MatrixB&
//
template< typename MatrixAB, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gbtrs( const MatrixAB& ab, const VectorIPIV& ipiv,
        MatrixB& b ) {
    return gbtrs_impl< typename value< MatrixAB >::type >::invoke( ab,
            ipiv, b );
}

//
// Overloaded function for gbtrs. Its overload differs for
// * const MatrixB&
//
template< typename MatrixAB, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gbtrs( const MatrixAB& ab, const VectorIPIV& ipiv,
        const MatrixB& b ) {
    return gbtrs_impl< typename value< MatrixAB >::type >::invoke( ab,
            ipiv, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

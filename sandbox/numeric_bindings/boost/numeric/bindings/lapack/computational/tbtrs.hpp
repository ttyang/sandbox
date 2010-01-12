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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TBTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TBTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
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
// The LAPACK-backend for tbtrs is the netlib-compatible backend.
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
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbtrs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const float* ab, const fortran_int_t ldab,
        float* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_STBTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbtrs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const double* ab, const fortran_int_t ldab,
        double* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_DTBTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbtrs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const std::complex<float>* ab,
        const fortran_int_t ldab, std::complex<float>* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_CTBTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbtrs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const std::complex<double>* ab,
        const fortran_int_t ldab, std::complex<double>* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_ZTBTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tbtrs.
//
template< typename Value >
struct tbtrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename MatrixB >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, MatrixB& b ) {
        typedef typename result_of::trans_tag< MatrixAB, order >::type trans;
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(ab) >= kd+1 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        return detail::tbtrs( uplo, trans(), diag(), n, kd, size_column(b),
                begin_value(ab), stride_major(ab), begin_value(b),
                stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the tbtrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tbtrs. Its overload differs for
// * MatrixB&
//
template< typename MatrixAB, typename MatrixB >
inline std::ptrdiff_t tbtrs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, MatrixB& b ) {
    return tbtrs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b );
}

//
// Overloaded function for tbtrs. Its overload differs for
// * const MatrixB&
//
template< typename MatrixAB, typename MatrixB >
inline std::ptrdiff_t tbtrs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b ) {
    return tbtrs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

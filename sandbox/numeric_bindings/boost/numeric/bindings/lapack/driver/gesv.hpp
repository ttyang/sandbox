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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GESV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GESV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_order.hpp>
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
// The LAPACK-backend for gesv is selected by defining a pre-processor
// variable, which can be one of
// * for ATLAS's CLAPACK, define BOOST_NUMERIC_BINDINGS_LAPACK_CLAPACK
// * netlib-compatible LAPACK is the default
//
#if defined BOOST_NUMERIC_BINDINGS_LAPACK_CLAPACK
#include <boost/numeric/bindings/lapack/detail/clapack.h>
#include <boost/numeric/bindings/lapack/detail/clapack_option.hpp>
#else
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#endif

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

#if defined BOOST_NUMERIC_BINDINGS_LAPACK_CLAPACK
//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * float value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const int n, const int nrhs, float* a,
        const int lda, int* ipiv, float* b, const int ldb ) {
    return clapack_sgesv( clapack_option< Order >::value, n, nrhs, a, lda,
            ipiv, b, ldb );
}

//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * double value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const int n, const int nrhs, double* a,
        const int lda, int* ipiv, double* b, const int ldb ) {
    return clapack_dgesv( clapack_option< Order >::value, n, nrhs, a, lda,
            ipiv, b, ldb );
}

//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * complex<float> value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const int n, const int nrhs,
        std::complex<float>* a, const int lda, int* ipiv,
        std::complex<float>* b, const int ldb ) {
    return clapack_cgesv( clapack_option< Order >::value, n, nrhs, a, lda,
            ipiv, b, ldb );
}

//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * complex<double> value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const int n, const int nrhs,
        std::complex<double>* a, const int lda, int* ipiv,
        std::complex<double>* b, const int ldb ) {
    return clapack_zgesv( clapack_option< Order >::value, n, nrhs, a, lda,
            ipiv, b, ldb );
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const fortran_int_t n,
        const fortran_int_t nrhs, float* a, const fortran_int_t lda,
        fortran_int_t* ipiv, float* b, const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_SGESV( &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const fortran_int_t n,
        const fortran_int_t nrhs, double* a, const fortran_int_t lda,
        fortran_int_t* ipiv, double* b, const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_DGESV( &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const fortran_int_t n,
        const fortran_int_t nrhs, std::complex<float>* a,
        const fortran_int_t lda, fortran_int_t* ipiv, std::complex<float>* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_CGESV( &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Order >
inline std::ptrdiff_t gesv( Order, const fortran_int_t n,
        const fortran_int_t nrhs, std::complex<double>* a,
        const fortran_int_t lda, fortran_int_t* ipiv, std::complex<double>* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_ZGESV( &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    return info;
}

#endif
} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gesv.
//
template< typename Value >
struct gesv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB >
    static std::ptrdiff_t invoke( MatrixA& a, VectorIPIV& ipiv, MatrixB& b ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_order< MatrixA >::type order;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIPIV >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::gesv( order(), bindings::size_column(a),
                bindings::size_column(b), bindings::begin_value(a),
                bindings::stride_major(a), bindings::begin_value(ipiv),
                bindings::begin_value(b), bindings::stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gesv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( MatrixA& a, VectorIPIV& ipiv, MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( const MatrixA& a, VectorIPIV& ipiv,
        MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( MatrixA& a, const VectorIPIV& ipiv,
        MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( const MatrixA& a, const VectorIPIV& ipiv,
        MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * const MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * const MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * const MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

//
// Overloaded function for gesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * const MatrixB&
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline std::ptrdiff_t gesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b ) {
    return gesv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, ipiv, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

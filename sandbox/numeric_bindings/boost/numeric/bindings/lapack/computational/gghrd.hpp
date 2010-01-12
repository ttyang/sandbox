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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGHRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGHRD_HPP

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
// The LAPACK-backend for gghrd is the netlib-compatible backend.
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
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, float* a, const fortran_int_t lda, float* b,
        const fortran_int_t ldb, float* q, const fortran_int_t ldq, float* z,
        const fortran_int_t ldz ) {
    fortran_int_t info(0);
    LAPACK_SGGHRD( &compq, &compz, &n, &ilo, &ihi, a, &lda, b, &ldb, q, &ldq,
            z, &ldz, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, double* a, const fortran_int_t lda,
        double* b, const fortran_int_t ldb, double* q,
        const fortran_int_t ldq, double* z, const fortran_int_t ldz ) {
    fortran_int_t info(0);
    LAPACK_DGGHRD( &compq, &compz, &n, &ilo, &ihi, a, &lda, b, &ldb, q, &ldq,
            z, &ldz, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, std::complex<float>* a,
        const fortran_int_t lda, std::complex<float>* b,
        const fortran_int_t ldb, std::complex<float>* q,
        const fortran_int_t ldq, std::complex<float>* z,
        const fortran_int_t ldz ) {
    fortran_int_t info(0);
    LAPACK_CGGHRD( &compq, &compz, &n, &ilo, &ihi, a, &lda, b, &ldb, q, &ldq,
            z, &ldz, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, std::complex<double>* a,
        const fortran_int_t lda, std::complex<double>* b,
        const fortran_int_t ldb, std::complex<double>* q,
        const fortran_int_t ldq, std::complex<double>* z,
        const fortran_int_t ldz ) {
    fortran_int_t info(0);
    LAPACK_ZGGHRD( &compq, &compz, &n, &ilo, &ihi, a, &lda, b, &ldb, q, &ldq,
            z, &ldz, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gghrd.
//
template< typename Value >
struct gghrd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename MatrixQ,
            typename MatrixZ >
    static std::ptrdiff_t invoke( const char compq, const char compz,
            const fortran_int_t n, const fortran_int_t ilo,
            MatrixA& a, MatrixB& b, MatrixQ& q, MatrixZ& z ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixQ >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( compq == 'N' || compq == 'I' || compq == 'V' );
        BOOST_ASSERT( compz == 'N' || compz == 'I' || compz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(q) == 1 || stride_minor(q) == 1 );
        BOOST_ASSERT( size_minor(z) == 1 || stride_minor(z) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        return detail::gghrd( compq, compz, n, ilo, size_column(a),
                begin_value(a), stride_major(a), begin_value(b),
                stride_major(b), begin_value(q), stride_major(q),
                begin_value(z), stride_major(z) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gghrd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        MatrixB& b, MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, MatrixB& b, MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        const MatrixB& b, MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, const MatrixB& b, MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        MatrixB& b, const MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, MatrixB& b, const MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        const MatrixB& b, const MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const MatrixQ&
// * MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, const MatrixB& b, const MatrixQ& q, MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        MatrixB& b, MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, MatrixB& b, MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        const MatrixB& b, MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, const MatrixB& b, MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * MatrixB&
// * const MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        MatrixB& b, const MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * MatrixB&
// * const MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, MatrixB& b, const MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * MatrixA&
// * const MatrixB&
// * const MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo, MatrixA& a,
        const MatrixB& b, const MatrixQ& q, const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

//
// Overloaded function for gghrd. Its overload differs for
// * const MatrixA&
// * const MatrixB&
// * const MatrixQ&
// * const MatrixZ&
//
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline std::ptrdiff_t gghrd( const char compq, const char compz,
        const fortran_int_t n, const fortran_int_t ilo,
        const MatrixA& a, const MatrixB& b, const MatrixQ& q,
        const MatrixZ& z ) {
    return gghrd_impl< typename value< MatrixA >::type >::invoke( compq,
            compz, n, ilo, a, b, q, z );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

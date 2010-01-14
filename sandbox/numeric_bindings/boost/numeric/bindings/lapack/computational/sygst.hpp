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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SYGST_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SYGST_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for sygst is the netlib-compatible backend.
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
template< typename UpLo >
inline std::ptrdiff_t sygst( const fortran_int_t itype, UpLo,
        const fortran_int_t n, float* a, const fortran_int_t lda,
        const float* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_SSYGST( &itype, &lapack_option< UpLo >::value, &n, a, &lda, b,
            &ldb, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t sygst( const fortran_int_t itype, UpLo,
        const fortran_int_t n, double* a, const fortran_int_t lda,
        const double* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_DSYGST( &itype, &lapack_option< UpLo >::value, &n, a, &lda, b,
            &ldb, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to sygst.
//
template< typename Value >
struct sygst_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB >
    static std::ptrdiff_t invoke( const fortran_int_t itype, MatrixA& a,
            const MatrixB& b ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::sygst( itype, uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(b), bindings::stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the sygst_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for sygst. Its overload differs for
// * MatrixA&
//
template< typename MatrixA, typename MatrixB >
inline std::ptrdiff_t sygst( const fortran_int_t itype, MatrixA& a,
        const MatrixB& b ) {
    return sygst_impl< typename value< MatrixA >::type >::invoke( itype,
            a, b );
}

//
// Overloaded function for sygst. Its overload differs for
// * const MatrixA&
//
template< typename MatrixA, typename MatrixB >
inline std::ptrdiff_t sygst( const fortran_int_t itype,
        const MatrixA& a, const MatrixB& b ) {
    return sygst_impl< typename value< MatrixA >::type >::invoke( itype,
            a, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

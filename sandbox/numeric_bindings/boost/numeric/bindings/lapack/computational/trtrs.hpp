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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
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
template< typename Trans, typename Diag >
inline void trtrs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const float* a, fortran_int_t lda, float* b,
        fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_STRTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
template< typename Trans, typename Diag >
inline void trtrs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const double* a, fortran_int_t lda, double* b,
        fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_DTRTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
template< typename Trans, typename Diag >
inline void trtrs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const std::complex<float>* a, fortran_int_t lda,
        std::complex<float>* b, fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_CTRTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
template< typename Trans, typename Diag >
inline void trtrs( char uplo, Trans, Diag, fortran_int_t n,
        fortran_int_t nrhs, const std::complex<double>* a, fortran_int_t lda,
        std::complex<double>* b, fortran_int_t ldb, fortran_int_t& info ) {
    LAPACK_ZTRTRS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &nrhs, a, &lda, b, &ldb, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trtrs.
//
template< typename Value >
struct trtrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB >
    static void invoke( const char uplo, const MatrixA& a, MatrixB& b,
            fortran_int_t& info ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_column_op(a, trans()) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,
                size_column_op(a, trans())) );
        detail::trtrs( uplo, trans(), diag(), size_column_op(a, trans()),
                size_column(b), begin_value(a), stride_major(a),
                begin_value(b), stride_major(b), info );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the trtrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trtrs. Its overload differs for
// * MatrixB&
//
template< typename MatrixA, typename MatrixB >
inline std::ptrdiff_t trtrs( const char uplo, const MatrixA& a,
        MatrixB& b ) {
    fortran_int_t info(0);
    trtrs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b,
            info );
    return info;
}

//
// Overloaded function for trtrs. Its overload differs for
// * const MatrixB&
//
template< typename MatrixA, typename MatrixB >
inline std::ptrdiff_t trtrs( const char uplo, const MatrixA& a,
        const MatrixB& b ) {
    fortran_int_t info(0);
    trtrs_impl< typename value< MatrixA >::type >::invoke( uplo, a, b,
            info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

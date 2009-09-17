//
// Copyright (c) 2003--2009
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SYTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SYTRS_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void sytrs( const char uplo, const integer_t n,
            const integer_t nrhs, const float* a, const integer_t lda,
            const integer_t* ipiv, float* b, const integer_t ldb,
            integer_t& info ) {
        LAPACK_SSYTRS( &uplo, &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    }
    inline void sytrs( const char uplo, const integer_t n,
            const integer_t nrhs, const double* a, const integer_t lda,
            const integer_t* ipiv, double* b, const integer_t ldb,
            integer_t& info ) {
        LAPACK_DSYTRS( &uplo, &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    }
    inline void sytrs( const char uplo, const integer_t n,
            const integer_t nrhs, const traits::complex_f* a,
            const integer_t lda, const integer_t* ipiv, traits::complex_f* b,
            const integer_t ldb, integer_t& info ) {
        LAPACK_CSYTRS( &uplo, &n, &nrhs, traits::complex_ptr(a), &lda, ipiv,
                traits::complex_ptr(b), &ldb, &info );
    }
    inline void sytrs( const char uplo, const integer_t n,
            const integer_t nrhs, const traits::complex_d* a,
            const integer_t lda, const integer_t* ipiv, traits::complex_d* b,
            const integer_t ldb, integer_t& info ) {
        LAPACK_ZSYTRS( &uplo, &n, &nrhs, traits::complex_ptr(a), &lda, ipiv,
                traits::complex_ptr(b), &ldb, &info );
    }
}

// value-type based template
template< typename ValueType >
struct sytrs_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorIPIV, typename MatrixB >
    static void invoke( const char uplo, const MatrixA& a,
            const VectorIPIV& ipiv, MatrixB& b, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(ipiv) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::sytrs( uplo, traits::matrix_num_columns(a),
                traits::matrix_num_columns(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(ipiv),
                traits::matrix_storage(b), traits::leading_dimension(b),
                info );
    }
};


// template function to call sytrs
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline integer_t sytrs( const char uplo, const MatrixA& a,
        const VectorIPIV& ipiv, MatrixB& b ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    sytrs_impl< value_type >::invoke( uplo, a, ipiv, b, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

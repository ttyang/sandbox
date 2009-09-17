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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_SYR2K_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_SYR2K_HPP

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/blas/detail/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {
namespace level3 {

// overloaded functions to call blas
namespace detail {
    inline void syr2k( const char uplo, const char trans, const integer_t n,
            const integer_t k, const float alpha, const float* a,
            const integer_t lda, const float* b, const integer_t ldb,
            const float beta, float* c, const integer_t ldc ) {
        BLAS_SSYR2K( &uplo, &trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta,
                c, &ldc );
    }
    inline void syr2k( const char uplo, const char trans, const integer_t n,
            const integer_t k, const double alpha, const double* a,
            const integer_t lda, const double* b, const integer_t ldb,
            const double beta, double* c, const integer_t ldc ) {
        BLAS_DSYR2K( &uplo, &trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta,
                c, &ldc );
    }
    inline void syr2k( const char uplo, const char trans, const integer_t n,
            const integer_t k, const traits::complex_f alpha,
            const traits::complex_f* a, const integer_t lda,
            const traits::complex_f* b, const integer_t ldb,
            const traits::complex_f beta, traits::complex_f* c,
            const integer_t ldc ) {
        BLAS_CSYR2K( &uplo, &trans, &n, &k, traits::complex_ptr(&alpha),
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                traits::complex_ptr(&beta), traits::complex_ptr(c), &ldc );
    }
    inline void syr2k( const char uplo, const char trans, const integer_t n,
            const integer_t k, const traits::complex_d alpha,
            const traits::complex_d* a, const integer_t lda,
            const traits::complex_d* b, const integer_t ldb,
            const traits::complex_d beta, traits::complex_d* c,
            const integer_t ldc ) {
        BLAS_ZSYR2K( &uplo, &trans, &n, &k, traits::complex_ptr(&alpha),
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                traits::complex_ptr(&beta), traits::complex_ptr(c), &ldc );
    }
}

// value-type based template
template< typename ValueType >
struct syr2k_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename MatrixB, typename MatrixC >
    static return_type invoke( const char trans, const value_type alpha,
            const MatrixA& a, const MatrixB& b, const value_type beta,
            MatrixC& c ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixC >::value_type >::value) );
        detail::syr2k( traits::matrix_uplo_tag(c), trans,
                traits::matrix_num_columns(c),
                (trans=='N'?traits::matrix_num_columns(a),
                traits::matrix_num_rows(a)), alpha, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), beta, traits::matrix_storage(c),
                traits::leading_dimension(c) );
    }
};

// low-level template function for direct calls to level3::syr2k
template< typename MatrixA, typename MatrixB, typename MatrixC >
inline typename syr2k_impl< typename traits::matrix_traits<
        MatrixA >::value_type >::return_type
syr2k( const char trans, const typename traits::matrix_traits<
        MatrixA >::value_type alpha, const MatrixA& a, const MatrixB& b,
        const typename traits::matrix_traits< MatrixA >::value_type beta,
        MatrixC& c ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    syr2k_impl< value_type >::invoke( trans, alpha, a, b, beta, c );
}

}}}}} // namespace boost::numeric::bindings::blas::level3

#endif

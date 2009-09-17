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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_TRSM_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL3_TRSM_HPP

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
    inline void trsm( const char side, const char uplo, const char transa,
            const char diag, const integer_t m, const integer_t n,
            const float alpha, float const* a, const integer_t lda, float* b,
            const integer_t ldb ) {
        BLAS_STRSM( &side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b,
                &ldb );
    }
    inline void trsm( const char side, const char uplo, const char transa,
            const char diag, const integer_t m, const integer_t n,
            const double alpha, double const* a, const integer_t lda,
            double* b, const integer_t ldb ) {
        BLAS_DTRSM( &side, &uplo, &transa, &diag, &m, &n, &alpha, a, &lda, b,
                &ldb );
    }
    inline void trsm( const char side, const char uplo, const char transa,
            const char diag, const integer_t m, const integer_t n,
            const traits::complex_f alpha, traits::complex_f const* a,
            const integer_t lda, traits::complex_f* b, const integer_t ldb ) {
        BLAS_CTRSM( &side, &uplo, &transa, &diag, &m, &n,
                traits::complex_ptr(&alpha), traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb );
    }
    inline void trsm( const char side, const char uplo, const char transa,
            const char diag, const integer_t m, const integer_t n,
            const traits::complex_d alpha, traits::complex_d const* a,
            const integer_t lda, traits::complex_d* b, const integer_t ldb ) {
        BLAS_ZTRSM( &side, &uplo, &transa, &diag, &m, &n,
                traits::complex_ptr(&alpha), traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb );
    }
}

// value-type based template
template< typename ValueType >
struct trsm_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename MatrixB >
    static return_type invoke( const char side, const char transa,
            const char diag, const value_type alpha, const MatrixA& a,
            MatrixB& b ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        detail::trsm( side, traits::matrix_uplo_tag(a), transa, diag,
                traits::matrix_num_rows(b), traits::matrix_num_columns(b),
                alpha, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b) );
    }
};

// low-level template function for direct calls to level3::trsm
template< typename MatrixA, typename MatrixB >
inline typename trsm_impl< typename traits::matrix_traits<
        MatrixA >::value_type >::return_type
trsm( const char side, const char transa, const char diag,
        const typename traits::matrix_traits< MatrixA >::value_type alpha,
        const MatrixA& a, MatrixB& b ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    trsm_impl< value_type >::invoke( side, transa, diag, alpha, a, b );
}

}}}}} // namespace boost::numeric::bindings::blas::level3

#endif

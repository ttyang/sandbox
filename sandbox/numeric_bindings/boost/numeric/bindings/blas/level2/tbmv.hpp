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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_TBMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_TBMV_HPP

#include <boost/numeric/bindings/blas/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//$DESCRIPTION

// overloaded functions to call blas
namespace detail {
    inline void tbmv( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const k, float* a,
            integer_t const lda, float* x, integer_t const incx ) {
        BLAS_STBMV( &uplo, &trans, &diag, &n, &k, a, &lda, x, &incx );
    }
    inline void tbmv( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const k, double* a,
            integer_t const lda, double* x, integer_t const incx ) {
        BLAS_DTBMV( &uplo, &trans, &diag, &n, &k, a, &lda, x, &incx );
    }
    inline void tbmv( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const k, traits::complex_f* a,
            integer_t const lda, traits::complex_f* x, integer_t const incx ) {
        BLAS_CTBMV( &uplo, &trans, &diag, &n, &k, traits::complex_ptr(a),
                &lda, traits::complex_ptr(x), &incx );
    }
    inline void tbmv( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const k, traits::complex_d* a,
            integer_t const lda, traits::complex_d* x, integer_t const incx ) {
        BLAS_ZTBMV( &uplo, &trans, &diag, &n, &k, traits::complex_ptr(a),
                &lda, traits::complex_ptr(x), &incx );
    }
}

// value-type based template
template< typename ValueType >
struct tbmv_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename VectorX >
    static return_type compute( char const uplo, char const trans,
            char const diag, integer_t const k, MatrixA& a, VectorX& x ) {
        detail::tbmv( uplo, trans, diag, traits::matrix_size2(a), k,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(x), traits::vector_stride(x) );
    }
};

// template function to call tbmv
template< typename MatrixA, typename VectorX >
inline integer_t tbmv( char const uplo, char const trans,
        char const diag, integer_t const k, MatrixA& a, VectorX& x ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    tbmv_impl< value_type >::compute( uplo, trans, diag, k, a, x );
}


}}}} // namespace boost::numeric::bindings::blas

#endif

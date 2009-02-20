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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_HERK_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_HERK_HPP

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
    inline void herk( char const uplo, char const trans, integer_t const n,
            integer_t const k, float const alpha, traits::complex_f* a,
            integer_t const lda, float const beta, traits::complex_f* c,
            integer_t const ldc ) {
        BLAS_CHERK( &uplo, &trans, &n, &k, &alpha, traits::complex_ptr(a),
                &lda, &beta, traits::complex_ptr(c), &ldc );
    }
    inline void herk( char const uplo, char const trans, integer_t const n,
            integer_t const k, double const alpha, traits::complex_d* a,
            integer_t const lda, double const beta, traits::complex_d* c,
            integer_t const ldc ) {
        BLAS_ZHERK( &uplo, &trans, &n, &k, &alpha, traits::complex_ptr(a),
                &lda, &beta, traits::complex_ptr(c), &ldc );
    }
}

// value-type based template
template< typename ValueType >
struct herk_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename MatrixC >
    static return_type compute( char const uplo, char const trans,
            integer_t const k, real_type const alpha, MatrixA& a,
            real_type const beta, MatrixC& c ) {
        detail::herk( uplo, trans, traits::matrix_size2(c), k, alpha,
                traits::matrix_storage(a), traits::leading_dimension(a), beta,
                traits::matrix_storage(c), traits::leading_dimension(c) );
    }
};

// template function to call herk
template< typename MatrixA, typename MatrixC >
inline integer_t herk( char const uplo, char const trans,
        integer_t const k,
        typename traits::matrix_traits< MatrixA >::value_type const alpha,
        MatrixA& a,
        typename traits::matrix_traits< MatrixA >::value_type const beta,
        MatrixC& c ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    herk_impl< value_type >::compute( uplo, trans, k, alpha, a, beta,
            c );
}


}}}} // namespace boost::numeric::bindings::blas

#endif

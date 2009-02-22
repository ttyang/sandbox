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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_SYMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_SYMV_HPP

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
    inline void symv( char const uplo, integer_t const n, float const alpha,
            float* a, integer_t const lda, float* x, integer_t const incx,
            float const beta, float* y, integer_t const incy ) {
        BLAS_SSYMV( &uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy );
    }
    inline void symv( char const uplo, integer_t const n, double const alpha,
            double* a, integer_t const lda, double* x, integer_t const incx,
            double const beta, double* y, integer_t const incy ) {
        BLAS_DSYMV( &uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy );
    }
}

// value-type based template
template< typename ValueType >
struct symv_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type compute( real_type const alpha, MatrixA& a, VectorX& x,
            real_type const beta, VectorY& y ) {
        detail::symv( traits::matrix_uplo_tag(a),
                traits::matrix_size2(a), alpha, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(x),
                traits::vector_stride(x), beta, traits::vector_storage(y),
                traits::vector_stride(y) );
    }
};

// template function to call symv
template< typename MatrixA, typename VectorX, typename VectorY >

        inline integer_t symv( typename traits::matrix_traits< MatrixA >::value_type const alpha,
        MatrixA& a, VectorX& x,
        typename traits::matrix_traits< MatrixA >::value_type const beta,
        VectorY& y ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    symv_impl< value_type >::compute( alpha, a, x, beta, y );
}


}}}} // namespace boost::numeric::bindings::blas

#endif

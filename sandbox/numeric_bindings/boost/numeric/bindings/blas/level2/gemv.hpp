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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_GEMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_GEMV_HPP

#include <boost/numeric/bindings/blas/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//$DESCRIPTION

// overloaded functions to call blas
namespace detail {
    inline void gemv( char const trans, integer_t const m, integer_t const n,
            float const alpha, float* a, integer_t const lda, float* x,
            integer_t const incx, float const beta, float* y,
            integer_t const incy ) {
        BLAS_SGEMV( &trans, &m, &n, &alpha, a, &lda, x, &incx, &beta, y,
                &incy );
    }
    inline void gemv( char const trans, integer_t const m, integer_t const n,
            double const alpha, double* a, integer_t const lda, double* x,
            integer_t const incx, double const beta, double* y,
            integer_t const incy ) {
        BLAS_DGEMV( &trans, &m, &n, &alpha, a, &lda, x, &incx, &beta, y,
                &incy );
    }
    inline void gemv( char const trans, integer_t const m, integer_t const n,
            traits::complex_f const alpha, traits::complex_f* a,
            integer_t const lda, traits::complex_f* x, integer_t const incx,
            traits::complex_f const beta, traits::complex_f* y,
            integer_t const incy ) {
        BLAS_CGEMV( &trans, &m, &n, traits::complex_ptr(&alpha),
                traits::complex_ptr(a), &lda, traits::complex_ptr(x), &incx,
                traits::complex_ptr(&beta), traits::complex_ptr(y), &incy );
    }
    inline void gemv( char const trans, integer_t const m, integer_t const n,
            traits::complex_d const alpha, traits::complex_d* a,
            integer_t const lda, traits::complex_d* x, integer_t const incx,
            traits::complex_d const beta, traits::complex_d* y,
            integer_t const incy ) {
        BLAS_ZGEMV( &trans, &m, &n, traits::complex_ptr(&alpha),
                traits::complex_ptr(a), &lda, traits::complex_ptr(x), &incx,
                traits::complex_ptr(&beta), traits::complex_ptr(y), &incy );
    }
}

// value-type based template
template< typename ValueType >
struct gemv_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type compute( char const trans, value_type const alpha,
            MatrixA& a, VectorX& x, value_type const beta, VectorY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        detail::gemv( trans, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), alpha,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(x), traits::vector_stride(x), beta,
                traits::vector_storage(y), traits::vector_stride(y) );
    }
};

// template function to call gemv
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename gemv_impl< typename traits::matrix_traits<
        MatrixA >::value_type >::return_type
gemv( char const trans, typename traits::matrix_traits<
        MatrixA >::value_type const alpha, MatrixA& a, VectorX& x,
        typename traits::matrix_traits< MatrixA >::value_type const beta,
        VectorY& y ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    gemv_impl< value_type >::compute( trans, alpha, a, x, beta, y );
}

}}}} // namespace boost::numeric::bindings::blas

#endif

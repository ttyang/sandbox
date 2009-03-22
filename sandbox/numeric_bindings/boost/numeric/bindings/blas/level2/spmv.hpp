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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_SPMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_SPMV_HPP

#include <boost/numeric/bindings/blas/detail/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {
namespace level2 {

// overloaded functions to call blas
namespace detail {
    inline void spmv( char const uplo, integer_t const n, float const alpha,
            float* ap, float* x, integer_t const incx, float const beta,
            float* y, integer_t const incy ) {
        BLAS_SSPMV( &uplo, &n, &alpha, ap, x, &incx, &beta, y, &incy );
    }
    inline void spmv( char const uplo, integer_t const n, double const alpha,
            double* ap, double* x, integer_t const incx, double const beta,
            double* y, integer_t const incy ) {
        BLAS_DSPMV( &uplo, &n, &alpha, ap, x, &incx, &beta, y, &incy );
    }
}

// value-type based template
template< typename ValueType >
struct spmv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixAP, typename VectorX, typename VectorY >
    static return_type invoke( real_type const alpha, MatrixAP& ap,
            VectorX& x, real_type const beta, VectorY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAP >::value_type, typename traits::vector_traits<
                VectorX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAP >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        detail::spmv( traits::matrix_uplo_tag(ap),
                traits::matrix_num_columns(ap), alpha,
                traits::matrix_storage(ap), traits::vector_storage(x),
                traits::vector_stride(x), beta, traits::vector_storage(y),
                traits::vector_stride(y) );
    }
};

// low-level template function for direct calls to level2::spmv
template< typename MatrixAP, typename VectorX, typename VectorY >
inline typename spmv_impl< typename traits::matrix_traits<
        MatrixAP >::value_type >::return_type
spmv( typename traits::matrix_traits<
        MatrixAP >::value_type const alpha, MatrixAP& ap, VectorX& x,
        typename traits::matrix_traits< MatrixAP >::value_type const beta,
        VectorY& y ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    spmv_impl< value_type >::invoke( alpha, ap, x, beta, y );
}

}}}}} // namespace boost::numeric::bindings::blas::level2

#endif

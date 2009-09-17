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
namespace level2 {

// overloaded functions to call blas
namespace detail {
    inline void spmv( const char uplo, const integer_t n, const float alpha,
            float const* ap, float const* x, const integer_t incx,
            const float beta, float* y, const integer_t incy ) {
        BLAS_SSPMV( &uplo, &n, &alpha, ap, x, &incx, &beta, y, &incy );
    }
    inline void spmv( const char uplo, const integer_t n, const double alpha,
            double const* ap, double const* x, const integer_t incx,
            const double beta, double* y, const integer_t incy ) {
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
    static return_type invoke( const real_type alpha, const MatrixAP& ap,
            const VectorX& x, const real_type beta, VectorY& y ) {
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
spmv( const typename traits::type_traits<
        typename traits::matrix_traits<
        MatrixAP >::value_type >::real_type alpha, const MatrixAP& ap,
        const VectorX& x, const typename traits::type_traits<
        typename traits::matrix_traits<
        MatrixAP >::value_type >::real_type beta, VectorY& y ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    spmv_impl< value_type >::invoke( alpha, ap, x, beta, y );
}

}}}}} // namespace boost::numeric::bindings::blas::level2

#endif

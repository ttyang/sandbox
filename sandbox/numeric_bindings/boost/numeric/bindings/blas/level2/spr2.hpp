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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_SPR2_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_SPR2_HPP

#include <boost/numeric/bindings/blas/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//$DESCRIPTION

// overloaded functions to call blas
namespace detail {
    inline void spr2( char const uplo, integer_t const n, float const alpha,
            float* x, integer_t const incx, float* y, integer_t const incy,
            float* ap ) {
        BLAS_SSPR2( &uplo, &n, &alpha, x, &incx, y, &incy, ap );
    }
    inline void spr2( char const uplo, integer_t const n, double const alpha,
            double* x, integer_t const incx, double* y, integer_t const incy,
            double* ap ) {
        BLAS_DSPR2( &uplo, &n, &alpha, x, &incx, y, &incy, ap );
    }
}

// value-type based template
template< typename ValueType >
struct spr2_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename VectorX, typename VectorY, typename MatrixAP >
    static return_type compute( real_type const alpha, VectorX& x, VectorY& y,
            MatrixAP& ap ) {
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type > );
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::matrix_traits<
                MatrixAP >::value_type > );
        detail::spr2( traits::matrix_uplo_tag(ap),
                traits::matrix_size2(ap), alpha, traits::vector_storage(x),
                traits::vector_stride(x), traits::vector_storage(y),
                traits::vector_stride(y), traits::matrix_storage(ap) );
    }
};

// template function to call spr2
template< typename VectorX, typename VectorY, typename MatrixAP >
inline typename spr2_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
spr2( typename traits::vector_traits< VectorX >::value_type const alpha,
        VectorX& x, VectorY& y, MatrixAP& ap ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    spr2_impl< value_type >::compute( alpha, x, y, ap );
}

}}}} // namespace boost::numeric::bindings::blas

#endif

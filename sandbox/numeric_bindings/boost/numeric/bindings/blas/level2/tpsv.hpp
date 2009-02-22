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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_TPSV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_TPSV_HPP

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
    inline void tpsv( char const uplo, char const trans, char const diag,
            integer_t const n, float* ap, float* x, integer_t const incx ) {
        BLAS_STPSV( &uplo, &trans, &diag, &n, ap, x, &incx );
    }
    inline void tpsv( char const uplo, char const trans, char const diag,
            integer_t const n, double* ap, double* x, integer_t const incx ) {
        BLAS_DTPSV( &uplo, &trans, &diag, &n, ap, x, &incx );
    }
    inline void tpsv( char const uplo, char const trans, char const diag,
            integer_t const n, traits::complex_f* ap, traits::complex_f* x,
            integer_t const incx ) {
        BLAS_CTPSV( &uplo, &trans, &diag, &n, traits::complex_ptr(ap),
                traits::complex_ptr(x), &incx );
    }
    inline void tpsv( char const uplo, char const trans, char const diag,
            integer_t const n, traits::complex_d* ap, traits::complex_d* x,
            integer_t const incx ) {
        BLAS_ZTPSV( &uplo, &trans, &diag, &n, traits::complex_ptr(ap),
                traits::complex_ptr(x), &incx );
    }
}

// value-type based template
template< typename ValueType >
struct tpsv_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixAP, typename VectorX >
    static return_type compute( char const trans, char const diag,
            MatrixAP& ap, VectorX& x ) {
        detail::tpsv( traits::matrix_uplo_tag(ap), trans, diag,
                traits::matrix_size2(ap), traits::matrix_storage(ap),
                traits::vector_storage(x), traits::vector_stride(x) );
    }
};

// template function to call tpsv
template< typename MatrixAP, typename VectorX >
inline integer_t tpsv( char const trans, char const diag, MatrixAP& ap,
        VectorX& x ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    tpsv_impl< value_type >::compute( trans, diag, ap, x );
}


}}}} // namespace boost::numeric::bindings::blas

#endif

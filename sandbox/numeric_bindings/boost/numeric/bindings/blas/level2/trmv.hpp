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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_TRMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_TRMV_HPP

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
    inline void trmv( char const uplo, char const trans, char const diag,
            integer_t const n, float* a, integer_t const lda, float* x,
            integer_t const incx ) {
        BLAS_STRMV( &uplo, &trans, &diag, &n, a, &lda, x, &incx );
    }
    inline void trmv( char const uplo, char const trans, char const diag,
            integer_t const n, double* a, integer_t const lda, double* x,
            integer_t const incx ) {
        BLAS_DTRMV( &uplo, &trans, &diag, &n, a, &lda, x, &incx );
    }
    inline void trmv( char const uplo, char const trans, char const diag,
            integer_t const n, traits::complex_f* a, integer_t const lda,
            traits::complex_f* x, integer_t const incx ) {
        BLAS_CTRMV( &uplo, &trans, &diag, &n, traits::complex_ptr(a), &lda,
                traits::complex_ptr(x), &incx );
    }
    inline void trmv( char const uplo, char const trans, char const diag,
            integer_t const n, traits::complex_d* a, integer_t const lda,
            traits::complex_d* x, integer_t const incx ) {
        BLAS_ZTRMV( &uplo, &trans, &diag, &n, traits::complex_ptr(a), &lda,
                traits::complex_ptr(x), &incx );
    }
}

// value-type based template
template< typename ValueType >
struct trmv_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename MatrixA, typename VectorX >
    static return_type compute( char const trans, char const diag, MatrixA& a,
            VectorX& x ) {
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorX >::value_type > );
        detail::trmv( traits::matrix_uplo_tag(a), trans, diag,
                traits::matrix_size2(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(x),
                traits::vector_stride(x) );
    }
};

// template function to call trmv
template< typename MatrixA, typename VectorX >
inline typename trmv_impl< typename traits::matrix_traits<
        MatrixA >::value_type >::return_type
trmv( char const trans, char const diag, MatrixA& a, VectorX& x ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    trmv_impl< value_type >::compute( trans, diag, a, x );
}

}}}} // namespace boost::numeric::bindings::blas

#endif

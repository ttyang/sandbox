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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HBMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HBMV_HPP

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

// overloaded functions to call blas
namespace detail {

inline void hbmv( const char uplo, const integer_t n, const integer_t k,
        const traits::complex_f alpha, const traits::complex_f* a,
        const integer_t lda, const traits::complex_f* x, const integer_t incx,
        const traits::complex_f beta, traits::complex_f* y,
        const integer_t incy ) {
    BLAS_CHBMV( &uplo, &n, &k, traits::complex_ptr(&alpha),
            traits::complex_ptr(a), &lda, traits::complex_ptr(x), &incx,
            traits::complex_ptr(&beta), traits::complex_ptr(y), &incy );
}

inline void hbmv( const char uplo, const integer_t n, const integer_t k,
        const traits::complex_d alpha, const traits::complex_d* a,
        const integer_t lda, const traits::complex_d* x, const integer_t incx,
        const traits::complex_d beta, traits::complex_d* y,
        const integer_t incy ) {
    BLAS_ZHBMV( &uplo, &n, &k, traits::complex_ptr(&alpha),
            traits::complex_ptr(a), &lda, traits::complex_ptr(x), &incx,
            traits::complex_ptr(&beta), traits::complex_ptr(y), &incy );
}

} // namespace detail

// value-type based template
template< typename ValueType >
struct hbmv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // static template member function
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type invoke( const integer_t k, const value_type alpha,
            const MatrixA& a, const VectorX& x, const value_type beta,
            VectorY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorX >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        detail::hbmv( traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), k, alpha,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(x), traits::vector_stride(x), beta,
                traits::vector_storage(y), traits::vector_stride(y) );
    }
};

// generic template function to call hbmv
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename hbmv_impl< typename traits::matrix_traits<
        MatrixA >::value_type >::return_type
hbmv( const integer_t k, const typename traits::matrix_traits<
        MatrixA >::value_type alpha, const MatrixA& a, const VectorX& x,
        const typename traits::matrix_traits< MatrixA >::value_type beta,
        VectorY& y ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    hbmv_impl< value_type >::invoke( k, alpha, a, x, beta, y );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

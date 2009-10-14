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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GERU_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GERU_HPP

// Include header of configured BLAS interface
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
#include <boost/numeric/bindings/blas/detail/cblas.h>
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
#include <boost/numeric/bindings/blas/detail/cublas.h>
#else
#include <boost/numeric/bindings/blas/detail/blas.h>
#endif

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

// The detail namespace is used for overloads on value type,
// and to dispatch to the right routine

namespace detail {

inline void geru( const integer_t m, const integer_t n,
        const traits::complex_f alpha, const traits::complex_f* x,
        const integer_t incx, const traits::complex_f* y,
        const integer_t incy, traits::complex_f* a, const integer_t lda ) {
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
    cblas_cgeru( CblasColMajor, m, n, traits::void_ptr(&alpha),
            traits::void_ptr(x), incx, traits::void_ptr(y), incy,
            traits::void_ptr(a), lda );
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
    cublasCgeru( m, n, traits::void_ptr(alpha), traits::void_ptr(x), incx,
            traits::void_ptr(y), incy, traits::void_ptr(a), lda );
#else
    BLAS_CGERU( &m, &n, traits::complex_ptr(&alpha), traits::complex_ptr(x),
            &incx, traits::complex_ptr(y), &incy, traits::complex_ptr(a),
            &lda );
#endif
}

inline void geru( const integer_t m, const integer_t n,
        const traits::complex_d alpha, const traits::complex_d* x,
        const integer_t incx, const traits::complex_d* y,
        const integer_t incy, traits::complex_d* a, const integer_t lda ) {
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
    cblas_zgeru( CblasColMajor, m, n, traits::void_ptr(&alpha),
            traits::void_ptr(x), incx, traits::void_ptr(y), incy,
            traits::void_ptr(a), lda );
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
    // NOT FOUND();
#else
    BLAS_ZGERU( &m, &n, traits::complex_ptr(&alpha), traits::complex_ptr(x),
            &incx, traits::complex_ptr(y), &incy, traits::complex_ptr(a),
            &lda );
#endif
}


} // namespace detail

// value-type based template
template< typename ValueType >
struct geru_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // static template member function
    template< typename VectorX, typename VectorY, typename MatrixA >
    static return_type invoke( const value_type alpha, const VectorX& x,
            const VectorY& y, MatrixA& a ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::matrix_traits<
                MatrixA >::value_type >::value) );
        detail::geru( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), alpha,
                traits::vector_storage(x), traits::vector_stride(x),
                traits::vector_storage(y), traits::vector_stride(y),
                traits::matrix_storage(a), traits::leading_dimension(a) );
    }
};

// generic template function to call geru
template< typename VectorX, typename VectorY, typename MatrixA >
inline typename geru_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
geru( const typename traits::vector_traits< VectorX >::value_type alpha,
        const VectorX& x, const VectorY& y, MatrixA& a ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    geru_impl< value_type >::invoke( alpha, x, y, a );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

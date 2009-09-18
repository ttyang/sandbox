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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPR_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_HPR_HPP

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

inline void hpr( const char uplo, const integer_t n, const float alpha,
        const traits::complex_f* x, const integer_t incx,
        traits::complex_f* ap ) {
    BLAS_CHPR( &uplo, &n, &alpha, traits::complex_ptr(x), &incx,
            traits::complex_ptr(ap) );
}

inline void hpr( const char uplo, const integer_t n, const double alpha,
        const traits::complex_d* x, const integer_t incx,
        traits::complex_d* ap ) {
    BLAS_ZHPR( &uplo, &n, &alpha, traits::complex_ptr(x), &incx,
            traits::complex_ptr(ap) );
}

} // namespace detail

// value-type based template
template< typename ValueType >
struct hpr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // templated specialization
    template< typename VectorX, typename MatrixAP >
    static return_type invoke( const real_type alpha, const VectorX& x,
            MatrixAP& ap ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::matrix_traits<
                MatrixAP >::value_type >::value) );
        detail::hpr( traits::matrix_uplo_tag(ap),
                traits::matrix_num_columns(ap), alpha,
                traits::vector_storage(x), traits::vector_stride(x),
                traits::matrix_storage(ap) );
    }
};

// generic template function for calling to hpr
template< typename VectorX, typename MatrixAP >
inline typename hpr_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
hpr( const typename traits::type_traits<
        typename traits::vector_traits<
        VectorX >::value_type >::real_type alpha, const VectorX& x,
        MatrixAP& ap ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    hpr_impl< value_type >::invoke( alpha, x, ap );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

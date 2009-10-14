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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_ROT_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_ROT_HPP

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

inline void rot( const integer_t n, const float* x, const integer_t incx,
        float* y, const integer_t incy, const float c, const float s ) {
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
    cblas_srot( n, x, incx, y, incy, c, s );
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
    cublasSrot( n, x, incx, y, incy, c, s );
#else
    BLAS_SROT( &n, x, &incx, y, &incy, &c, &s );
#endif
}

inline void rot( const integer_t n, const double* x, const integer_t incx,
        double* y, const integer_t incy, const double c, const double s ) {
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
    cblas_drot( n, x, incx, y, incy, c, s );
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
    cublasDrot( n, x, incx, y, incy, c, s );
#else
    BLAS_DROT( &n, x, &incx, y, &incy, &c, &s );
#endif
}


} // namespace detail

// value-type based template
template< typename ValueType >
struct rot_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // static template member function
    template< typename VectorX, typename VectorY >
    static return_type invoke( const VectorX& x, VectorY& y,
            const real_type c, const real_type s ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        detail::rot( traits::vector_size(x), traits::vector_storage(x),
                traits::vector_stride(x), traits::vector_storage(y),
                traits::vector_stride(y), c, s );
    }
};

// generic template function to call rot
template< typename VectorX, typename VectorY >
inline typename rot_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
rot( const VectorX& x, VectorY& y, const typename traits::type_traits<
        typename traits::vector_traits< VectorX >::value_type >::real_type c,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorX >::value_type >::real_type s ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    rot_impl< value_type >::invoke( x, y, c, s );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

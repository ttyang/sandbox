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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_DOT_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_DOT_HPP

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
namespace level1 {

// overloaded functions to call blas
namespace detail {
    inline float dot( integer_t const n, float* x, integer_t const incx,
            float* y, integer_t const incy ) {
        return BLAS_SDOT( &n, x, &incx, y, &incy );
    }
    inline double dot( integer_t const n, double* x, integer_t const incx,
            double* y, integer_t const incy ) {
        return BLAS_DDOT( &n, x, &incx, y, &incy );
    }
}

// value-type based template
template< typename ValueType >
struct dot_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef value_type return_type;

    // templated specialization
    template< typename VectorX, typename VectorY >
    static return_type invoke( VectorX& x, VectorY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        return detail::dot( traits::vector_size(x),
                traits::vector_storage(x), traits::vector_stride(x),
                traits::vector_storage(y), traits::vector_stride(y) );
    }
};

// low-level template function for direct calls to level1::dot
template< typename VectorX, typename VectorY >
inline typename dot_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
dot( VectorX& x, VectorY& y ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    return dot_impl< value_type >::invoke( x, y );
}

}}}}} // namespace boost::numeric::bindings::blas::level1

#endif

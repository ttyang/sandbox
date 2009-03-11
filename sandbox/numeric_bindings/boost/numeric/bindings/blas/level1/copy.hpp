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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_COPY_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_COPY_HPP

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
    inline void copy( integer_t const n, float* x, integer_t const incx,
            float* y, integer_t const incy ) {
        BLAS_SCOPY( &n, x, &incx, y, &incy );
    }
    inline void copy( integer_t const n, double* x, integer_t const incx,
            double* y, integer_t const incy ) {
        BLAS_DCOPY( &n, x, &incx, y, &incy );
    }
    inline void copy( integer_t const n, traits::complex_f* x,
            integer_t const incx, traits::complex_f* y,
            integer_t const incy ) {
        BLAS_CCOPY( &n, traits::complex_ptr(x), &incx, traits::complex_ptr(y),
                &incy );
    }
    inline void copy( integer_t const n, traits::complex_d* x,
            integer_t const incx, traits::complex_d* y,
            integer_t const incy ) {
        BLAS_ZCOPY( &n, traits::complex_ptr(x), &incx, traits::complex_ptr(y),
                &incy );
    }
}

// value-type based template
template< typename ValueType >
struct copy_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename VectorX, typename VectorY >
    static return_type compute( VectorX& x, VectorY& y ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        detail::copy( traits::vector_size(x), traits::vector_storage(x),
                traits::vector_stride(x), traits::vector_storage(y),
                traits::vector_stride(y) );
    }
};

// low-level template function for direct calls to level1::copy
template< typename VectorX, typename VectorY >
inline typename copy_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
copy( VectorX& x, VectorY& y ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    copy_impl< value_type >::compute( x, y );
}

}}}}} // namespace boost::numeric::bindings::blas::level1

#endif

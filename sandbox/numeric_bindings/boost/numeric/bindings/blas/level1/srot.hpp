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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_SROT_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_SROT_HPP

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
    inline void srot( integer_t const n, traits::complex_f* x,
            integer_t const incx, traits::complex_f* y, integer_t const incy,
            float const c, float const s ) {
        BLAS_CSROT( &n, traits::complex_ptr(x), &incx, traits::complex_ptr(y),
                &incy, &c, &s );
    }
}

// value-type based template
template< typename ValueType >
struct srot_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename VectorX, typename VectorY >
    static return_type compute( integer_t const n, VectorX& x,
            integer_t const incx, VectorY& y, integer_t const incy,
            real_type const c, real_type const s ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        detail::srot( n, traits::vector_storage(x), incx,
                traits::vector_storage(y), incy, c, s );
    }
};

// low-level template function for direct calls to level1::srot
template< typename VectorX, typename VectorY >
inline typename srot_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
srot( integer_t const n, VectorX& x, integer_t const incx, VectorY& y,
        integer_t const incy, typename traits::vector_traits<
        VectorX >::value_type const c, typename traits::vector_traits<
        VectorX >::value_type const s ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    srot_impl< value_type >::compute( n, x, incx, y, incy, c, s );
}

}}}}} // namespace boost::numeric::bindings::blas::level1

#endif

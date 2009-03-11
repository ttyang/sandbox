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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_SDOT_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_SDOT_HPP

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
    inline double sdot( integer_t const n, float* sx, integer_t const incx,
            float* sy, integer_t const incy ) {
        return BLAS_DSDOT( &n, sx, &incx, sy, &incy );
    }
}

// value-type based template
template< typename ValueType >
struct sdot_impl {

    typedef ValueType value_type;
    typedef value_type return_type;

    // templated specialization
    template< typename VectorSX, typename VectorSY >
    static return_type compute( integer_t const n, VectorSX& sx,
            integer_t const incx, VectorSY& sy, integer_t const incy ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorSX >::value_type, typename traits::vector_traits<
                VectorSY >::value_type >::value) );
        return detail::sdot( n, traits::vector_storage(sx), incx,
                traits::vector_storage(sy), incy );
    }
};

// low-level template function for direct calls to level1::sdot
template< typename VectorSX, typename VectorSY >
inline typename sdot_impl< typename traits::vector_traits<
        VectorSX >::value_type >::return_type
sdot( integer_t const n, VectorSX& sx, integer_t const incx,
        VectorSY& sy, integer_t const incy ) {
    typedef typename traits::vector_traits< VectorSX >::value_type value_type;
    return sdot_impl< value_type >::compute( n, sx, incx, sy, incy );
}

}}}}} // namespace boost::numeric::bindings::blas::level1

#endif

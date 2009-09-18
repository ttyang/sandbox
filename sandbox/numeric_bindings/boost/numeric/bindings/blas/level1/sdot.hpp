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

inline double sdot( const integer_t n, const float* sx, const integer_t incx,
        const float* sy, const integer_t incy ) {
    return BLAS_DSDOT( &n, sx, &incx, sy, &incy );
}

} // namespace detail

// value-type based template
template< typename ValueType >
struct sdot_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef value_type return_type;

    // static template member function
    template< typename VectorSX, typename VectorSY >
    static return_type invoke( const integer_t n, const VectorSX& sx,
            const integer_t incx, const VectorSY& sy, const integer_t incy ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorSX >::value_type, typename traits::vector_traits<
                VectorSY >::value_type >::value) );
        return detail::sdot( n, traits::vector_storage(sx), incx,
                traits::vector_storage(sy), incy );
    }
};

// generic template function to call sdot
template< typename VectorSX, typename VectorSY >
inline typename sdot_impl< typename traits::vector_traits<
        VectorSX >::value_type >::return_type
sdot( const integer_t n, const VectorSX& sx, const integer_t incx,
        const VectorSY& sy, const integer_t incy ) {
    typedef typename traits::vector_traits< VectorSX >::value_type value_type;
    return sdot_impl< value_type >::invoke( n, sx, incx, sy, incy );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

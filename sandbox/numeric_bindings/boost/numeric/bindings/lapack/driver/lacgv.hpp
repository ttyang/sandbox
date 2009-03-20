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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_LACGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_LACGV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void lacgv( integer_t const n, traits::complex_f* x,
            integer_t const incx ) {
        LAPACK_CLACGV( &n, traits::complex_ptr(x), &incx );
    }
    inline void lacgv( integer_t const n, traits::complex_d* x,
            integer_t const incx ) {
        LAPACK_ZLACGV( &n, traits::complex_ptr(x), &incx );
    }
}

// value-type based template
template< typename ValueType >
struct lacgv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< typename VectorX >
    static void invoke( integer_t const n, VectorX& x, integer_t const incx ) {
        BOOST_ASSERT( n >= 0 );
        detail::lacgv( n, traits::vector_storage(x), incx );
    }
};


// template function to call lacgv
template< typename VectorX >
inline integer_t lacgv( integer_t const n, VectorX& x,
        integer_t const incx ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    integer_t info(0);
    lacgv_impl< value_type >::invoke( n, x, incx );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

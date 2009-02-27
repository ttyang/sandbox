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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_ASUM_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_ASUM_HPP

#include <boost/numeric/bindings/blas/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//$DESCRIPTION

// overloaded functions to call blas
namespace detail {
    inline float asum( integer_t const n, float* x, integer_t const incx ) {
        return BLAS_SASUM( &n, x, &incx );
    }
    inline double asum( integer_t const n, double* x, integer_t const incx ) {
        return BLAS_DASUM( &n, x, &incx );
    }
}

// value-type based template
template< typename ValueType >
struct asum_impl {

    typedef ValueType value_type;
    typedef value_type return_type;

    // templated specialization
    template< typename VectorX >
    static return_type compute( VectorX& x ) {
        
        return detail::asum( traits::vector_size(x),
                traits::vector_storage(x), traits::vector_stride(x) );
    }
};

// template function to call asum
template< typename VectorX >
inline typename asum_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
asum( VectorX& x ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    return asum_impl< value_type >::compute( x );
}

}}}} // namespace boost::numeric::bindings::blas

#endif

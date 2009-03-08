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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_SCAL_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_SCAL_HPP

#include <boost/numeric/bindings/blas/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//$DESCRIPTION

// overloaded functions to call blas
namespace detail {
    inline void scal( integer_t const n, float const a, float* x,
            integer_t const incx ) {
        BLAS_SSCAL( &n, &a, x, &incx );
    }
    inline void scal( integer_t const n, double const a, double* x,
            integer_t const incx ) {
        BLAS_DSCAL( &n, &a, x, &incx );
    }
    inline void scal( integer_t const n, traits::complex_f const a,
            traits::complex_f* x, integer_t const incx ) {
        BLAS_CSCAL( &n, traits::complex_ptr(&a), traits::complex_ptr(x),
                &incx );
    }
    inline void scal( integer_t const n, traits::complex_d const a,
            traits::complex_d* x, integer_t const incx ) {
        BLAS_ZSCAL( &n, traits::complex_ptr(&a), traits::complex_ptr(x),
                &incx );
    }
}

// value-type based template
template< typename ValueType >
struct scal_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template< typename VectorX >
    static return_type compute( value_type const a, VectorX& x ) {
        
        detail::scal( traits::vector_size(x), a,
                traits::vector_storage(x), traits::vector_stride(x) );
    }
};

// template function to call scal
template< typename VectorX >
inline typename scal_impl< typename traits::vector_traits<
        VectorX >::value_type >::return_type
scal( typename traits::vector_traits< VectorX >::value_type const a,
        VectorX& x ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    scal_impl< value_type >::compute( a, x );
}

}}}} // namespace boost::numeric::bindings::blas

#endif

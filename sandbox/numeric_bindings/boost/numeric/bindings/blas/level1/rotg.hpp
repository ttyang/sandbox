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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_ROTG_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_ROTG_HPP

#include <boost/numeric/bindings/blas/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//$DESCRIPTION

// overloaded functions to call blas
namespace detail {
    inline void rotg( float& a, float& b, float& c, float& s ) {
        BLAS_SROTG( &a, &b, &c, &s );
    }
    inline void rotg( double& a, double& b, double& c, double& s ) {
        BLAS_DROTG( &a, &b, &c, &s );
    }
    inline void rotg( traits::complex_f& a, traits::complex_f& b, float& c,
            traits::complex_f& s ) {
        BLAS_CROTG( traits::complex_ptr(&a), traits::complex_ptr(&b), &c,
                traits::complex_ptr(&s) );
    }
    inline void rotg( traits::complex_d& a, traits::complex_d& b, double& c,
            traits::complex_d& s ) {
        BLAS_ZROTG( traits::complex_ptr(&a), traits::complex_ptr(&b), &c,
                traits::complex_ptr(&s) );
    }
}

// value-type based template
template< typename ValueType >
struct rotg_impl {

    typedef ValueType value_type;
    typedef void return_type;

    // templated specialization
    template<  >
    static return_type compute( value_type& a, value_type& b, real_type& c,
            value_type& s ) {
        detail::rotg( a, b, c, s );
    }
};

// template function to call rotg
template<  >
inline typename rotg_impl< typename traits::TODO_traits<
        TODO >::value_type >::return_type
rotg( typename traits::TODO_traits< TODO >::value_type& a,
        typename traits::TODO_traits< TODO >::value_type& b,
        typename traits::TODO_traits< TODO >::value_type& c,
        typename traits::TODO_traits< TODO >::value_type& s ) {
    typedef typename traits::TODO_traits< TODO >::value_type value_type;
    rotg_impl< value_type >::compute( a, b, c, s );
}

}}}} // namespace boost::numeric::bindings::blas

#endif

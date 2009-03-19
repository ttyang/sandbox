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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_LARGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_LARGV_HPP

#include <boost/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/keywords.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void largv( integer_t const n, float* x, integer_t const incx,
            float* y, integer_t const incy, float* c, integer_t const incc ) {
        LAPACK_SLARGV( &n, x, &incx, y, &incy, c, &incc );
    }
    inline void largv( integer_t const n, double* x, integer_t const incx,
            double* y, integer_t const incy, double* c,
            integer_t const incc ) {
        LAPACK_DLARGV( &n, x, &incx, y, &incy, c, &incc );
    }
    inline void largv( integer_t const n, traits::complex_f* x,
            integer_t const incx, traits::complex_f* y, integer_t const incy,
            float* c, integer_t const incc ) {
        LAPACK_CLARGV( &n, traits::complex_ptr(x), &incx,
                traits::complex_ptr(y), &incy, c, &incc );
    }
    inline void largv( integer_t const n, traits::complex_d* x,
            integer_t const incx, traits::complex_d* y, integer_t const incy,
            double* c, integer_t const incc ) {
        LAPACK_ZLARGV( &n, traits::complex_ptr(x), &incx,
                traits::complex_ptr(y), &incy, c, &incc );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct largv_impl{};

// real specialization
template< typename ValueType >
struct largv_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef typename mpl::vector<  > valid_keywords;

    // templated specialization
    template< typename VectorX, typename VectorY, typename VectorC >
    static void compute( integer_t const n, VectorX& x, integer_t const incx,
            VectorY& y, integer_t const incy, VectorC& c,
            integer_t const incc ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorC >::value_type >::value) );
        BOOST_ASSERT( traits::vector_size(x) >= 1+(n-1)*incx );
        BOOST_ASSERT( traits::vector_size(y) >= 1+(n-1)*incy );
        BOOST_ASSERT( traits::vector_size(c) >= 1+(n-1)*incc );
        detail::largv( n, traits::vector_storage(x), incx,
                traits::vector_storage(y), incy, traits::vector_storage(c),
                incc );
    }
};

// complex specialization
template< typename ValueType >
struct largv_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef typename mpl::vector<  > valid_keywords;

    // templated specialization
    template< typename VectorX, typename VectorY, typename VectorC >
    static void compute( integer_t const n, VectorX& x, integer_t const incx,
            VectorY& y, integer_t const incy, VectorC& c,
            integer_t const incc ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorX >::value_type, typename traits::vector_traits<
                VectorY >::value_type >::value) );
        BOOST_ASSERT( traits::vector_size(x) >= 1+(n-1)*incx );
        BOOST_ASSERT( traits::vector_size(y) >= 1+(n-1)*incy );
        BOOST_ASSERT( traits::vector_size(c) >= 1+(n-1)*incc );
        detail::largv( n, traits::vector_storage(x), incx,
                traits::vector_storage(y), incy, traits::vector_storage(c),
                incc );
    }
};


// template function to call largv
template< typename VectorX, typename VectorY, typename VectorC >
inline integer_t largv( integer_t const n, VectorX& x,
        integer_t const incx, VectorY& y, integer_t const incy, VectorC& c,
        integer_t const incc ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    integer_t info(0);
    largv_impl< value_type >::compute( n, x, incx, y, incy, c, incc );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

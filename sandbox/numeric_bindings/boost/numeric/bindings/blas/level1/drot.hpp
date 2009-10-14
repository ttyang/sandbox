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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_DROT_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_DROT_HPP

// Include header of configured BLAS interface
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
#include <boost/numeric/bindings/blas/detail/cblas.h>
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
#include <boost/numeric/bindings/blas/detail/cublas.h>
#else
#include <boost/numeric/bindings/blas/detail/blas.h>
#endif

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

// The detail namespace is used for overloads on value type,
// and to dispatch to the right routine

namespace detail {

inline void drot( const integer_t n, const traits::complex_d* cx,
        const integer_t incx, const traits::complex_d* cy,
        const integer_t incy, const double c, const double s ) {
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
    //TODO( ... ); // FIXME
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
    //TODO( ... ); // FIXME
#else
    BLAS_ZDROT( &n, traits::complex_ptr(cx), &incx, traits::complex_ptr(cy),
            &incy, &c, &s );
#endif
}


} // namespace detail

// value-type based template
template< typename ValueType >
struct drot_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // static template member function
    template< typename VectorCX, typename VectorCY >
    static return_type invoke( const integer_t n, const VectorCX& cx,
            const VectorCY& cy, const real_type c, const real_type s ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorCX >::value_type, typename traits::vector_traits<
                VectorCY >::value_type >::value) );
        detail::drot( n, traits::vector_storage(cx),
                traits::vector_stride(cx), traits::vector_storage(cy),
                traits::vector_stride(cy), c, s );
    }
};

// generic template function to call drot
template< typename VectorCX, typename VectorCY >
inline typename drot_impl< typename traits::vector_traits<
        VectorCX >::value_type >::return_type
drot( const integer_t n, const VectorCX& cx, const VectorCY& cy,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorCX >::value_type >::real_type c,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorCX >::value_type >::real_type s ) {
    typedef typename traits::vector_traits< VectorCX >::value_type value_type;
    drot_impl< value_type >::invoke( n, cx, cy, c, s );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

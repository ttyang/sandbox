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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GBTRF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GBTRF_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/lapack.h>
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
    inline void gbtrf( integer_t const m, integer_t const n,
            integer_t const kl, integer_t const ku, float* ab,
            integer_t const ldab, integer_t* ipiv, integer_t& info ) {
        LAPACK_SGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
    }
    inline void gbtrf( integer_t const m, integer_t const n,
            integer_t const kl, integer_t const ku, double* ab,
            integer_t const ldab, integer_t* ipiv, integer_t& info ) {
        LAPACK_DGBTRF( &m, &n, &kl, &ku, ab, &ldab, ipiv, &info );
    }
    inline void gbtrf( integer_t const m, integer_t const n,
            integer_t const kl, integer_t const ku, traits::complex_f* ab,
            integer_t const ldab, integer_t* ipiv, integer_t& info ) {
        LAPACK_CGBTRF( &m, &n, &kl, &ku, traits::complex_ptr(ab), &ldab, ipiv,
                &info );
    }
    inline void gbtrf( integer_t const m, integer_t const n,
            integer_t const kl, integer_t const ku, traits::complex_d* ab,
            integer_t const ldab, integer_t* ipiv, integer_t& info ) {
        LAPACK_ZGBTRF( &m, &n, &kl, &ku, traits::complex_ptr(ab), &ldab, ipiv,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct gbtrf_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB, typename VectorIPIV >
    static void compute( integer_t const m, integer_t const n,
            integer_t const kl, integer_t const ku, MatrixAB& ab,
            VectorIPIV& ipiv, integer_t& info ) {
        BOOST_ASSERT( m >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kl >= 0 );
        BOOST_ASSERT( ku >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= 2 );
        BOOST_ASSERT( traits::vector_size(ipiv) >= std::min(m,n) );
        detail::gbtrf( m, n, kl, ku, traits::matrix_storage(ab),
                traits::leading_dimension(ab), traits::vector_storage(ipiv),
                info );
    }
};


// template function to call gbtrf
template< typename MatrixAB, typename VectorIPIV >
inline integer_t gbtrf( integer_t const m, integer_t const n,
        integer_t const kl, integer_t const ku, MatrixAB& ab,
        VectorIPIV& ipiv ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    gbtrf_impl< value_type >::compute( m, n, kl, ku, ab, ipiv, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

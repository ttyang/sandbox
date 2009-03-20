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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBTRF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBTRF_HPP

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
    inline void pbtrf( char const uplo, integer_t const n, integer_t const kd,
            float* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_SPBTRF( &uplo, &n, &kd, ab, &ldab, &info );
    }
    inline void pbtrf( char const uplo, integer_t const n, integer_t const kd,
            double* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_DPBTRF( &uplo, &n, &kd, ab, &ldab, &info );
    }
    inline void pbtrf( char const uplo, integer_t const n, integer_t const kd,
            traits::complex_f* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_CPBTRF( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, &info );
    }
    inline void pbtrf( char const uplo, integer_t const n, integer_t const kd,
            traits::complex_d* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_ZPBTRF( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, &info );
    }
}

// value-type based template
template< typename ValueType >
struct pbtrf_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< typename MatrixAB >
    static void invoke( integer_t const n, integer_t const kd, MatrixAB& ab,
            integer_t& info ) {
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
        detail::pbtrf( traits::matrix_uplo_tag(a), n, kd,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                info );
    }
};


// template function to call pbtrf
template< typename MatrixAB >
inline integer_t pbtrf( integer_t const n, integer_t const kd,
        MatrixAB& ab ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbtrf_impl< value_type >::invoke( n, kd, ab, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

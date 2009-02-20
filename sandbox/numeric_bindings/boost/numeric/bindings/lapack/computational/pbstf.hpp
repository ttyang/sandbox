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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_PBSTF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_PBSTF_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void pbstf( char const uplo, integer_t const n, integer_t const kd,
            float* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_SPBSTF( &uplo, &n, &kd, ab, &ldab, &info );
    }
    inline void pbstf( char const uplo, integer_t const n, integer_t const kd,
            double* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_DPBSTF( &uplo, &n, &kd, ab, &ldab, &info );
    }
    inline void pbstf( char const uplo, integer_t const n, integer_t const kd,
            traits::complex_f* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_CPBSTF( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, &info );
    }
    inline void pbstf( char const uplo, integer_t const n, integer_t const kd,
            traits::complex_d* ab, integer_t const ldab, integer_t& info ) {
        LAPACK_ZPBSTF( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, &info );
    }
}

// value-type based template
template< typename ValueType >
struct pbstf_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB >
    static void compute( integer_t const n, integer_t const kd, MatrixAB& ab,
            integer_t& info ) {
#ifndef NDEBUG
        assert( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        assert( n >= 0 );
        assert( kd >= 0 );
        assert( traits::leading_dimension(ab) >= kd+1 );
#endif
        detail::pbstf( traits::matrix_uplo_tag(a), n, kd,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                info );
    }
};


// template function to call pbstf
template< typename MatrixAB >
inline integer_t pbstf( integer_t const n, integer_t const kd,
        MatrixAB& ab ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbstf_impl< value_type >::compute( n, kd, ab, info );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TPTRI_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TPTRI_HPP

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
    inline void tptri( char const uplo, char const diag, integer_t const n,
            float* ap, integer_t& info ) {
        LAPACK_STPTRI( &uplo, &diag, &n, ap, &info );
    }
    inline void tptri( char const uplo, char const diag, integer_t const n,
            double* ap, integer_t& info ) {
        LAPACK_DTPTRI( &uplo, &diag, &n, ap, &info );
    }
    inline void tptri( char const uplo, char const diag, integer_t const n,
            traits::complex_f* ap, integer_t& info ) {
        LAPACK_CTPTRI( &uplo, &diag, &n, traits::complex_ptr(ap), &info );
    }
    inline void tptri( char const uplo, char const diag, integer_t const n,
            traits::complex_d* ap, integer_t& info ) {
        LAPACK_ZTPTRI( &uplo, &diag, &n, traits::complex_ptr(ap), &info );
    }
}

// value-type based template
template< typename ValueType >
struct tptri_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAP >
    static void compute( char const diag, MatrixAP& ap, integer_t& info ) {
        BOOST_ASSERT( traits::matrix_uplo_tag(ap) == 'U' ||
                traits::matrix_uplo_tag(ap) == 'L' );
        BOOST_ASSERT( diag == 'N' || diag == 'U' );
        BOOST_ASSERT( traits::matrix_num_columns(ap) >= 0 );
        detail::tptri( traits::matrix_uplo_tag(ap), diag,
                traits::matrix_num_columns(ap), traits::matrix_storage(ap),
                info );
    }
};


// template function to call tptri
template< typename MatrixAP >
inline integer_t tptri( char const diag, MatrixAP& ap ) {
    typedef typename traits::matrix_traits< MatrixAP >::value_type value_type;
    integer_t info(0);
    tptri_impl< value_type >::compute( diag, ap, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

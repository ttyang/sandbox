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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRTRI_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRTRI_HPP

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
    inline void trtri( char const uplo, char const diag, integer_t const n,
            float* a, integer_t const lda, integer_t& info ) {
        LAPACK_STRTRI( &uplo, &diag, &n, a, &lda, &info );
    }
    inline void trtri( char const uplo, char const diag, integer_t const n,
            double* a, integer_t const lda, integer_t& info ) {
        LAPACK_DTRTRI( &uplo, &diag, &n, a, &lda, &info );
    }
    inline void trtri( char const uplo, char const diag, integer_t const n,
            traits::complex_f* a, integer_t const lda, integer_t& info ) {
        LAPACK_CTRTRI( &uplo, &diag, &n, traits::complex_ptr(a), &lda, &info );
    }
    inline void trtri( char const uplo, char const diag, integer_t const n,
            traits::complex_d* a, integer_t const lda, integer_t& info ) {
        LAPACK_ZTRTRI( &uplo, &diag, &n, traits::complex_ptr(a), &lda, &info );
    }
}

// value-type based template
template< typename ValueType >
struct trtri_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< typename MatrixA >
    static void invoke( char const diag, MatrixA& a, integer_t& info ) {
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( diag == 'N' || diag == 'U' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::trtri( traits::matrix_uplo_tag(a), diag,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), info );
    }
};


// template function to call trtri
template< typename MatrixA >
inline integer_t trtri( char const diag, MatrixA& a ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    trtri_impl< value_type >::invoke( diag, a, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

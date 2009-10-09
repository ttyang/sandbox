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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_POTRF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_POTRF_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
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

inline void potrf( const char uplo, const integer_t n, float* a,
        const integer_t lda, integer_t& info ) {
    LAPACK_SPOTRF( &uplo, &n, a, &lda, &info );
}
inline void potrf( const char uplo, const integer_t n, double* a,
        const integer_t lda, integer_t& info ) {
    LAPACK_DPOTRF( &uplo, &n, a, &lda, &info );
}
inline void potrf( const char uplo, const integer_t n, traits::complex_f* a,
        const integer_t lda, integer_t& info ) {
    LAPACK_CPOTRF( &uplo, &n, traits::complex_ptr(a), &lda, &info );
}
inline void potrf( const char uplo, const integer_t n, traits::complex_d* a,
        const integer_t lda, integer_t& info ) {
    LAPACK_ZPOTRF( &uplo, &n, traits::complex_ptr(a), &lda, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct potrf_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA >
    static void invoke( MatrixA& a, integer_t& info ) {
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(a)) );
        detail::potrf( traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), info );
    }
};


// template function to call potrf
template< typename MatrixA >
inline integer_t potrf( MatrixA& a ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    potrf_impl< value_type >::invoke( a, info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

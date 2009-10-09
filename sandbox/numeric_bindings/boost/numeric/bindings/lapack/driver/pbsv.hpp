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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_PBSV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_PBSV_HPP

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

inline void pbsv( const char uplo, const integer_t n, const integer_t kd,
        const integer_t nrhs, float* ab, const integer_t ldab, float* b,
        const integer_t ldb, integer_t& info ) {
    LAPACK_SPBSV( &uplo, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
}
inline void pbsv( const char uplo, const integer_t n, const integer_t kd,
        const integer_t nrhs, double* ab, const integer_t ldab, double* b,
        const integer_t ldb, integer_t& info ) {
    LAPACK_DPBSV( &uplo, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
}
inline void pbsv( const char uplo, const integer_t n, const integer_t kd,
        const integer_t nrhs, traits::complex_f* ab, const integer_t ldab,
        traits::complex_f* b, const integer_t ldb, integer_t& info ) {
    LAPACK_CPBSV( &uplo, &n, &kd, &nrhs, traits::complex_ptr(ab), &ldab,
            traits::complex_ptr(b), &ldb, &info );
}
inline void pbsv( const char uplo, const integer_t n, const integer_t kd,
        const integer_t nrhs, traits::complex_d* ab, const integer_t ldab,
        traits::complex_d* b, const integer_t ldb, integer_t& info ) {
    LAPACK_ZPBSV( &uplo, &n, &kd, &nrhs, traits::complex_ptr(ab), &ldab,
            traits::complex_ptr(b), &ldb, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct pbsv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // high-level solve typedefs and functions
    typedef boost::mpl::bool_<false> has_pivot;

    template< typename MatrixA, typename MatrixB, typename VectorP >
    static void solve( MatrixA& A, MatrixB& B, VectorP const&,
            integer_t& info ) {
        invoke( A, B, info );
    }

    // templated specialization
    template< typename MatrixAB, typename MatrixB >
    static void invoke( const integer_t kd, MatrixAB& ab, MatrixB& b,
            integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_uplo_tag(ab) == 'U' ||
                traits::matrix_uplo_tag(ab) == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(ab) >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(ab)) );
        detail::pbsv( traits::matrix_uplo_tag(ab),
                traits::matrix_num_columns(ab), kd,
                traits::matrix_num_columns(b), traits::matrix_storage(ab),
                traits::leading_dimension(ab), traits::matrix_storage(b),
                traits::leading_dimension(b), info );
    }
};


// template function to call pbsv
template< typename MatrixAB, typename MatrixB >
inline integer_t pbsv( const integer_t kd, MatrixAB& ab, MatrixB& b ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbsv_impl< value_type >::invoke( kd, ab, b, info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

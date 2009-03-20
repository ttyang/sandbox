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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GETRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GETRS_HPP

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
    inline void getrs( char const trans, integer_t const n,
            integer_t const nrhs, float* a, integer_t const lda,
            integer_t* ipiv, float* b, integer_t const ldb, integer_t& info ) {
        LAPACK_SGETRS( &trans, &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    }
    inline void getrs( char const trans, integer_t const n,
            integer_t const nrhs, double* a, integer_t const lda,
            integer_t* ipiv, double* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_DGETRS( &trans, &n, &nrhs, a, &lda, ipiv, b, &ldb, &info );
    }
    inline void getrs( char const trans, integer_t const n,
            integer_t const nrhs, traits::complex_f* a, integer_t const lda,
            integer_t* ipiv, traits::complex_f* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_CGETRS( &trans, &n, &nrhs, traits::complex_ptr(a), &lda, ipiv,
                traits::complex_ptr(b), &ldb, &info );
    }
    inline void getrs( char const trans, integer_t const n,
            integer_t const nrhs, traits::complex_d* a, integer_t const lda,
            integer_t* ipiv, traits::complex_d* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_ZGETRS( &trans, &n, &nrhs, traits::complex_ptr(a), &lda, ipiv,
                traits::complex_ptr(b), &ldb, &info );
    }
}

// value-type based template
template< typename ValueType >
struct getrs_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // templated specialization
    template< typename MatrixA, typename VectorIPIV, typename MatrixB >
    static void invoke( char const trans, MatrixA& a, VectorIPIV& ipiv,
            MatrixB& b, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( trans == 'N' || trans == 'T' || trans == 'C' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(ipiv) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_columns(a)) );
        detail::getrs( trans, traits::matrix_num_columns(a),
                traits::matrix_num_columns(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(ipiv),
                traits::matrix_storage(b), traits::leading_dimension(b),
                info );
    }
};


// template function to call getrs
template< typename MatrixA, typename VectorIPIV, typename MatrixB >
inline integer_t getrs( char const trans, MatrixA& a, VectorIPIV& ipiv,
        MatrixB& b ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    getrs_impl< value_type >::invoke( trans, a, ipiv, b, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

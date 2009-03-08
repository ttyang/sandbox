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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_TRTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_TRTRS_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void trtrs( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const nrhs, float* a,
            integer_t const lda, float* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_STRTRS( &uplo, &trans, &diag, &n, &nrhs, a, &lda, b, &ldb,
                &info );
    }
    inline void trtrs( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const nrhs, double* a,
            integer_t const lda, double* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_DTRTRS( &uplo, &trans, &diag, &n, &nrhs, a, &lda, b, &ldb,
                &info );
    }
    inline void trtrs( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const nrhs, traits::complex_f* a,
            integer_t const lda, traits::complex_f* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_CTRTRS( &uplo, &trans, &diag, &n, &nrhs,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &info );
    }
    inline void trtrs( char const uplo, char const trans, char const diag,
            integer_t const n, integer_t const nrhs, traits::complex_d* a,
            integer_t const lda, traits::complex_d* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_ZTRTRS( &uplo, &trans, &diag, &n, &nrhs,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct trtrs_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename MatrixB >
    static void compute( char const uplo, char const trans, char const diag,
            MatrixA& a, MatrixB& b, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
#ifndef NDEBUG
        assert( uplo == 'U' || uplo == 'L' );
        assert( trans == 'N' || trans == 'T' || trans == 'C' );
        assert( diag == 'N' || diag == 'U' );
        assert( traits::matrix_size2(a) >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_size2(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_size2(a)) );
#endif
        detail::trtrs( uplo, trans, diag, traits::matrix_size2(a),
                traits::matrix_size2(b), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), info );
    }
};


// template function to call trtrs
template< typename MatrixA, typename MatrixB >
inline integer_t trtrs( char const uplo, char const trans,
        char const diag, MatrixA& a, MatrixB& b ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    trtrs_impl< value_type >::compute( uplo, trans, diag, a, b, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

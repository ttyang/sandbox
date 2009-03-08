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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GGHRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GGHRD_HPP

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
    inline void gghrd( char const compq, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, float* a,
            integer_t const lda, float* b, integer_t const ldb, float* q,
            integer_t const ldq, float* z, integer_t const ldz,
            integer_t& info ) {
        LAPACK_SGGHRD( &compq, &compz, &n, &ilo, &ihi, a, &lda, b, &ldb, q,
                &ldq, z, &ldz, &info );
    }
    inline void gghrd( char const compq, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, double* a,
            integer_t const lda, double* b, integer_t const ldb, double* q,
            integer_t const ldq, double* z, integer_t const ldz,
            integer_t& info ) {
        LAPACK_DGGHRD( &compq, &compz, &n, &ilo, &ihi, a, &lda, b, &ldb, q,
                &ldq, z, &ldz, &info );
    }
    inline void gghrd( char const compq, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, traits::complex_f* a,
            integer_t const lda, traits::complex_f* b, integer_t const ldb,
            traits::complex_f* q, integer_t const ldq, traits::complex_f* z,
            integer_t const ldz, integer_t& info ) {
        LAPACK_CGGHRD( &compq, &compz, &n, &ilo, &ihi, traits::complex_ptr(a),
                &lda, traits::complex_ptr(b), &ldb, traits::complex_ptr(q),
                &ldq, traits::complex_ptr(z), &ldz, &info );
    }
    inline void gghrd( char const compq, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, traits::complex_d* a,
            integer_t const lda, traits::complex_d* b, integer_t const ldb,
            traits::complex_d* q, integer_t const ldq, traits::complex_d* z,
            integer_t const ldz, integer_t& info ) {
        LAPACK_ZGGHRD( &compq, &compz, &n, &ilo, &ihi, traits::complex_ptr(a),
                &lda, traits::complex_ptr(b), &ldb, traits::complex_ptr(q),
                &ldq, traits::complex_ptr(z), &ldz, &info );
    }
}

// value-type based template
template< typename ValueType >
struct gghrd_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename MatrixB, typename MatrixQ,
            typename MatrixZ >
    static void compute( char const compq, char const compz,
            integer_t const n, integer_t const ilo, MatrixA& a, MatrixB& b,
            MatrixQ& q, MatrixZ& z, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
#ifndef NDEBUG
        assert( compq == 'N' || compq == 'I' || compq == 'V' );
        assert( compz == 'N' || compz == 'I' || compz == 'V' );
        assert( n >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,n) );
        assert( traits::leading_dimension(b) >= std::max(1,n) );
#endif
        detail::gghrd( compq, compz, n, ilo, traits::matrix_size2(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::matrix_storage(q), traits::leading_dimension(q),
                traits::matrix_storage(z), traits::leading_dimension(z),
                info );
    }
};


// template function to call gghrd
template< typename MatrixA, typename MatrixB, typename MatrixQ,
        typename MatrixZ >
inline integer_t gghrd( char const compq, char const compz,
        integer_t const n, integer_t const ilo, MatrixA& a, MatrixB& b,
        MatrixQ& q, MatrixZ& z ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gghrd_impl< value_type >::compute( compq, compz, n, ilo, a, b, q, z,
            info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

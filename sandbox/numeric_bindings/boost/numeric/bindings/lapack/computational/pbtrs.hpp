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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_PBTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_PBTRS_HPP

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
    inline void pbtrs( char const uplo, integer_t const n, integer_t const kd,
            integer_t const nrhs, float* ab, integer_t const ldab, float* b,
            integer_t const ldb, integer_t& info ) {
        LAPACK_SPBTRS( &uplo, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
    }
    inline void pbtrs( char const uplo, integer_t const n, integer_t const kd,
            integer_t const nrhs, double* ab, integer_t const ldab, double* b,
            integer_t const ldb, integer_t& info ) {
        LAPACK_DPBTRS( &uplo, &n, &kd, &nrhs, ab, &ldab, b, &ldb, &info );
    }
    inline void pbtrs( char const uplo, integer_t const n, integer_t const kd,
            integer_t const nrhs, traits::complex_f* ab, integer_t const ldab,
            traits::complex_f* b, integer_t const ldb, integer_t& info ) {
        LAPACK_CPBTRS( &uplo, &n, &kd, &nrhs, traits::complex_ptr(ab), &ldab,
                traits::complex_ptr(b), &ldb, &info );
    }
    inline void pbtrs( char const uplo, integer_t const n, integer_t const kd,
            integer_t const nrhs, traits::complex_d* ab, integer_t const ldab,
            traits::complex_d* b, integer_t const ldb, integer_t& info ) {
        LAPACK_ZPBTRS( &uplo, &n, &kd, &nrhs, traits::complex_ptr(ab), &ldab,
                traits::complex_ptr(b), &ldb, &info );
    }
}

// value-type based template
template< typename ValueType >
struct pbtrs_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB, typename MatrixB >
    static void compute( char const uplo, integer_t const n,
            integer_t const kd, MatrixAB& ab, MatrixB& b, integer_t& info ) {
#ifndef NDEBUG
        assert( uplo == 'U' || uplo == 'L' );
        assert( n >= 0 );
        assert( kd >= 0 );
        assert( traits::matrix_size2(b) >= 0 );
        assert( traits::leading_dimension(ab) >= kd+1 );
        assert( traits::leading_dimension(b) >= std::max(1,n) );
#endif
        detail::pbtrs( uplo, n, kd, traits::matrix_size2(b),
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::matrix_storage(b), traits::leading_dimension(b),
                info );
    }
};


// template function to call pbtrs
template< typename MatrixAB, typename MatrixB >
inline integer_t pbtrs( char const uplo, integer_t const n,
        integer_t const kd, MatrixAB& ab, MatrixB& b ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbtrs_impl< value_type >::compute( uplo, n, kd, ab, b, info );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif

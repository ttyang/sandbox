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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GETRF_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GETRF_HPP

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
    inline void getrf( integer_t const m, integer_t const n, float* a,
            integer_t const lda, integer_t* ipiv, integer_t& info ) {
        LAPACK_SGETRF( &m, &n, a, &lda, ipiv, &info );
    }
    inline void getrf( integer_t const m, integer_t const n, double* a,
            integer_t const lda, integer_t* ipiv, integer_t& info ) {
        LAPACK_DGETRF( &m, &n, a, &lda, ipiv, &info );
    }
    inline void getrf( integer_t const m, integer_t const n,
            traits::complex_f* a, integer_t const lda, integer_t* ipiv,
            integer_t& info ) {
        LAPACK_CGETRF( &m, &n, traits::complex_ptr(a), &lda, ipiv, &info );
    }
    inline void getrf( integer_t const m, integer_t const n,
            traits::complex_d* a, integer_t const lda, integer_t* ipiv,
            integer_t& info ) {
        LAPACK_ZGETRF( &m, &n, traits::complex_ptr(a), &lda, ipiv, &info );
    }
}

// value-type based template
template< typename ValueType >
struct getrf_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorIPIV >
    static void compute( MatrixA& a, VectorIPIV& ipiv, integer_t& info ) {
        
#ifndef NDEBUG
        assert( traits::matrix_num_rows(a) >= 0 );
        assert( traits::matrix_num_columns(a) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        assert( traits::vector_size(ipiv) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
#endif
        detail::getrf( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(ipiv),
                info );
    }
};


// template function to call getrf
template< typename MatrixA, typename VectorIPIV >
inline integer_t getrf( MatrixA& a, VectorIPIV& ipiv ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    getrf_impl< value_type >::compute( a, ipiv, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

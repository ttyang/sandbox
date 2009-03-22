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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GTSV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GTSV_HPP

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
    inline void gtsv( integer_t const n, integer_t const nrhs, float* dl,
            float* d, float* du, float* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_SGTSV( &n, &nrhs, dl, d, du, b, &ldb, &info );
    }
    inline void gtsv( integer_t const n, integer_t const nrhs, double* dl,
            double* d, double* du, double* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_DGTSV( &n, &nrhs, dl, d, du, b, &ldb, &info );
    }
    inline void gtsv( integer_t const n, integer_t const nrhs,
            traits::complex_f* dl, traits::complex_f* d,
            traits::complex_f* du, traits::complex_f* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_CGTSV( &n, &nrhs, traits::complex_ptr(dl),
                traits::complex_ptr(d), traits::complex_ptr(du),
                traits::complex_ptr(b), &ldb, &info );
    }
    inline void gtsv( integer_t const n, integer_t const nrhs,
            traits::complex_d* dl, traits::complex_d* d,
            traits::complex_d* du, traits::complex_d* b, integer_t const ldb,
            integer_t& info ) {
        LAPACK_ZGTSV( &n, &nrhs, traits::complex_ptr(dl),
                traits::complex_ptr(d), traits::complex_ptr(du),
                traits::complex_ptr(b), &ldb, &info );
    }
}

// value-type based template
template< typename ValueType >
struct gtsv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // high-level solve typedefs and functions
    typedef boost::mpl::bool_<false> has_pivot;

    template< typename MatrixA, typename MatrixB, typename VectorP >
    static void solve( MatrixA& A, MatrixB& B, VectorP const&,
            integer_t& info ) {
        invoke( B, info );
    }

    // templated specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename MatrixB >
    static void invoke( integer_t const n, VectorDL& dl, VectorD& d,
            VectorDU& du, MatrixB& b, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorD >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::vector_size(dl) >= n-1 );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(du) >= n-1 );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        detail::gtsv( n, traits::matrix_num_columns(b),
                traits::vector_storage(dl), traits::vector_storage(d),
                traits::vector_storage(du), traits::matrix_storage(b),
                traits::leading_dimension(b), info );
    }
};


// template function to call gtsv
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename MatrixB >
inline integer_t gtsv( integer_t const n, VectorDL& dl, VectorD& d,
        VectorDU& du, MatrixB& b ) {
    typedef typename traits::vector_traits< VectorDL >::value_type value_type;
    integer_t info(0);
    gtsv_impl< value_type >::invoke( n, dl, d, du, b, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

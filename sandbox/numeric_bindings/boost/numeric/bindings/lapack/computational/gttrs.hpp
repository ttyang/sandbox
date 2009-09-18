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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GTTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GTTRS_HPP

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

inline void gttrs( const char trans, const integer_t n, const integer_t nrhs,
        const float* dl, const float* d, const float* du, const float* du2,
        const integer_t* ipiv, float* b, const integer_t ldb,
        integer_t& info ) {
    LAPACK_SGTTRS( &trans, &n, &nrhs, dl, d, du, du2, ipiv, b, &ldb, &info );
}

inline void gttrs( const char trans, const integer_t n, const integer_t nrhs,
        const double* dl, const double* d, const double* du,
        const double* du2, const integer_t* ipiv, double* b,
        const integer_t ldb, integer_t& info ) {
    LAPACK_DGTTRS( &trans, &n, &nrhs, dl, d, du, du2, ipiv, b, &ldb, &info );
}

inline void gttrs( const char trans, const integer_t n, const integer_t nrhs,
        const traits::complex_f* dl, const traits::complex_f* d,
        const traits::complex_f* du, const traits::complex_f* du2,
        const integer_t* ipiv, traits::complex_f* b, const integer_t ldb,
        integer_t& info ) {
    LAPACK_CGTTRS( &trans, &n, &nrhs, traits::complex_ptr(dl),
            traits::complex_ptr(d), traits::complex_ptr(du),
            traits::complex_ptr(du2), ipiv, traits::complex_ptr(b), &ldb,
            &info );
}

inline void gttrs( const char trans, const integer_t n, const integer_t nrhs,
        const traits::complex_d* dl, const traits::complex_d* d,
        const traits::complex_d* du, const traits::complex_d* du2,
        const integer_t* ipiv, traits::complex_d* b, const integer_t ldb,
        integer_t& info ) {
    LAPACK_ZGTTRS( &trans, &n, &nrhs, traits::complex_ptr(dl),
            traits::complex_ptr(d), traits::complex_ptr(du),
            traits::complex_ptr(du2), ipiv, traits::complex_ptr(b), &ldb,
            &info );
}

} // namespace detail

// value-type based template
template< typename ValueType >
struct gttrs_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename VectorDL, typename VectorD, typename VectorDU,
            typename VectorDU2, typename VectorIPIV, typename MatrixB >
    static void invoke( const char trans, const integer_t n,
            const VectorDL& dl, const VectorD& d, const VectorDU& du,
            const VectorDU2& du2, const VectorIPIV& ipiv, MatrixB& b,
            integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorD >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::vector_traits<
                VectorDU2 >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorDL >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( trans == 'N' || trans == 'T' || trans == 'C' );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::vector_size(dl) >= n-1 );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(du) >= n-1 );
        BOOST_ASSERT( traits::vector_size(du2) >= n-2 );
        BOOST_ASSERT( traits::vector_size(ipiv) >= n );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        detail::gttrs( trans, n, traits::matrix_num_columns(b),
                traits::vector_storage(dl), traits::vector_storage(d),
                traits::vector_storage(du), traits::vector_storage(du2),
                traits::vector_storage(ipiv), traits::matrix_storage(b),
                traits::leading_dimension(b), info );
    }
};


// template function to call gttrs
template< typename VectorDL, typename VectorD, typename VectorDU,
        typename VectorDU2, typename VectorIPIV, typename MatrixB >
inline integer_t gttrs( const char trans, const integer_t n,
        const VectorDL& dl, const VectorD& d, const VectorDU& du,
        const VectorDU2& du2, const VectorIPIV& ipiv, MatrixB& b ) {
    typedef typename traits::vector_traits< VectorDL >::value_type value_type;
    integer_t info(0);
    gttrs_impl< value_type >::invoke( trans, n, dl, d, du, du2, ipiv, b,
            info );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

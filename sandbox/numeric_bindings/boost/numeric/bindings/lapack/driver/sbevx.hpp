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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SBEVX_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SBEVX_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
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
    inline void sbevx( char const jobz, char const range, char const uplo,
            integer_t const n, integer_t const kd, float* ab,
            integer_t const ldab, float* q, integer_t const ldq,
            float const vl, float const vu, integer_t const il,
            integer_t const iu, float const abstol, integer_t& m, float* w,
            float* z, integer_t const ldz, float* work, integer_t* iwork,
            integer_t* ifail, integer_t& info ) {
        LAPACK_SSBEVX( &jobz, &range, &uplo, &n, &kd, ab, &ldab, q, &ldq, &vl,
                &vu, &il, &iu, &abstol, &m, w, z, &ldz, work, iwork, ifail,
                &info );
    }
    inline void sbevx( char const jobz, char const range, char const uplo,
            integer_t const n, integer_t const kd, double* ab,
            integer_t const ldab, double* q, integer_t const ldq,
            double const vl, double const vu, integer_t const il,
            integer_t const iu, double const abstol, integer_t& m, double* w,
            double* z, integer_t const ldz, double* work, integer_t* iwork,
            integer_t* ifail, integer_t& info ) {
        LAPACK_DSBEVX( &jobz, &range, &uplo, &n, &kd, ab, &ldab, q, &ldq, &vl,
                &vu, &il, &iu, &abstol, &m, w, z, &ldz, work, iwork, ifail,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct sbevx_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename MatrixQ, typename VectorW,
            typename MatrixZ, typename VectorIFAIL, typename WORK,
            typename IWORK >
    static void invoke( char const jobz, char const range, integer_t const n,
            integer_t const kd, MatrixAB& ab, MatrixQ& q, real_type const vl,
            real_type const vu, integer_t const il, integer_t const iu,
            real_type const abstol, integer_t& m, VectorW& w, MatrixZ& z,
            VectorIFAIL& ifail, integer_t& info, detail::workspace2< WORK,
            IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
        BOOST_ASSERT( traits::matrix_uplo_tag(ab) == 'U' ||
                traits::matrix_uplo_tag(ab) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd );
        BOOST_ASSERT( traits::leading_dimension(q) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(w) >= n );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( n ));
        detail::sbevx( jobz, range, traits::matrix_uplo_tag(ab), n, kd,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::matrix_storage(q), traits::leading_dimension(q), vl,
                vu, il, iu, abstol, m, traits::vector_storage(w),
                traits::matrix_storage(z), traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(ifail), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB, typename MatrixQ, typename VectorW,
            typename MatrixZ, typename VectorIFAIL >
    static void invoke( char const jobz, char const range, integer_t const n,
            integer_t const kd, MatrixAB& ab, MatrixQ& q, real_type const vl,
            real_type const vu, integer_t const il, integer_t const iu,
            real_type const abstol, integer_t& m, VectorW& w, MatrixZ& z,
            VectorIFAIL& ifail, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        invoke( jobz, range, n, kd, ab, q, vl, vu, il, iu, abstol, m, w, z,
                ifail, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB, typename MatrixQ, typename VectorW,
            typename MatrixZ, typename VectorIFAIL >
    static void invoke( char const jobz, char const range, integer_t const n,
            integer_t const kd, MatrixAB& ab, MatrixQ& q, real_type const vl,
            real_type const vu, integer_t const il, integer_t const iu,
            real_type const abstol, integer_t& m, VectorW& w, MatrixZ& z,
            VectorIFAIL& ifail, integer_t& info, optimal_workspace work ) {
        invoke( jobz, range, n, kd, ab, q, vl, vu, il, iu, abstol, m, w, z,
                ifail, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 7*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return 5*n;
    }
};


// template function to call sbevx
template< typename MatrixAB, typename MatrixQ, typename VectorW,
        typename MatrixZ, typename VectorIFAIL, typename Workspace >
inline integer_t sbevx( char const jobz, char const range,
        integer_t const n, integer_t const kd, MatrixAB& ab, MatrixQ& q,
        typename traits::matrix_traits< MatrixAB >::value_type const vl,
        typename traits::matrix_traits< MatrixAB >::value_type const vu,
        integer_t const il, integer_t const iu,
        typename traits::matrix_traits< MatrixAB >::value_type const abstol,
        integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    sbevx_impl< value_type >::invoke( jobz, range, n, kd, ab, q, vl, vu,
            il, iu, abstol, m, w, z, ifail, info, work );
    return info;
}

// template function to call sbevx, default workspace type
template< typename MatrixAB, typename MatrixQ, typename VectorW,
        typename MatrixZ, typename VectorIFAIL >
inline integer_t sbevx( char const jobz, char const range,
        integer_t const n, integer_t const kd, MatrixAB& ab, MatrixQ& q,
        typename traits::matrix_traits< MatrixAB >::value_type const vl,
        typename traits::matrix_traits< MatrixAB >::value_type const vu,
        integer_t const il, integer_t const iu,
        typename traits::matrix_traits< MatrixAB >::value_type const abstol,
        integer_t& m, VectorW& w, MatrixZ& z, VectorIFAIL& ifail ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    sbevx_impl< value_type >::invoke( jobz, range, n, kd, ab, q, vl, vu,
            il, iu, abstol, m, w, z, ifail, info, optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

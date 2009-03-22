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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SBEV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SBEV_HPP

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
    inline void sbev( char const jobz, char const uplo, integer_t const n,
            integer_t const kd, float* ab, integer_t const ldab, float* w,
            float* z, integer_t const ldz, float* work, integer_t& info ) {
        LAPACK_SSBEV( &jobz, &uplo, &n, &kd, ab, &ldab, w, z, &ldz, work,
                &info );
    }
    inline void sbev( char const jobz, char const uplo, integer_t const n,
            integer_t const kd, double* ab, integer_t const ldab, double* w,
            double* z, integer_t const ldz, double* work, integer_t& info ) {
        LAPACK_DSBEV( &jobz, &uplo, &n, &kd, ab, &ldab, w, z, &ldz, work,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct sbev_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixAB, typename VectorW, typename MatrixZ,
            typename WORK >
    static void invoke( char const jobz, integer_t const n,
            integer_t const kd, MatrixAB& ab, VectorW& w, MatrixZ& z,
            integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(ab) == 'U' ||
                traits::matrix_uplo_tag(ab) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        detail::sbev( jobz, traits::matrix_uplo_tag(ab), n, kd,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixAB, typename VectorW, typename MatrixZ >
    static void invoke( char const jobz, integer_t const n,
            integer_t const kd, MatrixAB& ab, VectorW& w, MatrixZ& z,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        invoke( jobz, n, kd, ab, w, z, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixAB, typename VectorW, typename MatrixZ >
    static void invoke( char const jobz, integer_t const n,
            integer_t const kd, MatrixAB& ab, VectorW& w, MatrixZ& z,
            integer_t& info, optimal_workspace work ) {
        invoke( jobz, n, kd, ab, w, z, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max(1,3*n-2);
    }
};


// template function to call sbev
template< typename MatrixAB, typename VectorW, typename MatrixZ,
        typename Workspace >
inline integer_t sbev( char const jobz, integer_t const n,
        integer_t const kd, MatrixAB& ab, VectorW& w, MatrixZ& z,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    sbev_impl< value_type >::invoke( jobz, n, kd, ab, w, z, info, work );
    return info;
}

// template function to call sbev, default workspace type
template< typename MatrixAB, typename VectorW, typename MatrixZ >
inline integer_t sbev( char const jobz, integer_t const n,
        integer_t const kd, MatrixAB& ab, VectorW& w, MatrixZ& z ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    sbev_impl< value_type >::invoke( jobz, n, kd, ab, w, z, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYGV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
    inline void sygv( integer_t const itype, char const jobz, char const uplo,
            integer_t const n, float* a, integer_t const lda, float* b,
            integer_t const ldb, float* w, float* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_SSYGV( &itype, &jobz, &uplo, &n, a, &lda, b, &ldb, w, work,
                &lwork, &info );
    }
    inline void sygv( integer_t const itype, char const jobz, char const uplo,
            integer_t const n, double* a, integer_t const lda, double* b,
            integer_t const ldb, double* w, double* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_DSYGV( &itype, &jobz, &uplo, &n, a, &lda, b, &ldb, w, work,
                &lwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct sygv_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW,
            typename WORK >
    static void invoke( integer_t const itype, char const jobz,
            integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        detail::sygv( itype, jobz, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(w),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( integer_t const itype, char const jobz,
            integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorW >
    static void invoke( integer_t const itype, char const jobz,
            integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
            integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::sygv( itype, jobz, traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(w), &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( itype, jobz, n, a, b, w, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max( 1, 3*n-1 );
    }
};


// template function to call sygv
template< typename MatrixA, typename MatrixB, typename VectorW,
        typename Workspace >
inline integer_t sygv( integer_t const itype, char const jobz,
        integer_t const n, MatrixA& a, MatrixB& b, VectorW& w,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    sygv_impl< value_type >::invoke( itype, jobz, n, a, b, w, info,
            work );
    return info;
}

// template function to call sygv, default workspace type
template< typename MatrixA, typename MatrixB, typename VectorW >
inline integer_t sygv( integer_t const itype, char const jobz,
        integer_t const n, MatrixA& a, MatrixB& b, VectorW& w ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    sygv_impl< value_type >::invoke( itype, jobz, n, a, b, w, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

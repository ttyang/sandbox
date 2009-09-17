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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYEV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYEV_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
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
    inline void syev( const char jobz, const char uplo, const integer_t n,
            float* a, const integer_t lda, float* w, float* work,
            const integer_t lwork, integer_t& info ) {
        LAPACK_SSYEV( &jobz, &uplo, &n, a, &lda, w, work, &lwork, &info );
    }
    inline void syev( const char jobz, const char uplo, const integer_t n,
            double* a, const integer_t lda, double* w, double* work,
            const integer_t lwork, integer_t& info ) {
        LAPACK_DSYEV( &jobz, &uplo, &n, a, &lda, w, work, &lwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct syev_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorW, typename WORK >
    static void invoke( const char jobz, MatrixA& a, VectorW& w,
            integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        detail::syev( jobz, traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(w),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorW >
    static void invoke( const char jobz, MatrixA& a, VectorW& w,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        invoke( jobz, a, w, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorW >
    static void invoke( const char jobz, MatrixA& a, VectorW& w,
            integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::syev( jobz, traits::matrix_uplo_tag(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(w),
                &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( jobz, a, w, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( const integer_t n ) {
        return std::max( 1, 3*n-1 );
    }
};


// template function to call syev
template< typename MatrixA, typename VectorW, typename Workspace >
inline integer_t syev( const char jobz, MatrixA& a, VectorW& w,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    syev_impl< value_type >::invoke( jobz, a, w, info, work );
    return info;
}

// template function to call syev, default workspace type
template< typename MatrixA, typename VectorW >
inline integer_t syev( const char jobz, MatrixA& a, VectorW& w ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    syev_impl< value_type >::invoke( jobz, a, w, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

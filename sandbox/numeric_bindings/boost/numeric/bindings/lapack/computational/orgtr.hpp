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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_ORGTR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_ORGTR_HPP

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

inline void orgtr( const char uplo, const integer_t n, float* a,
        const integer_t lda, const float* tau, float* work,
        const integer_t lwork, integer_t& info ) {
    LAPACK_SORGTR( &uplo, &n, a, &lda, tau, work, &lwork, &info );
}
inline void orgtr( const char uplo, const integer_t n, double* a,
        const integer_t lda, const double* tau, double* work,
        const integer_t lwork, integer_t& info ) {
    LAPACK_DORGTR( &uplo, &n, a, &lda, tau, work, &lwork, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct orgtr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAU, typename WORK >
    static void invoke( const integer_t n, MatrixA& a, const VectorTAU& tau,
            integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAU >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max<
                std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( traits::vector_size(tau) >= n-1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( n ));
        detail::orgtr( traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(tau),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAU >
    static void invoke( const integer_t n, MatrixA& a, const VectorTAU& tau,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        invoke( n, a, tau, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAU >
    static void invoke( const integer_t n, MatrixA& a, const VectorTAU& tau,
            integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::orgtr( traits::matrix_uplo_tag(a), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(tau), &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( n, a, tau, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( const integer_t n ) {
        return std::max( 1, n-1 );
    }
};


// template function to call orgtr
template< typename MatrixA, typename VectorTAU, typename Workspace >
inline integer_t orgtr( const integer_t n, MatrixA& a,
        const VectorTAU& tau, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    orgtr_impl< value_type >::invoke( n, a, tau, info, work );
    return info;
}

// template function to call orgtr, default workspace type
template< typename MatrixA, typename VectorTAU >
inline integer_t orgtr( const integer_t n, MatrixA& a,
        const VectorTAU& tau ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    orgtr_impl< value_type >::invoke( n, a, tau, info,
            optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

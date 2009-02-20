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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_ORMRQ_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_ORMRQ_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
    inline void ormrq( char const side, char const trans, integer_t const m,
            integer_t const n, integer_t const k, float* a,
            integer_t const lda, float* tau, float* c, integer_t const ldc,
            float* work, integer_t const lwork, integer_t& info ) {
        LAPACK_SORMRQ( &side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work,
                &lwork, &info );
    }
    inline void ormrq( char const side, char const trans, integer_t const m,
            integer_t const n, integer_t const k, double* a,
            integer_t const lda, double* tau, double* c, integer_t const ldc,
            double* work, integer_t const lwork, integer_t& info ) {
        LAPACK_DORMRQ( &side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work,
                &lwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct ormrq_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAU, typename MatrixC,
            typename WORK >
    static void compute( char const side, char const trans, integer_t const k,
            MatrixA& a, VectorTAU& tau, MatrixC& c, integer_t& info,
            detail::workspace1< WORK > work ) {
#ifndef NDEBUG
        assert( side == 'L' || side == 'R' );
        assert( trans == 'N' || trans == 'T' );
        assert( traits::matrix_size1(c) >= 0 );
        assert( traits::matrix_size2(c) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,k) );
        assert( traits::vector_size(tau) >= k );
        assert( traits::leading_dimension(c) >= std::max(1,
                traits::matrix_size1(c)) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                side, traits::matrix_size1(c), traits::matrix_size2(c) )));
#endif
        detail::ormrq( side, trans, traits::matrix_size1(c),
                traits::matrix_size2(c), k, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(tau),
                traits::matrix_storage(c), traits::leading_dimension(c),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAU, typename MatrixC >
    static void compute( char const side, char const trans, integer_t const k,
            MatrixA& a, VectorTAU& tau, MatrixC& c, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( side,
                traits::matrix_size1(c), traits::matrix_size2(c) ) );
        compute( side, trans, k, a, tau, c, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAU, typename MatrixC >
    static void compute( char const side, char const trans, integer_t const k,
            MatrixA& a, VectorTAU& tau, MatrixC& c, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        detail::ormrq( side, trans, traits::matrix_size1(c),
                traits::matrix_size2(c), k, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(tau),
                traits::matrix_storage(c), traits::leading_dimension(c),
                &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( side, trans, k, a, tau, c, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( char const side, integer_t const m,
            integer_t const n ) {
        if ( side == 'L' )
            return std::max( 1, n );
        else
            return std::max( 1, m );
    }
};


// template function to call ormrq
template< typename MatrixA, typename VectorTAU, typename MatrixC,
        typename Workspace >
inline integer_t ormrq( char const side, char const trans,
        integer_t const k, MatrixA& a, VectorTAU& tau, MatrixC& c,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ormrq_impl< value_type >::compute( side, trans, k, a, tau, c, info,
            work );
    return info;
}


}}}} // namespace boost::numeric::bindings::lapack

#endif

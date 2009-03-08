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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_OPMTR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_OPMTR_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
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
    inline void opmtr( char const side, char const uplo, char const trans,
            integer_t const m, integer_t const n, float* ap, float* tau,
            float* c, integer_t const ldc, float* work, integer_t& info ) {
        LAPACK_SOPMTR( &side, &uplo, &trans, &m, &n, ap, tau, c, &ldc, work,
                &info );
    }
    inline void opmtr( char const side, char const uplo, char const trans,
            integer_t const m, integer_t const n, double* ap, double* tau,
            double* c, integer_t const ldc, double* work, integer_t& info ) {
        LAPACK_DOPMTR( &side, &uplo, &trans, &m, &n, ap, tau, c, &ldc, work,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct opmtr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorAP, typename VectorTAU, typename MatrixC,
            typename WORK >
    static void compute( char const side, char const uplo, char const trans,
            VectorAP& ap, VectorTAU& tau, MatrixC& c, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorAP >::value_type, typename traits::vector_traits<
                VectorTAU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorAP >::value_type, typename traits::matrix_traits<
                MatrixC >::value_type >::value) );
#ifndef NDEBUG
        assert( side == 'L' || side == 'R' );
        assert( uplo == 'U' || uplo == 'L' );
        assert( trans == 'N' || trans == 'T' );
        assert( traits::matrix_num_rows(c) >= 0 );
        assert( traits::matrix_num_columns(c) >= 0 );
        assert( traits::leading_dimension(c) >= std::max(1,
                traits::matrix_num_rows(c)) );
        assert( traits::vector_size(work.select(real_type())) >=
                min_size_work( side, traits::matrix_num_rows(c),
                traits::matrix_num_columns(c) ));
#endif
        detail::opmtr( side, uplo, trans, traits::matrix_num_rows(c),
                traits::matrix_num_columns(c), traits::vector_storage(ap),
                traits::vector_storage(tau), traits::matrix_storage(c),
                traits::leading_dimension(c),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorAP, typename VectorTAU, typename MatrixC >
    static void compute( char const side, char const uplo, char const trans,
            VectorAP& ap, VectorTAU& tau, MatrixC& c, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( side,
                traits::matrix_num_rows(c), traits::matrix_num_columns(c) ) );
        compute( side, uplo, trans, ap, tau, c, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorAP, typename VectorTAU, typename MatrixC >
    static void compute( char const side, char const uplo, char const trans,
            VectorAP& ap, VectorTAU& tau, MatrixC& c, integer_t& info,
            optimal_workspace work ) {
        compute( side, uplo, trans, ap, tau, c, info, minimal_workspace() );
    }

    static integer_t min_size_work( char const side, integer_t const m,
            integer_t const n ) {
        if ( side == 'L' )
            return n;
        else
            return m;
    }
};


// template function to call opmtr
template< typename VectorAP, typename VectorTAU, typename MatrixC,
        typename Workspace >
inline integer_t opmtr( char const side, char const uplo,
        char const trans, VectorAP& ap, VectorTAU& tau, MatrixC& c,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits< VectorAP >::value_type value_type;
    integer_t info(0);
    opmtr_impl< value_type >::compute( side, uplo, trans, ap, tau, c,
            info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

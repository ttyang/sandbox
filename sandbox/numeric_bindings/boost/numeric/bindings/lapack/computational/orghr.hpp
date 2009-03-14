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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_ORGHR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_ORGHR_HPP

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
    inline void orghr( integer_t const n, integer_t const ilo,
            integer_t const ihi, float* a, integer_t const lda, float* tau,
            float* work, integer_t const lwork, integer_t& info ) {
        LAPACK_SORGHR( &n, &ilo, &ihi, a, &lda, tau, work, &lwork, &info );
    }
    inline void orghr( integer_t const n, integer_t const ilo,
            integer_t const ihi, double* a, integer_t const lda, double* tau,
            double* work, integer_t const lwork, integer_t& info ) {
        LAPACK_DORGHR( &n, &ilo, &ihi, a, &lda, tau, work, &lwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct orghr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorTAU, typename WORK >
    static void compute( integer_t const n, integer_t const ilo,
            integer_t const ihi, MatrixA& a, VectorTAU& tau, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorTAU >::value_type >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(tau) >= n-1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::orghr( n, ilo, ihi, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(tau),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorTAU >
    static void compute( integer_t const n, integer_t const ilo,
            integer_t const ihi, MatrixA& a, VectorTAU& tau, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( n, ilo, ihi, a, tau, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorTAU >
    static void compute( integer_t const n, integer_t const ilo,
            integer_t const ihi, MatrixA& a, VectorTAU& tau, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        detail::orghr( n, ilo, ihi, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(tau),
                &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( n, ilo, ihi, a, tau, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call orghr
template< typename MatrixA, typename VectorTAU, typename Workspace >
inline integer_t orghr( integer_t const n, integer_t const ilo,
        integer_t const ihi, MatrixA& a, VectorTAU& tau,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    orghr_impl< value_type >::compute( n, ilo, ihi, a, tau, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

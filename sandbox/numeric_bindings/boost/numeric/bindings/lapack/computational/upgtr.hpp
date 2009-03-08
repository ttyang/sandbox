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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_UPGTR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_UPGTR_HPP

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
    inline void upgtr( char const uplo, integer_t const n,
            traits::complex_f* ap, traits::complex_f* tau,
            traits::complex_f* q, integer_t const ldq,
            traits::complex_f* work, integer_t& info ) {
        LAPACK_CUPGTR( &uplo, &n, traits::complex_ptr(ap),
                traits::complex_ptr(tau), traits::complex_ptr(q), &ldq,
                traits::complex_ptr(work), &info );
    }
    inline void upgtr( char const uplo, integer_t const n,
            traits::complex_d* ap, traits::complex_d* tau,
            traits::complex_d* q, integer_t const ldq,
            traits::complex_d* work, integer_t& info ) {
        LAPACK_ZUPGTR( &uplo, &n, traits::complex_ptr(ap),
                traits::complex_ptr(tau), traits::complex_ptr(q), &ldq,
                traits::complex_ptr(work), &info );
    }
}

// value-type based template
template< typename ValueType >
struct upgtr_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorAP, typename VectorTAU, typename MatrixQ,
            typename WORK >
    static void compute( char const uplo, VectorAP& ap, VectorTAU& tau,
            MatrixQ& q, integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorAP >::value_type, typename traits::vector_traits<
                VectorTAU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorAP >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
#ifndef NDEBUG
        assert( uplo == 'U' || uplo == 'L' );
        assert( traits::matrix_num_columns(q) >= 0 );
        assert( traits::vector_size(ap) >=
                traits::matrix_num_columns(q)*(traits::matrix_num_columns(q)+
                1)/2 );
        assert( traits::vector_size(tau) >= traits::matrix_num_columns(q)-1 );
        assert( traits::leading_dimension(q) >= std::max(1,
                traits::matrix_num_columns(q)) );
        assert( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(q) ));
#endif
        detail::upgtr( uplo, traits::matrix_num_columns(q),
                traits::vector_storage(ap), traits::vector_storage(tau),
                traits::matrix_storage(q), traits::leading_dimension(q),
                traits::vector_storage(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorAP, typename VectorTAU, typename MatrixQ >
    static void compute( char const uplo, VectorAP& ap, VectorTAU& tau,
            MatrixQ& q, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(q) ) );
        compute( uplo, ap, tau, q, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorAP, typename VectorTAU, typename MatrixQ >
    static void compute( char const uplo, VectorAP& ap, VectorTAU& tau,
            MatrixQ& q, integer_t& info, optimal_workspace work ) {
        compute( uplo, ap, tau, q, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return n-1;
    }
};


// template function to call upgtr
template< typename VectorAP, typename VectorTAU, typename MatrixQ,
        typename Workspace >
inline integer_t upgtr( char const uplo, VectorAP& ap, VectorTAU& tau,
        MatrixQ& q, Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits< VectorAP >::value_type value_type;
    integer_t info(0);
    upgtr_impl< value_type >::compute( uplo, ap, tau, q, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

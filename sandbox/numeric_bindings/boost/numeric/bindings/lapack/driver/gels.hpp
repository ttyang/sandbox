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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GELS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GELS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void gels( char const trans, integer_t const m, integer_t const n,
            integer_t const nrhs, float* a, integer_t const lda, float* b,
            integer_t const ldb, float* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_SGELS( &trans, &m, &n, &nrhs, a, &lda, b, &ldb, work, &lwork,
                &info );
    }
    inline void gels( char const trans, integer_t const m, integer_t const n,
            integer_t const nrhs, double* a, integer_t const lda, double* b,
            integer_t const ldb, double* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_DGELS( &trans, &m, &n, &nrhs, a, &lda, b, &ldb, work, &lwork,
                &info );
    }
    inline void gels( char const trans, integer_t const m, integer_t const n,
            integer_t const nrhs, traits::complex_f* a, integer_t const lda,
            traits::complex_f* b, integer_t const ldb,
            traits::complex_f* work, integer_t const lwork, integer_t& info ) {
        LAPACK_CGELS( &trans, &m, &n, &nrhs, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, traits::complex_ptr(work),
                &lwork, &info );
    }
    inline void gels( char const trans, integer_t const m, integer_t const n,
            integer_t const nrhs, traits::complex_d* a, integer_t const lda,
            traits::complex_d* b, integer_t const ldb,
            traits::complex_d* work, integer_t const lwork, integer_t& info ) {
        LAPACK_ZGELS( &trans, &m, &n, &nrhs, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, traits::complex_ptr(work),
                &lwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gels_impl{};

// real specialization
template< typename ValueType >
struct gels_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename WORK >
    static void compute( char const trans, MatrixA& a, MatrixB& b,
            integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( trans == 'N' || trans == 'T' );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                std::max(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a))) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a),
                traits::matrix_num_columns(b) ));
        detail::gels( trans, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB >
    static void compute( char const trans, MatrixA& a, MatrixB& b,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a),
                traits::matrix_num_columns(b) ) );
        compute( trans, a, b, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB >
    static void compute( char const trans, MatrixA& a, MatrixB& b,
            integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        detail::gels( trans, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( trans, a, b, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            integer_t const nrhs ) {
        integer_t minmn = std::min( m, n );
        return std::max( 1, minmn + std::max( minmn, nrhs ) );
    }
};

// complex specialization
template< typename ValueType >
struct gels_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename WORK >
    static void compute( char const trans, MatrixA& a, MatrixB& b,
            integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_ASSERT( trans == 'N' || trans == 'C' );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                std::max(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a))) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a),
                traits::matrix_num_columns(b) ));
        detail::gels( trans, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB >
    static void compute( char const trans, MatrixA& a, MatrixB& b,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a),
                traits::matrix_num_columns(b) ) );
        compute( trans, a, b, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB >
    static void compute( char const trans, MatrixA& a, MatrixB& b,
            integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        detail::gels( trans, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                &opt_size_work, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( trans, a, b, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            integer_t const nrhs ) {
        integer_t minmn = std::min( m, n );
        return std::max( 1, minmn + std::max( minmn, nrhs ) );
    }
};


// template function to call gels
template< typename MatrixA, typename MatrixB, typename Workspace >
inline integer_t gels( char const trans, MatrixA& a, MatrixB& b,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gels_impl< value_type >::compute( trans, a, b, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

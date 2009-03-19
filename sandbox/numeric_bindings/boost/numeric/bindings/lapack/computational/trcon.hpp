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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRCON_HPP

#include <boost/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/keywords.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
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
    inline void trcon( char const norm, char const uplo, char const diag,
            integer_t const n, float* a, integer_t const lda, float& rcond,
            float* work, integer_t* iwork, integer_t& info ) {
        LAPACK_STRCON( &norm, &uplo, &diag, &n, a, &lda, &rcond, work, iwork,
                &info );
    }
    inline void trcon( char const norm, char const uplo, char const diag,
            integer_t const n, double* a, integer_t const lda, double& rcond,
            double* work, integer_t* iwork, integer_t& info ) {
        LAPACK_DTRCON( &norm, &uplo, &diag, &n, a, &lda, &rcond, work, iwork,
                &info );
    }
    inline void trcon( char const norm, char const uplo, char const diag,
            integer_t const n, traits::complex_f* a, integer_t const lda,
            float& rcond, traits::complex_f* work, float* rwork,
            integer_t& info ) {
        LAPACK_CTRCON( &norm, &uplo, &diag, &n, traits::complex_ptr(a), &lda,
                &rcond, traits::complex_ptr(work), rwork, &info );
    }
    inline void trcon( char const norm, char const uplo, char const diag,
            integer_t const n, traits::complex_d* a, integer_t const lda,
            double& rcond, traits::complex_d* work, double* rwork,
            integer_t& info ) {
        LAPACK_ZTRCON( &norm, &uplo, &diag, &n, traits::complex_ptr(a), &lda,
                &rcond, traits::complex_ptr(work), rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct trcon_impl{};

// real specialization
template< typename ValueType >
struct trcon_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef typename mpl::vector< keywords::tag::A > valid_keywords;

    // user-defined workspace specialization
    template< typename MatrixA, typename WORK, typename IWORK >
    static void compute( char const norm, char const uplo, char const diag,
            MatrixA& a, real_type& rcond, integer_t& info, detail::workspace2<
            WORK, IWORK > work ) {
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( diag == 'N' || diag == 'U' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( traits::matrix_num_columns(a) ));
        detail::trcon( norm, uplo, diag, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                rcond, traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA >
    static void compute( char const norm, char const uplo, char const diag,
            MatrixA& a, real_type& rcond, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_num_columns(a) ) );
        compute( norm, uplo, diag, a, rcond, info, workspace( tmp_work,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA >
    static void compute( char const norm, char const uplo, char const diag,
            MatrixA& a, real_type& rcond, integer_t& info,
            optimal_workspace work ) {
        compute( norm, uplo, diag, a, rcond, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 3*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return n;
    }
};

// complex specialization
template< typename ValueType >
struct trcon_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef typename mpl::vector< keywords::tag::A > valid_keywords;

    // user-defined workspace specialization
    template< typename MatrixA, typename WORK, typename RWORK >
    static void compute( char const norm, char const uplo, char const diag,
            MatrixA& a, real_type& rcond, integer_t& info, detail::workspace2<
            WORK, RWORK > work ) {
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( diag == 'N' || diag == 'U' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( traits::matrix_num_columns(a) ));
        detail::trcon( norm, uplo, diag, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                rcond, traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA >
    static void compute( char const norm, char const uplo, char const diag,
            MatrixA& a, real_type& rcond, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        compute( norm, uplo, diag, a, rcond, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA >
    static void compute( char const norm, char const uplo, char const diag,
            MatrixA& a, real_type& rcond, integer_t& info,
            optimal_workspace work ) {
        compute( norm, uplo, diag, a, rcond, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 2*n;
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return n;
    }
};


// template function to call trcon
template< typename MatrixA, typename Workspace >
inline integer_t trcon( char const norm, char const uplo,
        char const diag, MatrixA& a, typename traits::matrix_traits<
        MatrixA >::value_type& rcond, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    trcon_impl< value_type >::compute( norm, uplo, diag, a, rcond, info,
            work );
    return info;
}

// template function to call trcon, default workspace type
template< typename MatrixA >
inline integer_t trcon( char const norm, char const uplo,
        char const diag, MatrixA& a, typename traits::matrix_traits<
        MatrixA >::value_type& rcond ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    trcon_impl< value_type >::compute( norm, uplo, diag, a, rcond, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

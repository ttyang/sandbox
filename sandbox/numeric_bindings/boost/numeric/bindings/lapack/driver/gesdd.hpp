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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GESDD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GESDD_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
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
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void gesdd( char const jobz, integer_t const m, integer_t const n,
            float* a, integer_t const lda, float* s, float* u,
            integer_t const ldu, float* vt, integer_t const ldvt, float* work,
            integer_t const lwork, integer_t* iwork, integer_t& info ) {
        LAPACK_SGESDD( &jobz, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work,
                &lwork, iwork, &info );
    }
    inline void gesdd( char const jobz, integer_t const m, integer_t const n,
            double* a, integer_t const lda, double* s, double* u,
            integer_t const ldu, double* vt, integer_t const ldvt,
            double* work, integer_t const lwork, integer_t* iwork,
            integer_t& info ) {
        LAPACK_DGESDD( &jobz, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work,
                &lwork, iwork, &info );
    }
    inline void gesdd( char const jobz, integer_t const m, integer_t const n,
            traits::complex_f* a, integer_t const lda, float* s,
            traits::complex_f* u, integer_t const ldu, traits::complex_f* vt,
            integer_t const ldvt, traits::complex_f* work,
            integer_t const lwork, float* rwork, integer_t* iwork,
            integer_t& info ) {
        LAPACK_CGESDD( &jobz, &m, &n, traits::complex_ptr(a), &lda, s,
                traits::complex_ptr(u), &ldu, traits::complex_ptr(vt), &ldvt,
                traits::complex_ptr(work), &lwork, rwork, iwork, &info );
    }
    inline void gesdd( char const jobz, integer_t const m, integer_t const n,
            traits::complex_d* a, integer_t const lda, double* s,
            traits::complex_d* u, integer_t const ldu, traits::complex_d* vt,
            integer_t const ldvt, traits::complex_d* work,
            integer_t const lwork, double* rwork, integer_t* iwork,
            integer_t& info ) {
        LAPACK_ZGESDD( &jobz, &m, &n, traits::complex_ptr(a), &lda, s,
                traits::complex_ptr(u), &ldu, traits::complex_ptr(vt), &ldvt,
                traits::complex_ptr(work), &lwork, rwork, iwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gesdd_impl{};

// real specialization
template< typename ValueType >
struct gesdd_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT, typename WORK, typename IWORK >
    static void compute( char const jobz, MatrixA& a, VectorS& s, MatrixU& u,
            MatrixVT& vt, integer_t& info, detail::workspace2< WORK,
            IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVT >::value_type >::value) );
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
#ifndef NDEBUG
        assert( jobz == 'A' || jobz == 'S' || jobz == 'O' || jobz == 'N' );
        assert( traits::matrix_num_rows(a) >= 0 );
        assert( traits::matrix_num_columns(a) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        assert( traits::vector_size(s) >= std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        assert( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), jobz, minmn ));
        assert( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( minmn ));
#endif
        detail::gesdd( jobz, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void compute( char const jobz, MatrixA& a, VectorS& s, MatrixU& u,
            MatrixVT& vt, integer_t& info, minimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a),
                jobz, minmn ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                minmn ) );
        compute( jobz, a, s, u, vt, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void compute( char const jobz, MatrixA& a, VectorS& s, MatrixU& u,
            MatrixVT& vt, integer_t& info, optimal_workspace work ) {
        compute( jobz, a, s, u, vt, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            char const jobz, integer_t const minmn ) {
        if ( n == 0 ) return 1;
        if ( jobz == 'N' ) return 3*minmn + std::max( std::max(m,n), 7*minmn );
        if ( jobz == 'O' ) return 3*minmn*minmn + std::max( std::max( m,n ),
                5*minmn*minmn + 4*minmn );
        return 3*minmn*minmn + std::max( std::max( m,n ), 4*minmn*minmn +
                4*minmn );
    }

    static integer_t min_size_iwork( integer_t const minmn ) {
            return 8*minmn;
    }
};

// complex specialization
template< typename ValueType >
struct gesdd_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT, typename WORK, typename RWORK, typename IWORK >
    static void compute( char const jobz, MatrixA& a, VectorS& s, MatrixU& u,
            MatrixVT& vt, integer_t& info, detail::workspace3< WORK, RWORK,
            IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVT >::value_type >::value) );
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
#ifndef NDEBUG
        assert( jobz == 'A' || jobz == 'S' || jobz == 'O' || jobz == 'N' );
        assert( traits::matrix_num_rows(a) >= 0 );
        assert( traits::matrix_num_columns(a) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        assert( traits::vector_size(s) >= std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        assert( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), jobz, minmn ));
        assert( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( minmn, jobz ));
        assert( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( minmn ));
#endif
        detail::gesdd( jobz, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void compute( char const jobz, MatrixA& a, VectorS& s, MatrixU& u,
            MatrixVT& vt, integer_t& info, minimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a),
                jobz, minmn ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( minmn,
                jobz ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                minmn ) );
        compute( jobz, a, s, u, vt, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void compute( char const jobz, MatrixA& a, VectorS& s, MatrixU& u,
            MatrixVT& vt, integer_t& info, optimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( minmn,
                jobz ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                minmn ) );
        detail::gesdd( jobz, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                &opt_size_work, -1, traits::vector_storage(tmp_rwork),
                traits::vector_storage(tmp_iwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( jobz, a, s, u, vt, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            char const jobz, integer_t const minmn ) {
        if ( n == 0 ) return 1;
        if ( jobz == 'N' ) return 2*minmn + std::max( m,n );
        if ( jobz == 'O' ) return 2*(minmn*minmn + minmn) + std::max( m, n );
        return minmn*minmn + 2*minmn + std::max( m, n );
    }

    static integer_t min_size_rwork( integer_t const minmn, char const jobz ) {
        if ( jobz == 'N' ) return 5*minmn;
        return 5*minmn*minmn + 7*minmn;
    }

    static integer_t min_size_iwork( integer_t const minmn ) {
            return 8*minmn;
    }
};


// template function to call gesdd
template< typename MatrixA, typename VectorS, typename MatrixU,
        typename MatrixVT, typename Workspace >
inline integer_t gesdd( char const jobz, MatrixA& a, VectorS& s,
        MatrixU& u, MatrixVT& vt, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gesdd_impl< value_type >::compute( jobz, a, s, u, vt, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GESVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GESVD_HPP

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
    inline void gesvd( char const jobu, char const jobvt, integer_t const m,
            integer_t const n, float* a, integer_t const lda, float* s,
            float* u, integer_t const ldu, float* vt, integer_t const ldvt,
            float* work, integer_t const lwork, integer_t& info ) {
        LAPACK_SGESVD( &jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt,
                work, &lwork, &info );
    }
    inline void gesvd( char const jobu, char const jobvt, integer_t const m,
            integer_t const n, double* a, integer_t const lda, double* s,
            double* u, integer_t const ldu, double* vt, integer_t const ldvt,
            double* work, integer_t const lwork, integer_t& info ) {
        LAPACK_DGESVD( &jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt,
                work, &lwork, &info );
    }
    inline void gesvd( char const jobu, char const jobvt, integer_t const m,
            integer_t const n, traits::complex_f* a, integer_t const lda,
            float* s, traits::complex_f* u, integer_t const ldu,
            traits::complex_f* vt, integer_t const ldvt,
            traits::complex_f* work, integer_t const lwork, float* rwork,
            integer_t& info ) {
        LAPACK_CGESVD( &jobu, &jobvt, &m, &n, traits::complex_ptr(a), &lda, s,
                traits::complex_ptr(u), &ldu, traits::complex_ptr(vt), &ldvt,
                traits::complex_ptr(work), &lwork, rwork, &info );
    }
    inline void gesvd( char const jobu, char const jobvt, integer_t const m,
            integer_t const n, traits::complex_d* a, integer_t const lda,
            double* s, traits::complex_d* u, integer_t const ldu,
            traits::complex_d* vt, integer_t const ldvt,
            traits::complex_d* work, integer_t const lwork, double* rwork,
            integer_t& info ) {
        LAPACK_ZGESVD( &jobu, &jobvt, &m, &n, traits::complex_ptr(a), &lda, s,
                traits::complex_ptr(u), &ldu, traits::complex_ptr(vt), &ldvt,
                traits::complex_ptr(work), &lwork, rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gesvd_impl{};

// real specialization
template< typename ValueType >
struct gesvd_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // user-defined workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT, typename WORK >
    static void invoke( char const jobu, char const jobvt, MatrixA& a,
            VectorS& s, MatrixU& u, MatrixVT& vt, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVT >::value_type >::value) );
        BOOST_ASSERT( jobu == 'A' || jobu == 'S' || jobu == 'O' ||
                jobu == 'N' );
        BOOST_ASSERT( jobvt == 'A' || jobvt == 'S' || jobvt == 'O' ||
                jobvt == 'N' );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(s) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) ));
        detail::gesvd( jobu, jobvt, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void invoke( char const jobu, char const jobvt, MatrixA& a,
            VectorS& s, MatrixU& u, MatrixVT& vt, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a) ) );
        invoke( jobu, jobvt, a, s, u, vt, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void invoke( char const jobu, char const jobvt, MatrixA& a,
            VectorS& s, MatrixU& u, MatrixVT& vt, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        detail::gesvd( jobu, jobvt, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                &opt_size_work, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( jobu, jobvt, a, s, u, vt, info, workspace( tmp_work ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n ) {
        integer_t minmn = std::min( m, n );
        return std::max( 1, std::max( 3*minmn+std::max(m,n), 5*minmn ) );
    }
};

// complex specialization
template< typename ValueType >
struct gesvd_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

$INCLUDE_TEMPLATES
    // user-defined workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT, typename WORK, typename RWORK >
    static void invoke( char const jobu, char const jobvt, MatrixA& a,
            VectorS& s, MatrixU& u, MatrixVT& vt, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVT >::value_type >::value) );
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( jobu == 'A' || jobu == 'S' || jobu == 'O' ||
                jobu == 'N' );
        BOOST_ASSERT( jobvt == 'A' || jobvt == 'S' || jobvt == 'O' ||
                jobvt == 'N' );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::vector_size(s) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), minmn ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( minmn ));
        detail::gesvd( jobu, jobvt, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void invoke( char const jobu, char const jobvt, MatrixA& a,
            VectorS& s, MatrixU& u, MatrixVT& vt, integer_t& info,
            minimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_rows(a), traits::matrix_num_columns(a),
                minmn ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                minmn ) );
        invoke( jobu, jobvt, a, s, u, vt, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorS, typename MatrixU,
            typename MatrixVT >
    static void invoke( char const jobu, char const jobvt, MatrixA& a,
            VectorS& s, MatrixU& u, MatrixVT& vt, integer_t& info,
            optimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                minmn ) );
        detail::gesvd( jobu, jobvt, traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(s),
                traits::matrix_storage(u), traits::leading_dimension(u),
                traits::matrix_storage(vt), traits::leading_dimension(vt),
                &opt_size_work, -1, traits::vector_storage(tmp_rwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( jobu, jobvt, a, s, u, vt, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    static integer_t min_size_work( integer_t const m, integer_t const n,
            integer_t const minmn ) {
        return std::max( 1, 2*minmn+std::max(m,n) );
    }

    static integer_t min_size_rwork( integer_t const minmn ) {
        return 5*minmn;
    }
};


// template function to call gesvd
template< typename MatrixA, typename VectorS, typename MatrixU,
        typename MatrixVT, typename Workspace >
inline integer_t gesvd( char const jobu, char const jobvt, MatrixA& a,
        VectorS& s, MatrixU& u, MatrixVT& vt, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gesvd_impl< value_type >::invoke( jobu, jobvt, a, s, u, vt, info,
            work );
    return info;
}

// template function to call gesvd, default workspace type
template< typename MatrixA, typename VectorS, typename MatrixU,
        typename MatrixVT >
inline integer_t gesvd( char const jobu, char const jobvt, MatrixA& a,
        VectorS& s, MatrixU& u, MatrixVT& vt ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gesvd_impl< value_type >::invoke( jobu, jobvt, a, s, u, vt, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

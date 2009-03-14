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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGSVP_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGSVP_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
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
    inline void ggsvp( char const jobu, char const jobv, char const jobq,
            integer_t const m, integer_t const p, integer_t const n, float* a,
            integer_t const lda, float* b, integer_t const ldb,
            float const tola, float const tolb, integer_t& k, integer_t& l,
            float* u, integer_t const ldu, float* v, integer_t const ldv,
            float* q, integer_t const ldq, integer_t* iwork, float* tau,
            float* work, integer_t& info ) {
        LAPACK_SGGSVP( &jobu, &jobv, &jobq, &m, &p, &n, a, &lda, b, &ldb,
                &tola, &tolb, &k, &l, u, &ldu, v, &ldv, q, &ldq, iwork, tau,
                work, &info );
    }
    inline void ggsvp( char const jobu, char const jobv, char const jobq,
            integer_t const m, integer_t const p, integer_t const n,
            double* a, integer_t const lda, double* b, integer_t const ldb,
            double const tola, double const tolb, integer_t& k, integer_t& l,
            double* u, integer_t const ldu, double* v, integer_t const ldv,
            double* q, integer_t const ldq, integer_t* iwork, double* tau,
            double* work, integer_t& info ) {
        LAPACK_DGGSVP( &jobu, &jobv, &jobq, &m, &p, &n, a, &lda, b, &ldb,
                &tola, &tolb, &k, &l, u, &ldu, v, &ldv, q, &ldq, iwork, tau,
                work, &info );
    }
    inline void ggsvp( char const jobu, char const jobv, char const jobq,
            integer_t const m, integer_t const p, integer_t const n,
            traits::complex_f* a, integer_t const lda, traits::complex_f* b,
            integer_t const ldb, float const tola, float const tolb,
            integer_t& k, integer_t& l, traits::complex_f* u,
            integer_t const ldu, traits::complex_f* v, integer_t const ldv,
            traits::complex_f* q, integer_t const ldq, integer_t* iwork,
            float* rwork, traits::complex_f* tau, traits::complex_f* work,
            integer_t& info ) {
        LAPACK_CGGSVP( &jobu, &jobv, &jobq, &m, &p, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &tola, &tolb, &k, &l, traits::complex_ptr(u), &ldu,
                traits::complex_ptr(v), &ldv, traits::complex_ptr(q), &ldq,
                iwork, rwork, traits::complex_ptr(tau),
                traits::complex_ptr(work), &info );
    }
    inline void ggsvp( char const jobu, char const jobv, char const jobq,
            integer_t const m, integer_t const p, integer_t const n,
            traits::complex_d* a, integer_t const lda, traits::complex_d* b,
            integer_t const ldb, double const tola, double const tolb,
            integer_t& k, integer_t& l, traits::complex_d* u,
            integer_t const ldu, traits::complex_d* v, integer_t const ldv,
            traits::complex_d* q, integer_t const ldq, integer_t* iwork,
            double* rwork, traits::complex_d* tau, traits::complex_d* work,
            integer_t& info ) {
        LAPACK_ZGGSVP( &jobu, &jobv, &jobq, &m, &p, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &tola, &tolb, &k, &l, traits::complex_ptr(u), &ldu,
                traits::complex_ptr(v), &ldv, traits::complex_ptr(q), &ldq,
                iwork, rwork, traits::complex_ptr(tau),
                traits::complex_ptr(work), &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct ggsvp_impl{};

// real specialization
template< typename ValueType >
struct ggsvp_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ, typename IWORK, typename TAU,
            typename WORK >
    static void compute( char const jobu, char const jobv, char const jobq,
            MatrixA& a, MatrixB& b, real_type const tola,
            real_type const tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, detail::workspace3<
            IWORK, TAU, WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixV >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_ASSERT( jobu == 'U' || jobu == 'N' );
        BOOST_ASSERT( jobv == 'V' || jobv == 'N' );
        BOOST_ASSERT( jobq == 'Q' || jobq == 'N' );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_rows(b) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_rows(b)) );
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_tau( traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_columns(b),
                traits::matrix_num_rows(a), traits::matrix_num_rows(b) ));
        detail::ggsvp( jobu, jobv, jobq, traits::matrix_num_rows(a),
                traits::matrix_num_rows(b), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b), tola,
                tolb, k, l, traits::matrix_storage(u),
                traits::leading_dimension(u), traits::matrix_storage(v),
                traits::leading_dimension(v), traits::matrix_storage(q),
                traits::leading_dimension(q),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ >
    static void compute( char const jobu, char const jobv, char const jobq,
            MatrixA& a, MatrixB& b, real_type const tola,
            real_type const tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, minimal_workspace work ) {
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_num_columns(b) ) );
        traits::detail::array<
                real_type > tmp_tau( min_size_tau( traits::matrix_num_columns(b) ) );
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(b), traits::matrix_num_rows(a),
                traits::matrix_num_rows(b) ) );
        compute( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                workspace( tmp_iwork, tmp_tau, tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ >
    static void compute( char const jobu, char const jobv, char const jobq,
            MatrixA& a, MatrixB& b, real_type const tola,
            real_type const tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, optimal_workspace work ) {
        compute( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                minimal_workspace() );
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return n;
    }

    static integer_t min_size_tau( integer_t const n ) {
        return n;
    }

    static integer_t min_size_work( integer_t const n, integer_t const m,
            integer_t const p ) {
        return std::max(3*n,std::max(m,p));
    }
};

// complex specialization
template< typename ValueType >
struct ggsvp_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ, typename IWORK,
            typename RWORK, typename TAU, typename WORK >
    static void compute( char const jobu, char const jobv, char const jobq,
            MatrixA& a, MatrixB& b, real_type const tola,
            real_type const tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, detail::workspace4<
            IWORK, RWORK, TAU, WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixU >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixV >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_ASSERT( jobu == 'U' || jobu == 'N' );
        BOOST_ASSERT( jobv == 'V' || jobv == 'N' );
        BOOST_ASSERT( jobq == 'Q' || jobq == 'N' );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_rows(b) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_rows(b)) );
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_tau( traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(b),
                traits::matrix_num_rows(a), traits::matrix_num_rows(b) ));
        detail::ggsvp( jobu, jobv, jobq, traits::matrix_num_rows(a),
                traits::matrix_num_rows(b), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b), tola,
                tolb, k, l, traits::matrix_storage(u),
                traits::leading_dimension(u), traits::matrix_storage(v),
                traits::leading_dimension(v), traits::matrix_storage(q),
                traits::leading_dimension(q),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ >
    static void compute( char const jobu, char const jobv, char const jobq,
            MatrixA& a, MatrixB& b, real_type const tola,
            real_type const tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, minimal_workspace work ) {
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_num_columns(b) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(b) ) );
        traits::detail::array<
                value_type > tmp_tau( min_size_tau( traits::matrix_num_columns(b) ) );
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(b), traits::matrix_num_rows(a),
                traits::matrix_num_rows(b) ) );
        compute( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                workspace( tmp_iwork, tmp_rwork, tmp_tau, tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ >
    static void compute( char const jobu, char const jobv, char const jobq,
            MatrixA& a, MatrixB& b, real_type const tola,
            real_type const tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, optimal_workspace work ) {
        compute( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                minimal_workspace() );
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return n;
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return 2*n;
    }

    static integer_t min_size_tau( integer_t const n ) {
        return n;
    }

    static integer_t min_size_work( integer_t const n, integer_t const m,
            integer_t const p ) {
        return std::max(3*n,std::max(m,p));
    }
};


// template function to call ggsvp
template< typename MatrixA, typename MatrixB, typename MatrixU,
        typename MatrixV, typename MatrixQ, typename Workspace >
inline integer_t ggsvp( char const jobu, char const jobv,
        char const jobq, MatrixA& a, MatrixB& b,
        typename traits::matrix_traits< MatrixA >::value_type const tola,
        typename traits::matrix_traits< MatrixA >::value_type const tolb,
        integer_t& k, integer_t& l, MatrixU& u, MatrixV& v, MatrixQ& q,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggsvp_impl< value_type >::compute( jobu, jobv, jobq, a, b, tola,
            tolb, k, l, u, v, q, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

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
#include <boost/mpl/bool.hpp>
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
    inline void ggsvp( const char jobu, const char jobv, const char jobq,
            const integer_t m, const integer_t p, const integer_t n, float* a,
            const integer_t lda, float* b, const integer_t ldb,
            const float tola, const float tolb, integer_t& k, integer_t& l,
            float* u, const integer_t ldu, float* v, const integer_t ldv,
            float* q, const integer_t ldq, integer_t* iwork, float* tau,
            float* work, integer_t& info ) {
        LAPACK_SGGSVP( &jobu, &jobv, &jobq, &m, &p, &n, a, &lda, b, &ldb,
                &tola, &tolb, &k, &l, u, &ldu, v, &ldv, q, &ldq, iwork, tau,
                work, &info );
    }
    inline void ggsvp( const char jobu, const char jobv, const char jobq,
            const integer_t m, const integer_t p, const integer_t n,
            double* a, const integer_t lda, double* b, const integer_t ldb,
            const double tola, const double tolb, integer_t& k, integer_t& l,
            double* u, const integer_t ldu, double* v, const integer_t ldv,
            double* q, const integer_t ldq, integer_t* iwork, double* tau,
            double* work, integer_t& info ) {
        LAPACK_DGGSVP( &jobu, &jobv, &jobq, &m, &p, &n, a, &lda, b, &ldb,
                &tola, &tolb, &k, &l, u, &ldu, v, &ldv, q, &ldq, iwork, tau,
                work, &info );
    }
    inline void ggsvp( const char jobu, const char jobv, const char jobq,
            const integer_t m, const integer_t p, const integer_t n,
            traits::complex_f* a, const integer_t lda, traits::complex_f* b,
            const integer_t ldb, const float tola, const float tolb,
            integer_t& k, integer_t& l, traits::complex_f* u,
            const integer_t ldu, traits::complex_f* v, const integer_t ldv,
            traits::complex_f* q, const integer_t ldq, integer_t* iwork,
            float* rwork, traits::complex_f* tau, traits::complex_f* work,
            integer_t& info ) {
        LAPACK_CGGSVP( &jobu, &jobv, &jobq, &m, &p, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &tola, &tolb, &k, &l, traits::complex_ptr(u), &ldu,
                traits::complex_ptr(v), &ldv, traits::complex_ptr(q), &ldq,
                iwork, rwork, traits::complex_ptr(tau),
                traits::complex_ptr(work), &info );
    }
    inline void ggsvp( const char jobu, const char jobv, const char jobq,
            const integer_t m, const integer_t p, const integer_t n,
            traits::complex_d* a, const integer_t lda, traits::complex_d* b,
            const integer_t ldb, const double tola, const double tolb,
            integer_t& k, integer_t& l, traits::complex_d* u,
            const integer_t ldu, traits::complex_d* v, const integer_t ldv,
            traits::complex_d* q, const integer_t ldq, integer_t* iwork,
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
    static void invoke( const char jobu, const char jobv, const char jobq,
            MatrixA& a, MatrixB& b, const real_type tola,
            const real_type tolb, integer_t& k, integer_t& l, MatrixU& u,
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
    static void invoke( const char jobu, const char jobv, const char jobq,
            MatrixA& a, MatrixB& b, const real_type tola,
            const real_type tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, minimal_workspace work ) {
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_num_columns(b) ) );
        traits::detail::array<
                real_type > tmp_tau( min_size_tau( traits::matrix_num_columns(b) ) );
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(b), traits::matrix_num_rows(a),
                traits::matrix_num_rows(b) ) );
        invoke( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                workspace( tmp_iwork, tmp_tau, tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ >
    static void invoke( const char jobu, const char jobv, const char jobq,
            MatrixA& a, MatrixB& b, const real_type tola,
            const real_type tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, optimal_workspace work ) {
        invoke( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                minimal_workspace() );
    }

    static integer_t min_size_iwork( const integer_t n ) {
        return n;
    }

    static integer_t min_size_tau( const integer_t n ) {
        return n;
    }

    static integer_t min_size_work( const integer_t n, const integer_t m,
            const integer_t p ) {
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
    static void invoke( const char jobu, const char jobv, const char jobq,
            MatrixA& a, MatrixB& b, const real_type tola,
            const real_type tolb, integer_t& k, integer_t& l, MatrixU& u,
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
    static void invoke( const char jobu, const char jobv, const char jobq,
            MatrixA& a, MatrixB& b, const real_type tola,
            const real_type tolb, integer_t& k, integer_t& l, MatrixU& u,
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
        invoke( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                workspace( tmp_iwork, tmp_rwork, tmp_tau, tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename MatrixU,
            typename MatrixV, typename MatrixQ >
    static void invoke( const char jobu, const char jobv, const char jobq,
            MatrixA& a, MatrixB& b, const real_type tola,
            const real_type tolb, integer_t& k, integer_t& l, MatrixU& u,
            MatrixV& v, MatrixQ& q, integer_t& info, optimal_workspace work ) {
        invoke( jobu, jobv, jobq, a, b, tola, tolb, k, l, u, v, q, info,
                minimal_workspace() );
    }

    static integer_t min_size_iwork( const integer_t n ) {
        return n;
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return 2*n;
    }

    static integer_t min_size_tau( const integer_t n ) {
        return n;
    }

    static integer_t min_size_work( const integer_t n, const integer_t m,
            const integer_t p ) {
        return std::max(3*n,std::max(m,p));
    }
};


// template function to call ggsvp
template< typename MatrixA, typename MatrixB, typename MatrixU,
        typename MatrixV, typename MatrixQ, typename Workspace >
inline integer_t ggsvp( const char jobu, const char jobv,
        const char jobq, MatrixA& a, MatrixB& b,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type tola,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type tolb, integer_t& k, integer_t& l,
        MatrixU& u, MatrixV& v, MatrixQ& q, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggsvp_impl< value_type >::invoke( jobu, jobv, jobq, a, b, tola, tolb,
            k, l, u, v, q, info, work );
    return info;
}

// template function to call ggsvp, default workspace type
template< typename MatrixA, typename MatrixB, typename MatrixU,
        typename MatrixV, typename MatrixQ >
inline integer_t ggsvp( const char jobu, const char jobv,
        const char jobq, MatrixA& a, MatrixB& b,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type tola,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type tolb, integer_t& k, integer_t& l,
        MatrixU& u, MatrixV& v, MatrixQ& q ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    ggsvp_impl< value_type >::invoke( jobu, jobv, jobq, a, b, tola, tolb,
            k, l, u, v, q, info, optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

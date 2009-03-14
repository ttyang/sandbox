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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGSEN_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGSEN_HPP

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
    inline void tgsen( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, logical_t* select, integer_t const n,
            float* a, integer_t const lda, float* b, integer_t const ldb,
            float* alphar, float* alphai, float* beta, float* q,
            integer_t const ldq, float* z, integer_t const ldz, integer_t& m,
            float& pl, float& pr, float* dif, float* work,
            integer_t const lwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_STGSEN( &ijob, &wantq, &wantz, select, &n, a, &lda, b, &ldb,
                alphar, alphai, beta, q, &ldq, z, &ldz, &m, &pl, &pr, dif,
                work, &lwork, iwork, &liwork, &info );
    }
    inline void tgsen( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, logical_t* select, integer_t const n,
            double* a, integer_t const lda, double* b, integer_t const ldb,
            double* alphar, double* alphai, double* beta, double* q,
            integer_t const ldq, double* z, integer_t const ldz, integer_t& m,
            double& pl, double& pr, double* dif, double* work,
            integer_t const lwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_DTGSEN( &ijob, &wantq, &wantz, select, &n, a, &lda, b, &ldb,
                alphar, alphai, beta, q, &ldq, z, &ldz, &m, &pl, &pr, dif,
                work, &lwork, iwork, &liwork, &info );
    }
    inline void tgsen( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, logical_t* select, integer_t const n,
            traits::complex_f* a, integer_t const lda, traits::complex_f* b,
            integer_t const ldb, traits::complex_f* alpha,
            traits::complex_f* beta, traits::complex_f* q,
            integer_t const ldq, traits::complex_f* z, integer_t const ldz,
            integer_t& m, float& pl, float& pr, float* dif,
            traits::complex_f* work, integer_t const lwork, integer_t* iwork,
            integer_t const liwork, integer_t& info ) {
        LAPACK_CTGSEN( &ijob, &wantq, &wantz, select, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                traits::complex_ptr(alpha), traits::complex_ptr(beta),
                traits::complex_ptr(q), &ldq, traits::complex_ptr(z), &ldz,
                &m, &pl, &pr, dif, traits::complex_ptr(work), &lwork, iwork,
                &liwork, &info );
    }
    inline void tgsen( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, logical_t* select, integer_t const n,
            traits::complex_d* a, integer_t const lda, traits::complex_d* b,
            integer_t const ldb, traits::complex_d* alpha,
            traits::complex_d* beta, traits::complex_d* q,
            integer_t const ldq, traits::complex_d* z, integer_t const ldz,
            integer_t& m, double& pl, double& pr, double* dif,
            traits::complex_d* work, integer_t const lwork, integer_t* iwork,
            integer_t const liwork, integer_t& info ) {
        LAPACK_ZTGSEN( &ijob, &wantq, &wantz, select, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                traits::complex_ptr(alpha), traits::complex_ptr(beta),
                traits::complex_ptr(q), &ldq, traits::complex_ptr(z), &ldz,
                &m, &pl, &pr, dif, traits::complex_ptr(work), &lwork, iwork,
                &liwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct tgsen_impl{};

// real specialization
template< typename ValueType >
struct tgsen_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixA, typename MatrixB,
            typename VectorALPHAR, typename VectorALPHAI, typename VectorBETA,
            typename MatrixQ, typename MatrixZ, typename VectorDIF,
            typename WORK, typename IWORK >
    static void compute( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, VectorSELECT& select, integer_t const n,
            MatrixA& a, MatrixB& b, VectorALPHAR& alphar,
            VectorALPHAI& alphai, VectorBETA& beta, MatrixQ& q, MatrixZ& z,
            integer_t& m, real_type& pl, real_type& pr, VectorDIF& dif,
            integer_t& info, detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorALPHAR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorALPHAI >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorBETA >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorDIF >::value_type >::value) );
        BOOST_ASSERT( traits::vector_size(select) >= n );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(alphar) >= n );
        BOOST_ASSERT( traits::vector_size(alphai) >= n );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( $CALL_MIN_SIZE ));
        detail::tgsen( ijob, wantq, wantz, traits::vector_storage(select), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(alphar),
                traits::vector_storage(alphai), traits::vector_storage(beta),
                traits::matrix_storage(q), traits::leading_dimension(q),
                traits::matrix_storage(z), traits::leading_dimension(z), m,
                pl, pr, traits::vector_storage(dif),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixA, typename MatrixB,
            typename VectorALPHAR, typename VectorALPHAI, typename VectorBETA,
            typename MatrixQ, typename MatrixZ, typename VectorDIF >
    static void compute( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, VectorSELECT& select, integer_t const n,
            MatrixA& a, MatrixB& b, VectorALPHAR& alphar,
            VectorALPHAI& alphai, VectorBETA& beta, MatrixQ& q, MatrixZ& z,
            integer_t& m, real_type& pl, real_type& pr, VectorDIF& dif,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                $CALL_MIN_SIZE ) );
        compute( ijob, wantq, wantz, select, n, a, b, alphar, alphai, beta, q,
                z, m, pl, pr, dif, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixA, typename MatrixB,
            typename VectorALPHAR, typename VectorALPHAI, typename VectorBETA,
            typename MatrixQ, typename MatrixZ, typename VectorDIF >
    static void compute( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, VectorSELECT& select, integer_t const n,
            MatrixA& a, MatrixB& b, VectorALPHAR& alphar,
            VectorALPHAI& alphai, VectorBETA& beta, MatrixQ& q, MatrixZ& z,
            integer_t& m, real_type& pl, real_type& pr, VectorDIF& dif,
            integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        integer_t opt_size_iwork;
        detail::tgsen( ijob, wantq, wantz,
                traits::vector_storage(select), n, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(alphar),
                traits::vector_storage(alphai), traits::vector_storage(beta),
                traits::matrix_storage(q), traits::leading_dimension(q),
                traits::matrix_storage(z), traits::leading_dimension(z), m,
                pl, pr, traits::vector_storage(dif), &opt_size_work, -1,
                &opt_size_iwork, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        compute( ijob, wantq, wantz, select, n, a, b, alphar, alphai, beta, q,
                z, m, pl, pr, dif, info, workspace( tmp_work, tmp_iwork ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    static integer_t min_size_iwork( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

// complex specialization
template< typename ValueType >
struct tgsen_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixA, typename MatrixB,
            typename VectorALPHA, typename VectorBETA, typename MatrixQ,
            typename MatrixZ, typename VectorDIF, typename WORK,
            typename IWORK >
    static void compute( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, VectorSELECT& select, integer_t const n,
            MatrixA& a, MatrixB& b, VectorALPHA& alpha, VectorBETA& beta,
            MatrixQ& q, MatrixZ& z, integer_t& m, real_type& pl,
            real_type& pr, VectorDIF& dif, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorALPHA >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorBETA >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixQ >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( traits::vector_size(select) >= n );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,n) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,n) );
        BOOST_ASSERT( traits::vector_size(alpha) >= n );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( $CALL_MIN_SIZE ));
        detail::tgsen( ijob, wantq, wantz, traits::vector_storage(select), n,
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(alpha), traits::vector_storage(beta),
                traits::matrix_storage(q), traits::leading_dimension(q),
                traits::matrix_storage(z), traits::leading_dimension(z), m,
                pl, pr, traits::vector_storage(dif),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixA, typename MatrixB,
            typename VectorALPHA, typename VectorBETA, typename MatrixQ,
            typename MatrixZ, typename VectorDIF >
    static void compute( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, VectorSELECT& select, integer_t const n,
            MatrixA& a, MatrixB& b, VectorALPHA& alpha, VectorBETA& beta,
            MatrixQ& q, MatrixZ& z, integer_t& m, real_type& pl,
            real_type& pr, VectorDIF& dif, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                $CALL_MIN_SIZE ) );
        compute( ijob, wantq, wantz, select, n, a, b, alpha, beta, q, z, m,
                pl, pr, dif, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixA, typename MatrixB,
            typename VectorALPHA, typename VectorBETA, typename MatrixQ,
            typename MatrixZ, typename VectorDIF >
    static void compute( integer_t const ijob, logical_t const wantq,
            logical_t const wantz, VectorSELECT& select, integer_t const n,
            MatrixA& a, MatrixB& b, VectorALPHA& alpha, VectorBETA& beta,
            MatrixQ& q, MatrixZ& z, integer_t& m, real_type& pl,
            real_type& pr, VectorDIF& dif, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        integer_t opt_size_iwork;
        detail::tgsen( ijob, wantq, wantz,
                traits::vector_storage(select), n, traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), traits::vector_storage(alpha),
                traits::vector_storage(beta), traits::matrix_storage(q),
                traits::leading_dimension(q), traits::matrix_storage(z),
                traits::leading_dimension(z), m, pl, pr,
                traits::vector_storage(dif), &opt_size_work, -1,
                &opt_size_iwork, -1, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        compute( ijob, wantq, wantz, select, n, a, b, alpha, beta, q, z, m,
                pl, pr, dif, info, workspace( tmp_work, tmp_iwork ) );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    static integer_t min_size_iwork( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call tgsen
template< typename VectorSELECT, typename MatrixA, typename MatrixB,
        typename VectorALPHAR, typename VectorALPHAI, typename VectorBETA,
        typename MatrixQ, typename MatrixZ, typename VectorDIF,
        typename Workspace >
inline integer_t tgsen( integer_t const ijob, logical_t const wantq,
        logical_t const wantz, VectorSELECT& select, integer_t const n,
        MatrixA& a, MatrixB& b, VectorALPHAR& alphar, VectorALPHAI& alphai,
        VectorBETA& beta, MatrixQ& q, MatrixZ& z, integer_t& m,
        typename traits::vector_traits< VectorSELECT >::value_type& pl,
        typename traits::vector_traits< VectorSELECT >::value_type& pr,
        VectorDIF& dif, Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits<
            VectorSELECT >::value_type value_type;
    integer_t info(0);
    tgsen_impl< value_type >::compute( ijob, wantq, wantz, select, n, a,
            b, alphar, alphai, beta, q, z, m, pl, pr, dif, info, work );
    return info;
}
// template function to call tgsen
template< typename VectorSELECT, typename MatrixA, typename MatrixB,
        typename VectorALPHA, typename VectorBETA, typename MatrixQ,
        typename MatrixZ, typename VectorDIF, typename Workspace >
inline integer_t tgsen( integer_t const ijob, logical_t const wantq,
        logical_t const wantz, VectorSELECT& select, integer_t const n,
        MatrixA& a, MatrixB& b, VectorALPHA& alpha, VectorBETA& beta,
        MatrixQ& q, MatrixZ& z, integer_t& m, typename traits::vector_traits<
        VectorSELECT >::value_type& pl, typename traits::vector_traits<
        VectorSELECT >::value_type& pr, VectorDIF& dif,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits<
            VectorSELECT >::value_type value_type;
    integer_t info(0);
    tgsen_impl< value_type >::compute( ijob, wantq, wantz, select, n, a,
            b, alpha, beta, q, z, m, pl, pr, dif, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

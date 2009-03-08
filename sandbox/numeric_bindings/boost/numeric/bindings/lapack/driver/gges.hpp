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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_GGES_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_GGES_HPP

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
    inline void gges( char const jobvsl, char const jobvsr, char const sort,
            logical_t* selctg, integer_t const n, float* a,
            integer_t const lda, float* b, integer_t const ldb,
            integer_t& sdim, float* alphar, float* alphai, float* beta,
            float* vsl, integer_t const ldvsl, float* vsr,
            integer_t const ldvsr, float* work, integer_t const lwork,
            logical_t* bwork, integer_t& info ) {
        LAPACK_SGGES( &jobvsl, &jobvsr, &sort, &selctg, &n, a, &lda, b, &ldb,
                &sdim, alphar, alphai, beta, vsl, &ldvsl, vsr, &ldvsr, work,
                &lwork, bwork, &info );
    }
    inline void gges( char const jobvsl, char const jobvsr, char const sort,
            logical_t* selctg, integer_t const n, double* a,
            integer_t const lda, double* b, integer_t const ldb,
            integer_t& sdim, double* alphar, double* alphai, double* beta,
            double* vsl, integer_t const ldvsl, double* vsr,
            integer_t const ldvsr, double* work, integer_t const lwork,
            logical_t* bwork, integer_t& info ) {
        LAPACK_DGGES( &jobvsl, &jobvsr, &sort, &selctg, &n, a, &lda, b, &ldb,
                &sdim, alphar, alphai, beta, vsl, &ldvsl, vsr, &ldvsr, work,
                &lwork, bwork, &info );
    }
    inline void gges( char const jobvsl, char const jobvsr, char const sort,
            logical_t* selctg, integer_t const n, traits::complex_f* a,
            integer_t const lda, traits::complex_f* b, integer_t const ldb,
            integer_t& sdim, traits::complex_f* alpha,
            traits::complex_f* beta, traits::complex_f* vsl,
            integer_t const ldvsl, traits::complex_f* vsr,
            integer_t const ldvsr, traits::complex_f* work,
            integer_t const lwork, float* rwork, logical_t* bwork,
            integer_t& info ) {
        LAPACK_CGGES( &jobvsl, &jobvsr, &sort, &selctg, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &sdim, traits::complex_ptr(alpha), traits::complex_ptr(beta),
                traits::complex_ptr(vsl), &ldvsl, traits::complex_ptr(vsr),
                &ldvsr, traits::complex_ptr(work), &lwork, rwork, bwork,
                &info );
    }
    inline void gges( char const jobvsl, char const jobvsr, char const sort,
            logical_t* selctg, integer_t const n, traits::complex_d* a,
            integer_t const lda, traits::complex_d* b, integer_t const ldb,
            integer_t& sdim, traits::complex_d* alpha,
            traits::complex_d* beta, traits::complex_d* vsl,
            integer_t const ldvsl, traits::complex_d* vsr,
            integer_t const ldvsr, traits::complex_d* work,
            integer_t const lwork, double* rwork, logical_t* bwork,
            integer_t& info ) {
        LAPACK_ZGGES( &jobvsl, &jobvsr, &sort, &selctg, &n,
                traits::complex_ptr(a), &lda, traits::complex_ptr(b), &ldb,
                &sdim, traits::complex_ptr(alpha), traits::complex_ptr(beta),
                traits::complex_ptr(vsl), &ldvsl, traits::complex_ptr(vsr),
                &ldvsr, traits::complex_ptr(work), &lwork, rwork, bwork,
                &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gges_impl{};

// real specialization
template< typename ValueType >
struct gges_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorALPHAR,
            typename VectorALPHAI, typename VectorBETA, typename MatrixVSL,
            typename MatrixVSR, typename WORK, typename BWORK >
    static void compute( char const jobvsl, char const jobvsr,
            char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
            integer_t& sdim, VectorALPHAR& alphar, VectorALPHAI& alphai,
            VectorBETA& beta, MatrixVSL& vsl, MatrixVSR& vsr, integer_t& info,
            detail::workspace2< WORK, BWORK > work ) {
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
                MatrixVSL >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVSR >::value_type >::value) );
#ifndef NDEBUG
        assert( jobvsl == 'N' || jobvsl == 'V' );
        assert( jobvsr == 'N' || jobvsr == 'V' );
        assert( sort == 'N' || sort == 'S' );
        assert( traits::matrix_num_columns(a) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_columns(a)) );
        assert( traits::vector_size(alphar) >= traits::matrix_num_columns(a) );
        assert( traits::vector_size(alphai) >= traits::matrix_num_columns(a) );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                traits::matrix_num_columns(a) )));
        assert( traits::vector_size(work.select(bool()) >= min_size_bwork(
                traits::matrix_num_columns(a), sort )));
#endif
        detail::gges( jobvsl, jobvsr, sort, selctg,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), sdim,
                traits::vector_storage(alphar),
                traits::vector_storage(alphai), traits::vector_storage(beta),
                traits::matrix_storage(vsl), traits::leading_dimension(vsl),
                traits::matrix_storage(vsr), traits::leading_dimension(vsr),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(bool())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorALPHAR,
            typename VectorALPHAI, typename VectorBETA, typename MatrixVSL,
            typename MatrixVSR >
    static void compute( char const jobvsl, char const jobvsr,
            char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
            integer_t& sdim, VectorALPHAR& alphar, VectorALPHAI& alphai,
            VectorBETA& beta, MatrixVSL& vsl, MatrixVSR& vsr, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        compute( jobvsl, jobvsr, sort, selctg, a, b, sdim, alphar, alphai,
                beta, vsl, vsr, info, workspace( tmp_work, tmp_bwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorALPHAR,
            typename VectorALPHAI, typename VectorBETA, typename MatrixVSL,
            typename MatrixVSR >
    static void compute( char const jobvsl, char const jobvsr,
            char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
            integer_t& sdim, VectorALPHAR& alphar, VectorALPHAI& alphai,
            VectorBETA& beta, MatrixVSL& vsl, MatrixVSR& vsr, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        detail::gges( jobvsl, jobvsr, sort, selctg,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), sdim,
                traits::vector_storage(alphar),
                traits::vector_storage(alphai), traits::vector_storage(beta),
                traits::matrix_storage(vsl), traits::leading_dimension(vsl),
                traits::matrix_storage(vsr), traits::leading_dimension(vsr),
                &opt_size_work, -1, traits::vector_storage(tmp_bwork), info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( jobvsl, jobvsr, sort, selctg, a, b, sdim, alphar, alphai,
                beta, vsl, vsr, info, workspace( tmp_work, tmp_bwork ) );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max( 1, 8*n + 16 );
    }

    static integer_t min_size_bwork( integer_t const n, char const sort ) {
        if ( sort == 'N' )
            return 0;
        else
            return n;
    }
};

// complex specialization
template< typename ValueType >
struct gges_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixVSL, typename MatrixVSR,
            typename WORK, typename RWORK, typename BWORK >
    static void compute( char const jobvsl, char const jobvsr,
            char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
            integer_t& sdim, VectorALPHA& alpha, VectorBETA& beta,
            MatrixVSL& vsl, MatrixVSR& vsr, integer_t& info,
            detail::workspace3< WORK, RWORK, BWORK > work ) {
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
                MatrixVSL >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVSR >::value_type >::value) );
#ifndef NDEBUG
        assert( jobvsl == 'N' || jobvsl == 'V' );
        assert( jobvsr == 'N' || jobvsr == 'V' );
        assert( sort == 'N' || sort == 'S' );
        assert( traits::matrix_num_columns(a) >= 0 );
        assert( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        assert( traits::leading_dimension(b) >= std::max(1,
                traits::matrix_num_columns(a)) );
        assert( traits::vector_size(alpha) >= traits::matrix_num_columns(a) );
        assert( traits::vector_size(beta) >= traits::matrix_num_columns(a) );
        assert( traits::vector_size(work.select(value_type()) >=
                min_size_work( traits::matrix_num_columns(a) )));
        assert( traits::vector_size(work.select(real_type()) >=
                min_size_rwork( traits::matrix_num_columns(a) )));
        assert( traits::vector_size(work.select(bool()) >= min_size_bwork(
                traits::matrix_num_columns(a), sort )));
#endif
        detail::gges( jobvsl, jobvsr, sort, selctg,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), sdim,
                traits::vector_storage(alpha), traits::vector_storage(beta),
                traits::matrix_storage(vsl), traits::leading_dimension(vsl),
                traits::matrix_storage(vsr), traits::leading_dimension(vsr),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(bool())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixVSL, typename MatrixVSR >
    static void compute( char const jobvsl, char const jobvsr,
            char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
            integer_t& sdim, VectorALPHA& alpha, VectorBETA& beta,
            MatrixVSL& vsl, MatrixVSR& vsr, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        compute( jobvsl, jobvsr, sort, selctg, a, b, sdim, alpha, beta, vsl,
                vsr, info, workspace( tmp_work, tmp_rwork, tmp_bwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorALPHA,
            typename VectorBETA, typename MatrixVSL, typename MatrixVSR >
    static void compute( char const jobvsl, char const jobvsr,
            char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
            integer_t& sdim, VectorALPHA& alpha, VectorBETA& beta,
            MatrixVSL& vsl, MatrixVSR& vsr, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        detail::gges( jobvsl, jobvsr, sort, selctg,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::matrix_storage(b),
                traits::leading_dimension(b), sdim,
                traits::vector_storage(alpha), traits::vector_storage(beta),
                traits::matrix_storage(vsl), traits::leading_dimension(vsl),
                traits::matrix_storage(vsr), traits::leading_dimension(vsr),
                &opt_size_work, -1, traits::vector_storage(tmp_rwork),
                traits::vector_storage(tmp_bwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        compute( jobvsl, jobvsr, sort, selctg, a, b, sdim, alpha, beta, vsl,
                vsr, info, workspace( tmp_work, tmp_rwork, tmp_bwork ) );
    }

    static integer_t min_size_work( integer_t const n ) {
        return std::max( 1, 2*n );
    }

    static integer_t min_size_rwork( integer_t const n ) {
        return 8*n;
    }

    static integer_t min_size_bwork( integer_t const n, char const sort ) {
        if ( sort == 'N' )
            return 0;
        else
            return n;
    }
};


// template function to call gges
template< typename MatrixA, typename MatrixB, typename VectorALPHAR,
        typename VectorALPHAI, typename VectorBETA, typename MatrixVSL,
        typename MatrixVSR, typename Workspace >
inline integer_t gges( char const jobvsl, char const jobvsr,
        char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
        integer_t& sdim, VectorALPHAR& alphar, VectorALPHAI& alphai,
        VectorBETA& beta, MatrixVSL& vsl, MatrixVSR& vsr,
        Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gges_impl< value_type >::compute( jobvsl, jobvsr, sort, selctg, a,
            b, sdim, alphar, alphai, beta, vsl, vsr, info, work );
    return info;
}
// template function to call gges
template< typename MatrixA, typename MatrixB, typename VectorALPHA,
        typename VectorBETA, typename MatrixVSL, typename MatrixVSR,
        typename Workspace >
inline integer_t gges( char const jobvsl, char const jobvsr,
        char const sort, logical_t* selctg, MatrixA& a, MatrixB& b,
        integer_t& sdim, VectorALPHA& alpha, VectorBETA& beta, MatrixVSL& vsl,
        MatrixVSR& vsr, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gges_impl< value_type >::compute( jobvsl, jobvsr, sort, selctg, a,
            b, sdim, alpha, beta, vsl, vsr, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

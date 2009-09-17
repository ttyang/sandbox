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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GELSD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GELSD_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/auxiliary/ilaenv.hpp>
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
    inline void gelsd( const integer_t m, const integer_t n,
            const integer_t nrhs, const float* a, const integer_t lda,
            float* b, const integer_t ldb, float* s, const float rcond,
            integer_t& rank, float* work, const integer_t lwork,
            integer_t* iwork, integer_t& info ) {
        LAPACK_SGELSD( &m, &n, &nrhs, a, &lda, b, &ldb, s, &rcond, &rank,
                work, &lwork, iwork, &info );
    }
    inline void gelsd( const integer_t m, const integer_t n,
            const integer_t nrhs, const double* a, const integer_t lda,
            double* b, const integer_t ldb, double* s, const double rcond,
            integer_t& rank, double* work, const integer_t lwork,
            integer_t* iwork, integer_t& info ) {
        LAPACK_DGELSD( &m, &n, &nrhs, a, &lda, b, &ldb, s, &rcond, &rank,
                work, &lwork, iwork, &info );
    }
    inline void gelsd( const integer_t m, const integer_t n,
            const integer_t nrhs, traits::complex_f* a, const integer_t lda,
            traits::complex_f* b, const integer_t ldb, float* s,
            const float rcond, integer_t& rank, traits::complex_f* work,
            const integer_t lwork, float* rwork, integer_t* iwork,
            integer_t& info ) {
        LAPACK_CGELSD( &m, &n, &nrhs, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, s, &rcond, &rank,
                traits::complex_ptr(work), &lwork, rwork, iwork, &info );
    }
    inline void gelsd( const integer_t m, const integer_t n,
            const integer_t nrhs, const traits::complex_d* a,
            const integer_t lda, traits::complex_d* b, const integer_t ldb,
            double* s, const double rcond, integer_t& rank,
            traits::complex_d* work, const integer_t lwork, double* rwork,
            integer_t* iwork, integer_t& info ) {
        LAPACK_ZGELSD( &m, &n, &nrhs, traits::complex_ptr(a), &lda,
                traits::complex_ptr(b), &ldb, s, &rcond, &rank,
                traits::complex_ptr(work), &lwork, rwork, iwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct gelsd_impl{};

// real specialization
template< typename ValueType >
struct gelsd_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS,
            typename WORK, typename IWORK >
    static void invoke( const MatrixA& a, MatrixB& b, VectorS& s,
            const real_type rcond, integer_t& rank, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        integer_t smlsiz = ilaenv(9, "GELSD", "");
        integer_t nlvl = static_cast<integer_t>(((std::log(
                static_cast<real_type>(minmn)) /
                std::log(static_cast<real_type>(2.))) / (smlsiz+1)) + 1);
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                std::max(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a))) );
        BOOST_ASSERT( traits::vector_size(s) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( minmn, smlsiz, nlvl,
                traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( minmn, nlvl ));
        detail::gelsd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(s), rcond, rank,
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void invoke( const MatrixA& a, MatrixB& b, VectorS& s,
            const real_type rcond, integer_t& rank, integer_t& info,
            minimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        integer_t smlsiz = ilaenv(9, "GELSD", "");
        integer_t nlvl = static_cast<integer_t>(((std::log(
                static_cast<real_type>(minmn)) /
                std::log(static_cast<real_type>(2.))) / (smlsiz+1)) + 1);
        traits::detail::array< real_type > tmp_work( min_size_work( minmn,
                smlsiz, nlvl, traits::matrix_num_columns(b) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( minmn,
                nlvl ) );
        invoke( a, b, s, rcond, rank, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void invoke( const MatrixA& a, MatrixB& b, VectorS& s,
            const real_type rcond, integer_t& rank, integer_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        integer_t opt_size_iwork;
        detail::gelsd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(s), rcond, rank, &opt_size_work, -1,
                &opt_size_iwork, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        invoke( a, b, s, rcond, rank, info, workspace( tmp_work, tmp_iwork ) );
    }

    static integer_t min_size_work( const integer_t minmn,
            const integer_t smlsiz, const integer_t nlvl,
            const integer_t nrhs ) {
        integer_t smlsiz_plus_one = smlsiz + 1;
        return std::max( 1, 12*minmn + 2*minmn*smlsiz + 8*minmn*nlvl +
                minmn*nrhs + smlsiz_plus_one * smlsiz_plus_one );
    }

    static integer_t min_size_iwork( const integer_t minmn,
            const integer_t nlvl ) {
        return std::max( 1, 3*minmn*nlvl + 11*minmn );
    }
};

// complex specialization
template< typename ValueType >
struct gelsd_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS,
            typename WORK, typename RWORK, typename IWORK >
    static void invoke( MatrixA& a, MatrixB& b, VectorS& s,
            const real_type rcond, integer_t& rank, integer_t& info,
            detail::workspace3< WORK, RWORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixB >::value_type >::value) );
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        integer_t smlsiz = ilaenv(9, "GELSD", "");
        integer_t nlvl = static_cast<integer_t>(((std::log(
                static_cast<real_type>(minmn)) /
                std::log(static_cast<real_type>(2.))) / (smlsiz+1)) + 1);
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(b) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        BOOST_ASSERT( traits::leading_dimension(b) >= std::max(1,
                std::max(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a))) );
        BOOST_ASSERT( traits::vector_size(s) >=
                std::min(traits::matrix_num_rows(a),
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( minmn, traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( minmn, smlsiz, nlvl,
                traits::matrix_num_columns(b) ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( minmn, nlvl ));
        detail::gelsd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(s), rcond, rank,
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void invoke( MatrixA& a, MatrixB& b, VectorS& s,
            const real_type rcond, integer_t& rank, integer_t& info,
            minimal_workspace work ) {
        integer_t minmn = std::min( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a) );
        integer_t smlsiz = ilaenv(9, "GELSD", "");
        integer_t nlvl = static_cast<integer_t>(((std::log(
                static_cast<real_type>(minmn)) /
                std::log(static_cast<real_type>(2.))) / (smlsiz+1)) + 1);
        traits::detail::array< value_type > tmp_work( min_size_work( minmn,
                traits::matrix_num_columns(b) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork( minmn,
                smlsiz, nlvl, traits::matrix_num_columns(b) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( minmn,
                nlvl ) );
        invoke( a, b, s, rcond, rank, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename MatrixB, typename VectorS >
    static void invoke( MatrixA& a, MatrixB& b, VectorS& s,
            const real_type rcond, integer_t& rank, integer_t& info,
            optimal_workspace work ) {
        value_type opt_size_work;
        real_type opt_size_rwork;
        integer_t opt_size_iwork;
        detail::gelsd( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_num_columns(b),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::matrix_storage(b), traits::leading_dimension(b),
                traits::vector_storage(s), rcond, rank, &opt_size_work, -1,
                &opt_size_rwork, &opt_size_iwork, info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        invoke( a, b, s, rcond, rank, info, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    static integer_t min_size_work( const integer_t minmn,
            const integer_t nrhs ) {
        return std::max( 1, 2*minmn + minmn*nrhs );
    }

    static integer_t min_size_rwork( const integer_t minmn,
            const integer_t smlsiz, const integer_t nlvl,
            const integer_t nrhs ) {
        integer_t smlsiz_plus_one = smlsiz + 1;
        return std::max( 1, 10*minmn + 2*minmn*smlsiz + 8*minmn*nlvl +
                3*smlsiz*nrhs + smlsiz_plus_one * smlsiz_plus_one );
    }

    static integer_t min_size_iwork( const integer_t minmn,
            const integer_t nlvl ) {
        return std::max( 1, 3*minmn*nlvl + 11*minmn );
    }
};


// template function to call gelsd
template< typename MatrixA, typename MatrixB, typename VectorS,
        typename Workspace >
inline integer_t gelsd( const MatrixA& a, MatrixB& b, VectorS& s,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type rcond, integer_t& rank,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gelsd_impl< value_type >::invoke( a, b, s, rcond, rank, info, work );
    return info;
}

// template function to call gelsd, default workspace type
template< typename MatrixA, typename MatrixB, typename VectorS >
inline integer_t gelsd( const MatrixA& a, MatrixB& b, VectorS& s,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type rcond, integer_t& rank ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gelsd_impl< value_type >::invoke( a, b, s, rcond, rank, info,
            optimal_workspace() );
    return info;
}
// template function to call gelsd
template< typename MatrixA, typename MatrixB, typename VectorS,
        typename Workspace >
inline integer_t gelsd( MatrixA& a, MatrixB& b, VectorS& s,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type rcond, integer_t& rank,
        Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gelsd_impl< value_type >::invoke( a, b, s, rcond, rank, info, work );
    return info;
}

// template function to call gelsd, default workspace type
template< typename MatrixA, typename MatrixB, typename VectorS >
inline integer_t gelsd( MatrixA& a, MatrixB& b, VectorS& s,
        const typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type rcond, integer_t& rank ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gelsd_impl< value_type >::invoke( a, b, s, rcond, rank, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

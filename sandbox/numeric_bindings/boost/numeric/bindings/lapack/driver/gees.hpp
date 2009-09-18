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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEES_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEES_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
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

inline void gees( const char jobvs, const char sort, logical_t* select,
        const integer_t n, float* a, const integer_t lda, integer_t& sdim,
        float* wr, float* wi, float* vs, const integer_t ldvs, float* work,
        const integer_t lwork, logical_t* bwork, integer_t& info ) {
    LAPACK_SGEES( &jobvs, &sort, &select, &n, a, &lda, &sdim, wr, wi, vs,
            &ldvs, work, &lwork, bwork, &info );
}

inline void gees( const char jobvs, const char sort, logical_t* select,
        const integer_t n, double* a, const integer_t lda, integer_t& sdim,
        double* wr, double* wi, double* vs, const integer_t ldvs,
        double* work, const integer_t lwork, logical_t* bwork,
        integer_t& info ) {
    LAPACK_DGEES( &jobvs, &sort, &select, &n, a, &lda, &sdim, wr, wi, vs,
            &ldvs, work, &lwork, bwork, &info );
}

inline void gees( const char jobvs, const char sort, logical_t* select,
        const integer_t n, traits::complex_f* a, const integer_t lda,
        integer_t& sdim, traits::complex_f* w, traits::complex_f* vs,
        const integer_t ldvs, traits::complex_f* work, const integer_t lwork,
        float* rwork, logical_t* bwork, integer_t& info ) {
    LAPACK_CGEES( &jobvs, &sort, &select, &n, traits::complex_ptr(a), &lda,
            &sdim, traits::complex_ptr(w), traits::complex_ptr(vs), &ldvs,
            traits::complex_ptr(work), &lwork, rwork, bwork, &info );
}

inline void gees( const char jobvs, const char sort, logical_t* select,
        const integer_t n, traits::complex_d* a, const integer_t lda,
        integer_t& sdim, traits::complex_d* w, traits::complex_d* vs,
        const integer_t ldvs, traits::complex_d* work, const integer_t lwork,
        double* rwork, logical_t* bwork, integer_t& info ) {
    LAPACK_ZGEES( &jobvs, &sort, &select, &n, traits::complex_ptr(a), &lda,
            &sdim, traits::complex_ptr(w), traits::complex_ptr(vs), &ldvs,
            traits::complex_ptr(work), &lwork, rwork, bwork, &info );
}

} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct gees_impl{};

// real specialization
template< typename ValueType >
struct gees_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVS, typename WORK, typename BWORK >
    static void invoke( const char jobvs, const char sort, logical_t* select,
            MatrixA& a, integer_t& sdim, VectorWR& wr, VectorWI& wi,
            MatrixVS& vs, integer_t& info, detail::workspace2< WORK,
            BWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorWR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorWI >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVS >::value_type >::value) );
        BOOST_ASSERT( jobvs == 'N' || jobvs == 'V' );
        BOOST_ASSERT( sort == 'N' || sort == 'S' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(wr) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(wi) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(bool())) >=
                min_size_bwork( traits::matrix_num_columns(a), sort ));
        detail::gees( jobvs, sort, select, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a), sdim,
                traits::vector_storage(wr), traits::vector_storage(wi),
                traits::matrix_storage(vs), traits::leading_dimension(vs),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(bool())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVS >
    static void invoke( const char jobvs, const char sort, logical_t* select,
            MatrixA& a, integer_t& sdim, VectorWR& wr, VectorWI& wi,
            MatrixVS& vs, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        invoke( jobvs, sort, select, a, sdim, wr, wi, vs, info,
                workspace( tmp_work, tmp_bwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVS >
    static void invoke( const char jobvs, const char sort, logical_t* select,
            MatrixA& a, integer_t& sdim, VectorWR& wr, VectorWI& wi,
            MatrixVS& vs, integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        detail::gees( jobvs, sort, select,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), sdim,
                traits::vector_storage(wr), traits::vector_storage(wi),
                traits::matrix_storage(vs), traits::leading_dimension(vs),
                &opt_size_work, -1, traits::vector_storage(tmp_bwork), info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( jobvs, sort, select, a, sdim, wr, wi, vs, info,
                workspace( tmp_work, tmp_bwork ) );
    }

    static integer_t min_size_work( const integer_t n ) {
        return std::max( 1, 3*n );
    }

    static integer_t min_size_bwork( const integer_t n, const char sort ) {
        if ( sort == 'N' )
            return 0;
        else
            return n;
    }
};

// complex specialization
template< typename ValueType >
struct gees_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixVS,
            typename WORK, typename RWORK, typename BWORK >
    static void invoke( const char jobvs, const char sort, logical_t* select,
            MatrixA& a, integer_t& sdim, VectorW& w, MatrixVS& vs,
            integer_t& info, detail::workspace3< WORK, RWORK, BWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::matrix_traits<
                MatrixVS >::value_type >::value) );
        BOOST_ASSERT( jobvs == 'N' || jobvs == 'V' );
        BOOST_ASSERT( sort == 'N' || sort == 'S' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(w) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(bool())) >=
                min_size_bwork( traits::matrix_num_columns(a), sort ));
        detail::gees( jobvs, sort, select, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a), sdim,
                traits::vector_storage(w), traits::matrix_storage(vs),
                traits::leading_dimension(vs),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(bool())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixVS >
    static void invoke( const char jobvs, const char sort, logical_t* select,
            MatrixA& a, integer_t& sdim, VectorW& w, MatrixVS& vs,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        invoke( jobvs, sort, select, a, sdim, w, vs, info,
                workspace( tmp_work, tmp_rwork, tmp_bwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorW, typename MatrixVS >
    static void invoke( const char jobvs, const char sort, logical_t* select,
            MatrixA& a, integer_t& sdim, VectorW& w, MatrixVS& vs,
            integer_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< bool > tmp_bwork( min_size_bwork(
                traits::matrix_num_columns(a), sort ) );
        detail::gees( jobvs, sort, select,
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), sdim, traits::vector_storage(w),
                traits::matrix_storage(vs), traits::leading_dimension(vs),
                &opt_size_work, -1, traits::vector_storage(tmp_rwork),
                traits::vector_storage(tmp_bwork), info );
        traits::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( jobvs, sort, select, a, sdim, w, vs, info,
                workspace( tmp_work, tmp_rwork, tmp_bwork ) );
    }

    static integer_t min_size_work( const integer_t n ) {
        return std::max( 1, 2*n );
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return n;
    }

    static integer_t min_size_bwork( const integer_t n, const char sort ) {
        if ( sort == 'N' )
            return 0;
        else
            return n;
    }
};


// template function to call gees
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS, typename Workspace >
inline integer_t gees( const char jobvs, const char sort,
        logical_t* select, MatrixA& a, integer_t& sdim, VectorWR& wr,
        VectorWI& wi, MatrixVS& vs, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gees_impl< value_type >::invoke( jobvs, sort, select, a, sdim, wr,
            wi, vs, info, work );
    return info;
}

// template function to call gees, default workspace type
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS >
inline integer_t gees( const char jobvs, const char sort,
        logical_t* select, MatrixA& a, integer_t& sdim, VectorWR& wr,
        VectorWI& wi, MatrixVS& vs ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gees_impl< value_type >::invoke( jobvs, sort, select, a, sdim, wr,
            wi, vs, info, optimal_workspace() );
    return info;
}
// template function to call gees
template< typename MatrixA, typename VectorW, typename MatrixVS,
        typename Workspace >
inline integer_t gees( const char jobvs, const char sort,
        logical_t* select, MatrixA& a, integer_t& sdim, VectorW& w,
        MatrixVS& vs, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gees_impl< value_type >::invoke( jobvs, sort, select, a, sdim, w,
            vs, info, work );
    return info;
}

// template function to call gees, default workspace type
template< typename MatrixA, typename VectorW, typename MatrixVS >
inline integer_t gees( const char jobvs, const char sort,
        logical_t* select, MatrixA& a, integer_t& sdim, VectorW& w,
        MatrixVS& vs ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    gees_impl< value_type >::invoke( jobvs, sort, select, a, sdim, w,
            vs, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

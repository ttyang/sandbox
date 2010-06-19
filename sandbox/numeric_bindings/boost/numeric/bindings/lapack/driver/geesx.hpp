//
// Copyright (c) 2002--2010
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEESX_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEESX_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for geesx is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
inline std::ptrdiff_t geesx( const char jobvs, const char sort,
        logical_t* select, const char sense, const fortran_int_t n, float* a,
        const fortran_int_t lda, fortran_int_t& sdim, float* wr, float* wi,
        float* vs, const fortran_int_t ldvs, float& rconde, float& rcondv,
        float* work, const fortran_int_t lwork, fortran_int_t* iwork,
        const fortran_int_t liwork, logical_t* bwork ) {
    fortran_int_t info(0);
    LAPACK_SGEESX( &jobvs, &sort, &select, &sense, &n, a, &lda, &sdim, wr, wi,
            vs, &ldvs, &rconde, &rcondv, work, &lwork, iwork, &liwork, bwork,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t geesx( const char jobvs, const char sort,
        logical_t* select, const char sense, const fortran_int_t n, double* a,
        const fortran_int_t lda, fortran_int_t& sdim, double* wr, double* wi,
        double* vs, const fortran_int_t ldvs, double& rconde, double& rcondv,
        double* work, const fortran_int_t lwork, fortran_int_t* iwork,
        const fortran_int_t liwork, logical_t* bwork ) {
    fortran_int_t info(0);
    LAPACK_DGEESX( &jobvs, &sort, &select, &sense, &n, a, &lda, &sdim, wr, wi,
            vs, &ldvs, &rconde, &rcondv, work, &lwork, iwork, &liwork, bwork,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t geesx( const char jobvs, const char sort,
        logical_t* select, const char sense, const fortran_int_t n,
        std::complex<float>* a, const fortran_int_t lda, fortran_int_t& sdim,
        std::complex<float>* w, std::complex<float>* vs,
        const fortran_int_t ldvs, float& rconde, float& rcondv,
        std::complex<float>* work, const fortran_int_t lwork, float* rwork,
        logical_t* bwork ) {
    fortran_int_t info(0);
    LAPACK_CGEESX( &jobvs, &sort, &select, &sense, &n, a, &lda, &sdim, w, vs,
            &ldvs, &rconde, &rcondv, work, &lwork, rwork, bwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t geesx( const char jobvs, const char sort,
        logical_t* select, const char sense, const fortran_int_t n,
        std::complex<double>* a, const fortran_int_t lda, fortran_int_t& sdim,
        std::complex<double>* w, std::complex<double>* vs,
        const fortran_int_t ldvs, double& rconde, double& rcondv,
        std::complex<double>* work, const fortran_int_t lwork, double* rwork,
        logical_t* bwork ) {
    fortran_int_t info(0);
    LAPACK_ZGEESX( &jobvs, &sort, &select, &sense, &n, a, &lda, &sdim, w, vs,
            &ldvs, &rconde, &rcondv, work, &lwork, rwork, bwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to geesx.
//
template< typename Value, typename Enable = void >
struct geesx_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct geesx_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVS, typename WORK, typename IWORK, typename BWORK >
    static std::ptrdiff_t invoke( const char jobvs, const char sort,
            logical_t* select, const char sense, MatrixA& a,
            fortran_int_t& sdim, VectorWR& wr, VectorWI& wi, MatrixVS& vs,
            real_type& rconde, real_type& rcondv, detail::workspace3< WORK,
            IWORK, BWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVS >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorWR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorWI >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVS >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorWR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorWI >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVS >::value) );
        BOOST_ASSERT( bindings::size(wi) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( bindings::size_column(a), sense ));
        BOOST_ASSERT( bindings::size(work.select(bool())) >= min_size_bwork(
                bindings::size_column(a), sort ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(a), sense ));
        BOOST_ASSERT( bindings::size(wr) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(vs) == 1 ||
                bindings::stride_minor(vs) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( jobvs == 'N' || jobvs == 'V' );
        BOOST_ASSERT( sense == 'N' || sense == 'E' || sense == 'V' ||
                sense == 'B' );
        BOOST_ASSERT( sort == 'N' || sort == 'S' );
        return detail::geesx( jobvs, sort, select, sense,
                bindings::size_column(a), bindings::begin_value(a),
                bindings::stride_major(a), sdim, bindings::begin_value(wr),
                bindings::begin_value(wi), bindings::begin_value(vs),
                bindings::stride_major(vs), rconde, rcondv,
                bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())),
                bindings::size(work.select(fortran_int_t())),
                bindings::begin_value(work.select(bool())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVS >
    static std::ptrdiff_t invoke( const char jobvs, const char sort,
            logical_t* select, const char sense, MatrixA& a,
            fortran_int_t& sdim, VectorWR& wr, VectorWI& wi, MatrixVS& vs,
            real_type& rconde, real_type& rcondv, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(a), sense ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( bindings::size_column(a), sense ) );
        bindings::detail::array< bool > tmp_bwork( min_size_bwork(
                bindings::size_column(a), sort ) );
        return invoke( jobvs, sort, select, sense, a, sdim, wr, wi, vs,
                rconde, rcondv, workspace( tmp_work, tmp_iwork, tmp_bwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorWR, typename VectorWI,
            typename MatrixVS >
    static std::ptrdiff_t invoke( const char jobvs, const char sort,
            logical_t* select, const char sense, MatrixA& a,
            fortran_int_t& sdim, VectorWR& wr, VectorWI& wi, MatrixVS& vs,
            real_type& rconde, real_type& rcondv, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        real_type opt_size_work;
        fortran_int_t opt_size_iwork;
        bindings::detail::array< bool > tmp_bwork( min_size_bwork(
                bindings::size_column(a), sort ) );
        detail::geesx( jobvs, sort, select, sense,
                bindings::size_column(a), bindings::begin_value(a),
                bindings::stride_major(a), sdim, bindings::begin_value(wr),
                bindings::begin_value(wi), bindings::begin_value(vs),
                bindings::stride_major(vs), rconde, rcondv, &opt_size_work,
                -1, &opt_size_iwork, -1, bindings::begin_value(tmp_bwork) );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        return invoke( jobvs, sort, select, sense, a, sdim, wr, wi, vs,
                rconde, rcondv, workspace( tmp_work, tmp_iwork, tmp_bwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n,
            const char sense ) {
        if ( sense == 'N' )
            return std::max< std::ptrdiff_t >( 1, 3*n );
        else
            return std::max< std::ptrdiff_t >( 1, n+n*n/2 );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n,
            const char sense ) {
        if ( sense == 'N' || sense == 'E' )
            return 1;
        else
            return std::max< std::ptrdiff_t >( 1, n*n/4 );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array bwork.
    //
    static std::ptrdiff_t min_size_bwork( const std::ptrdiff_t n,
            const char sort ) {
        if ( sort == 'N' )
            return 0;
        else
            return n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct geesx_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorW, typename MatrixVS,
            typename WORK, typename RWORK, typename BWORK >
    static std::ptrdiff_t invoke( const char jobvs, const char sort,
            logical_t* select, const char sense, MatrixA& a,
            fortran_int_t& sdim, VectorW& w, MatrixVS& vs,
            real_type& rconde, real_type& rcondv, detail::workspace3< WORK,
            RWORK, BWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVS >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVS >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVS >::value) );
        BOOST_ASSERT( bindings::size(w) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(work.select(bool())) >= min_size_bwork(
                bindings::size_column(a), sort ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(a), sense ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(vs) == 1 ||
                bindings::stride_minor(vs) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( jobvs == 'N' || jobvs == 'V' );
        BOOST_ASSERT( sense == 'N' || sense == 'E' || sense == 'V' ||
                sense == 'B' );
        BOOST_ASSERT( sort == 'N' || sort == 'S' );
        return detail::geesx( jobvs, sort, select, sense,
                bindings::size_column(a), bindings::begin_value(a),
                bindings::stride_major(a), sdim, bindings::begin_value(w),
                bindings::begin_value(vs), bindings::stride_major(vs), rconde,
                rcondv, bindings::begin_value(work.select(value_type())),
                bindings::size(work.select(value_type())),
                bindings::begin_value(work.select(real_type())),
                bindings::begin_value(work.select(bool())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorW, typename MatrixVS >
    static std::ptrdiff_t invoke( const char jobvs, const char sort,
            logical_t* select, const char sense, MatrixA& a,
            fortran_int_t& sdim, VectorW& w, MatrixVS& vs,
            real_type& rconde, real_type& rcondv, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(a), sense ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(a) ) );
        bindings::detail::array< bool > tmp_bwork( min_size_bwork(
                bindings::size_column(a), sort ) );
        return invoke( jobvs, sort, select, sense, a, sdim, w, vs, rconde,
                rcondv, workspace( tmp_work, tmp_rwork, tmp_bwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorW, typename MatrixVS >
    static std::ptrdiff_t invoke( const char jobvs, const char sort,
            logical_t* select, const char sense, MatrixA& a,
            fortran_int_t& sdim, VectorW& w, MatrixVS& vs,
            real_type& rconde, real_type& rcondv, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        value_type opt_size_work;
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(a) ) );
        bindings::detail::array< bool > tmp_bwork( min_size_bwork(
                bindings::size_column(a), sort ) );
        detail::geesx( jobvs, sort, select, sense,
                bindings::size_column(a), bindings::begin_value(a),
                bindings::stride_major(a), sdim, bindings::begin_value(w),
                bindings::begin_value(vs), bindings::stride_major(vs), rconde,
                rcondv, &opt_size_work, -1, bindings::begin_value(tmp_rwork),
                bindings::begin_value(tmp_bwork) );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( jobvs, sort, select, sense, a, sdim, w, vs, rconde,
                rcondv, workspace( tmp_work, tmp_rwork, tmp_bwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n,
            const char sense ) {
        if ( sense == 'N' )
            return std::max< std::ptrdiff_t >( 1, 2*n );
        else
            return std::max< std::ptrdiff_t >( 1, n*n/2 );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const std::ptrdiff_t n ) {
        return n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array bwork.
    //
    static std::ptrdiff_t min_size_bwork( const std::ptrdiff_t n,
            const char sort ) {
        if ( sort == 'N' )
            return 0;
        else
            return n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the geesx_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorWR& wr,
        VectorWI& wi, MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorWR& wr,
        VectorWI& wi, MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, optimal_workspace() );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorWR& wr, VectorWI& wi, MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorWR& wr, VectorWI& wi, MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, optimal_workspace() );
}

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * const MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorWR& wr,
        VectorWI& wi, const MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * const MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorWR& wr,
        VectorWI& wi, const MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, optimal_workspace() );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * const MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorWR& wr, VectorWI& wi, const MatrixVS& vs,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rconde, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rcondv,
        Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * const MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorWR, typename VectorWI,
        typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorWR& wr, VectorWI& wi, const MatrixVS& vs,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rconde, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim,
            wr, wi, vs, rconde, rcondv, optimal_workspace() );
}
//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename MatrixVS,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorW& w,
        MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW, typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorW& w,
        MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, optimal_workspace() );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename MatrixVS,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorW& w, MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW, typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorW& w, MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, optimal_workspace() );
}

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * const MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename MatrixVS,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorW& w,
        const MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * MatrixA&
// * const MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW, typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, MatrixA& a, fortran_int_t& sdim, VectorW& w,
        const MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, optimal_workspace() );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * const MatrixVS&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename MatrixVS,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorW& w, const MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv, Workspace work ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, work );
}

//
// Overloaded function for geesx. Its overload differs for
// * const MatrixA&
// * const MatrixVS&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW, typename MatrixVS >
inline typename boost::disable_if< detail::is_workspace< MatrixVS >,
        std::ptrdiff_t >::type
geesx( const char jobvs, const char sort, logical_t* select,
        const char sense, const MatrixA& a, fortran_int_t& sdim,
        VectorW& w, const MatrixVS& vs, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rconde,
        typename remove_imaginary< typename bindings::value_type<
        MatrixA >::type >::type& rcondv ) {
    return geesx_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( jobvs, sort, select, sense, a, sdim, w,
            vs, rconde, rcondv, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

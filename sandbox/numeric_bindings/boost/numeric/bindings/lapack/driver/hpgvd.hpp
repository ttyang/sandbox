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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HPGVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HPGVD_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for hpgvd is the netlib-compatible backend.
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
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype, const char jobz, UpLo,
        const fortran_int_t n, std::complex<float>* ap,
        std::complex<float>* bp, float* w, std::complex<float>* z,
        const fortran_int_t ldz, std::complex<float>* work,
        const fortran_int_t lwork, float* rwork, const fortran_int_t lrwork,
        fortran_int_t* iwork, const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_CHPGVD( &itype, &jobz, &lapack_option< UpLo >::value, &n, ap, bp,
            w, z, &ldz, work, &lwork, rwork, &lrwork, iwork, &liwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype, const char jobz, UpLo,
        const fortran_int_t n, std::complex<double>* ap,
        std::complex<double>* bp, double* w, std::complex<double>* z,
        const fortran_int_t ldz, std::complex<double>* work,
        const fortran_int_t lwork, double* rwork, const fortran_int_t lrwork,
        fortran_int_t* iwork, const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_ZHPGVD( &itype, &jobz, &lapack_option< UpLo >::value, &n, ap, bp,
            w, z, &ldz, work, &lwork, rwork, &lrwork, iwork, &liwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hpgvd.
//
template< typename Value >
struct hpgvd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename MatrixBP, typename VectorW,
            typename MatrixZ, typename WORK, typename RWORK, typename IWORK >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, const fortran_int_t n, MatrixAP& ap,
            MatrixBP& bp, VectorW& w, MatrixZ& z, detail::workspace3< WORK,
            RWORK, IWORK > work ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixBP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAP >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixBP >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( jobz, n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_rwork( jobz,
                n ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work( jobz,
                n ));
        BOOST_ASSERT( size_minor(z) == 1 || stride_minor(z) == 1 );
        return detail::hpgvd( itype, jobz, uplo(), n, begin_value(ap),
                begin_value(bp), begin_value(w), begin_value(z),
                stride_major(z), begin_value(work.select(value_type())),
                size(work.select(value_type())),
                begin_value(work.select(real_type())),
                size(work.select(real_type())),
                begin_value(work.select(fortran_int_t())),
                size(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAP, typename MatrixBP, typename VectorW,
            typename MatrixZ >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, const fortran_int_t n, MatrixAP& ap,
            MatrixBP& bp, VectorW& w, MatrixZ& z, minimal_workspace work ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work( jobz,
                n ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork( jobz,
                n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( jobz, n ) );
        return invoke( itype, jobz, n, ap, bp, w, z, workspace( tmp_work,
                tmp_rwork, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAP, typename MatrixBP, typename VectorW,
            typename MatrixZ >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, const fortran_int_t n, MatrixAP& ap,
            MatrixBP& bp, VectorW& w, MatrixZ& z, optimal_workspace work ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        value_type opt_size_work;
        real_type opt_size_rwork;
        fortran_int_t opt_size_iwork;
        detail::hpgvd( itype, jobz, uplo(), n, begin_value(ap),
                begin_value(bp), begin_value(w), begin_value(z),
                stride_major(z), &opt_size_work, -1, &opt_size_rwork, -1,
                &opt_size_iwork, -1 );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        return invoke( itype, jobz, n, ap, bp, w, z, workspace( tmp_work,
                tmp_rwork, tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char jobz,
            const std::ptrdiff_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 2*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 1 + 5*n + 2*n*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hpgvd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, VectorW& w, const MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, VectorW& w, const MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, const MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, const MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        MatrixBP& bp, const VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, const MatrixZ& z,
        Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, const MatrixZ& z,
        Workspace work ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, work );
}

//
// Overloaded function for hpgvd. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t hpgvd( const fortran_int_t itype,
        const char jobz, const fortran_int_t n, const MatrixAP& ap,
        const MatrixBP& bp, const VectorW& w, const MatrixZ& z ) {
    return hpgvd_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, n, ap, bp, w, z, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

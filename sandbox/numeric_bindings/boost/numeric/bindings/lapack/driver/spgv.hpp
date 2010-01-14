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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SPGV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SPGV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for spgv is the netlib-compatible backend.
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
template< typename UpLo >
inline std::ptrdiff_t spgv( const fortran_int_t itype, const char jobz, UpLo,
        const fortran_int_t n, float* ap, float* bp, float* w, float* z,
        const fortran_int_t ldz, float* work ) {
    fortran_int_t info(0);
    LAPACK_SSPGV( &itype, &jobz, &lapack_option< UpLo >::value, &n, ap, bp, w,
            z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t spgv( const fortran_int_t itype, const char jobz, UpLo,
        const fortran_int_t n, double* ap, double* bp, double* w, double* z,
        const fortran_int_t ldz, double* work ) {
    fortran_int_t info(0);
    LAPACK_DSPGV( &itype, &jobz, &lapack_option< UpLo >::value, &n, ap, bp, w,
            z, &ldz, work, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to spgv.
//
template< typename Value >
struct spgv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename MatrixBP, typename VectorW,
            typename MatrixZ, typename WORK >
    static std::ptrdiff_t invoke( const fortran_int_t itype,
            const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w,
            MatrixZ& z, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixBP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAP >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixBP >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(ap) ));
        BOOST_ASSERT( bindings::size_column(ap) >= 0 );
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        return detail::spgv( itype, jobz, uplo(), bindings::size_column(ap),
                bindings::begin_value(ap), bindings::begin_value(bp),
                bindings::begin_value(w), bindings::begin_value(z),
                bindings::stride_major(z),
                bindings::begin_value(work.select(real_type())) );
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
            const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w,
            MatrixZ& z, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(ap) ) );
        return invoke( itype, jobz, ap, bp, w, z, workspace( tmp_work ) );
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
            const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w,
            MatrixZ& z, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        return invoke( itype, jobz, ap, bp, w, z, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 3*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the spgv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w, MatrixZ& z,
        Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w, MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, VectorW& w,
        MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, const VectorW& w,
        MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, const VectorW& w,
        MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp,
        const VectorW& w, MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp,
        const VectorW& w, MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp, VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, MatrixBP& bp, const VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, const VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, MatrixAP& ap, const MatrixBP& bp, const VectorW& w,
        const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ, typename Workspace >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp,
        const VectorW& w, const MatrixZ& z, Workspace work ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, work );
}

//
// Overloaded function for spgv. Its overload differs for
// * const MatrixAP&
// * const MatrixBP&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename MatrixBP, typename VectorW,
        typename MatrixZ >
inline std::ptrdiff_t spgv( const fortran_int_t itype,
        const char jobz, const MatrixAP& ap, const MatrixBP& bp,
        const VectorW& w, const MatrixZ& z ) {
    return spgv_impl< typename value< MatrixAP >::type >::invoke( itype,
            jobz, ap, bp, w, z, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

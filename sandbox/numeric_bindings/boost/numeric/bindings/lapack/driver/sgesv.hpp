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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SGESV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SGESV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

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
// Overloaded function for dispatching to double value-type.
//
inline void sgesv( fortran_int_t n, fortran_int_t nrhs, double* a,
        fortran_int_t lda, fortran_int_t* ipiv, const double* b,
        fortran_int_t ldb, double* x, fortran_int_t ldx, double* work,
        float* swork, fortran_int_t& iter, fortran_int_t& info ) {
    LAPACK_DSGESV( &n, &nrhs, a, &lda, ipiv, b, &ldb, x, &ldx, work, swork,
            &iter, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to sgesv.
//
template< typename Value >
struct sgesv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename MatrixX, typename WORK, typename SWORK >
    static void invoke( MatrixA& a, VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, fortran_int_t& iter, fortran_int_t& info,
            detail::workspace2< WORK, SWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorIPIV >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixX >::value) );
        BOOST_ASSERT( size(ipiv) >= size_column(a) );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_swork(
                size_column(a), size_column(b) ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                $CALL_MIN_SIZE ));
        BOOST_ASSERT( size_column(a) >= 0 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(x) == 1 || stride_minor(x) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_column(a)) );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,
                size_column(a)) );
        BOOST_ASSERT( stride_major(x) >= std::max< std::ptrdiff_t >(1,
                size_column(a)) );
        detail::sgesv( size_column(a), size_column(b), begin_value(a),
                stride_major(a), begin_value(ipiv), begin_value(b),
                stride_major(b), begin_value(x), stride_major(x),
                begin_value(work), begin_value(work.select(real_type())),
                iter, info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename MatrixX >
    static void invoke( MatrixA& a, VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, fortran_int_t& iter, fortran_int_t& info,
            minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        bindings::detail::array< real_type > tmp_swork( min_size_swork(
                size_column(a), size_column(b) ) );
        invoke( a, ipiv, b, x, iter, info, workspace( tmp_work, tmp_swork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorIPIV, typename MatrixB,
            typename MatrixX >
    static void invoke( MatrixA& a, VectorIPIV& ipiv, const MatrixB& b,
            MatrixX& x, fortran_int_t& iter, fortran_int_t& info,
            optimal_workspace work ) {
        invoke( a, ipiv, b, x, iter, info, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array swork.
    //
    static std::ptrdiff_t min_size_swork( const std::ptrdiff_t n,
            const std::ptrdiff_t nrhs ) {
        return n*(n+nrhs);
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the sgesv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX, typename Workspace >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter,
        Workspace work ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, work );
    return info;
}

//
// Overloaded function for sgesv. Its overload differs for
// * const MatrixA&
// * const VectorIPIV&
// * const MatrixX&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorIPIV, typename MatrixB,
        typename MatrixX >
inline std::ptrdiff_t sgesv( const MatrixA& a, const VectorIPIV& ipiv,
        const MatrixB& b, const MatrixX& x, const fortran_int_t& iter ) {
    fortran_int_t info(0);
    sgesv_impl< typename value< MatrixA >::type >::invoke( a, ipiv, b, x,
            iter, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

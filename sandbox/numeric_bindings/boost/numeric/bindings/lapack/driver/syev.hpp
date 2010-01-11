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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYEV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_SYEV_HPP

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
// The LAPACK-backend for syev is the netlib-compatible backend.
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
inline std::ptrdiff_t syev( char jobz, UpLo, fortran_int_t n, float* a,
        fortran_int_t lda, float* w, float* work, fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_SSYEV( &jobz, &lapack_option< UpLo >::value, &n, a, &lda, w, work,
            &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t syev( char jobz, UpLo, fortran_int_t n, double* a,
        fortran_int_t lda, double* w, double* work, fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_DSYEV( &jobz, &lapack_option< UpLo >::value, &n, a, &lda, w, work,
            &lwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to syev.
//
template< typename Value >
struct syev_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorW, typename WORK >
    static std::ptrdiff_t invoke( const char jobz, MatrixA& a, VectorW& w,
            detail::workspace1< WORK > work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorW >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                size_column(a) ));
        BOOST_ASSERT( size_column(a) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_column(a)) );
        return detail::syev( jobz, uplo(), size_column(a), begin_value(a),
                stride_major(a), begin_value(w),
                begin_value(work.select(real_type())),
                size(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorW >
    static std::ptrdiff_t invoke( const char jobz, MatrixA& a, VectorW& w,
            minimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                size_column(a) ) );
        return invoke( jobz, a, w, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorW >
    static std::ptrdiff_t invoke( const char jobz, MatrixA& a, VectorW& w,
            optimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        real_type opt_size_work;
        detail::syev( jobz, uplo(), size_column(a), begin_value(a),
                stride_major(a), begin_value(w), &opt_size_work, -1 );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( jobz, a, w, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return std::max< std::ptrdiff_t >( 1, 3*n-1 );
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the syev_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for syev. Its overload differs for
// * MatrixA&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename Workspace >
inline std::ptrdiff_t syev( const char jobz, MatrixA& a, VectorW& w,
        Workspace work ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, work );
}

//
// Overloaded function for syev. Its overload differs for
// * MatrixA&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW >
inline std::ptrdiff_t syev( const char jobz, MatrixA& a, VectorW& w ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, optimal_workspace() );
}

//
// Overloaded function for syev. Its overload differs for
// * const MatrixA&
// * VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename Workspace >
inline std::ptrdiff_t syev( const char jobz, const MatrixA& a,
        VectorW& w, Workspace work ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, work );
}

//
// Overloaded function for syev. Its overload differs for
// * const MatrixA&
// * VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW >
inline std::ptrdiff_t syev( const char jobz, const MatrixA& a,
        VectorW& w ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, optimal_workspace() );
}

//
// Overloaded function for syev. Its overload differs for
// * MatrixA&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename Workspace >
inline std::ptrdiff_t syev( const char jobz, MatrixA& a,
        const VectorW& w, Workspace work ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, work );
}

//
// Overloaded function for syev. Its overload differs for
// * MatrixA&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW >
inline std::ptrdiff_t syev( const char jobz, MatrixA& a,
        const VectorW& w ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, optimal_workspace() );
}

//
// Overloaded function for syev. Its overload differs for
// * const MatrixA&
// * const VectorW&
// * User-defined workspace
//
template< typename MatrixA, typename VectorW, typename Workspace >
inline std::ptrdiff_t syev( const char jobz, const MatrixA& a,
        const VectorW& w, Workspace work ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, work );
}

//
// Overloaded function for syev. Its overload differs for
// * const MatrixA&
// * const VectorW&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorW >
inline std::ptrdiff_t syev( const char jobz, const MatrixA& a,
        const VectorW& w ) {
    return syev_impl< typename value< MatrixA >::type >::invoke( jobz,
            a, w, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

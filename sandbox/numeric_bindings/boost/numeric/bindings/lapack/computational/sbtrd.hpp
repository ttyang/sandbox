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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SBTRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SBTRD_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
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
// Overloaded function for dispatching to float value-type.
//
template< typename UpLo >
inline void sbtrd( char vect, UpLo, fortran_int_t n, fortran_int_t kd,
        float* ab, fortran_int_t ldab, float* d, float* e, float* q,
        fortran_int_t ldq, float* work, fortran_int_t& info ) {
    LAPACK_SSBTRD( &vect, &lapack_option< UpLo >::value, &n, &kd, ab, &ldab,
            d, e, q, &ldq, work, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
template< typename UpLo >
inline void sbtrd( char vect, UpLo, fortran_int_t n, fortran_int_t kd,
        double* ab, fortran_int_t ldab, double* d, double* e, double* q,
        fortran_int_t ldq, double* work, fortran_int_t& info ) {
    LAPACK_DSBTRD( &vect, &lapack_option< UpLo >::value, &n, &kd, ab, &ldab,
            d, e, q, &ldq, work, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to sbtrd.
//
template< typename Value >
struct sbtrd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorD, typename VectorE,
            typename MatrixQ, typename WORK >
    static void invoke( const char vect, const fortran_int_t n,
            MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q,
            fortran_int_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                VectorD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixQ >::value) );
        BOOST_ASSERT( bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(d) >= n );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( size_minor(q) == 1 || stride_minor(q) == 1 );
        BOOST_ASSERT( stride_major(ab) >= bandwidth_upper(ab)+1 );
        BOOST_ASSERT( vect == 'N' || vect == 'V' || vect == 'U' );
        detail::sbtrd( vect, uplo(), n, bandwidth_upper(ab), begin_value(ab),
                stride_major(ab), begin_value(d), begin_value(e),
                begin_value(q), stride_major(q),
                begin_value(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB, typename VectorD, typename VectorE,
            typename MatrixQ >
    static void invoke( const char vect, const fortran_int_t n,
            MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q,
            fortran_int_t& info, minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        invoke( vect, n, ab, d, e, q, info, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename VectorD, typename VectorE,
            typename MatrixQ >
    static void invoke( const char vect, const fortran_int_t n,
            MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q,
            fortran_int_t& info, optimal_workspace work ) {
        invoke( vect, n, ab, d, e, q, info, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the sbtrd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q, Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * const VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, const VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * const VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, const VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * const VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, const VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * const VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, const VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * const VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, const VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * const VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, const VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * const VectorE&
// * MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, const VectorE& e, MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * const VectorE&
// * MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, const VectorE& e, MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * const VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, const VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * VectorD&
// * const VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, VectorD& d, const VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * const VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, const VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * VectorD&
// * const VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, VectorD& d, const VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * const VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, const VectorE& e, const MatrixQ& q,
        Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * MatrixAB&
// * const VectorD&
// * const VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        MatrixAB& ab, const VectorD& d, const VectorE& e, const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * const VectorE&
// * const MatrixQ&
// * User-defined workspace
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ, typename Workspace >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, const VectorE& e,
        const MatrixQ& q, Workspace work ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, work );
    return info;
}

//
// Overloaded function for sbtrd. Its overload differs for
// * const MatrixAB&
// * const VectorD&
// * const VectorE&
// * const MatrixQ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorD, typename VectorE,
        typename MatrixQ >
inline std::ptrdiff_t sbtrd( const char vect, const fortran_int_t n,
        const MatrixAB& ab, const VectorD& d, const VectorE& e,
        const MatrixQ& q ) {
    fortran_int_t info(0);
    sbtrd_impl< typename value< MatrixAB >::type >::invoke( vect, n, ab,
            d, e, q, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HETRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HETRD_HPP

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
#include <boost/numeric/bindings/traits/detail/utils.hpp>
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
// Overloaded function for dispatching to complex<float> value-type.
//
template< typename UpLo >
inline void hetrd( UpLo, fortran_int_t n, std::complex<float>* a,
        fortran_int_t lda, float* d, float* e, std::complex<float>* tau,
        std::complex<float>* work, fortran_int_t lwork, fortran_int_t& info ) {
    LAPACK_CHETRD( &lapack_option< UpLo >::value, &n, a, &lda, d, e, tau,
            work, &lwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
template< typename UpLo >
inline void hetrd( UpLo, fortran_int_t n, std::complex<double>* a,
        fortran_int_t lda, double* d, double* e, std::complex<double>* tau,
        std::complex<double>* work, fortran_int_t lwork,
        fortran_int_t& info ) {
    LAPACK_ZHETRD( &lapack_option< UpLo >::value, &n, a, &lda, d, e, tau,
            work, &lwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hetrd.
//
template< typename Value >
struct hetrd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU, typename WORK >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAU& tau,
            fortran_int_t& info, detail::workspace1< WORK > work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorD >::type >::type,
                typename remove_const< typename value<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorTAU >::value) );
        BOOST_ASSERT( size(d) >= size_column(a) );
        BOOST_ASSERT( size(tau) >= size_column(a)-1 );
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work());
        BOOST_ASSERT( size_column(a) >= 0 );
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( stride_major(a) >= std::max< std::ptrdiff_t >(1,
                size_column(a)) );
        detail::hetrd( uplo(), size_column(a), begin_value(a),
                stride_major(a), begin_value(d), begin_value(e),
                begin_value(tau), begin_value(work.select(value_type())),
                size(work.select(value_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAU& tau,
            fortran_int_t& info, minimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work() );
        invoke( a, d, e, tau, info, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU >
    static void invoke( MatrixA& a, VectorD& d, VectorE& e, VectorTAU& tau,
            fortran_int_t& info, optimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        value_type opt_size_work;
        detail::hetrd( uplo(), size_column(a), begin_value(a),
                stride_major(a), begin_value(d), begin_value(e),
                begin_value(tau), &opt_size_work, -1, info );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( a, d, e, tau, info, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work() {
        return 1;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hetrd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, VectorE& e,
        VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, VectorE& e,
        VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d, VectorE& e,
        VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d, VectorE& e,
        VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d, VectorE& e,
        VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d, VectorE& e,
        VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        VectorE& e, VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        VectorE& e, VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * const VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, const VectorE& e,
        VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * const VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, const VectorE& e,
        VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * const VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d,
        const VectorE& e, VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * const VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d,
        const VectorE& e, VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * const VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d,
        const VectorE& e, VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * const VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d,
        const VectorE& e, VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * const VectorE&
// * VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        const VectorE& e, VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * const VectorE&
// * VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        const VectorE& e, VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, VectorE& e,
        const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, VectorE& e,
        const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d, VectorE& e,
        const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d, VectorE& e,
        const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d, VectorE& e,
        const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d, VectorE& e,
        const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        VectorE& e, const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        VectorE& e, const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * const VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, const VectorE& e,
        const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * VectorD&
// * const VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, VectorD& d, const VectorE& e,
        const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * const VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d,
        const VectorE& e, const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * VectorD&
// * const VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, VectorD& d,
        const VectorE& e, const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * const VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d,
        const VectorE& e, const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * MatrixA&
// * const VectorD&
// * const VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( MatrixA& a, const VectorD& d,
        const VectorE& e, const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * const VectorE&
// * const VectorTAU&
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        const VectorE& e, const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, work );
    return info;
}

//
// Overloaded function for hetrd. Its overload differs for
// * const MatrixA&
// * const VectorD&
// * const VectorE&
// * const VectorTAU&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline std::ptrdiff_t hetrd( const MatrixA& a, const VectorD& d,
        const VectorE& e, const VectorTAU& tau ) {
    fortran_int_t info(0);
    hetrd_impl< typename value< MatrixA >::type >::invoke( a, d, e, tau,
            info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

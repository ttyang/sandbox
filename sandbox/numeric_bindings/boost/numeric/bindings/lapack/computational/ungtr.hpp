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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_UNGTR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_UNGTR_HPP

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
inline void ungtr( UpLo, fortran_int_t n, std::complex<float>* a,
        fortran_int_t lda, const std::complex<float>* tau,
        std::complex<float>* work, fortran_int_t lwork, fortran_int_t& info ) {
    LAPACK_CUNGTR( &lapack_option< UpLo >::value, &n, a, &lda, tau, work,
            &lwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
template< typename UpLo >
inline void ungtr( UpLo, fortran_int_t n, std::complex<double>* a,
        fortran_int_t lda, const std::complex<double>* tau,
        std::complex<double>* work, fortran_int_t lwork,
        fortran_int_t& info ) {
    LAPACK_ZUNGTR( &lapack_option< UpLo >::value, &n, a, &lda, tau, work,
            &lwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to ungtr.
//
template< typename Value >
struct ungtr_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorTAU, typename WORK >
    static void invoke( const fortran_int_t n, MatrixA& a,
            const VectorTAU& tau, fortran_int_t& info, detail::workspace1<
            WORK > work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixA >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(tau) >= n-1 );
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work( side,
                m, n ));
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( stride_major(a) >= n );
        detail::ungtr( uplo(), n, begin_value(a), stride_major(a),
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
    template< typename MatrixA, typename VectorTAU >
    static void invoke( const fortran_int_t n, MatrixA& a,
            const VectorTAU& tau, fortran_int_t& info,
            minimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work( side,
                m, n ) );
        invoke( n, a, tau, info, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorTAU >
    static void invoke( const fortran_int_t n, MatrixA& a,
            const VectorTAU& tau, fortran_int_t& info,
            optimal_workspace work ) {
        typedef typename result_of::data_side< MatrixA >::type uplo;
        value_type opt_size_work;
        detail::ungtr( uplo(), n, begin_value(a), stride_major(a),
                begin_value(tau), &opt_size_work, -1, info );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( n, a, tau, info, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t side,
            const std::ptrdiff_t m, const std::ptrdiff_t n ) {
        if ( side == 'L' )
            return std::max< std::ptrdiff_t >( 1, n );
        else
            return std::max< std::ptrdiff_t >( 1, m );
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the ungtr_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for ungtr. Its overload differs for
// * MatrixA&
// * User-defined workspace
//
template< typename MatrixA, typename VectorTAU, typename Workspace >
inline std::ptrdiff_t ungtr( const fortran_int_t n, MatrixA& a,
        const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    ungtr_impl< typename value< MatrixA >::type >::invoke( n, a, tau,
            info, work );
    return info;
}

//
// Overloaded function for ungtr. Its overload differs for
// * MatrixA&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorTAU >
inline std::ptrdiff_t ungtr( const fortran_int_t n, MatrixA& a,
        const VectorTAU& tau ) {
    fortran_int_t info(0);
    ungtr_impl< typename value< MatrixA >::type >::invoke( n, a, tau,
            info, optimal_workspace() );
    return info;
}

//
// Overloaded function for ungtr. Its overload differs for
// * const MatrixA&
// * User-defined workspace
//
template< typename MatrixA, typename VectorTAU, typename Workspace >
inline std::ptrdiff_t ungtr( const fortran_int_t n, const MatrixA& a,
        const VectorTAU& tau, Workspace work ) {
    fortran_int_t info(0);
    ungtr_impl< typename value< MatrixA >::type >::invoke( n, a, tau,
            info, work );
    return info;
}

//
// Overloaded function for ungtr. Its overload differs for
// * const MatrixA&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorTAU >
inline std::ptrdiff_t ungtr( const fortran_int_t n, const MatrixA& a,
        const VectorTAU& tau ) {
    fortran_int_t info(0);
    ungtr_impl< typename value< MatrixA >::type >::invoke( n, a, tau,
            info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

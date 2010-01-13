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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SPCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SPCON_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for spcon is the netlib-compatible backend.
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
inline std::ptrdiff_t spcon( const char uplo, const fortran_int_t n,
        const float* ap, const fortran_int_t* ipiv, const float anorm,
        float& rcond, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SSPCON( &uplo, &n, ap, ipiv, &anorm, &rcond, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t spcon( const char uplo, const fortran_int_t n,
        const double* ap, const fortran_int_t* ipiv, const double anorm,
        double& rcond, double* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DSPCON( &uplo, &n, ap, ipiv, &anorm, &rcond, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t spcon( const char uplo, const fortran_int_t n,
        const std::complex<float>* ap, const fortran_int_t* ipiv,
        const float anorm, float& rcond, std::complex<float>* work ) {
    fortran_int_t info(0);
    LAPACK_CSPCON( &uplo, &n, ap, ipiv, &anorm, &rcond, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t spcon( const char uplo, const fortran_int_t n,
        const std::complex<double>* ap, const fortran_int_t* ipiv,
        const double anorm, double& rcond, std::complex<double>* work ) {
    fortran_int_t info(0);
    LAPACK_ZSPCON( &uplo, &n, ap, ipiv, &anorm, &rcond, work, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to spcon.
//
template< typename Value, typename Enable = void >
struct spcon_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct spcon_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename VectorIPIV, typename WORK,
            typename IWORK >
    static std::ptrdiff_t invoke( const char uplo, const MatrixAP& ap,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_ASSERT( size(ipiv) >= size_column(ap) );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( size_column(ap) ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                size_column(ap) ));
        BOOST_ASSERT( size_column(ap) >= 0 );
        return detail::spcon( uplo, size_column(ap), begin_value(ap),
                begin_value(ipiv), anorm, rcond,
                begin_value(work.select(real_type())),
                begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAP, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char uplo, const MatrixAP& ap,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work(
                size_column(ap) ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( size_column(ap) ) );
        return invoke( uplo, ap, ipiv, anorm, rcond, workspace( tmp_work,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAP, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char uplo, const MatrixAP& ap,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            optimal_workspace work ) {
        return invoke( uplo, ap, ipiv, anorm, rcond, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n ) {
        return n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct spcon_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename VectorIPIV, typename WORK >
    static std::ptrdiff_t invoke( const char uplo, const MatrixAP& ap,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            detail::workspace1< WORK > work ) {
        BOOST_ASSERT( size(ipiv) >= size_column(ap) );
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work(
                size_column(ap) ));
        BOOST_ASSERT( size_column(ap) >= 0 );
        return detail::spcon( uplo, size_column(ap), begin_value(ap),
                begin_value(ipiv), anorm, rcond,
                begin_value(work.select(value_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAP, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char uplo, const MatrixAP& ap,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            minimal_workspace work ) {
        bindings::detail::array< value_type > tmp_work( min_size_work(
                size_column(ap) ) );
        return invoke( uplo, ap, ipiv, anorm, rcond, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAP, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char uplo, const MatrixAP& ap,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            optimal_workspace work ) {
        return invoke( uplo, ap, ipiv, anorm, rcond, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the spcon_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for spcon. Its overload differs for
// * User-defined workspace
//
template< typename MatrixAP, typename VectorIPIV, typename Workspace >
inline std::ptrdiff_t spcon( const char uplo, const MatrixAP& ap,
        const VectorIPIV& ipiv, const typename remove_imaginary<
        typename value< MatrixAP >::type >::type anorm,
        typename remove_imaginary< typename value<
        MatrixAP >::type >::type& rcond, Workspace work ) {
    return spcon_impl< typename value< MatrixAP >::type >::invoke( uplo,
            ap, ipiv, anorm, rcond, work );
}

//
// Overloaded function for spcon. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename VectorIPIV >
inline std::ptrdiff_t spcon( const char uplo, const MatrixAP& ap,
        const VectorIPIV& ipiv, const typename remove_imaginary<
        typename value< MatrixAP >::type >::type anorm,
        typename remove_imaginary< typename value<
        MatrixAP >::type >::type& rcond ) {
    return spcon_impl< typename value< MatrixAP >::type >::invoke( uplo,
            ap, ipiv, anorm, rcond, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

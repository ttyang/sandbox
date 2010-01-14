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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GBCON_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
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
// The LAPACK-backend for gbcon is the netlib-compatible backend.
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
inline std::ptrdiff_t gbcon( const char norm, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku, const float* ab,
        const fortran_int_t ldab, const fortran_int_t* ipiv,
        const float anorm, float& rcond, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SGBCON( &norm, &n, &kl, &ku, ab, &ldab, ipiv, &anorm, &rcond, work,
            iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gbcon( const char norm, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku, const double* ab,
        const fortran_int_t ldab, const fortran_int_t* ipiv,
        const double anorm, double& rcond, double* work,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DGBCON( &norm, &n, &kl, &ku, ab, &ldab, ipiv, &anorm, &rcond, work,
            iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t gbcon( const char norm, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        const std::complex<float>* ab, const fortran_int_t ldab,
        const fortran_int_t* ipiv, const float anorm, float& rcond,
        std::complex<float>* work, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CGBCON( &norm, &n, &kl, &ku, ab, &ldab, ipiv, &anorm, &rcond, work,
            rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t gbcon( const char norm, const fortran_int_t n,
        const fortran_int_t kl, const fortran_int_t ku,
        const std::complex<double>* ab, const fortran_int_t ldab,
        const fortran_int_t* ipiv, const double anorm, double& rcond,
        std::complex<double>* work, double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZGBCON( &norm, &n, &kl, &ku, ab, &ldab, ipiv, &anorm, &rcond, work,
            rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gbcon.
//
template< typename Value, typename Enable = void >
struct gbcon_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct gbcon_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorIPIV, typename WORK,
            typename IWORK >
    static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_ASSERT( bindings::bandwidth_lower(ab) >= 0 );
        BOOST_ASSERT( bindings::bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column(ab) );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= 2 );
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        return detail::gbcon( norm, bindings::size_column(ab),
                bindings::bandwidth_lower(ab), bindings::bandwidth_upper(ab),
                bindings::begin_value(ab), bindings::stride_major(ab),
                bindings::begin_value(ipiv), anorm, rcond,
                bindings::begin_value(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(ab) ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( bindings::size_column(ab) ) );
        return invoke( norm, ab, ipiv, anorm, rcond, workspace( tmp_work,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( norm, ab, ipiv, anorm, rcond, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 3*n;
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
struct gbcon_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorIPIV, typename WORK,
            typename RWORK >
    static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_ASSERT( bindings::bandwidth_lower(ab) >= 0 );
        BOOST_ASSERT( bindings::bandwidth_upper(ab) >= 0 );
        BOOST_ASSERT( bindings::size(ipiv) >= bindings::size_column(ab) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= 2 );
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        return detail::gbcon( norm, bindings::size_column(ab),
                bindings::bandwidth_lower(ab), bindings::bandwidth_upper(ab),
                bindings::begin_value(ab), bindings::stride_major(ab),
                bindings::begin_value(ipiv), anorm, rcond,
                bindings::begin_value(work.select(value_type())),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(ab) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(ab) ) );
        return invoke( norm, ab, ipiv, anorm, rcond, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename VectorIPIV >
    static std::ptrdiff_t invoke( const char norm, const MatrixAB& ab,
            const VectorIPIV& ipiv, const real_type anorm, real_type& rcond,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( norm, ab, ipiv, anorm, rcond, minimal_workspace() );
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
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const std::ptrdiff_t n ) {
        return n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gbcon_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gbcon. Its overload differs for
// * User-defined workspace
//
template< typename MatrixAB, typename VectorIPIV, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
gbcon( const char norm, const MatrixAB& ab, const VectorIPIV& ipiv,
        const typename remove_imaginary< typename value<
        MatrixAB >::type >::type anorm, typename remove_imaginary<
        typename value< MatrixAB >::type >::type& rcond, Workspace work ) {
    return gbcon_impl< typename value< MatrixAB >::type >::invoke( norm,
            ab, ipiv, anorm, rcond, work );
}

//
// Overloaded function for gbcon. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename VectorIPIV >
inline typename boost::disable_if< detail::is_workspace< VectorIPIV >,
        std::ptrdiff_t >::type
gbcon( const char norm, const MatrixAB& ab, const VectorIPIV& ipiv,
        const typename remove_imaginary< typename value<
        MatrixAB >::type >::type anorm, typename remove_imaginary<
        typename value< MatrixAB >::type >::type& rcond ) {
    return gbcon_impl< typename value< MatrixAB >::type >::invoke( norm,
            ab, ipiv, anorm, rcond, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

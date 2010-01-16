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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LANTB_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LANTB_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for lantb is the netlib-compatible backend.
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
template< typename Diag >
inline std::ptrdiff_t lantb( const char norm, const char uplo, Diag,
        const fortran_int_t n, const fortran_int_t k, const float* ab,
        const fortran_int_t ldab, float* work ) {
    fortran_int_t info(0);
    LAPACK_SLANTB( &norm, &uplo, &lapack_option< Diag >::value, &n, &k, ab,
            &ldab, work );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Diag >
inline std::ptrdiff_t lantb( const char norm, const char uplo, Diag,
        const fortran_int_t n, const fortran_int_t k, const double* ab,
        const fortran_int_t ldab, double* work ) {
    fortran_int_t info(0);
    LAPACK_DLANTB( &norm, &uplo, &lapack_option< Diag >::value, &n, &k, ab,
            &ldab, work );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Diag >
inline std::ptrdiff_t lantb( const char norm, const char uplo, Diag,
        const fortran_int_t n, const fortran_int_t k,
        const std::complex<float>* ab, const fortran_int_t ldab,
        float* work ) {
    fortran_int_t info(0);
    LAPACK_CLANTB( &norm, &uplo, &lapack_option< Diag >::value, &n, &k, ab,
            &ldab, work );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Diag >
inline std::ptrdiff_t lantb( const char norm, const char uplo, Diag,
        const fortran_int_t n, const fortran_int_t k,
        const std::complex<double>* ab, const fortran_int_t ldab,
        double* work ) {
    fortran_int_t info(0);
    LAPACK_ZLANTB( &norm, &uplo, &lapack_option< Diag >::value, &n, &k, ab,
            &ldab, work );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to lantb.
//
template< typename Value >
struct lantb_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename WORK >
    static std::ptrdiff_t invoke( const char norm, const char uplo,
            const fortran_int_t k, const MatrixAB& ab, detail::workspace1<
            WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= k+1 );
        BOOST_ASSERT( k >= 0 );
        return detail::lantb( norm, uplo, diag(), bindings::size_column(ab),
                k, bindings::begin_value(ab), bindings::stride_major(ab),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB >
    static std::ptrdiff_t invoke( const char norm, const char uplo,
            const fortran_int_t k, const MatrixAB& ab,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        return invoke( norm, uplo, k, ab, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB >
    static std::ptrdiff_t invoke( const char norm, const char uplo,
            const fortran_int_t k, const MatrixAB& ab,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        return invoke( norm, uplo, k, ab, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the lantb_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for lantb. Its overload differs for
// * User-defined workspace
//
template< typename MatrixAB, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
lantb( const char norm, const char uplo, const fortran_int_t k,
        const MatrixAB& ab, Workspace work ) {
    return lantb_impl< typename value< MatrixAB >::type >::invoke( norm,
            uplo, k, ab, work );
}

//
// Overloaded function for lantb. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixAB >
inline typename boost::disable_if< detail::is_workspace< MatrixAB >,
        std::ptrdiff_t >::type
lantb( const char norm, const char uplo, const fortran_int_t k,
        const MatrixAB& ab ) {
    return lantb_impl< typename value< MatrixAB >::type >::invoke( norm,
            uplo, k, ab, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

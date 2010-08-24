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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LANTP_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LANTP_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for lantp is the netlib-compatible backend.
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
inline std::ptrdiff_t lantp( const char norm, const char uplo, const Diag,
        const fortran_int_t n, const float* ap, float* work ) {
    fortran_int_t info(0);
    LAPACK_SLANTP( &norm, &uplo, &lapack_option< Diag >::value, &n, ap, work );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Diag >
inline std::ptrdiff_t lantp( const char norm, const char uplo, const Diag,
        const fortran_int_t n, const double* ap, double* work ) {
    fortran_int_t info(0);
    LAPACK_DLANTP( &norm, &uplo, &lapack_option< Diag >::value, &n, ap, work );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Diag >
inline std::ptrdiff_t lantp( const char norm, const char uplo, const Diag,
        const fortran_int_t n, const std::complex<float>* ap, float* work ) {
    fortran_int_t info(0);
    LAPACK_CLANTP( &norm, &uplo, &lapack_option< Diag >::value, &n, ap, work );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Diag >
inline std::ptrdiff_t lantp( const char norm, const char uplo, const Diag,
        const fortran_int_t n, const std::complex<double>* ap, double* work ) {
    fortran_int_t info(0);
    LAPACK_ZLANTP( &norm, &uplo, &lapack_option< Diag >::value, &n, ap, work );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to lantp.
//
template< typename Value >
struct lantp_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename WORK >
    static std::ptrdiff_t invoke( const char norm, const char uplo,
            const MatrixAP& ap, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::diag_tag< MatrixAP >::type diag;
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( norm, bindings::size_column(ap) ));
        BOOST_ASSERT( bindings::size_column(ap) >= 0 );
        return detail::lantp( norm, uplo, diag(), bindings::size_column(ap),
                bindings::begin_value(ap),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAP >
    static std::ptrdiff_t invoke( const char norm, const char uplo,
            const MatrixAP& ap, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::diag_tag< MatrixAP >::type diag;
        bindings::detail::array< real_type > tmp_work( min_size_work( norm,
                bindings::size_column(ap) ) );
        return invoke( norm, uplo, ap, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAP >
    static std::ptrdiff_t invoke( const char norm, const char uplo,
            const MatrixAP& ap, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::diag_tag< MatrixAP >::type diag;
        return invoke( norm, uplo, ap, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char norm,
            const std::ptrdiff_t n ) {
        if ( norm == 'I' )
            return std::max< std::ptrdiff_t >( 1, n );
        else
            return 1;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the lantp_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for lantp. Its overload differs for
// * User-defined workspace
//
template< typename MatrixAP, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
lantp( const char norm, const char uplo, const MatrixAP& ap,
        Workspace work ) {
    return lantp_impl< typename bindings::value_type<
            MatrixAP >::type >::invoke( norm, uplo, ap, work );
}

//
// Overloaded function for lantp. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixAP >
inline typename boost::disable_if< detail::is_workspace< MatrixAP >,
        std::ptrdiff_t >::type
lantp( const char norm, const char uplo, const MatrixAP& ap ) {
    return lantp_impl< typename bindings::value_type<
            MatrixAP >::type >::invoke( norm, uplo, ap, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

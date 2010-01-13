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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HPTRI_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HPTRI_HPP

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
// The LAPACK-backend for hptri is the netlib-compatible backend.
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
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hptri( UpLo, const fortran_int_t n,
        std::complex<float>* ap, const fortran_int_t* ipiv,
        std::complex<float>* work ) {
    fortran_int_t info(0);
    LAPACK_CHPTRI( &lapack_option< UpLo >::value, &n, ap, ipiv, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hptri( UpLo, const fortran_int_t n,
        std::complex<double>* ap, const fortran_int_t* ipiv,
        std::complex<double>* work ) {
    fortran_int_t info(0);
    LAPACK_ZHPTRI( &lapack_option< UpLo >::value, &n, ap, ipiv, work, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hptri.
//
template< typename Value >
struct hptri_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename VectorIPIV, typename WORK >
    static std::ptrdiff_t invoke( MatrixAP& ap, const VectorIPIV& ipiv,
            detail::workspace1< WORK > work ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAP >::value) );
        BOOST_ASSERT( size(ipiv) >= size_column(ap) );
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work(
                size_column(ap) ));
        BOOST_ASSERT( size_column(ap) >= 0 );
        return detail::hptri( uplo(), size_column(ap), begin_value(ap),
                begin_value(ipiv), begin_value(work.select(value_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAP, typename VectorIPIV >
    static std::ptrdiff_t invoke( MatrixAP& ap, const VectorIPIV& ipiv,
            minimal_workspace work ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                size_column(ap) ) );
        return invoke( ap, ipiv, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAP, typename VectorIPIV >
    static std::ptrdiff_t invoke( MatrixAP& ap, const VectorIPIV& ipiv,
            optimal_workspace work ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        return invoke( ap, ipiv, minimal_workspace() );
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
// Calls to these functions are passed to the hptri_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hptri. Its overload differs for
// * MatrixAP&
// * User-defined workspace
//
template< typename MatrixAP, typename VectorIPIV, typename Workspace >
inline std::ptrdiff_t hptri( MatrixAP& ap, const VectorIPIV& ipiv,
        Workspace work ) {
    return hptri_impl< typename value< MatrixAP >::type >::invoke( ap,
            ipiv, work );
}

//
// Overloaded function for hptri. Its overload differs for
// * MatrixAP&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename VectorIPIV >
inline std::ptrdiff_t hptri( MatrixAP& ap, const VectorIPIV& ipiv ) {
    return hptri_impl< typename value< MatrixAP >::type >::invoke( ap,
            ipiv, optimal_workspace() );
}

//
// Overloaded function for hptri. Its overload differs for
// * const MatrixAP&
// * User-defined workspace
//
template< typename MatrixAP, typename VectorIPIV, typename Workspace >
inline std::ptrdiff_t hptri( const MatrixAP& ap, const VectorIPIV& ipiv,
        Workspace work ) {
    return hptri_impl< typename value< MatrixAP >::type >::invoke( ap,
            ipiv, work );
}

//
// Overloaded function for hptri. Its overload differs for
// * const MatrixAP&
// * Default workspace-type (optimal)
//
template< typename MatrixAP, typename VectorIPIV >
inline std::ptrdiff_t hptri( const MatrixAP& ap, const VectorIPIV& ipiv ) {
    return hptri_impl< typename value< MatrixAP >::type >::invoke( ap,
            ipiv, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

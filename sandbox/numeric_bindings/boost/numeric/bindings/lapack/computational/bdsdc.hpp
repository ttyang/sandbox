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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_BDSDC_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_BDSDC_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
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
// The LAPACK-backend for bdsdc is the netlib-compatible backend.
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
inline std::ptrdiff_t bdsdc( const char uplo, const char compq,
        const fortran_int_t n, float* d, float* e, float* u,
        const fortran_int_t ldu, float* vt, const fortran_int_t ldvt,
        float* q, fortran_int_t* iq, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SBDSDC( &uplo, &compq, &n, d, e, u, &ldu, vt, &ldvt, q, iq, work,
            iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t bdsdc( const char uplo, const char compq,
        const fortran_int_t n, double* d, double* e, double* u,
        const fortran_int_t ldu, double* vt, const fortran_int_t ldvt,
        double* q, fortran_int_t* iq, double* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DBDSDC( &uplo, &compq, &n, d, e, u, &ldu, vt, &ldvt, q, iq, work,
            iwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to bdsdc.
//
template< typename Value >
struct bdsdc_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename MatrixU,
            typename MatrixVT, typename VectorQ, typename VectorIQ,
            typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const char uplo, const char compq,
            const fortran_int_t n, VectorD& d, VectorE& e, MatrixU& u,
            MatrixVT& vt, VectorQ& q, VectorIQ& iq, detail::workspace2< WORK,
            IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVT >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVT >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVT >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorQ >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIQ >::value) );
        BOOST_ASSERT( bindings::size(e) >= n-1 );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( n ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( compq, n ));
        BOOST_ASSERT( bindings::size_minor(u) == 1 ||
                bindings::stride_minor(u) == 1 );
        BOOST_ASSERT( bindings::size_minor(vt) == 1 ||
                bindings::stride_minor(vt) == 1 );
        BOOST_ASSERT( compq == 'N' || compq == 'P' || compq == 'I' );
        BOOST_ASSERT( n >= 0 );
        return detail::bdsdc( uplo, compq, n, bindings::begin_value(d),
                bindings::begin_value(e), bindings::begin_value(u),
                bindings::stride_major(u), bindings::begin_value(vt),
                bindings::stride_major(vt), bindings::begin_value(q),
                bindings::begin_value(iq),
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
    template< typename VectorD, typename VectorE, typename MatrixU,
            typename MatrixVT, typename VectorQ, typename VectorIQ >
    static std::ptrdiff_t invoke( const char uplo, const char compq,
            const fortran_int_t n, VectorD& d, VectorE& e, MatrixU& u,
            MatrixVT& vt, VectorQ& q, VectorIQ& iq, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( compq,
                n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n ) );
        return invoke( uplo, compq, n, d, e, u, vt, q, iq,
                workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename MatrixU,
            typename MatrixVT, typename VectorQ, typename VectorIQ >
    static std::ptrdiff_t invoke( const char uplo, const char compq,
            const fortran_int_t n, VectorD& d, VectorE& e, MatrixU& u,
            MatrixVT& vt, VectorQ& q, VectorIQ& iq, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( uplo, compq, n, d, e, u, vt, q, iq,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char compq,
            const std::ptrdiff_t n ) {
        switch ( compq ) {
            case 'N': return 4*n;
            case 'P': return 6*n;
            case 'I': return 3*n*n + 4*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n ) {
        return 8*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the bdsdc_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for bdsdc. Its overload differs for
// * MatrixU&
// * MatrixVT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixU& u, MatrixVT& vt, VectorQ& q,
        VectorIQ& iq, Workspace work ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            work );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * MatrixU&
// * MatrixVT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ >
inline typename boost::disable_if< detail::is_workspace< VectorIQ >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixU& u, MatrixVT& vt, VectorQ& q,
        VectorIQ& iq ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            optimal_workspace() );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * const MatrixU&
// * MatrixVT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixU& u, MatrixVT& vt, VectorQ& q,
        VectorIQ& iq, Workspace work ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            work );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * const MatrixU&
// * MatrixVT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ >
inline typename boost::disable_if< detail::is_workspace< VectorIQ >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixU& u, MatrixVT& vt, VectorQ& q,
        VectorIQ& iq ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            optimal_workspace() );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * MatrixU&
// * const MatrixVT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixU& u, const MatrixVT& vt, VectorQ& q,
        VectorIQ& iq, Workspace work ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            work );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * MatrixU&
// * const MatrixVT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ >
inline typename boost::disable_if< detail::is_workspace< VectorIQ >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixU& u, const MatrixVT& vt, VectorQ& q,
        VectorIQ& iq ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            optimal_workspace() );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * const MatrixU&
// * const MatrixVT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixU& u, const MatrixVT& vt,
        VectorQ& q, VectorIQ& iq, Workspace work ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            work );
}

//
// Overloaded function for bdsdc. Its overload differs for
// * const MatrixU&
// * const MatrixVT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixU,
        typename MatrixVT, typename VectorQ, typename VectorIQ >
inline typename boost::disable_if< detail::is_workspace< VectorIQ >,
        std::ptrdiff_t >::type
bdsdc( const char uplo, const char compq, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixU& u, const MatrixVT& vt,
        VectorQ& q, VectorIQ& iq ) {
    return bdsdc_impl< typename bindings::value_type<
            VectorD >::type >::invoke( uplo, compq, n, d, e, u, vt, q, iq,
            optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LARRE_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LARRE_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for larre is the netlib-compatible backend.
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
inline std::ptrdiff_t larre( const char range, const fortran_int_t n,
        float& vl, float& vu, const fortran_int_t il, const fortran_int_t iu,
        float* d, float* e, float* e2, const float rtol1, const float rtol2,
        const float spltol, fortran_int_t& nsplit, fortran_int_t* isplit,
        fortran_int_t& m, float* w, float* werr, float* wgap,
        fortran_int_t* iblock, fortran_int_t* indexw, float* gers,
        float& pivmin, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SLARRE( &range, &n, &vl, &vu, &il, &iu, d, e, e2, &rtol1, &rtol2,
            &spltol, &nsplit, isplit, &m, w, werr, wgap, iblock, indexw, gers,
            &pivmin, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t larre( const char range, const fortran_int_t n,
        double& vl, double& vu, const fortran_int_t il,
        const fortran_int_t iu, double* d, double* e, double* e2,
        const double rtol1, const double rtol2, const double spltol,
        fortran_int_t& nsplit, fortran_int_t* isplit, fortran_int_t& m,
        double* w, double* werr, double* wgap, fortran_int_t* iblock,
        fortran_int_t* indexw, double* gers, double& pivmin, double* work,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DLARRE( &range, &n, &vl, &vu, &il, &iu, d, e, e2, &rtol1, &rtol2,
            &spltol, &nsplit, isplit, &m, w, werr, wgap, iblock, indexw, gers,
            &pivmin, work, iwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to larre.
//
template< typename Value >
struct larre_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename VectorE2,
            typename VectorISPLIT, typename VectorW, typename VectorWERR,
            typename VectorWGAP, typename VectorIBLOCK, typename VectorINDEXW,
            typename VectorGERS, typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const char range, const fortran_int_t n,
            real_type& vl, real_type& vu, const fortran_int_t il,
            const fortran_int_t iu, VectorD& d, VectorE& e, VectorE2& e2,
            const real_type rtol1, const real_type rtol2,
            const real_type spltol, fortran_int_t& nsplit,
            VectorISPLIT& isplit, fortran_int_t& m, VectorW& w,
            VectorWERR& werr, VectorWGAP& wgap, VectorIBLOCK& iblock,
            VectorINDEXW& indexw, VectorGERS& gers, real_type& pivmin,
            detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE2 >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorWERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorWGAP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorGERS >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorISPLIT >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorIBLOCK >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorISPLIT >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorINDEXW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE2 >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorISPLIT >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorWERR >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorWGAP >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorIBLOCK >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorINDEXW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorGERS >::value) );
        BOOST_ASSERT( bindings::size(d) >= n );
        BOOST_ASSERT( bindings::size(e) >= n );
        BOOST_ASSERT( bindings::size(e2) >= n );
        BOOST_ASSERT( bindings::size(gers) >= 2*n );
        BOOST_ASSERT( bindings::size(indexw) >= n );
        BOOST_ASSERT( bindings::size(isplit) >= n );
        BOOST_ASSERT( bindings::size(w) >= n );
        BOOST_ASSERT( bindings::size(werr) >= n );
        BOOST_ASSERT( bindings::size(wgap) >= n );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( n ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( n ));
        BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
        return detail::larre( range, n, vl, vu, il, iu,
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(e2), rtol1, rtol2, spltol, nsplit,
                bindings::begin_value(isplit), m, bindings::begin_value(w),
                bindings::begin_value(werr), bindings::begin_value(wgap),
                bindings::begin_value(iblock), bindings::begin_value(indexw),
                bindings::begin_value(gers), pivmin,
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
    template< typename VectorD, typename VectorE, typename VectorE2,
            typename VectorISPLIT, typename VectorW, typename VectorWERR,
            typename VectorWGAP, typename VectorIBLOCK, typename VectorINDEXW,
            typename VectorGERS >
    static std::ptrdiff_t invoke( const char range, const fortran_int_t n,
            real_type& vl, real_type& vu, const fortran_int_t il,
            const fortran_int_t iu, VectorD& d, VectorE& e, VectorE2& e2,
            const real_type rtol1, const real_type rtol2,
            const real_type spltol, fortran_int_t& nsplit,
            VectorISPLIT& isplit, fortran_int_t& m, VectorW& w,
            VectorWERR& werr, VectorWGAP& wgap, VectorIBLOCK& iblock,
            VectorINDEXW& indexw, VectorGERS& gers, real_type& pivmin,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n ) );
        return invoke( range, n, vl, vu, il, iu, d, e, e2, rtol1, rtol2,
                spltol, nsplit, isplit, m, w, werr, wgap, iblock, indexw,
                gers, pivmin, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename VectorE2,
            typename VectorISPLIT, typename VectorW, typename VectorWERR,
            typename VectorWGAP, typename VectorIBLOCK, typename VectorINDEXW,
            typename VectorGERS >
    static std::ptrdiff_t invoke( const char range, const fortran_int_t n,
            real_type& vl, real_type& vu, const fortran_int_t il,
            const fortran_int_t iu, VectorD& d, VectorE& e, VectorE2& e2,
            const real_type rtol1, const real_type rtol2,
            const real_type spltol, fortran_int_t& nsplit,
            VectorISPLIT& isplit, fortran_int_t& m, VectorW& w,
            VectorWERR& werr, VectorWGAP& wgap, VectorIBLOCK& iblock,
            VectorINDEXW& indexw, VectorGERS& gers, real_type& pivmin,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( range, n, vl, vu, il, iu, d, e, e2, rtol1, rtol2,
                spltol, nsplit, isplit, m, w, werr, wgap, iblock, indexw,
                gers, pivmin, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 6*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n ) {
        return 5*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the larre_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for larre. Its overload differs for
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorE2,
        typename VectorISPLIT, typename VectorW, typename VectorWERR,
        typename VectorWGAP, typename VectorIBLOCK, typename VectorINDEXW,
        typename VectorGERS, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
larre( const char range, const fortran_int_t n,
        typename remove_imaginary< typename bindings::value_type<
        VectorD >::type >::type& vl, typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type& vu,
        const fortran_int_t il, const fortran_int_t iu, VectorD& d,
        VectorE& e, VectorE2& e2, const typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type rtol1,
        const typename remove_imaginary< typename bindings::value_type<
        VectorD >::type >::type rtol2, const typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type spltol,
        fortran_int_t& nsplit, VectorISPLIT& isplit, fortran_int_t& m,
        VectorW& w, VectorWERR& werr, VectorWGAP& wgap, VectorIBLOCK& iblock,
        VectorINDEXW& indexw, VectorGERS& gers, typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type& pivmin,
        Workspace work ) {
    return larre_impl< typename bindings::value_type<
            VectorD >::type >::invoke( range, n, vl, vu, il, iu, d, e, e2,
            rtol1, rtol2, spltol, nsplit, isplit, m, w, werr, wgap, iblock,
            indexw, gers, pivmin, work );
}

//
// Overloaded function for larre. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorE2,
        typename VectorISPLIT, typename VectorW, typename VectorWERR,
        typename VectorWGAP, typename VectorIBLOCK, typename VectorINDEXW,
        typename VectorGERS >
inline typename boost::disable_if< detail::is_workspace< VectorGERS >,
        std::ptrdiff_t >::type
larre( const char range, const fortran_int_t n,
        typename remove_imaginary< typename bindings::value_type<
        VectorD >::type >::type& vl, typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type& vu,
        const fortran_int_t il, const fortran_int_t iu, VectorD& d,
        VectorE& e, VectorE2& e2, const typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type rtol1,
        const typename remove_imaginary< typename bindings::value_type<
        VectorD >::type >::type rtol2, const typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type spltol,
        fortran_int_t& nsplit, VectorISPLIT& isplit, fortran_int_t& m,
        VectorW& w, VectorWERR& werr, VectorWGAP& wgap, VectorIBLOCK& iblock,
        VectorINDEXW& indexw, VectorGERS& gers, typename remove_imaginary<
        typename bindings::value_type< VectorD >::type >::type& pivmin ) {
    return larre_impl< typename bindings::value_type<
            VectorD >::type >::invoke( range, n, vl, vu, il, iu, d, e, e2,
            rtol1, rtol2, spltol, nsplit, isplit, m, w, werr, wgap, iblock,
            indexw, gers, pivmin, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

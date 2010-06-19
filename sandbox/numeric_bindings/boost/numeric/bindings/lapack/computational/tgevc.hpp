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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGEVC_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGEVC_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for tgevc is the netlib-compatible backend.
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
template< typename Side >
inline std::ptrdiff_t tgevc( const Side side, const char howmny,
        const logical_t* select, const fortran_int_t n, const float* s,
        const fortran_int_t lds, const float* p, const fortran_int_t ldp,
        float* vl, const fortran_int_t ldvl, float* vr,
        const fortran_int_t ldvr, const fortran_int_t mm, fortran_int_t& m,
        float* work ) {
    fortran_int_t info(0);
    LAPACK_STGEVC( &lapack_option< Side >::value, &howmny, select, &n, s,
            &lds, p, &ldp, vl, &ldvl, vr, &ldvr, &mm, &m, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Side >
inline std::ptrdiff_t tgevc( const Side side, const char howmny,
        const logical_t* select, const fortran_int_t n, const double* s,
        const fortran_int_t lds, const double* p, const fortran_int_t ldp,
        double* vl, const fortran_int_t ldvl, double* vr,
        const fortran_int_t ldvr, const fortran_int_t mm, fortran_int_t& m,
        double* work ) {
    fortran_int_t info(0);
    LAPACK_DTGEVC( &lapack_option< Side >::value, &howmny, select, &n, s,
            &lds, p, &ldp, vl, &ldvl, vr, &ldvr, &mm, &m, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Side >
inline std::ptrdiff_t tgevc( const Side side, const char howmny,
        const logical_t* select, const fortran_int_t n,
        const std::complex<float>* s, const fortran_int_t lds,
        const std::complex<float>* p, const fortran_int_t ldp,
        std::complex<float>* vl, const fortran_int_t ldvl,
        std::complex<float>* vr, const fortran_int_t ldvr,
        const fortran_int_t mm, fortran_int_t& m, std::complex<float>* work,
        float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CTGEVC( &lapack_option< Side >::value, &howmny, select, &n, s,
            &lds, p, &ldp, vl, &ldvl, vr, &ldvr, &mm, &m, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Side >
inline std::ptrdiff_t tgevc( const Side side, const char howmny,
        const logical_t* select, const fortran_int_t n,
        const std::complex<double>* s, const fortran_int_t lds,
        const std::complex<double>* p, const fortran_int_t ldp,
        std::complex<double>* vl, const fortran_int_t ldvl,
        std::complex<double>* vr, const fortran_int_t ldvr,
        const fortran_int_t mm, fortran_int_t& m, std::complex<double>* work,
        double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZTGEVC( &lapack_option< Side >::value, &howmny, select, &n, s,
            &lds, p, &ldp, vl, &ldvl, vr, &ldvr, &mm, &m, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tgevc.
//
template< typename Value, typename Enable = void >
struct tgevc_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct tgevc_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename Side, typename VectorSELECT, typename MatrixS,
            typename MatrixP, typename MatrixVL, typename MatrixVR,
            typename WORK >
    static std::ptrdiff_t invoke( const Side side, const char howmny,
            const VectorSELECT& select, const MatrixS& s, const MatrixP& p,
            MatrixVL& vl, MatrixVR& vr, const fortran_int_t mm,
            fortran_int_t& m, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixS >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixP >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVR >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixS >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixS >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVL >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixS >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(s) ));
        BOOST_ASSERT( bindings::size_column(s) >= 0 );
        BOOST_ASSERT( bindings::size_minor(p) == 1 ||
                bindings::stride_minor(p) == 1 );
        BOOST_ASSERT( bindings::size_minor(s) == 1 ||
                bindings::stride_minor(s) == 1 );
        BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
                bindings::stride_minor(vl) == 1 );
        BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
                bindings::stride_minor(vr) == 1 );
        BOOST_ASSERT( bindings::stride_major(p) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(s)) );
        BOOST_ASSERT( bindings::stride_major(s) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(s)) );
        BOOST_ASSERT( howmny == 'A' || howmny == 'B' || howmny == 'S' );
        return detail::tgevc( side, howmny, bindings::begin_value(select),
                bindings::size_column(s), bindings::begin_value(s),
                bindings::stride_major(s), bindings::begin_value(p),
                bindings::stride_major(p), bindings::begin_value(vl),
                bindings::stride_major(vl), bindings::begin_value(vr),
                bindings::stride_major(vr), mm, m,
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename Side, typename VectorSELECT, typename MatrixS,
            typename MatrixP, typename MatrixVL, typename MatrixVR >
    static std::ptrdiff_t invoke( const Side side, const char howmny,
            const VectorSELECT& select, const MatrixS& s, const MatrixP& p,
            MatrixVL& vl, MatrixVR& vr, const fortran_int_t mm,
            fortran_int_t& m, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(s) ) );
        return invoke( side, howmny, select, s, p, vl, vr, mm, m,
                workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename Side, typename VectorSELECT, typename MatrixS,
            typename MatrixP, typename MatrixVL, typename MatrixVR >
    static std::ptrdiff_t invoke( const Side side, const char howmny,
            const VectorSELECT& select, const MatrixS& s, const MatrixP& p,
            MatrixVL& vl, MatrixVR& vr, const fortran_int_t mm,
            fortran_int_t& m, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( side, howmny, select, s, p, vl, vr, mm, m,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 6*n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct tgevc_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename Side, typename VectorSELECT, typename MatrixS,
            typename MatrixP, typename MatrixVL, typename MatrixVR,
            typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const Side side, const char howmny,
            const VectorSELECT& select, const MatrixS& s, const MatrixP& p,
            MatrixVL& vl, MatrixVR& vr, const fortran_int_t mm,
            fortran_int_t& m, detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixS >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixP >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixVR >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixS >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixP >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixS >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVL >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixS >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixVR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(s) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(s) ));
        BOOST_ASSERT( bindings::size_column(s) >= 0 );
        BOOST_ASSERT( bindings::size_minor(p) == 1 ||
                bindings::stride_minor(p) == 1 );
        BOOST_ASSERT( bindings::size_minor(s) == 1 ||
                bindings::stride_minor(s) == 1 );
        BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
                bindings::stride_minor(vl) == 1 );
        BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
                bindings::stride_minor(vr) == 1 );
        BOOST_ASSERT( bindings::stride_major(p) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(s)) );
        BOOST_ASSERT( bindings::stride_major(s) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(s)) );
        BOOST_ASSERT( howmny == 'A' || howmny == 'B' || howmny == 'S' );
        return detail::tgevc( side, howmny, bindings::begin_value(select),
                bindings::size_column(s), bindings::begin_value(s),
                bindings::stride_major(s), bindings::begin_value(p),
                bindings::stride_major(p), bindings::begin_value(vl),
                bindings::stride_major(vl), bindings::begin_value(vr),
                bindings::stride_major(vr), mm, m,
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
    template< typename Side, typename VectorSELECT, typename MatrixS,
            typename MatrixP, typename MatrixVL, typename MatrixVR >
    static std::ptrdiff_t invoke( const Side side, const char howmny,
            const VectorSELECT& select, const MatrixS& s, const MatrixP& p,
            MatrixVL& vl, MatrixVR& vr, const fortran_int_t mm,
            fortran_int_t& m, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(s) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(s) ) );
        return invoke( side, howmny, select, s, p, vl, vr, mm, m,
                workspace( tmp_work, tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename Side, typename VectorSELECT, typename MatrixS,
            typename MatrixP, typename MatrixVL, typename MatrixVR >
    static std::ptrdiff_t invoke( const Side side, const char howmny,
            const VectorSELECT& select, const MatrixS& s, const MatrixP& p,
            MatrixVL& vl, MatrixVR& vr, const fortran_int_t mm,
            fortran_int_t& m, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( side, howmny, select, s, p, vl, vr, mm, m,
                minimal_workspace() );
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
        return 2*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the tgevc_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tgevc. Its overload differs for
// * MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, work );
}

//
// Overloaded function for tgevc. Its overload differs for
// * MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR >
inline typename boost::disable_if< detail::is_workspace< MatrixVR >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, optimal_workspace() );
}

//
// Overloaded function for tgevc. Its overload differs for
// * const MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, const MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, work );
}

//
// Overloaded function for tgevc. Its overload differs for
// * const MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR >
inline typename boost::disable_if< detail::is_workspace< MatrixVR >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, const MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, optimal_workspace() );
}

//
// Overloaded function for tgevc. Its overload differs for
// * MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, MatrixVL& vl, const MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, work );
}

//
// Overloaded function for tgevc. Its overload differs for
// * MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR >
inline typename boost::disable_if< detail::is_workspace< MatrixVR >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, MatrixVL& vl, const MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, optimal_workspace() );
}

//
// Overloaded function for tgevc. Its overload differs for
// * const MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, work );
}

//
// Overloaded function for tgevc. Its overload differs for
// * const MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename Side, typename VectorSELECT, typename MatrixS,
        typename MatrixP, typename MatrixVL, typename MatrixVR >
inline typename boost::disable_if< detail::is_workspace< MatrixVR >,
        std::ptrdiff_t >::type
tgevc( const Side side, const char howmny, const VectorSELECT& select,
        const MatrixS& s, const MatrixP& p, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return tgevc_impl< typename bindings::value_type<
            MatrixS >::type >::invoke( side, howmny, select, s, p, vl, vr, mm,
            m, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

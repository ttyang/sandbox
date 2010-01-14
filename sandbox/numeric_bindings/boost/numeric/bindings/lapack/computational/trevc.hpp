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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TREVC_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TREVC_HPP

#include <boost/assert.hpp>
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
// The LAPACK-backend for trevc is the netlib-compatible backend.
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
inline std::ptrdiff_t trevc( const char side, const char howmny,
        logical_t* select, const fortran_int_t n, const float* t,
        const fortran_int_t ldt, float* vl, const fortran_int_t ldvl,
        float* vr, const fortran_int_t ldvr, const fortran_int_t mm,
        fortran_int_t& m, float* work ) {
    fortran_int_t info(0);
    LAPACK_STREVC( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            &mm, &m, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t trevc( const char side, const char howmny,
        logical_t* select, const fortran_int_t n, const double* t,
        const fortran_int_t ldt, double* vl, const fortran_int_t ldvl,
        double* vr, const fortran_int_t ldvr, const fortran_int_t mm,
        fortran_int_t& m, double* work ) {
    fortran_int_t info(0);
    LAPACK_DTREVC( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            &mm, &m, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const logical_t* select, const fortran_int_t n,
        std::complex<float>* t, const fortran_int_t ldt,
        std::complex<float>* vl, const fortran_int_t ldvl,
        std::complex<float>* vr, const fortran_int_t ldvr,
        const fortran_int_t mm, fortran_int_t& m, std::complex<float>* work,
        float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CTREVC( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            &mm, &m, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const logical_t* select, const fortran_int_t n,
        std::complex<double>* t, const fortran_int_t ldt,
        std::complex<double>* vl, const fortran_int_t ldvl,
        std::complex<double>* vr, const fortran_int_t ldvr,
        const fortran_int_t mm, fortran_int_t& m, std::complex<double>* work,
        double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZTREVC( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            &mm, &m, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trevc.
//
template< typename Value, typename Enable = void >
struct trevc_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct trevc_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename WORK >
    static std::ptrdiff_t invoke( const char side, const char howmny,
            VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
            detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixT >::type >::type,
                typename remove_const< typename value<
                MatrixVL >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixT >::type >::type,
                typename remove_const< typename value<
                MatrixVR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorSELECT >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(t) ));
        BOOST_ASSERT( bindings::size_column(t) >= 0 );
        BOOST_ASSERT( bindings::size_minor(t) == 1 ||
                bindings::stride_minor(t) == 1 );
        BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
                bindings::stride_minor(vl) == 1 );
        BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
                bindings::stride_minor(vr) == 1 );
        BOOST_ASSERT( bindings::stride_major(t) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(t)) );
        BOOST_ASSERT( howmny == 'A' || howmny == 'B' || howmny == 'S' );
        BOOST_ASSERT( mm >= m );
        BOOST_ASSERT( side == 'R' || side == 'L' || side == 'B' );
        return detail::trevc( side, howmny, bindings::begin_value(select),
                bindings::size_column(t), bindings::begin_value(t),
                bindings::stride_major(t), bindings::begin_value(vl),
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
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static std::ptrdiff_t invoke( const char side, const char howmny,
            VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(t) ) );
        return invoke( side, howmny, select, t, vl, vr, mm, m,
                workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static std::ptrdiff_t invoke( const char side, const char howmny,
            VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( side, howmny, select, t, vl, vr, mm, m,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 3*n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct trevc_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const char side, const char howmny,
            const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
            detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixT >::type >::type,
                typename remove_const< typename value<
                MatrixVL >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixT >::type >::type,
                typename remove_const< typename value<
                MatrixVR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixT >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVL >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixVR >::value) );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(t) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(t) ));
        BOOST_ASSERT( bindings::size_column(t) >= 0 );
        BOOST_ASSERT( bindings::size_minor(t) == 1 ||
                bindings::stride_minor(t) == 1 );
        BOOST_ASSERT( bindings::size_minor(vl) == 1 ||
                bindings::stride_minor(vl) == 1 );
        BOOST_ASSERT( bindings::size_minor(vr) == 1 ||
                bindings::stride_minor(vr) == 1 );
        BOOST_ASSERT( bindings::stride_major(t) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(t)) );
        BOOST_ASSERT( howmny == 'A' || howmny == 'B' || howmny == 'S' );
        BOOST_ASSERT( mm >= m );
        BOOST_ASSERT( side == 'R' || side == 'L' || side == 'B' );
        return detail::trevc( side, howmny, bindings::begin_value(select),
                bindings::size_column(t), bindings::begin_value(t),
                bindings::stride_major(t), bindings::begin_value(vl),
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
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static std::ptrdiff_t invoke( const char side, const char howmny,
            const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
            minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(t) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(t) ) );
        return invoke( side, howmny, select, t, vl, vr, mm, m,
                workspace( tmp_work, tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static std::ptrdiff_t invoke( const char side, const char howmny,
            const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
            optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( side, howmny, select, t, vl, vr, mm, m,
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
        return n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the trevc_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, const MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, const MatrixVL& vl, MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, const MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, const MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, MatrixVL& vl, const MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m, Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, MatrixVL& vl, const MatrixVR& vr,
        const fortran_int_t mm, fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm, fortran_int_t& m,
        Workspace work ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, work );
}

//
// Overloaded function for trevc. Its overload differs for
// * const VectorSELECT&
// * const MatrixT&
// * const MatrixVL&
// * const MatrixVR&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline std::ptrdiff_t trevc( const char side, const char howmny,
        const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, const fortran_int_t mm,
        fortran_int_t& m ) {
    return trevc_impl< typename value< MatrixT >::type >::invoke( side,
            howmny, select, t, vl, vr, mm, m, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

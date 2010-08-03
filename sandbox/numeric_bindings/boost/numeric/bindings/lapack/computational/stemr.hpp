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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEMR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEMR_HPP

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
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for stemr is the netlib-compatible backend.
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
inline std::ptrdiff_t stemr( const char jobz, const char range,
        const fortran_int_t n, float* d, float* e, const float vl,
        const float vu, const fortran_int_t il, const fortran_int_t iu,
        fortran_int_t& m, float* w, float* z, const fortran_int_t ldz,
        const fortran_int_t nzc, fortran_int_t* isuppz,
        fortran_bool_t& tryrac, float* work, const fortran_int_t lwork,
        fortran_int_t* iwork, const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_SSTEMR( &jobz, &range, &n, d, e, &vl, &vu, &il, &iu, &m, w, z,
            &ldz, &nzc, isuppz, &tryrac, work, &lwork, iwork, &liwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t stemr( const char jobz, const char range,
        const fortran_int_t n, double* d, double* e, const double vl,
        const double vu, const fortran_int_t il, const fortran_int_t iu,
        fortran_int_t& m, double* w, double* z, const fortran_int_t ldz,
        const fortran_int_t nzc, fortran_int_t* isuppz,
        fortran_bool_t& tryrac, double* work, const fortran_int_t lwork,
        fortran_int_t* iwork, const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_DSTEMR( &jobz, &range, &n, d, e, &vl, &vu, &il, &iu, &m, w, z,
            &ldz, &nzc, isuppz, &tryrac, work, &lwork, iwork, &liwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t stemr( const char jobz, const char range,
        const fortran_int_t n, float* d, float* e, const float vl,
        const float vu, const fortran_int_t il, const fortran_int_t iu,
        fortran_int_t& m, float* w, std::complex<float>* z,
        const fortran_int_t ldz, const fortran_int_t nzc,
        fortran_int_t* isuppz, fortran_bool_t& tryrac, float* work,
        const fortran_int_t lwork, fortran_int_t* iwork,
        const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_CSTEMR( &jobz, &range, &n, d, e, &vl, &vu, &il, &iu, &m, w, z,
            &ldz, &nzc, isuppz, &tryrac, work, &lwork, iwork, &liwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t stemr( const char jobz, const char range,
        const fortran_int_t n, double* d, double* e, const double vl,
        const double vu, const fortran_int_t il, const fortran_int_t iu,
        fortran_int_t& m, double* w, std::complex<double>* z,
        const fortran_int_t ldz, const fortran_int_t nzc,
        fortran_int_t* isuppz, fortran_bool_t& tryrac, double* work,
        const fortran_int_t lwork, fortran_int_t* iwork,
        const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_ZSTEMR( &jobz, &range, &n, d, e, &vl, &vu, &il, &iu, &m, w, z,
            &ldz, &nzc, isuppz, &tryrac, work, &lwork, iwork, &liwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to stemr.
//
template< typename Value, typename Enable = void >
struct stemr_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct stemr_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename MatrixZ, typename VectorISUPPZ, typename WORK,
            typename IWORK >
    static std::ptrdiff_t invoke( const char jobz, const char range,
            const fortran_int_t n, VectorD& d, VectorE& e,
            const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            fortran_int_t& m, VectorW& w, MatrixZ& z,
            const fortran_int_t nzc, VectorISUPPZ& isuppz,
            fortran_bool_t& tryrac, detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixZ >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorISUPPZ >::value) );
        BOOST_ASSERT( bindings::size(d) >= n );
        BOOST_ASSERT( bindings::size(e) >= n );
        BOOST_ASSERT( bindings::size(w) >= n );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( n, jobz ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( n, jobz ));
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
        return detail::stemr( jobz, range, n, bindings::begin_value(d),
                bindings::begin_value(e), vl, vu, il, iu, m,
                bindings::begin_value(w), bindings::begin_value(z),
                bindings::stride_major(z), nzc, bindings::begin_value(isuppz),
                tryrac, bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())),
                bindings::size(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename MatrixZ, typename VectorISUPPZ >
    static std::ptrdiff_t invoke( const char jobz, const char range,
            const fortran_int_t n, VectorD& d, VectorE& e,
            const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            fortran_int_t& m, VectorW& w, MatrixZ& z,
            const fortran_int_t nzc, VectorISUPPZ& isuppz,
            fortran_bool_t& tryrac, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( n,
                jobz ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n, jobz ) );
        return invoke( jobz, range, n, d, e, vl, vu, il, iu, m, w, z, nzc,
                isuppz, tryrac, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename MatrixZ, typename VectorISUPPZ >
    static std::ptrdiff_t invoke( const char jobz, const char range,
            const fortran_int_t n, VectorD& d, VectorE& e,
            const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            fortran_int_t& m, VectorW& w, MatrixZ& z,
            const fortran_int_t nzc, VectorISUPPZ& isuppz,
            fortran_bool_t& tryrac, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        real_type opt_size_work;
        fortran_int_t opt_size_iwork;
        detail::stemr( jobz, range, n, bindings::begin_value(d),
                bindings::begin_value(e), vl, vu, il, iu, m,
                bindings::begin_value(w), bindings::begin_value(z),
                bindings::stride_major(z), nzc, bindings::begin_value(isuppz),
                tryrac, &opt_size_work, -1, &opt_size_iwork, -1 );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        return invoke( jobz, range, n, d, e, vl, vu, il, iu, m, w, z, nzc,
                isuppz, tryrac, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n,
            const char jobz ) {
        if ( jobz == 'V' ) {
            return std::max< std::ptrdiff_t >( 1, 18*n );
        } else {
            return std::max< std::ptrdiff_t >( 1, 12*n );
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n,
            const char jobz ) {
        if ( jobz == 'V' ) {
            return std::max< std::ptrdiff_t >( 1, 10*n );
        } else {
            return std::max< std::ptrdiff_t >( 1, 8*n );
        }
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct stemr_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename MatrixZ, typename VectorISUPPZ, typename WORK,
            typename IWORK >
    static std::ptrdiff_t invoke( const char jobz, const char range,
            const fortran_int_t n, VectorD& d, VectorE& e,
            const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            fortran_int_t& m, VectorW& w, MatrixZ& z,
            const fortran_int_t nzc, VectorISUPPZ& isuppz,
            fortran_bool_t& tryrac, detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixZ >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorISUPPZ >::value) );
        BOOST_ASSERT( bindings::size(d) >= n );
        BOOST_ASSERT( bindings::size(e) >= n );
        BOOST_ASSERT( bindings::size(w) >= n );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( n, jobz ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( n, jobz ));
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
        return detail::stemr( jobz, range, n, bindings::begin_value(d),
                bindings::begin_value(e), vl, vu, il, iu, m,
                bindings::begin_value(w), bindings::begin_value(z),
                bindings::stride_major(z), nzc, bindings::begin_value(isuppz),
                tryrac, bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())),
                bindings::size(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename MatrixZ, typename VectorISUPPZ >
    static std::ptrdiff_t invoke( const char jobz, const char range,
            const fortran_int_t n, VectorD& d, VectorE& e,
            const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            fortran_int_t& m, VectorW& w, MatrixZ& z,
            const fortran_int_t nzc, VectorISUPPZ& isuppz,
            fortran_bool_t& tryrac, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( n,
                jobz ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n, jobz ) );
        return invoke( jobz, range, n, d, e, vl, vu, il, iu, m, w, z, nzc,
                isuppz, tryrac, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename MatrixZ, typename VectorISUPPZ >
    static std::ptrdiff_t invoke( const char jobz, const char range,
            const fortran_int_t n, VectorD& d, VectorE& e,
            const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            fortran_int_t& m, VectorW& w, MatrixZ& z,
            const fortran_int_t nzc, VectorISUPPZ& isuppz,
            fortran_bool_t& tryrac, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        real_type opt_size_work;
        fortran_int_t opt_size_iwork;
        detail::stemr( jobz, range, n, bindings::begin_value(d),
                bindings::begin_value(e), vl, vu, il, iu, m,
                bindings::begin_value(w), bindings::begin_value(z),
                bindings::stride_major(z), nzc, bindings::begin_value(isuppz),
                tryrac, &opt_size_work, -1, &opt_size_iwork, -1 );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        return invoke( jobz, range, n, d, e, vl, vu, il, iu, m, w, z, nzc,
                isuppz, tryrac, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n,
            const char jobz ) {
        if ( jobz == 'V' ) {
            return std::max< std::ptrdiff_t >( 1, 18*n );
        } else {
            return std::max< std::ptrdiff_t >( 1, 12*n );
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n,
            const char jobz ) {
        if ( jobz == 'V' ) {
            return std::max< std::ptrdiff_t >( 1, 10*n );
        } else {
            return std::max< std::ptrdiff_t >( 1, 8*n );
        }
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the stemr_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for stemr. Its overload differs for
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename MatrixZ, typename VectorISUPPZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
stemr( const char jobz, const char range, const fortran_int_t n,
        VectorD& d, VectorE& e, const typename remove_imaginary<
        typename bindings::value_type< MatrixZ >::type >::type vl,
        const typename remove_imaginary< typename bindings::value_type<
        MatrixZ >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, fortran_int_t& m, VectorW& w,
        MatrixZ& z, const fortran_int_t nzc, VectorISUPPZ& isuppz,
        fortran_bool_t& tryrac, Workspace work ) {
    return stemr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( jobz, range, n, d, e, vl, vu, il, iu,
            m, w, z, nzc, isuppz, tryrac, work );
}

//
// Overloaded function for stemr. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename MatrixZ, typename VectorISUPPZ >
inline typename boost::disable_if< detail::is_workspace< VectorISUPPZ >,
        std::ptrdiff_t >::type
stemr( const char jobz, const char range, const fortran_int_t n,
        VectorD& d, VectorE& e, const typename remove_imaginary<
        typename bindings::value_type< MatrixZ >::type >::type vl,
        const typename remove_imaginary< typename bindings::value_type<
        MatrixZ >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, fortran_int_t& m, VectorW& w,
        MatrixZ& z, const fortran_int_t nzc, VectorISUPPZ& isuppz,
        fortran_bool_t& tryrac ) {
    return stemr_impl< typename bindings::value_type<
            MatrixZ >::type >::invoke( jobz, range, n, d, e, vl, vu, il, iu,
            m, w, z, nzc, isuppz, tryrac, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

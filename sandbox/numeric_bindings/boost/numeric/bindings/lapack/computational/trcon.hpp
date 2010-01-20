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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRCON_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for trcon is the netlib-compatible backend.
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
template< typename UpLo, typename Diag >
inline std::ptrdiff_t trcon( const char norm, const UpLo uplo, const Diag diag,
        const fortran_int_t n, const float* a, const fortran_int_t lda,
        float& rcond, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_STRCON( &norm, &lapack_option< UpLo >::value, &lapack_option<
            Diag >::value, &n, a, &lda, &rcond, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo, typename Diag >
inline std::ptrdiff_t trcon( const char norm, const UpLo uplo, const Diag diag,
        const fortran_int_t n, const double* a, const fortran_int_t lda,
        double& rcond, double* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DTRCON( &norm, &lapack_option< UpLo >::value, &lapack_option<
            Diag >::value, &n, a, &lda, &rcond, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename UpLo, typename Diag >
inline std::ptrdiff_t trcon( const char norm, const UpLo uplo, const Diag diag,
        const fortran_int_t n, const std::complex<float>* a,
        const fortran_int_t lda, float& rcond, std::complex<float>* work,
        float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CTRCON( &norm, &lapack_option< UpLo >::value, &lapack_option<
            Diag >::value, &n, a, &lda, &rcond, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo, typename Diag >
inline std::ptrdiff_t trcon( const char norm, const UpLo uplo, const Diag diag,
        const fortran_int_t n, const std::complex<double>* a,
        const fortran_int_t lda, double& rcond, std::complex<double>* work,
        double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZTRCON( &norm, &lapack_option< UpLo >::value, &lapack_option<
            Diag >::value, &n, a, &lda, &rcond, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trcon.
//
template< typename Value, typename Enable = void >
struct trcon_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct trcon_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
            real_type& rcond, detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        return detail::trcon( norm, uplo(), diag(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a), rcond,
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
    template< typename MatrixA >
    static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
            real_type& rcond, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( bindings::size_column(a) ) );
        return invoke( norm, a, rcond, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA >
    static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
            real_type& rcond, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        return invoke( norm, a, rcond, minimal_workspace() );
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
struct trcon_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename WORK, typename RWORK >
    static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
            real_type& rcond, detail::workspace2< WORK, RWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        return detail::trcon( norm, uplo(), diag(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a), rcond,
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
    template< typename MatrixA >
    static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
            real_type& rcond, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(a) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork(
                bindings::size_column(a) ) );
        return invoke( norm, a, rcond, workspace( tmp_work, tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA >
    static std::ptrdiff_t invoke( const char norm, const MatrixA& a,
            real_type& rcond, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        typedef typename result_of::diag_tag< MatrixA >::type diag;
        return invoke( norm, a, rcond, minimal_workspace() );
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
// Calls to these functions are passed to the trcon_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trcon. Its overload differs for
// * User-defined workspace
//
template< typename MatrixA, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
trcon( const char norm, const MatrixA& a, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rcond,
        Workspace work ) {
    return trcon_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( norm, a, rcond, work );
}

//
// Overloaded function for trcon. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixA >
inline typename boost::disable_if< detail::is_workspace< MatrixA >,
        std::ptrdiff_t >::type
trcon( const char norm, const MatrixA& a, typename remove_imaginary<
        typename bindings::value_type< MatrixA >::type >::type& rcond ) {
    return trcon_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( norm, a, rcond, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

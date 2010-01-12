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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGSYL_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TGSYL_HPP

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
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for tgsyl is the netlib-compatible backend.
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
template< typename Trans >
inline std::ptrdiff_t tgsyl( Trans, const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n, const float* a,
        const fortran_int_t lda, const float* b, const fortran_int_t ldb,
        float* c, const fortran_int_t ldc, const float* d,
        const fortran_int_t ldd, const float* e, const fortran_int_t lde,
        float* f, const fortran_int_t ldf, float& scale, float& dif,
        float* work, const fortran_int_t lwork, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_STGSYL( &lapack_option< Trans >::value, &ijob, &m, &n, a, &lda, b,
            &ldb, c, &ldc, d, &ldd, e, &lde, f, &ldf, &scale, &dif, work,
            &lwork, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Trans >
inline std::ptrdiff_t tgsyl( Trans, const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n, const double* a,
        const fortran_int_t lda, const double* b, const fortran_int_t ldb,
        double* c, const fortran_int_t ldc, const double* d,
        const fortran_int_t ldd, const double* e, const fortran_int_t lde,
        double* f, const fortran_int_t ldf, double& scale, double& dif,
        double* work, const fortran_int_t lwork, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DTGSYL( &lapack_option< Trans >::value, &ijob, &m, &n, a, &lda, b,
            &ldb, c, &ldc, d, &ldd, e, &lde, f, &ldf, &scale, &dif, work,
            &lwork, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Trans >
inline std::ptrdiff_t tgsyl( Trans, const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const std::complex<float>* a, const fortran_int_t lda,
        const std::complex<float>* b, const fortran_int_t ldb,
        std::complex<float>* c, const fortran_int_t ldc,
        const std::complex<float>* d, const fortran_int_t ldd,
        const std::complex<float>* e, const fortran_int_t lde,
        std::complex<float>* f, const fortran_int_t ldf, float& scale,
        float& dif, std::complex<float>* work, const fortran_int_t lwork,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_CTGSYL( &lapack_option< Trans >::value, &ijob, &m, &n, a, &lda, b,
            &ldb, c, &ldc, d, &ldd, e, &lde, f, &ldf, &scale, &dif, work,
            &lwork, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Trans >
inline std::ptrdiff_t tgsyl( Trans, const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const std::complex<double>* a, const fortran_int_t lda,
        const std::complex<double>* b, const fortran_int_t ldb,
        std::complex<double>* c, const fortran_int_t ldc,
        const std::complex<double>* d, const fortran_int_t ldd,
        const std::complex<double>* e, const fortran_int_t lde,
        std::complex<double>* f, const fortran_int_t ldf, double& scale,
        double& dif, std::complex<double>* work, const fortran_int_t lwork,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_ZTGSYL( &lapack_option< Trans >::value, &ijob, &m, &n, a, &lda, b,
            &ldb, c, &ldc, d, &ldd, e, &lde, f, &ldf, &scale, &dif, work,
            &lwork, iwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tgsyl.
//
template< typename Value, typename Enable = void >
struct tgsyl_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct tgsyl_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename MatrixC,
            typename MatrixD, typename MatrixE, typename MatrixF,
            typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const fortran_int_t ijob,
            const fortran_int_t m, const fortran_int_t n,
            const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
            const MatrixE& e, MatrixF& f, real_type& scale, real_type& dif,
            detail::workspace2< WORK, IWORK > work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixC >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixC >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixF >::value) );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( m, n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work(
                $CALL_MIN_SIZE ));
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(c) == 1 || stride_minor(c) == 1 );
        BOOST_ASSERT( size_minor(d) == 1 || stride_minor(d) == 1 );
        BOOST_ASSERT( size_minor(e) == 1 || stride_minor(e) == 1 );
        BOOST_ASSERT( size_minor(f) == 1 || stride_minor(f) == 1 );
        return detail::tgsyl( trans(), ijob, m, n, begin_value(a),
                stride_major(a), begin_value(b), stride_major(b),
                begin_value(c), stride_major(c), begin_value(d),
                stride_major(d), begin_value(e), stride_major(e),
                begin_value(f), stride_major(f), scale, dif,
                begin_value(work.select(real_type())),
                size(work.select(real_type())),
                begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixC,
            typename MatrixD, typename MatrixE, typename MatrixF >
    static std::ptrdiff_t invoke( const fortran_int_t ijob,
            const fortran_int_t m, const fortran_int_t n,
            const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
            const MatrixE& e, MatrixF& f, real_type& scale, real_type& dif,
            minimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( m, n ) );
        return invoke( ijob, m, n, a, b, c, d, e, f, scale, dif,
                workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixC,
            typename MatrixD, typename MatrixE, typename MatrixF >
    static std::ptrdiff_t invoke( const fortran_int_t ijob,
            const fortran_int_t m, const fortran_int_t n,
            const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
            const MatrixE& e, MatrixF& f, real_type& scale, real_type& dif,
            optimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        real_type opt_size_work;
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( m, n ) );
        detail::tgsyl( trans(), ijob, m, n, begin_value(a),
                stride_major(a), begin_value(b), stride_major(b),
                begin_value(c), stride_major(c), begin_value(d),
                stride_major(d), begin_value(e), stride_major(e),
                begin_value(f), stride_major(f), scale, dif, &opt_size_work,
                -1, begin_value(tmp_iwork) );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( ijob, m, n, a, b, c, d, e, f, scale, dif,
                workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t m,
            const std::ptrdiff_t n ) {
        return m+n+6;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct tgsyl_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB, typename MatrixC,
            typename MatrixD, typename MatrixE, typename MatrixF,
            typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const fortran_int_t ijob,
            const fortran_int_t m, const fortran_int_t n,
            const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
            const MatrixE& e, MatrixF& f, real_type& scale, real_type& dif,
            detail::workspace2< WORK, IWORK > work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixC >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixA >::type >::type,
                typename remove_const< typename value<
                MatrixF >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixC >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixF >::value) );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( m, n ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work(
                $CALL_MIN_SIZE ));
        BOOST_ASSERT( size_minor(a) == 1 || stride_minor(a) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(c) == 1 || stride_minor(c) == 1 );
        BOOST_ASSERT( size_minor(d) == 1 || stride_minor(d) == 1 );
        BOOST_ASSERT( size_minor(e) == 1 || stride_minor(e) == 1 );
        BOOST_ASSERT( size_minor(f) == 1 || stride_minor(f) == 1 );
        return detail::tgsyl( trans(), ijob, m, n, begin_value(a),
                stride_major(a), begin_value(b), stride_major(b),
                begin_value(c), stride_major(c), begin_value(d),
                stride_major(d), begin_value(e), stride_major(e),
                begin_value(f), stride_major(f), scale, dif,
                begin_value(work.select(value_type())),
                size(work.select(value_type())),
                begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixC,
            typename MatrixD, typename MatrixE, typename MatrixF >
    static std::ptrdiff_t invoke( const fortran_int_t ijob,
            const fortran_int_t m, const fortran_int_t n,
            const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
            const MatrixE& e, MatrixF& f, real_type& scale, real_type& dif,
            minimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( m, n ) );
        return invoke( ijob, m, n, a, b, c, d, e, f, scale, dif,
                workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename MatrixB, typename MatrixC,
            typename MatrixD, typename MatrixE, typename MatrixF >
    static std::ptrdiff_t invoke( const fortran_int_t ijob,
            const fortran_int_t m, const fortran_int_t n,
            const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
            const MatrixE& e, MatrixF& f, real_type& scale, real_type& dif,
            optimal_workspace work ) {
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        value_type opt_size_work;
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( m, n ) );
        detail::tgsyl( trans(), ijob, m, n, begin_value(a),
                stride_major(a), begin_value(b), stride_major(b),
                begin_value(c), stride_major(c), begin_value(d),
                stride_major(d), begin_value(e), stride_major(e),
                begin_value(f), stride_major(f), scale, dif, &opt_size_work,
                -1, begin_value(tmp_iwork) );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( ijob, m, n, a, b, c, d, e, f, scale, dif,
                workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t m,
            const std::ptrdiff_t n ) {
        return m+n+2;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the tgsyl_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tgsyl. Its overload differs for
// * MatrixC&
// * MatrixF&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF,
        typename Workspace >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
        const MatrixE& e, MatrixF& f, typename remove_imaginary<
        typename value< MatrixA >::type >::type& scale,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& dif, Workspace work ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, work );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * MatrixC&
// * MatrixF&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
        const MatrixE& e, MatrixF& f, typename remove_imaginary<
        typename value< MatrixA >::type >::type& scale,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& dif ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, optimal_workspace() );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * const MatrixC&
// * MatrixF&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF,
        typename Workspace >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, const MatrixC& c,
        const MatrixD& d, const MatrixE& e, MatrixF& f,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& scale, typename remove_imaginary<
        typename value< MatrixA >::type >::type& dif, Workspace work ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, work );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * const MatrixC&
// * MatrixF&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, const MatrixC& c,
        const MatrixD& d, const MatrixE& e, MatrixF& f,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& scale, typename remove_imaginary<
        typename value< MatrixA >::type >::type& dif ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, optimal_workspace() );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * MatrixC&
// * const MatrixF&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF,
        typename Workspace >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
        const MatrixE& e, const MatrixF& f, typename remove_imaginary<
        typename value< MatrixA >::type >::type& scale,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& dif, Workspace work ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, work );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * MatrixC&
// * const MatrixF&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, MatrixC& c, const MatrixD& d,
        const MatrixE& e, const MatrixF& f, typename remove_imaginary<
        typename value< MatrixA >::type >::type& scale,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& dif ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, optimal_workspace() );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * const MatrixC&
// * const MatrixF&
// * User-defined workspace
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF,
        typename Workspace >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, const MatrixC& c,
        const MatrixD& d, const MatrixE& e, const MatrixF& f,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& scale, typename remove_imaginary<
        typename value< MatrixA >::type >::type& dif, Workspace work ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, work );
}

//
// Overloaded function for tgsyl. Its overload differs for
// * const MatrixC&
// * const MatrixF&
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename MatrixB, typename MatrixC,
        typename MatrixD, typename MatrixE, typename MatrixF >
inline std::ptrdiff_t tgsyl( const fortran_int_t ijob,
        const fortran_int_t m, const fortran_int_t n,
        const MatrixA& a, const MatrixB& b, const MatrixC& c,
        const MatrixD& d, const MatrixE& e, const MatrixF& f,
        typename remove_imaginary< typename value<
        MatrixA >::type >::type& scale, typename remove_imaginary<
        typename value< MatrixA >::type >::type& dif ) {
    return tgsyl_impl< typename value< MatrixA >::type >::invoke( ijob,
            m, n, a, b, c, d, e, f, scale, dif, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

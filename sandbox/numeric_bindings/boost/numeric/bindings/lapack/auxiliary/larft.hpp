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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LARFT_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LARFT_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for larft is the netlib-compatible backend.
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
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k, float* v,
        const fortran_int_t ldv, const float* tau, float* t,
        const fortran_int_t ldt ) {
    fortran_int_t info(0);
    LAPACK_SLARFT( &direct, &storev, &n, &k, v, &ldv, tau, t, &ldt );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k, double* v,
        const fortran_int_t ldv, const double* tau, double* t,
        const fortran_int_t ldt ) {
    fortran_int_t info(0);
    LAPACK_DLARFT( &direct, &storev, &n, &k, v, &ldv, tau, t, &ldt );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k, std::complex<float>* v,
        const fortran_int_t ldv, const std::complex<float>* tau,
        std::complex<float>* t, const fortran_int_t ldt ) {
    fortran_int_t info(0);
    LAPACK_CLARFT( &direct, &storev, &n, &k, v, &ldv, tau, t, &ldt );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k, std::complex<double>* v,
        const fortran_int_t ldv, const std::complex<double>* tau,
        std::complex<double>* t, const fortran_int_t ldt ) {
    fortran_int_t info(0);
    LAPACK_ZLARFT( &direct, &storev, &n, &k, v, &ldv, tau, t, &ldt );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to larft.
//
template< typename Value >
struct larft_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixV, typename VectorTAU, typename MatrixT >
    static std::ptrdiff_t invoke( const char direct, const char storev,
            const fortran_int_t n, const fortran_int_t k, MatrixV& v,
            const VectorTAU& tau, MatrixT& t ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixV >::type >::type,
                typename remove_const< typename value<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixV >::type >::type,
                typename remove_const< typename value<
                MatrixT >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixV >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixT >::value) );
        BOOST_ASSERT( direct == 'F' || direct == 'B' );
        BOOST_ASSERT( k >= 1 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(tau) >= k );
        BOOST_ASSERT( size_minor(t) == 1 || stride_minor(t) == 1 );
        BOOST_ASSERT( size_minor(v) == 1 || stride_minor(v) == 1 );
        BOOST_ASSERT( storev == 'C' || storev == 'R' );
        BOOST_ASSERT( stride_major(t) >= k );
        return detail::larft( direct, storev, n, k, begin_value(v),
                stride_major(v), begin_value(tau), begin_value(t),
                stride_major(t) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the larft_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for larft. Its overload differs for
// * MatrixV&
// * MatrixT&
//
template< typename MatrixV, typename VectorTAU, typename MatrixT >
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k, MatrixV& v,
        const VectorTAU& tau, MatrixT& t ) {
    return larft_impl< typename value< MatrixV >::type >::invoke( direct,
            storev, n, k, v, tau, t );
}

//
// Overloaded function for larft. Its overload differs for
// * const MatrixV&
// * MatrixT&
//
template< typename MatrixV, typename VectorTAU, typename MatrixT >
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k,
        const MatrixV& v, const VectorTAU& tau, MatrixT& t ) {
    return larft_impl< typename value< MatrixV >::type >::invoke( direct,
            storev, n, k, v, tau, t );
}

//
// Overloaded function for larft. Its overload differs for
// * MatrixV&
// * const MatrixT&
//
template< typename MatrixV, typename VectorTAU, typename MatrixT >
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k, MatrixV& v,
        const VectorTAU& tau, const MatrixT& t ) {
    return larft_impl< typename value< MatrixV >::type >::invoke( direct,
            storev, n, k, v, tau, t );
}

//
// Overloaded function for larft. Its overload differs for
// * const MatrixV&
// * const MatrixT&
//
template< typename MatrixV, typename VectorTAU, typename MatrixT >
inline std::ptrdiff_t larft( const char direct, const char storev,
        const fortran_int_t n, const fortran_int_t k,
        const MatrixV& v, const VectorTAU& tau, const MatrixT& t ) {
    return larft_impl< typename value< MatrixV >::type >::invoke( direct,
            storev, n, k, v, tau, t );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGBAK_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GGBAK_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for ggbak is the netlib-compatible backend.
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
inline std::ptrdiff_t ggbak( char job, char side, fortran_int_t n,
        fortran_int_t ilo, fortran_int_t ihi, const float* lscale,
        const float* rscale, fortran_int_t m, float* v, fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_SGGBAK( &job, &side, &n, &ilo, &ihi, lscale, rscale, &m, v, &ldv,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t ggbak( char job, char side, fortran_int_t n,
        fortran_int_t ilo, fortran_int_t ihi, const double* lscale,
        const double* rscale, fortran_int_t m, double* v, fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_DGGBAK( &job, &side, &n, &ilo, &ihi, lscale, rscale, &m, v, &ldv,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t ggbak( char job, char side, fortran_int_t n,
        fortran_int_t ilo, fortran_int_t ihi, const float* lscale,
        const float* rscale, fortran_int_t m, std::complex<float>* v,
        fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_CGGBAK( &job, &side, &n, &ilo, &ihi, lscale, rscale, &m, v, &ldv,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t ggbak( char job, char side, fortran_int_t n,
        fortran_int_t ilo, fortran_int_t ihi, const double* lscale,
        const double* rscale, fortran_int_t m, std::complex<double>* v,
        fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_ZGGBAK( &job, &side, &n, &ilo, &ihi, lscale, rscale, &m, v, &ldv,
            &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to ggbak.
//
template< typename Value, typename Enable = void >
struct ggbak_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct ggbak_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorLSCALE, typename VectorRSCALE, typename MatrixV >
    static std::ptrdiff_t invoke( const char job, const char side,
            const fortran_int_t ilo, const fortran_int_t ihi,
            const VectorLSCALE& lscale, const VectorRSCALE& rscale,
            MatrixV& v ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorLSCALE >::type >::type,
                typename remove_const< typename value<
                VectorRSCALE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorLSCALE >::type >::type,
                typename remove_const< typename value<
                MatrixV >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixV >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( side == 'R' || side == 'L' );
        BOOST_ASSERT( size(lscale) >= size_row(v) );
        BOOST_ASSERT( size(rscale) >= size_row(v) );
        BOOST_ASSERT( size_column(v) >= 0 );
        BOOST_ASSERT( size_minor(v) == 1 || stride_minor(v) == 1 );
        BOOST_ASSERT( size_row(v) >= 0 );
        BOOST_ASSERT( stride_major(v) >= std::max< std::ptrdiff_t >(1,
                size_row(v)) );
        return detail::ggbak( job, side, size_row(v), ilo, ihi,
                begin_value(lscale), begin_value(rscale), size_column(v),
                begin_value(v), stride_major(v) );
    }

};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct ggbak_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorLSCALE, typename VectorRSCALE, typename MatrixV >
    static std::ptrdiff_t invoke( const char job, const char side,
            const fortran_int_t ilo, const fortran_int_t ihi,
            const VectorLSCALE& lscale, const VectorRSCALE& rscale,
            MatrixV& v ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorLSCALE >::type >::type,
                typename remove_const< typename value<
                VectorRSCALE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixV >::value) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( side == 'R' || side == 'L' );
        BOOST_ASSERT( size(lscale) >= size_row(v) );
        BOOST_ASSERT( size(rscale) >= size_row(v) );
        BOOST_ASSERT( size_column(v) >= 0 );
        BOOST_ASSERT( size_minor(v) == 1 || stride_minor(v) == 1 );
        BOOST_ASSERT( size_row(v) >= 0 );
        BOOST_ASSERT( stride_major(v) >= std::max< std::ptrdiff_t >(1,
                size_row(v)) );
        return detail::ggbak( job, side, size_row(v), ilo, ihi,
                begin_value(lscale), begin_value(rscale), size_column(v),
                begin_value(v), stride_major(v) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the ggbak_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for ggbak. Its overload differs for
// * MatrixV&
//
template< typename VectorLSCALE, typename VectorRSCALE, typename MatrixV >
inline std::ptrdiff_t ggbak( const char job, const char side,
        const fortran_int_t ilo, const fortran_int_t ihi,
        const VectorLSCALE& lscale, const VectorRSCALE& rscale, MatrixV& v ) {
    return ggbak_impl< typename value< MatrixV >::type >::invoke( job,
            side, ilo, ihi, lscale, rscale, v );
}

//
// Overloaded function for ggbak. Its overload differs for
// * const MatrixV&
//
template< typename VectorLSCALE, typename VectorRSCALE, typename MatrixV >
inline std::ptrdiff_t ggbak( const char job, const char side,
        const fortran_int_t ilo, const fortran_int_t ihi,
        const VectorLSCALE& lscale, const VectorRSCALE& rscale,
        const MatrixV& v ) {
    return ggbak_impl< typename value< MatrixV >::type >::invoke( job,
            side, ilo, ihi, lscale, rscale, v );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

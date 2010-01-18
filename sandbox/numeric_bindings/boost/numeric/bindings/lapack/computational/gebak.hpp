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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBAK_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEBAK_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for gebak is the netlib-compatible backend.
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
inline std::ptrdiff_t gebak( const char job, const char side,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, const float* scale, const fortran_int_t m,
        float* v, const fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_SGEBAK( &job, &side, &n, &ilo, &ihi, scale, &m, v, &ldv, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gebak( const char job, const char side,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, const double* scale, const fortran_int_t m,
        double* v, const fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_DGEBAK( &job, &side, &n, &ilo, &ihi, scale, &m, v, &ldv, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t gebak( const char job, const char side,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, const float* scale, const fortran_int_t m,
        std::complex<float>* v, const fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_CGEBAK( &job, &side, &n, &ilo, &ihi, scale, &m, v, &ldv, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t gebak( const char job, const char side,
        const fortran_int_t n, const fortran_int_t ilo,
        const fortran_int_t ihi, const double* scale, const fortran_int_t m,
        std::complex<double>* v, const fortran_int_t ldv ) {
    fortran_int_t info(0);
    LAPACK_ZGEBAK( &job, &side, &n, &ilo, &ihi, scale, &m, v, &ldv, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gebak.
//
template< typename Value, typename Enable = void >
struct gebak_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct gebak_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorSCALE, typename MatrixV >
    static std::ptrdiff_t invoke( const char job, const char side,
            const fortran_int_t ilo, const fortran_int_t ihi,
            const VectorSCALE& scale, MatrixV& v ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorSCALE >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixV >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixV >::value) );
        BOOST_ASSERT( bindings::size(scale) >= bindings::size_row(v) );
        BOOST_ASSERT( bindings::size_column(v) >= 0 );
        BOOST_ASSERT( bindings::size_minor(v) == 1 ||
                bindings::stride_minor(v) == 1 );
        BOOST_ASSERT( bindings::size_row(v) >= 0 );
        BOOST_ASSERT( bindings::stride_major(v) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(v)) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( side == 'R' || side == 'L' );
        return detail::gebak( job, side, bindings::size_row(v), ilo, ihi,
                bindings::begin_value(scale), bindings::size_column(v),
                bindings::begin_value(v), bindings::stride_major(v) );
    }

};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct gebak_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorSCALE, typename MatrixV >
    static std::ptrdiff_t invoke( const char job, const char side,
            const fortran_int_t ilo, const fortran_int_t ihi,
            const VectorSCALE& scale, MatrixV& v ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixV >::value) );
        BOOST_ASSERT( bindings::size(scale) >= bindings::size_row(v) );
        BOOST_ASSERT( bindings::size_column(v) >= 0 );
        BOOST_ASSERT( bindings::size_minor(v) == 1 ||
                bindings::stride_minor(v) == 1 );
        BOOST_ASSERT( bindings::size_row(v) >= 0 );
        BOOST_ASSERT( bindings::stride_major(v) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(v)) );
        BOOST_ASSERT( job == 'N' || job == 'P' || job == 'S' || job == 'B' );
        BOOST_ASSERT( side == 'R' || side == 'L' );
        return detail::gebak( job, side, bindings::size_row(v), ilo, ihi,
                bindings::begin_value(scale), bindings::size_column(v),
                bindings::begin_value(v), bindings::stride_major(v) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gebak_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gebak. Its overload differs for
// * MatrixV&
//
template< typename VectorSCALE, typename MatrixV >
inline std::ptrdiff_t gebak( const char job, const char side,
        const fortran_int_t ilo, const fortran_int_t ihi,
        const VectorSCALE& scale, MatrixV& v ) {
    return gebak_impl< typename bindings::value_type<
            MatrixV >::type >::invoke( job, side, ilo, ihi, scale, v );
}

//
// Overloaded function for gebak. Its overload differs for
// * const MatrixV&
//
template< typename VectorSCALE, typename MatrixV >
inline std::ptrdiff_t gebak( const char job, const char side,
        const fortran_int_t ilo, const fortran_int_t ihi,
        const VectorSCALE& scale, const MatrixV& v ) {
    return gebak_impl< typename bindings::value_type<
            MatrixV >::type >::invoke( job, side, ilo, ihi, scale, v );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

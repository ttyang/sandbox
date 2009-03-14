//
// Copyright (c) 2003--2009
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HSEQR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HSEQR_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void hseqr( char const job, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, float* h,
            integer_t const ldh, float* wr, float* wi, float* z,
            integer_t const ldz, float* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_SHSEQR( &job, &compz, &n, &ilo, &ihi, h, &ldh, wr, wi, z, &ldz,
                work, &lwork, &info );
    }
    inline void hseqr( char const job, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, double* h,
            integer_t const ldh, double* wr, double* wi, double* z,
            integer_t const ldz, double* work, integer_t const lwork,
            integer_t& info ) {
        LAPACK_DHSEQR( &job, &compz, &n, &ilo, &ihi, h, &ldh, wr, wi, z, &ldz,
                work, &lwork, &info );
    }
    inline void hseqr( char const job, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, traits::complex_f* h,
            integer_t const ldh, traits::complex_f* w, traits::complex_f* z,
            integer_t const ldz, traits::complex_f* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_CHSEQR( &job, &compz, &n, &ilo, &ihi, traits::complex_ptr(h),
                &ldh, traits::complex_ptr(w), traits::complex_ptr(z), &ldz,
                traits::complex_ptr(work), &lwork, &info );
    }
    inline void hseqr( char const job, char const compz, integer_t const n,
            integer_t const ilo, integer_t const ihi, traits::complex_d* h,
            integer_t const ldh, traits::complex_d* w, traits::complex_d* z,
            integer_t const ldz, traits::complex_d* work,
            integer_t const lwork, integer_t& info ) {
        LAPACK_ZHSEQR( &job, &compz, &n, &ilo, &ihi, traits::complex_ptr(h),
                &ldh, traits::complex_ptr(w), traits::complex_ptr(z), &ldz,
                traits::complex_ptr(work), &lwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct hseqr_impl{};

// real specialization
template< typename ValueType >
struct hseqr_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixH, typename VectorWR, typename VectorWI,
            typename MatrixZ, typename WORK >
    static void compute( char const job, char const compz,
            integer_t const ilo, integer_t const ihi, MatrixH& h,
            VectorWR& wr, VectorWI& wi, MatrixZ& z, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixH >::value_type, typename traits::vector_traits<
                VectorWR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixH >::value_type, typename traits::vector_traits<
                VectorWI >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixH >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( job == 'E' || job == 'S' );
        BOOST_ASSERT( compz == 'N' || compz == 'I' || compz == 'V' );
        BOOST_ASSERT( traits::vector_size(wr) >=
                traits::matrix_num_columns(h) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::hseqr( job, compz, traits::matrix_num_columns(h), ilo, ihi,
                traits::matrix_storage(h), traits::leading_dimension(h),
                traits::vector_storage(wr), traits::vector_storage(wi),
                traits::matrix_storage(z), traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixH, typename VectorWR, typename VectorWI,
            typename MatrixZ >
    static void compute( char const job, char const compz,
            integer_t const ilo, integer_t const ihi, MatrixH& h,
            VectorWR& wr, VectorWI& wi, MatrixZ& z, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( job, compz, ilo, ihi, h, wr, wi, z, info,
                workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixH, typename VectorWR, typename VectorWI,
            typename MatrixZ >
    static void compute( char const job, char const compz,
            integer_t const ilo, integer_t const ihi, MatrixH& h,
            VectorWR& wr, VectorWI& wi, MatrixZ& z, integer_t& info,
            optimal_workspace work ) {
        compute( job, compz, ilo, ihi, h, wr, wi, z, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

// complex specialization
template< typename ValueType >
struct hseqr_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixH, typename VectorW, typename MatrixZ,
            typename WORK >
    static void compute( char const job, char const compz,
            integer_t const ilo, integer_t const ihi, MatrixH& h, VectorW& w,
            MatrixZ& z, integer_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixH >::value_type, typename traits::vector_traits<
                VectorW >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixH >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( job == 'E' || job == 'S' );
        BOOST_ASSERT( compz == 'N' || compz == 'I' || compz == 'V' );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        detail::hseqr( job, compz, traits::matrix_num_columns(h), ilo, ihi,
                traits::matrix_storage(h), traits::leading_dimension(h),
                traits::vector_storage(w), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(value_type())),
                traits::vector_size(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixH, typename VectorW, typename MatrixZ >
    static void compute( char const job, char const compz,
            integer_t const ilo, integer_t const ihi, MatrixH& h, VectorW& w,
            MatrixZ& z, integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        compute( job, compz, ilo, ihi, h, w, z, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixH, typename VectorW, typename MatrixZ >
    static void compute( char const job, char const compz,
            integer_t const ilo, integer_t const ihi, MatrixH& h, VectorW& w,
            MatrixZ& z, integer_t& info, optimal_workspace work ) {
        compute( job, compz, ilo, ihi, h, w, z, info, minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call hseqr
template< typename MatrixH, typename VectorWR, typename VectorWI,
        typename MatrixZ, typename Workspace >
inline integer_t hseqr( char const job, char const compz,
        integer_t const ilo, integer_t const ihi, MatrixH& h, VectorWR& wr,
        VectorWI& wi, MatrixZ& z, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixH >::value_type value_type;
    integer_t info(0);
    hseqr_impl< value_type >::compute( job, compz, ilo, ihi, h, wr, wi,
            z, info, work );
    return info;
}
// template function to call hseqr
template< typename MatrixH, typename VectorW, typename MatrixZ,
        typename Workspace >
inline integer_t hseqr( char const job, char const compz,
        integer_t const ilo, integer_t const ihi, MatrixH& h, VectorW& w,
        MatrixZ& z, Workspace work = optimal_workspace() ) {
    typedef typename traits::matrix_traits< MatrixH >::value_type value_type;
    integer_t info(0);
    hseqr_impl< value_type >::compute( job, compz, ilo, ihi, h, w, z,
            info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

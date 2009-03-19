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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRSNA_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRSNA_HPP

#include <boost/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/keywords.hpp>
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
    inline void trsna( char const job, char const howmny, logical_t* select,
            integer_t const n, float* t, integer_t const ldt, float* vl,
            integer_t const ldvl, float* vr, integer_t const ldvr, float* s,
            float* sep, integer_t const mm, integer_t& m, float* work,
            integer_t const ldwork, integer_t* iwork, integer_t& info ) {
        LAPACK_STRSNA( &job, &howmny, select, &n, t, &ldt, vl, &ldvl, vr,
                &ldvr, s, sep, &mm, &m, work, &ldwork, iwork, &info );
    }
    inline void trsna( char const job, char const howmny, logical_t* select,
            integer_t const n, double* t, integer_t const ldt, double* vl,
            integer_t const ldvl, double* vr, integer_t const ldvr, double* s,
            double* sep, integer_t const mm, integer_t& m, double* work,
            integer_t const ldwork, integer_t* iwork, integer_t& info ) {
        LAPACK_DTRSNA( &job, &howmny, select, &n, t, &ldt, vl, &ldvl, vr,
                &ldvr, s, sep, &mm, &m, work, &ldwork, iwork, &info );
    }
    inline void trsna( char const job, char const howmny, logical_t* select,
            integer_t const n, traits::complex_f* t, integer_t const ldt,
            traits::complex_f* vl, integer_t const ldvl,
            traits::complex_f* vr, integer_t const ldvr, float* s, float* sep,
            integer_t const mm, integer_t& m, traits::complex_f* work,
            integer_t const ldwork, float* rwork, integer_t& info ) {
        LAPACK_CTRSNA( &job, &howmny, select, &n, traits::complex_ptr(t),
                &ldt, traits::complex_ptr(vl), &ldvl, traits::complex_ptr(vr),
                &ldvr, s, sep, &mm, &m, traits::complex_ptr(work), &ldwork,
                rwork, &info );
    }
    inline void trsna( char const job, char const howmny, logical_t* select,
            integer_t const n, traits::complex_d* t, integer_t const ldt,
            traits::complex_d* vl, integer_t const ldvl,
            traits::complex_d* vr, integer_t const ldvr, double* s,
            double* sep, integer_t const mm, integer_t& m,
            traits::complex_d* work, integer_t const ldwork, double* rwork,
            integer_t& info ) {
        LAPACK_ZTRSNA( &job, &howmny, select, &n, traits::complex_ptr(t),
                &ldt, traits::complex_ptr(vl), &ldvl, traits::complex_ptr(vr),
                &ldvr, s, sep, &mm, &m, traits::complex_ptr(work), &ldwork,
                rwork, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct trsna_impl{};

// real specialization
template< typename ValueType >
struct trsna_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef typename mpl::vector<  > valid_keywords;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP,
            typename WORK, typename IWORK >
    static void compute( char const job, char const howmny,
            VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
            VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
            integer_t& info, detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVL >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::vector_traits<
                VectorSEP >::value_type >::value) );
        BOOST_ASSERT( job == 'E' || job == 'V' || job == 'B' );
        BOOST_ASSERT( howmny == 'A' || howmny == 'S' );
        BOOST_ASSERT( traits::matrix_num_columns(t) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(t) >= std::max(1,
                traits::matrix_num_columns(t)) );
        BOOST_ASSERT( mm >= m );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( $CALL_MIN_SIZE ));
        detail::trsna( job, howmny, traits::vector_storage(select),
                traits::matrix_num_columns(t), traits::matrix_storage(t),
                traits::leading_dimension(t), traits::matrix_storage(vl),
                traits::leading_dimension(vl), traits::matrix_storage(vr),
                traits::leading_dimension(vr), traits::vector_storage(s),
                traits::vector_storage(sep), mm, m,
                traits::matrix_storage(work), traits::leading_dimension(work),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP >
    static void compute( char const job, char const howmny,
            VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
            VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                $CALL_MIN_SIZE ) );
        compute( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
                workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP >
    static void compute( char const job, char const howmny,
            VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
            VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
            integer_t& info, optimal_workspace work ) {
        compute( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    static integer_t min_size_iwork( $ARGUMENTS ) {
        $MIN_SIZE
    }
};

// complex specialization
template< typename ValueType >
struct trsna_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef typename mpl::vector<  > valid_keywords;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP,
            typename WORK, typename RWORK >
    static void compute( char const job, char const howmny,
            VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
            VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
            integer_t& info, detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorS >::value_type, typename traits::vector_traits<
                VectorSEP >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVL >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVR >::value_type >::value) );
        BOOST_ASSERT( job == 'E' || job == 'V' || job == 'B' );
        BOOST_ASSERT( howmny == 'A' || howmny == 'S' );
        BOOST_ASSERT( traits::matrix_num_columns(t) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(t) >= std::max(1,
                traits::matrix_num_columns(t)) );
        BOOST_ASSERT( mm >= m );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( $CALL_MIN_SIZE ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( $CALL_MIN_SIZE ));
        detail::trsna( job, howmny, traits::vector_storage(select),
                traits::matrix_num_columns(t), traits::matrix_storage(t),
                traits::leading_dimension(t), traits::matrix_storage(vl),
                traits::leading_dimension(vl), traits::matrix_storage(vr),
                traits::leading_dimension(vr), traits::vector_storage(s),
                traits::vector_storage(sep), mm, m,
                traits::matrix_storage(work), traits::leading_dimension(work),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP >
    static void compute( char const job, char const howmny,
            VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
            VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                $CALL_MIN_SIZE ) );
        compute( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
                workspace( tmp_work, tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP >
    static void compute( char const job, char const howmny,
            VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
            VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
            integer_t& info, optimal_workspace work ) {
        compute( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }

    static integer_t min_size_rwork( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


// template function to call trsna
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename VectorS, typename VectorSEP,
        typename Workspace >
inline integer_t trsna( char const job, char const howmny,
        VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m,
        Workspace work ) {
    typedef typename traits::vector_traits<
            VectorSELECT >::value_type value_type;
    integer_t info(0);
    trsna_impl< value_type >::compute( job, howmny, select, t, vl, vr, s,
            sep, mm, m, info, work );
    return info;
}

// template function to call trsna, default workspace type
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename VectorS, typename VectorSEP >
inline integer_t trsna( char const job, char const howmny,
        VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        VectorS& s, VectorSEP& sep, integer_t const mm, integer_t& m ) {
    typedef typename traits::vector_traits<
            VectorSELECT >::value_type value_type;
    integer_t info(0);
    trsna_impl< value_type >::compute( job, howmny, select, t, vl, vr, s,
            sep, mm, m, info, optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

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
#include <boost/mpl/bool.hpp>
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

inline void trsna( const char job, const char howmny, const logical_t* select,
        const integer_t n, const float* t, const integer_t ldt,
        const float* vl, const integer_t ldvl, const float* vr,
        const integer_t ldvr, float* s, float* sep, const integer_t mm,
        integer_t& m, float* work, const integer_t ldwork, integer_t* iwork,
        integer_t& info ) {
    LAPACK_STRSNA( &job, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            s, sep, &mm, &m, work, &ldwork, iwork, &info );
}

inline void trsna( const char job, const char howmny, const logical_t* select,
        const integer_t n, const double* t, const integer_t ldt,
        const double* vl, const integer_t ldvl, const double* vr,
        const integer_t ldvr, double* s, double* sep, const integer_t mm,
        integer_t& m, double* work, const integer_t ldwork, integer_t* iwork,
        integer_t& info ) {
    LAPACK_DTRSNA( &job, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            s, sep, &mm, &m, work, &ldwork, iwork, &info );
}

inline void trsna( const char job, const char howmny, const logical_t* select,
        const integer_t n, const traits::complex_f* t, const integer_t ldt,
        const traits::complex_f* vl, const integer_t ldvl,
        const traits::complex_f* vr, const integer_t ldvr, float* s,
        float* sep, const integer_t mm, integer_t& m, traits::complex_f* work,
        const integer_t ldwork, float* rwork, integer_t& info ) {
    LAPACK_CTRSNA( &job, &howmny, select, &n, traits::complex_ptr(t), &ldt,
            traits::complex_ptr(vl), &ldvl, traits::complex_ptr(vr), &ldvr, s,
            sep, &mm, &m, traits::complex_ptr(work), &ldwork, rwork, &info );
}

inline void trsna( const char job, const char howmny, const logical_t* select,
        const integer_t n, const traits::complex_d* t, const integer_t ldt,
        const traits::complex_d* vl, const integer_t ldvl,
        const traits::complex_d* vr, const integer_t ldvr, double* s,
        double* sep, const integer_t mm, integer_t& m,
        traits::complex_d* work, const integer_t ldwork, double* rwork,
        integer_t& info ) {
    LAPACK_ZTRSNA( &job, &howmny, select, &n, traits::complex_ptr(t), &ldt,
            traits::complex_ptr(vl), &ldvl, traits::complex_ptr(vr), &ldvr, s,
            sep, &mm, &m, traits::complex_ptr(work), &ldwork, rwork, &info );
}

} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct trsna_impl{};

// real specialization
template< typename ValueType >
struct trsna_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP,
            typename WORK, typename IWORK >
    static void invoke( const char job, const char howmny,
            const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
            const MatrixVR& vr, VectorS& s, VectorSEP& sep,
            const integer_t mm, integer_t& m, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
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
    static void invoke( const char job, const char howmny,
            const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
            const MatrixVR& vr, VectorS& s, VectorSEP& sep,
            const integer_t mm, integer_t& m, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                $CALL_MIN_SIZE ) );
        invoke( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
                workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP >
    static void invoke( const char job, const char howmny,
            const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
            const MatrixVR& vr, VectorS& s, VectorSEP& sep,
            const integer_t mm, integer_t& m, integer_t& info,
            optimal_workspace work ) {
        invoke( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
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

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP,
            typename WORK, typename RWORK >
    static void invoke( const char job, const char howmny,
            const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
            const MatrixVR& vr, VectorS& s, VectorSEP& sep,
            const integer_t mm, integer_t& m, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
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
    static void invoke( const char job, const char howmny,
            const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
            const MatrixVR& vr, VectorS& s, VectorSEP& sep,
            const integer_t mm, integer_t& m, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                $CALL_MIN_SIZE ) );
        invoke( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
                workspace( tmp_work, tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename VectorS, typename VectorSEP >
    static void invoke( const char job, const char howmny,
            const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
            const MatrixVR& vr, VectorS& s, VectorSEP& sep,
            const integer_t mm, integer_t& m, integer_t& info,
            optimal_workspace work ) {
        invoke( job, howmny, select, t, vl, vr, s, sep, mm, m, info,
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
inline integer_t trsna( const char job, const char howmny,
        const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, VectorS& s, VectorSEP& sep, const integer_t mm,
        integer_t& m, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trsna_impl< value_type >::invoke( job, howmny, select, t, vl, vr, s,
            sep, mm, m, info, work );
    return info;
}

// template function to call trsna, default workspace type
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename VectorS, typename VectorSEP >
inline integer_t trsna( const char job, const char howmny,
        const VectorSELECT& select, const MatrixT& t, const MatrixVL& vl,
        const MatrixVR& vr, VectorS& s, VectorSEP& sep, const integer_t mm,
        integer_t& m ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trsna_impl< value_type >::invoke( job, howmny, select, t, vl, vr, s,
            sep, mm, m, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TREVC_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TREVC_HPP

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

inline void trevc( const char side, const char howmny, logical_t* select,
        const integer_t n, const float* t, const integer_t ldt, float* vl,
        const integer_t ldvl, float* vr, const integer_t ldvr,
        const integer_t mm, integer_t& m, float* work, integer_t& info ) {
    LAPACK_STREVC( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            &mm, &m, work, &info );
}
inline void trevc( const char side, const char howmny, logical_t* select,
        const integer_t n, const double* t, const integer_t ldt, double* vl,
        const integer_t ldvl, double* vr, const integer_t ldvr,
        const integer_t mm, integer_t& m, double* work, integer_t& info ) {
    LAPACK_DTREVC( &side, &howmny, select, &n, t, &ldt, vl, &ldvl, vr, &ldvr,
            &mm, &m, work, &info );
}
inline void trevc( const char side, const char howmny,
        const logical_t* select, const integer_t n, traits::complex_f* t,
        const integer_t ldt, traits::complex_f* vl, const integer_t ldvl,
        traits::complex_f* vr, const integer_t ldvr, const integer_t mm,
        integer_t& m, traits::complex_f* work, float* rwork,
        integer_t& info ) {
    LAPACK_CTREVC( &side, &howmny, select, &n, traits::complex_ptr(t), &ldt,
            traits::complex_ptr(vl), &ldvl, traits::complex_ptr(vr), &ldvr,
            &mm, &m, traits::complex_ptr(work), rwork, &info );
}
inline void trevc( const char side, const char howmny,
        const logical_t* select, const integer_t n, traits::complex_d* t,
        const integer_t ldt, traits::complex_d* vl, const integer_t ldvl,
        traits::complex_d* vr, const integer_t ldvr, const integer_t mm,
        integer_t& m, traits::complex_d* work, double* rwork,
        integer_t& info ) {
    LAPACK_ZTREVC( &side, &howmny, select, &n, traits::complex_ptr(t), &ldt,
            traits::complex_ptr(vl), &ldvl, traits::complex_ptr(vr), &ldvr,
            &mm, &m, traits::complex_ptr(work), rwork, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType, typename Enable = void >
struct trevc_impl{};

// real specialization
template< typename ValueType >
struct trevc_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename WORK >
    static void invoke( const char side, const char howmny,
            VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const integer_t mm, integer_t& m, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVL >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVR >::value_type >::value) );
        BOOST_ASSERT( side == 'R' || side == 'L' || side == 'B' );
        BOOST_ASSERT( howmny == 'A' || howmny == 'B' || howmny == 'S' );
        BOOST_ASSERT( traits::matrix_num_columns(t) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(t) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(t)) );
        BOOST_ASSERT( mm >= m );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_columns(t) ));
        detail::trevc( side, howmny, traits::vector_storage(select),
                traits::matrix_num_columns(t), traits::matrix_storage(t),
                traits::leading_dimension(t), traits::matrix_storage(vl),
                traits::leading_dimension(vl), traits::matrix_storage(vr),
                traits::leading_dimension(vr), mm, m,
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static void invoke( const char side, const char howmny,
            VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const integer_t mm, integer_t& m, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(t) ) );
        invoke( side, howmny, select, t, vl, vr, mm, m, info,
                workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static void invoke( const char side, const char howmny,
            VectorSELECT& select, const MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const integer_t mm, integer_t& m, integer_t& info,
            optimal_workspace work ) {
        invoke( side, howmny, select, t, vl, vr, mm, m, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 3*n;
    }
};

// complex specialization
template< typename ValueType >
struct trevc_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR, typename WORK, typename RWORK >
    static void invoke( const char side, const char howmny,
            const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const integer_t mm, integer_t& m, integer_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVL >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixT >::value_type, typename traits::matrix_traits<
                MatrixVR >::value_type >::value) );
        BOOST_ASSERT( side == 'R' || side == 'L' || side == 'B' );
        BOOST_ASSERT( howmny == 'A' || howmny == 'B' || howmny == 'S' );
        BOOST_ASSERT( traits::matrix_num_columns(t) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(t) >= std::max<
                std::ptrdiff_t >(1,traits::matrix_num_columns(t)) );
        BOOST_ASSERT( mm >= m );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(t) ));
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_rwork( traits::matrix_num_columns(t) ));
        detail::trevc( side, howmny, traits::vector_storage(select),
                traits::matrix_num_columns(t), traits::matrix_storage(t),
                traits::leading_dimension(t), traits::matrix_storage(vl),
                traits::leading_dimension(vl), traits::matrix_storage(vr),
                traits::leading_dimension(vr), mm, m,
                traits::vector_storage(work.select(value_type())),
                traits::vector_storage(work.select(real_type())), info );
    }

    // minimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static void invoke( const char side, const char howmny,
            const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const integer_t mm, integer_t& m, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(t) ) );
        traits::detail::array< real_type > tmp_rwork( min_size_rwork(
                traits::matrix_num_columns(t) ) );
        invoke( side, howmny, select, t, vl, vr, mm, m, info,
                workspace( tmp_work, tmp_rwork ) );
    }

    // optimal workspace specialization
    template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
            typename MatrixVR >
    static void invoke( const char side, const char howmny,
            const VectorSELECT& select, MatrixT& t, MatrixVL& vl,
            MatrixVR& vr, const integer_t mm, integer_t& m, integer_t& info,
            optimal_workspace work ) {
        invoke( side, howmny, select, t, vl, vr, mm, m, info,
                minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t n ) {
        return 2*n;
    }

    static integer_t min_size_rwork( const integer_t n ) {
        return n;
    }
};


// template function to call trevc
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline integer_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const integer_t mm, integer_t& m, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trevc_impl< value_type >::invoke( side, howmny, select, t, vl, vr,
            mm, m, info, work );
    return info;
}

// template function to call trevc, default workspace type
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline integer_t trevc( const char side, const char howmny,
        VectorSELECT& select, const MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const integer_t mm, integer_t& m ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trevc_impl< value_type >::invoke( side, howmny, select, t, vl, vr,
            mm, m, info, optimal_workspace() );
    return info;
}
// template function to call trevc
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR, typename Workspace >
inline integer_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const integer_t mm, integer_t& m, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trevc_impl< value_type >::invoke( side, howmny, select, t, vl, vr,
            mm, m, info, work );
    return info;
}

// template function to call trevc, default workspace type
template< typename VectorSELECT, typename MatrixT, typename MatrixVL,
        typename MatrixVR >
inline integer_t trevc( const char side, const char howmny,
        const VectorSELECT& select, MatrixT& t, MatrixVL& vl, MatrixVR& vr,
        const integer_t mm, integer_t& m ) {
    typedef typename traits::matrix_traits< MatrixT >::value_type value_type;
    integer_t info(0);
    trevc_impl< value_type >::invoke( side, howmny, select, t, vl, vr,
            mm, m, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

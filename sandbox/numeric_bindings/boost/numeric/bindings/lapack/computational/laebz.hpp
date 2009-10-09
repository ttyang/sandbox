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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LAEBZ_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_LAEBZ_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {

inline void laebz( const integer_t ijob, const integer_t nitmax,
        const integer_t n, const integer_t mmax, const integer_t minp,
        const integer_t nbmin, const float abstol, const float reltol,
        const float pivmin, const float* d, const float* e, const float* e2,
        integer_t* nval, float* ab, float* c, integer_t& mout, integer_t* nab,
        float* work, integer_t* iwork, integer_t& info ) {
    LAPACK_SLAEBZ( &ijob, &nitmax, &n, &mmax, &minp, &nbmin, &abstol, &reltol,
            &pivmin, d, e, e2, nval, ab, c, &mout, nab, work, iwork, &info );
}
inline void laebz( const integer_t ijob, const integer_t nitmax,
        const integer_t n, const integer_t mmax, const integer_t minp,
        const integer_t nbmin, const double abstol, const double reltol,
        const double pivmin, const double* d, const double* e,
        const double* e2, integer_t* nval, double* ab, double* c,
        integer_t& mout, integer_t* nab, double* work, integer_t* iwork,
        integer_t& info ) {
    LAPACK_DLAEBZ( &ijob, &nitmax, &n, &mmax, &minp, &nbmin, &abstol, &reltol,
            &pivmin, d, e, e2, nval, ab, c, &mout, nab, work, iwork, &info );
}
} // namespace detail

// value-type based template
template< typename ValueType >
struct laebz_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename VectorE2,
            typename VectorNVAL, typename MatrixAB, typename VectorC,
            typename MatrixNAB, typename WORK, typename IWORK >
    static void invoke( const integer_t ijob, const integer_t nitmax,
            const integer_t n, const integer_t minp, const integer_t nbmin,
            const real_type abstol, const real_type reltol,
            const real_type pivmin, const VectorD& d, const VectorE& e,
            const VectorE2& e2, VectorNVAL& nval, MatrixAB& ab, VectorC& c,
            integer_t& mout, MatrixNAB& nab, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE2 >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixAB >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorC >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorNVAL >::value_type, typename traits::matrix_traits<
                MatrixNAB >::value_type >::value) );
        BOOST_ASSERT( traits::vector_size(d) >= n );
        BOOST_ASSERT( traits::vector_size(e) >= n );
        BOOST_ASSERT( traits::vector_size(e2) >= n );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::leading_dimension(ab) ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( traits::leading_dimension(ab) ));
        detail::laebz( ijob, nitmax, n, traits::leading_dimension(ab), minp,
                nbmin, abstol, reltol, pivmin, traits::vector_storage(d),
                traits::vector_storage(e), traits::vector_storage(e2),
                traits::vector_storage(nval), traits::matrix_storage(ab),
                traits::vector_storage(c), mout, traits::matrix_storage(nab),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorE2,
            typename VectorNVAL, typename MatrixAB, typename VectorC,
            typename MatrixNAB >
    static void invoke( const integer_t ijob, const integer_t nitmax,
            const integer_t n, const integer_t minp, const integer_t nbmin,
            const real_type abstol, const real_type reltol,
            const real_type pivmin, const VectorD& d, const VectorE& e,
            const VectorE2& e2, VectorNVAL& nval, MatrixAB& ab, VectorC& c,
            integer_t& mout, MatrixNAB& nab, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::leading_dimension(ab) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::leading_dimension(ab) ) );
        invoke( ijob, nitmax, n, minp, nbmin, abstol, reltol, pivmin, d, e,
                e2, nval, ab, c, mout, nab, info, workspace( tmp_work,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorE2,
            typename VectorNVAL, typename MatrixAB, typename VectorC,
            typename MatrixNAB >
    static void invoke( const integer_t ijob, const integer_t nitmax,
            const integer_t n, const integer_t minp, const integer_t nbmin,
            const real_type abstol, const real_type reltol,
            const real_type pivmin, const VectorD& d, const VectorE& e,
            const VectorE2& e2, VectorNVAL& nval, MatrixAB& ab, VectorC& c,
            integer_t& mout, MatrixNAB& nab, integer_t& info,
            optimal_workspace work ) {
        invoke( ijob, nitmax, n, minp, nbmin, abstol, reltol, pivmin, d, e,
                e2, nval, ab, c, mout, nab, info, minimal_workspace() );
    }

    static integer_t min_size_work( const integer_t mmax ) {
        return mmax;
    }

    static integer_t min_size_iwork( const integer_t mmax ) {
        return mmax;
    }
};


// template function to call laebz
template< typename VectorD, typename VectorE, typename VectorE2,
        typename VectorNVAL, typename MatrixAB, typename VectorC,
        typename MatrixNAB, typename Workspace >
inline integer_t laebz( const integer_t ijob, const integer_t nitmax,
        const integer_t n, const integer_t minp, const integer_t nbmin,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorD >::value_type >::real_type abstol,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorD >::value_type >::real_type reltol,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorD >::value_type >::real_type pivmin, const VectorD& d,
        const VectorE& e, const VectorE2& e2, VectorNVAL& nval, MatrixAB& ab,
        VectorC& c, integer_t& mout, MatrixNAB& nab, Workspace work ) {
    typedef typename traits::vector_traits< VectorD >::value_type value_type;
    integer_t info(0);
    laebz_impl< value_type >::invoke( ijob, nitmax, n, minp, nbmin,
            abstol, reltol, pivmin, d, e, e2, nval, ab, c, mout, nab, info,
            work );
    return info;
}

// template function to call laebz, default workspace type
template< typename VectorD, typename VectorE, typename VectorE2,
        typename VectorNVAL, typename MatrixAB, typename VectorC,
        typename MatrixNAB >
inline integer_t laebz( const integer_t ijob, const integer_t nitmax,
        const integer_t n, const integer_t minp, const integer_t nbmin,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorD >::value_type >::real_type abstol,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorD >::value_type >::real_type reltol,
        const typename traits::type_traits< typename traits::vector_traits<
        VectorD >::value_type >::real_type pivmin, const VectorD& d,
        const VectorE& e, const VectorE2& e2, VectorNVAL& nval, MatrixAB& ab,
        VectorC& c, integer_t& mout, MatrixNAB& nab ) {
    typedef typename traits::vector_traits< VectorD >::value_type value_type;
    integer_t info(0);
    laebz_impl< value_type >::invoke( ijob, nitmax, n, minp, nbmin,
            abstol, reltol, pivmin, d, e, e2, nval, ab, c, mout, nab, info,
            optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

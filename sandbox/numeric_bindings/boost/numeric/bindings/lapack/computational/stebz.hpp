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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_STEBZ_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_STEBZ_HPP

#include <boost/numeric/bindings/lapack/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp
#include <boost/type_traits/is_same.hpp>
#include <cassert>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void stebz( char const range, char const order, integer_t const n,
            float const vl, float const vu, integer_t const il,
            integer_t const iu, float const abstol, float* d, float* e,
            integer_t& m, integer_t& nsplit, float* w, integer_t* iblock,
            integer_t* isplit, float* work, integer_t* iwork,
            integer_t& info ) {
        LAPACK_SSTEBZ( &range, &order, &n, &vl, &vu, &il, &iu, &abstol, d, e,
                &m, &nsplit, w, iblock, isplit, work, iwork, &info );
    }
    inline void stebz( char const range, char const order, integer_t const n,
            double const vl, double const vu, integer_t const il,
            integer_t const iu, double const abstol, double* d, double* e,
            integer_t& m, integer_t& nsplit, double* w, integer_t* iblock,
            integer_t* isplit, double* work, integer_t* iwork,
            integer_t& info ) {
        LAPACK_DSTEBZ( &range, &order, &n, &vl, &vu, &il, &iu, &abstol, d, e,
                &m, &nsplit, w, iblock, isplit, work, iwork, &info );
    }
}

// value-type based template
template< typename ValueType >
struct stebz_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename WORK,
            typename IWORK >
    static void compute( char const range, char const order,
            integer_t const n, real_type const vl, real_type const vu,
            integer_t const il, integer_t const iu, real_type const abstol,
            VectorD& d, VectorE& e, integer_t& m, integer_t& nsplit,
            VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit,
            integer_t& info, detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type > );
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorW >::value_type > );
        BOOST_STATIC_ASSERT( boost::is_same< typename traits::vector_traits<
                VectorIBLOCK >::value_type, typename traits::vector_traits<
                VectorISPLIT >::value_type > );
#ifndef NDEBUG
        assert( range == 'A' || range == 'V' || range == 'I' );
        assert( order == 'B' || order == 'E' );
        assert( n >= 0 );
        assert( traits::vector_size(d) >= n );
        assert( traits::vector_size(e) >= n-1 );
        assert( traits::vector_size(w) >= n );
        assert( traits::vector_size(isplit) >= n );
        assert( traits::vector_size(work.select(real_type()) >= min_size_work(
                n )));
        assert( traits::vector_size(work.select(integer_t()) >=
                min_size_iwork( n )));
#endif
        detail::stebz( range, order, n, vl, vu, il, iu, abstol,
                traits::vector_storage(d), traits::vector_storage(e), m,
                nsplit, traits::vector_storage(w),
                traits::vector_storage(iblock),
                traits::vector_storage(isplit),
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT >
    static void compute( char const range, char const order,
            integer_t const n, real_type const vl, real_type const vu,
            integer_t const il, integer_t const iu, real_type const abstol,
            VectorD& d, VectorE& e, integer_t& m, integer_t& nsplit,
            VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit,
            integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( n ) );
        compute( range, order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w,
                iblock, isplit, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT >
    static void compute( char const range, char const order,
            integer_t const n, real_type const vl, real_type const vu,
            integer_t const il, integer_t const iu, real_type const abstol,
            VectorD& d, VectorE& e, integer_t& m, integer_t& nsplit,
            VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit,
            integer_t& info, optimal_workspace work ) {
        compute( range, order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w,
                iblock, isplit, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 4*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return 3*n;
    }
};


// template function to call stebz
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline integer_t stebz( char const range, char const order,
        integer_t const n, typename traits::vector_traits<
        VectorD >::value_type const vl, typename traits::vector_traits<
        VectorD >::value_type const vu, integer_t const il,
        integer_t const iu, typename traits::vector_traits<
        VectorD >::value_type const abstol, VectorD& d, VectorE& e,
        integer_t& m, integer_t& nsplit, VectorW& w, VectorIBLOCK& iblock,
        VectorISPLIT& isplit, Workspace work = optimal_workspace() ) {
    typedef typename traits::vector_traits< VectorD >::value_type value_type;
    integer_t info(0);
    stebz_impl< value_type >::compute( range, order, n, vl, vu, il, iu,
            abstol, d, e, m, nsplit, w, iblock, isplit, info, work );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif

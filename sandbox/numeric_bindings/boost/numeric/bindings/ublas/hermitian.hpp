//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_UBLAS_HERMITIAN_HPP
#define BOOST_NUMERIC_BINDINGS_UBLAS_HERMITIAN_HPP

#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/adaptor.hpp>
#include <boost/numeric/bindings/end.hpp>
#include <boost/numeric/bindings/ublas/detail/basic_ublas_adaptor.hpp>
#include <boost/numeric/bindings/ublas/detail/convert_to.hpp>
#include <boost/numeric/bindings/ublas/matrix.hpp>
#include <boost/numeric/bindings/ublas/triangular.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/numeric/ublas/hermitian.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace detail {

template< typename T, typename F1, typename F2, typename A, typename Id, typename Enable >
struct adaptor< ublas::hermitian_matrix< T, F1, F2, A >, Id, Enable > {

    typedef typename copy_const< Id, T >::type value_type;
    typedef mpl::map<
        mpl::pair< tag::value_type, value_type >,
        mpl::pair< tag::entity, tag::matrix >,
        mpl::pair< tag::size_type<1>, std::ptrdiff_t >,
        mpl::pair< tag::size_type<2>, std::ptrdiff_t >,
        mpl::pair< tag::matrix_type, tag::hermitian >,
        mpl::pair< tag::data_structure, tag::triangular_array >,
        mpl::pair< tag::data_side, typename convert_to< tag::data_side, F1 >::type >,
        mpl::pair< tag::data_order, typename convert_to< tag::data_order, F2 >::type >
    > property_map;

    static std::ptrdiff_t size1( const Id& id ) {
        return id.size1();
    }

    static std::ptrdiff_t size2( const Id& id ) {
        return id.size2();
    }

    static value_type* begin_value( Id& id ) {
        return bindings::begin_value( id.data() );
    }

    static value_type* end_value( Id& id ) {
        return bindings::end_value( id.data() );
    }

};

template< typename T, typename F, typename Id, typename Enable >
struct adaptor< ublas::hermitian_adaptor< T, F >, Id, Enable >:
    basic_ublas_adaptor<
        T,
        Id,
        mpl::pair< tag::matrix_type, tag::hermitian >,
        mpl::pair< tag::data_side, typename convert_to< tag::data_side, F >::type >
    > {

    typedef typename convert_to< tag::data_side, F >::type data_side;

    static std::ptrdiff_t bandwidth1( const Id& id ) {
        return bindings::bandwidth( id.data(), data_side() );
    }

    static std::ptrdiff_t bandwidth2( const Id& id ) {
        return bindings::bandwidth( id.data(), data_side() );
    }

};

} // namespace detail
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

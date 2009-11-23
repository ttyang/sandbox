//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_TENSOR_RANK_HPP
#define BOOST_NUMERIC_BINDINGS_TENSOR_RANK_HPP

#include <boost/numeric/bindings/detail/adaptor.hpp>

namespace boost {
namespace numeric {
namespace bindings {

template< typename T >
struct tensor_rank: mpl::int_< detail::property_at< T, detail::tag::entity >::type::value > {};

} // namespace bindings
} // namespace numeric
} // namespace boost

#endif

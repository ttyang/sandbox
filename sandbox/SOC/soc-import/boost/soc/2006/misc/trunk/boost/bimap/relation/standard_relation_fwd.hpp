// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/standard_relation_fwd.hpp
/// \brief Defines the standard_pair_view class.

#ifndef BOOST_BIMAP_RELATION_STANDARD_RELATION_FWD_HPP
#define BOOST_BIMAP_RELATION_STANDARD_RELATION_FWD_HPP

namespace boost {
namespace bimap {
namespace relation {

template< class TA, class TB, bool force_mutable = false > class standard_relation;

template< class TA, class TB > class standard_relation_view;
template< class TA, class TB > class const_standard_relation_view;

} // namespace relation
} // namespace bimap
} // namespace boost

#endif // BOOST_BIMAP_RELATION_STANDARD_RELATION_FWD_HPP


// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_CONTAINER_GEN_TEST_RESULT_RANGE_HPP_INCLUDED
#define LIBS_CONTAINER_GEN_TEST_RESULT_RANGE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/adaptor/indirected.hpp>

//[test__result_range
template <typename ResultRange, typename AddedContainer>
bool
    test_result_range(
        ResultRange const& r
      , AddedContainer const& c
      , boost::mpl::true_
    )
{
    return boost::range::equal(boost::adaptors::indirect(r), c);
}

template <typename ResultRange, typename AddedContainer>
bool
    test_result_range(
        ResultRange const& r
      , AddedContainer const& c
      , boost::mpl::false_
    )
{
    return boost::range::equal(r, c);
}
//]

#endif  // LIBS_CONTAINER_GEN_TEST_RESULT_RANGE_HPP_INCLUDED


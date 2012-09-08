//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>

#if !defined BOOST_NO_STD_ALLOCATOR

#include <boost/mpl/bool.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <memory>
#include <iostream>

//[example__container_gen__list_with_custom_allocator_selector
struct int_allocator_selector
{
    template <typename T>
    struct apply
    {
        typedef std::allocator<int> type;
    };
};

int main(int, char*[])
{
    boost::adjacency_list<
        boost::list_selector<boost::mpl::false_,int_allocator_selector>
      , boost::dequeS
      , boost::directedS
    > g(5);

    std::cout << boost::get(
        boost::get(boost::vertex_index, g)
      , boost::vertex(4, g)
    ) << std::endl;

    return 0;
}
//]

#else

int main(int, char*[])
{
    return 0;
}

#endif


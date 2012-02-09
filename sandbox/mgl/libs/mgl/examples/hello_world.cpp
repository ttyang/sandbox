// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mgl/mgl.hpp>

using namespace boost::mgl;

namespace mpl = boost::mpl;

class hello_world : public directed_graph<hello_world>
{
public:
    // vertices
    struct hello {};
    struct mgl {};
    struct world {};

    // adjacency list
    struct adjacency_list : mpl::vector3<
        //   node from      adjacency nodes
        // +--------------+----------------------------+
        row< hello        , mpl::vector1<mgl>          >,
        row< mgl          , mpl::vector1<world>        >,
        row< world        , mpl::vector1<world>        >
        // +--------------+----------------------------+
    > {};
};

int main()
{
    return 0;
}

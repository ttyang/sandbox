// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cxxabi.h>
#include <iostream>
#include <typeinfo>

#include <boost/mgl/mgl.hpp>

using namespace std;
using namespace boost::mgl;

namespace mpl = boost::mpl;

class sample_graph : public directed_graph<sample_graph>
{
public:
    // vertices
    struct A {};
    struct B {};
    struct C {};
    struct D {};
    struct E {};
    struct F {};

    // adjacency list
    struct adjacency_list : mpl::vector6<
        //   node from      adjacency nodes
        // +--------------+----------------------------+
        row< A            , mpl::vector1<B>            >,
        row< B            , mpl::vector2<B, C>         >,
        row< C            , mpl::vector2<A, E>         >,
        row< D            , mpl::vector0<>             >,
        row< E            , mpl::vector2<B, C>         >,
        row< F            , mpl::vector1<D>            >
        // +--------------+----------------------------+
    > {};
};

int main()
{
    typedef depth_first_search<sample_graph,vertex_trace_visitor>::type::visitor_result result;
    typedef BOOST_TYPEOF(result()) result_t;

	cout << abi::__cxa_demangle(typeid(result_t).name(), 0, 0, 0) << endl;

    return 0;
}

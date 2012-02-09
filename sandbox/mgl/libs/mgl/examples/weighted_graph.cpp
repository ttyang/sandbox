// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cxxabi.h>
#include <iostream>
#include <typeinfo>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef  BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#define BOOST_MPL_LIMIT_METAFUNCTION_ARITY 7
#include <boost/mpl/apply.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>

#include <boost/mgl/mgl.hpp>

using namespace std;
using namespace boost::mgl;

namespace mpl = boost::mpl;

class weighted_graph : public directed_graph<weighted_graph>
{
public:
    // vertices
    struct A {};
    struct B {};
    struct C {};
    struct D {};
    struct E {};
    struct F {};
    struct G {};

    // adjacency list
    struct adjacency_list : mpl::vector7<
        //   node from      adjacency nodes
        // +--------------+----------------------------+
        row< A            , mpl::vector2<B, C>         >,
        row< B            , mpl::vector2<E, D>         >,
        row< C            , mpl::vector2<F, G>         >,
        row< D            , mpl::vector1<A>            >,
        row< E            , mpl::vector0<>             >,
        row< F            , mpl::vector0<>             >,
        row< G            , mpl::vector1<C>            >
        // +--------------+----------------------------+
    > {};

    // edge weights
    struct edge_list : mpl::vector8<
        //     node from   node to     weight
        //   +-----------+-----------+-----------+
        edge < A         , B         , 2         >,
        edge < A         , C         , 4         >,
        //   +-----------+-----------+-----------+
        edge < B         , E         , 7         >,
        edge < B         , D         , 1         >,
        //   +-----------+-----------+-----------+
        edge < C         , F         , 3         >,
        edge < C         , G         , 5         >,
        //   +-----------+-----------+-----------+
        edge < D         , A         , 3         >,
        //   +-----------+-----------+-----------+
        edge < G         , C         , 8         >
        //   +-----------+-----------+-----------+
    > {};
};

// a visitor accumulating the weights of the edges
struct edge_weights_accumulator
{
    typedef ::boost::mpl::true_ examine_edge;

    struct on_init
    {
        typedef ::boost::mpl::int_<0> type;
    };

    template<typename Vertex1, typename Vertex2, typename Weight, typename T, typename TraversalStack, typename ColorMap>
    struct on_examine_edge
    {
//        typedef typename ::boost::mpl::push_back<T, Edge>::type type;
        typedef typename ::boost::mpl::plus<T, Weight>::type type;
    };
};

int main()
{
    typedef depth_first_search<weighted_graph, edge_weights_accumulator>::type::visitor_result result;
    typedef BOOST_TYPEOF(result()) result_t;

    cout << abi::__cxa_demangle(typeid(result_t).name(), 0, 0, 0) << endl;

    return 0;
}

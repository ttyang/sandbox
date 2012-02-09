// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#include <typeinfo>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#undef  BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#define BOOST_MPL_LIMIT_METAFUNCTION_ARITY 7
#include <boost/mpl/apply.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>

#include <boost/typeof/typeof.hpp>

#include <boost/mgl/directed_graph.hpp>
#include <boost/mgl/breadth_first_search.hpp>
#include <boost/mgl/visitors.hpp>

#define BOOST_TEST_MODULE "Breadth First Search Test"
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::mgl;

namespace mgl = boost::mgl;

// vertices
struct v0 {};
struct v1 {};
struct v2 {};
struct v3 {};
struct v4 {};
struct v5 {};
struct v6 {};
struct v7 {};
struct v8 {};
struct v9 {};

class some_graph : public directed_graph<some_graph>
{
public:
    // adjacency list of the graph
    struct adjacency_list : mpl::vector10<
        //    Node   Adjacency
        //    from   nodes
        //  +------+--------------------------------------------+
        row < v0   , mpl::vector1<v6>                           >,
        row < v1   , mpl::vector1<v8>                           >,
        row < v2   , mpl::vector5<v5, v8, v1, v9, v6>           >,
        row < v3   , mpl::vector1<v7>                           >,
        row < v4   , mpl::vector2<v1, v5>                       >,
        row < v5   , mpl::vector0<>                             >,
        row < v6   , mpl::vector0<>                             >,
        row < v7   , mpl::vector1<v1>                           >,
        row < v8   , mpl::vector1<v3>                           >,
        row < v9   , mpl::vector0<>                             >
        //  +------+--------------------------------------------+
    > {};
};

struct foo {};

BOOST_AUTO_TEST_CASE(invalid_breadth_first_search)
{
	typedef BOOST_TYPEOF(mpl::void_()) void_t;

	typedef breadth_first_search<foo>::type::vertex bfs;
	typedef BOOST_TYPEOF(bfs()) bfs_t;

	BOOST_CHECK_MESSAGE(typeid(bfs_t) == typeid(void_t), "breadth_first_search<> should return mpl::void_ for invalid graph type");
}

BOOST_AUTO_TEST_CASE(perform_breadth_first_search)
{
	// perform search from first vertex
	typedef mpl::vector2<
		v0,
		v6
	> expected_result11;
	typedef BOOST_TYPEOF(expected_result11()) expected_result11_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v0,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result11;
	typedef BOOST_TYPEOF(result11()) result11_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result11_t, expected_result11_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from first vertex (visit all vertices)
	typedef mpl::vector10<
		v0,
		v6,
		v9,
		v8,
		v3,
		v7,
		v1,
		v5,
		v4,
		v2
	> expected_result12;
	typedef BOOST_TYPEOF(expected_result12()) expected_result12_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v0
	>::type::visitor_result result12;
	typedef BOOST_TYPEOF(result12()) result12_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result12_t, expected_result12_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v1'
	typedef mpl::vector4<
		v1,
		v8,
		v3,
		v7
	> expected_result21;
	typedef BOOST_TYPEOF(expected_result21()) expected_result21_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v1,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result21;
	typedef BOOST_TYPEOF(result21()) result21_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result21_t, expected_result21_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v1' (visit all vertices)
	typedef mpl::vector10<
		v1,
		v8,
		v3,
		v7,
		v9,
		v6,
		v5,
		v4,
		v2,
		v0
	> expected_result22;
	typedef BOOST_TYPEOF(expected_result22()) expected_result22_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v1
	>::type::visitor_result result22;
	typedef BOOST_TYPEOF(result22()) result22_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result22_t, expected_result22_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v2'
	typedef mpl::vector8<
		v2,
		v5,
		v8,
		v1,
		v9,
		v6,
		v3,
		v7
	> expected_result31;
	typedef BOOST_TYPEOF(expected_result31()) expected_result31_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v2,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result31;
	typedef BOOST_TYPEOF(result31()) result31_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result31_t, expected_result31_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v2' (visit all vertices)
	typedef mpl::vector10<
		v2,
		v5,
		v8,
		v1,
		v9,
		v6,
		v3,
		v7,
		v4,
		v0
	> expected_result32;
	typedef BOOST_TYPEOF(expected_result32()) expected_result32_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v2
	>::type::visitor_result result32;
	typedef BOOST_TYPEOF(result32()) result32_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result32_t, expected_result32_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v3'
	typedef mpl::vector4<
		v3,
		v7,
		v1,
		v8
	> expected_result41;
	typedef BOOST_TYPEOF(expected_result41()) expected_result41_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v3,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result41;
	typedef BOOST_TYPEOF(result41()) result41_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result41_t, expected_result41_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v3' (visit all vertices)
	typedef mpl::vector10<
		v3,
		v7,
		v1,
		v8,
		v9,
		v6,
		v5,
		v4,
		v2,
		v0
	> expected_result42;
	typedef BOOST_TYPEOF(expected_result42()) expected_result42_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v3
	>::type::visitor_result result42;
	typedef BOOST_TYPEOF(result42()) result42_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result42_t, expected_result42_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v4'
	typedef mpl::vector6<
		v4,
		v1,
		v5,
		v8,
		v3,
		v7
	> expected_result51;
	typedef BOOST_TYPEOF(expected_result51()) expected_result51_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v4,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result51;
	typedef BOOST_TYPEOF(result51()) result51_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result51_t, expected_result51_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v4' (visit all vertices)
	typedef mpl::vector10<
		v4,
		v1,
		v5,
		v8,
		v3,
		v7,
		v9,
		v6,
		v2,
		v0
	> expected_result52;
	typedef BOOST_TYPEOF(expected_result52()) expected_result52_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v4
	>::type::visitor_result result52;
	typedef BOOST_TYPEOF(result52()) result52_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result52_t, expected_result52_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v5'
	typedef mpl::vector1<
		v5
	> expected_result61;
	typedef BOOST_TYPEOF(expected_result61()) expected_result61_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v5,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result61;
	typedef BOOST_TYPEOF(result61()) result61_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result61_t, expected_result61_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v5' (visit all vertices)
	typedef mpl::vector10<
		v5,
		v9,
		v8,
		v3,
		v7,
		v1,
		v6,
		v4,
		v2,
		v0
	> expected_result62;
	typedef BOOST_TYPEOF(expected_result62()) expected_result62_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v5
	>::type::visitor_result result62;
	typedef BOOST_TYPEOF(result62()) result62_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result62_t, expected_result62_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v6'
	typedef mpl::vector1<
		v6
	> expected_result71;
	typedef BOOST_TYPEOF(expected_result71()) expected_result71_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v6,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result71;
	typedef BOOST_TYPEOF(result71()) result71_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result71_t, expected_result71_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v6' (visit all vertices)
	typedef mpl::vector10<
		v6,
		v9,
		v8,
		v3,
		v7,
		v1,
		v5,
		v4,
		v2,
		v0
	> expected_result72;
	typedef BOOST_TYPEOF(expected_result72()) expected_result72_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v6
	>::type::visitor_result result72;
	typedef BOOST_TYPEOF(result72()) result72_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result72_t, expected_result72_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v7'
	typedef mpl::vector4<
		v7,
		v1,
		v8,
		v3
	> expected_result81;
	typedef BOOST_TYPEOF(expected_result81()) expected_result81_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v7,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result81;
	typedef BOOST_TYPEOF(result81()) result81_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result81_t, expected_result81_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v7' (visit all vertices)
	typedef mpl::vector10<
		v7,
		v1,
		v8,
		v3,
		v9,
		v6,
		v5,
		v4,
		v2,
		v0
	> expected_result82;
	typedef BOOST_TYPEOF(expected_result82()) expected_result82_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v7
	>::type::visitor_result result82;
	typedef BOOST_TYPEOF(result82()) result82_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result82_t, expected_result82_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v8'
	typedef mpl::vector4<
		v8,
		v3,
		v7,
		v1
	> expected_result91;
	typedef BOOST_TYPEOF(expected_result91()) expected_result91_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v8,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result91;
	typedef BOOST_TYPEOF(result91()) result91_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result91_t, expected_result91_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v8' (visit all vertices)
	typedef mpl::vector10<
		v8,
		v3,
		v7,
		v1,
		v9,
		v6,
		v5,
		v4,
		v2,
		v0
	> expected_result92;
	typedef BOOST_TYPEOF(expected_result92()) expected_result92_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v8
	>::type::visitor_result result92;
	typedef BOOST_TYPEOF(result92()) result92_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result92_t, expected_result92_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v9'
	typedef mpl::vector1<
		v9
	> expected_result101;
	typedef BOOST_TYPEOF(expected_result101()) expected_result101_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v9,
		::boost::mgl::EndWhenNoVerticesFound
	>::type::visitor_result result101;
	typedef BOOST_TYPEOF(result101()) result101_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result101_t, expected_result101_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");

	// perform search from vertex 'v9' (visit all vertices)
	typedef mpl::vector10<
		v9,
		v8,
		v3,
		v7,
		v1,
		v6,
		v5,
		v4,
		v2,
		v0
	> expected_result102;
	typedef BOOST_TYPEOF(expected_result102()) expected_result102_t;

	typedef breadth_first_search<
		some_graph,
		::boost::mgl::vertex_trace_visitor,
		v9
	>::type::visitor_result result102;
	typedef BOOST_TYPEOF(result102()) result102_t;

	BOOST_CHECK_MESSAGE((::boost::mpl::equal<result102_t, expected_result102_t>::value), "breadth_first_search<> should return the right mpl::vector<> type");
}

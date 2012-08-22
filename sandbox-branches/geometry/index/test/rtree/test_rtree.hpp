// Boost.Geometry (aka GGL, Generic Geometry Library)
// Unit Test

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2011-2012 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_TEST_RTREE_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_TEST_RTREE_HPP

#include <geometry_index_test_common.hpp>

#include <boost/foreach.hpp>
#include <vector>

#include <boost/geometry/extensions/index/rtree/rtree.hpp>

// TODO: fix this issue differently
#ifdef max
#undef max
#endif
#include <boost/geometry/extensions/index/rtree/visitors/are_levels_ok.hpp>
#include <boost/geometry/extensions/index/rtree/visitors/are_boxes_ok.hpp>

// Values, input and rtree generation

template <typename Value>
struct generate_value
{};

template <typename T, typename C>
struct generate_value< bg::model::point<T, 2, C> >
{
    typedef bg::model::point<T, 2, C> P;
    static P apply(int x, int y)
    {
        return P(x, y);
    }
};

template <typename T, typename C>
struct generate_value< bg::model::box< bg::model::point<T, 2, C> > >
{
    typedef bg::model::point<T, 2, C> P;
    typedef bg::model::box<P> B;
    static B apply(int x, int y)
    {
        return B(P(x, y), P(x + 2, y + 3));
    }
};

template <typename T, typename C>
struct generate_value< std::pair<bg::model::point<T, 2, C>, int> >
{
    typedef bg::model::point<T, 2, C> P;
    typedef std::pair<P, int> R;
    static R apply(int x, int y)
    {
        return std::make_pair(P(x, y), x + y * 100);
    }
};

template <typename T, typename C>
struct generate_value< std::pair<bg::model::box< bg::model::point<T, 2, C> >, int> >
{
    typedef bg::model::point<T, 2, C> P;
    typedef bg::model::box<P> B;
    typedef std::pair<B, int> R;
    static R apply(int x, int y)
    {
        return std::make_pair(B(P(x, y), P(x + 2, y + 3)), x + y * 100);
    }
};

template <typename T, typename C>
struct generate_value< bg::model::point<T, 3, C> >
{
    typedef bg::model::point<T, 3, C> P;
    static P apply(int x, int y, int z)
    {
        return P(x, y, z);
    }
};

template <typename T, typename C>
struct generate_value< bg::model::box< bg::model::point<T, 3, C> > >
{
    typedef bg::model::point<T, 3, C> P;
    typedef bg::model::box<P> B;
    static B apply(int x, int y, int z)
    {
        return B(P(x, y, z), P(x + 2, y + 3, z + 4));
    }
};

template <typename T, typename C>
struct generate_value< std::pair<bg::model::point<T, 3, C>, int> >
{
    typedef bg::model::point<T, 3, C> P;
    typedef std::pair<P, int> R;
    static R apply(int x, int y, int z)
    {
        return std::make_pair(P(x, y, z), x + y * 100 + z * 10000);
    }
};

template <typename T, typename C>
struct generate_value< std::pair<bg::model::box< bg::model::point<T, 3, C> >, int> >
{
    typedef bg::model::point<T, 3, C> P;
    typedef bg::model::box<P> B;
    typedef std::pair<B, int> R;
    static R apply(int x, int y, int z)
    {
        return std::make_pair(B(P(x, y, z), P(x + 2, y + 3, z + 4)), x + y * 100 + z * 10000);
    }
};

template <size_t Dimension>
struct generate_input
{};

template <>
struct generate_input<2>
{
    template <typename Value, typename Box>
    static void apply(std::vector<Value> & input, Box & qbox)
    {
        for ( int i = 0 ; i < 12 ; i += 3 )
        {
            for ( int j = 1 ; j < 25 ; j += 4 )
            {
                input.push_back( generate_value<Value>::apply(i, j) );
            }
        }

        typedef typename bg::traits::point_type<Box>::type P;

        qbox = Box(P(3, 0), P(10, 9));
    }
};

template <>
struct generate_input<3>
{
    template <typename Value, typename Box>
    static void apply(std::vector<Value> & input, Box & qbox)
    {
        for ( int i = 0 ; i < 12 ; i += 3 )
        {
            for ( int j = 1 ; j < 25 ; j += 4 )
            {
                for ( int k = 2 ; k < 12 ; k += 5 )
                {
                    input.push_back( generate_value<Value>::apply(i, j, k) );
                }
            }
        }

        typedef typename bg::traits::point_type<Box>::type P;

        qbox = Box(P(3, 0, 3), P(10, 9, 11));
    }
};

template<typename Value, typename Algo, typename Box>
void generate_rtree(bgi::rtree<Value, Algo> & tree, std::vector<Value> & input, Box & qbox)
{
    typedef bgi::rtree<Value, Algo> T;
    typedef typename T::box_type B;
    typedef typename T::value_type V;
    typedef typename T::indexable_type I;

    generate_input<
        bgi::traits::dimension<I>::value
    >::apply(input, qbox);

    tree.insert(input.begin(), input.end());
}

// low level test functions

template <typename Rtree, typename Iter, typename Value>
Iter test_find(Rtree const& rtree, Iter first, Iter last, Value const& value)
{
    for ( ; first != last ; ++first )
        if ( rtree.translator().equals(value, *first) )
            return first;
    return first;
}

template <typename Rtree, typename Value>
void test_compare_outputs(Rtree const& rtree, std::vector<Value> const& output, std::vector<Value> const& expected_output)
{
    bool are_sizes_ok = (expected_output.size() == output.size());
    BOOST_CHECK( are_sizes_ok );
    if ( are_sizes_ok )
    {
        BOOST_FOREACH(Value const& v, expected_output)
        {
            BOOST_CHECK(test_find(rtree, output.begin(), output.end(), v) != output.end() );
        }
    }
}

template <typename Rtree, typename Range1, typename Range2>
void test_exactly_the_same_outputs(Rtree const& rtree, Range1 const& output, Range2 const& expected_output)
{
    size_t s1 = std::distance(output.begin(), output.end());
    size_t s2 = std::distance(expected_output.begin(), expected_output.end());
    BOOST_CHECK(s1 == s2);

    if ( s1 == s2 )
    {
        Range1::const_iterator it1 = output.begin();
        Range2::const_iterator it2 = expected_output.begin();
        for ( ; it1 != output.end() && it2 != expected_output.end() ; ++it1, ++it2 )
        {
            if ( !rtree.translator().equals(*it1, *it2) )
            {
                BOOST_CHECK(false);
                break;
            }
        }
    }
}

template <typename Rtree, typename Value, typename Predicates>
void test_query(Rtree & rtree, Predicates const& pred, std::vector<Value> const& expected_output)
{
    BOOST_CHECK( bgi::are_levels_ok(rtree) );
    BOOST_CHECK( bgi::are_boxes_ok(rtree) );

    std::vector<Value> output;
    size_t n = rtree.query(pred, std::back_inserter(output));

    BOOST_CHECK( expected_output.size() == n );
    test_compare_outputs(rtree, output, expected_output);

    std::vector<Value> output2;
    size_t n2 = query(rtree, pred, std::back_inserter(output2));

    BOOST_CHECK( n == n2 );
    test_exactly_the_same_outputs(rtree, output, output2);

    test_exactly_the_same_outputs(rtree, output, rtree | bgi::query_filtered(pred));
}

// rtree queries tests

template <typename Value, typename Algo, typename Box>
void test_intersects_and_disjoint(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
{
    std::vector<Value> expected_output;

    BOOST_FOREACH(Value const& v, input)
        if ( bg::intersects(tree.translator()(v), qbox) )
            expected_output.push_back(v);

    test_query(tree, qbox, expected_output);
    test_query(tree, bgi::intersects(qbox), expected_output);
    test_query(tree, !bgi::not_intersects(qbox), expected_output);
    test_query(tree, !bgi::disjoint(qbox), expected_output);
    test_query(tree, bgi::not_disjoint(qbox), expected_output);
}

template <typename Value, typename Algo, typename Box>
void test_covered_by(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
{
    std::vector<Value> expected_output;

    BOOST_FOREACH(Value const& v, input)
        if ( bg::covered_by(tree.translator()(v), qbox) )
            expected_output.push_back(v);

    test_query(tree, bgi::covered_by(qbox), expected_output);
}

template <typename Tag>
struct test_overlap_impl
{
    template <typename Value, typename Algo, typename Box>
    static void apply(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
    {
        std::vector<Value> expected_output;

        BOOST_FOREACH(Value const& v, input)
            if ( bg::overlaps(tree.translator()(v), qbox) )
                expected_output.push_back(v);

        test_query(tree, bgi::overlaps(qbox), expected_output);
    }
};

template <>
struct test_overlap_impl<bg::point_tag>
{
    template <typename Value, typename Algo, typename Box>
    static void apply(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
    {}
};

template <typename Value, typename Algo, typename Box>
void test_overlaps(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
{
    test_overlap_impl<
        typename bgi::traits::tag<
            typename bgi::rtree<Value, Algo>::indexable_type
        >::type
    >::apply(tree, input, qbox);
}

//template <typename Tag, size_t Dimension>
//struct test_touches_impl
//{
//    template <typename Value, typename Algo, typename Box>
//    static void apply(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
//    {}
//};
//
//template <>
//struct test_touches_impl<bg::box_tag, 2>
//{
//    template <typename Value, typename Algo, typename Box>
//    static void apply(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
//    {
//        std::vector<Value> expected_output;
//
//        BOOST_FOREACH(Value const& v, input)
//            if ( bg::touches(tree.translator()(v), qbox) )
//                expected_output.push_back(v);
//
//        test_query(tree, bgi::touches(qbox), expected_output);
//    }
//};
//
//template <typename Value, typename Algo, typename Box>
//void test_touches(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
//{
//    test_touches_impl<
//        bgi::traits::tag<
//            typename bgi::rtree<Value, Algo>::indexable_type
//        >::type,
//        bgi::traits::dimension<
//            typename bgi::rtree<Value, Algo>::indexable_type
//        >::value
//    >::apply(tree, input, qbox);
//}

template <typename Value, typename Algo, typename Box>
void test_within(bgi::rtree<Value, Algo> const& tree, std::vector<Value> const& input, Box const& qbox)
{
    std::vector<Value> expected_output;

    BOOST_FOREACH(Value const& v, input)
        if ( bg::within(tree.translator()(v), qbox) )
            expected_output.push_back(v);

    test_query(tree, bgi::within(qbox), expected_output);
}

template <typename Value, typename Algo, typename Box>
void test_copy_assignment_move(bgi::rtree<Value, Algo> & tree, Box const& qbox)
{
    std::vector<Value> expected_output;
    tree.query(qbox, std::back_inserter(expected_output));

    // copy constructor
    bgi::rtree<Value, Algo> t1(tree);

    std::vector<Value> output;
    t1.query(qbox, std::back_inserter(output));
    test_exactly_the_same_outputs(t1, output, expected_output);

    // copying assignment operator
    t1 = tree;

    output.clear();
    t1.query(qbox, std::back_inserter(output));
    test_exactly_the_same_outputs(t1, output, expected_output);

    // moving constructor
    bgi::rtree<Value, Algo> t2(boost::move(tree));

    output.clear();
    t2.query(qbox, std::back_inserter(output));
    test_exactly_the_same_outputs(t2, output, expected_output);

    // moving assignment operator
    t2 = boost::move(t1);

    output.clear();
    t2.query(qbox, std::back_inserter(output));
    test_exactly_the_same_outputs(t2, output, expected_output);
}

template <typename Value, typename Algo>
void test_rtree_by_value()
{
    typedef bgi::rtree<Value, Algo> Tree;
    typedef typename Tree::box_type B;

    Tree tree;
    std::vector<Value> input;
    B qbox;

    generate_rtree(tree, input, qbox);

    test_intersects_and_disjoint(tree, input, qbox);
    test_covered_by(tree, input, qbox);
    test_overlaps(tree, input, qbox);
    //test_touches(tree, input, qbox);
    test_within(tree, input, qbox);

    test_copy_assignment_move(tree, qbox);
}

template<typename Point, typename Algo>
void test_rtree()
{
    typedef bg::model::box<Point> Box;
    typedef std::pair<Box, int> PairB;
    typedef std::pair<Point, int> PairP;

    test_rtree_by_value<Point, Algo>();
    test_rtree_by_value<Box, Algo>();
    test_rtree_by_value<PairB, Algo>();
    test_rtree_by_value<PairP, Algo>();
}

#endif

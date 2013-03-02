// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <set>
#include <boost/cstdint.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/typeof/boost/tree_node/with_count.hpp>
#include <boost/typeof/boost/tree_node/with_height.hpp>
#include <boost/typeof/boost/tree_node/with_position.hpp>
#include <boost/typeof/boost/tree_node/with_red_black_flag.hpp>
#include <boost/typeof/boost/tree_node/binary_node.hpp>
#include <boost/tree_node/iterator/breadth_first.hpp>
#include <boost/tree_node/iterator/breadth_first_descendant.hpp>
#include <boost/tree_node/iterator/depth_first.hpp>
#include <boost/tree_node/balancer/adelson_velskii_landis.hpp>
#include <boost/tree_node/container/binode.hpp>
#include <boost/tree_node/container/binode_associative.hpp>
#include <boost/test/minimal.hpp>

template <typename T1, typename T2>
void test_output_data(::std::pair<T1,T2> const& p)
{
    std::cout << '<' << p.first << ", " << p.second << '>';
}

template <typename T>
void test_output_data(T const& t)
{
    std::cout << t;
}

template <typename Node>
void test_red_black_node(Node const& root)
{
    typename Node::size_type black_depth = boost::initialized_value;
    std::cout << std::endl;

    for (
        boost::tree_node::depth_first_iterator<Node const> itr(root);
        itr;
        ++itr
    )
    {
        switch (boost::tree_node::traversal_state(itr))
        {
            case boost::tree_node::pre_order_traversal:
            {
                ++black_depth;

                for (
                    typename Node::size_type depth = 0;
                    depth < black_depth;
                    ++depth
                )
                {
                    std::cout << "    ";
                }

                if (Node const* p = itr->get_parent_ptr())
                {
                    std::cout << (
                        (&*itr == p->get_left_child_ptr()) ? "left" : "right"
                    );
                }

                std::cout << '(' << (
                    get(*itr, boost::tree_node::red_flag_key())
                  ? "red,"
                  : "black,"
                );
                test_output_data(get(*itr, boost::tree_node::data_key()));
                std::cout << std::endl;
                break;
            }

            case boost::tree_node::post_order_traversal:
            {
                for (
                    typename Node::size_type depth = 0;
                    depth < black_depth;
                    ++depth
                )
                {
                    std::cout << "    ";
                }

                --black_depth;
                std::cout << (
                    get(*itr, boost::tree_node::red_flag_key())
                  ? "red,"
                  : "black,"
                );
                test_output_data(get(*itr, boost::tree_node::data_key()));
                std::cout << ')' << std::endl;
                break;
            }

            default:
            {
                BOOST_CHECK(false);
            }
        }
    }

    BOOST_CHECK(get(root, boost::tree_node::black_flag_key()));

    if (root.empty())
    {
        return;
    }

    for (
        boost::tree_node::breadth_first_descendant_iterator<Node const> itr(
            root
        );
        itr;
        ++itr
    )
    {
        if (get(*itr, boost::tree_node::red_flag_key()))
        {
            BOOST_CHECK(
                !itr->get_left_child_ptr() || get(
                    *itr->get_left_child_ptr()
                  , boost::tree_node::black_flag_key()
                )
            );
            BOOST_CHECK(
                !itr->get_right_child_ptr() || get(
                    *itr->get_right_child_ptr()
                  , boost::tree_node::black_flag_key()
                )
            );
        }

        if (!itr->get_left_child_ptr() || !itr->get_right_child_ptr())
        {
            typename Node::size_type depth = boost::initialized_value;

            for (Node const* p = &*itr; p; p = p->get_parent_ptr())
            {
                if (get(*p, boost::tree_node::black_flag_key()))
                {
                    ++depth;
                }
            }

            if (black_depth)
            {
                BOOST_CHECK(black_depth == depth);
            }
            else
            {
                black_depth = depth;
            }
        }
    }
}

template <typename Node>
void test_avl_node(Node const& root)
{
    typename Node::size_type max_depth = boost::initialized_value;
    std::cout << std::endl;

    for (
        boost::tree_node::depth_first_iterator<Node const> itr(root);
        itr;
        ++itr
    )
    {
        switch (boost::tree_node::traversal_state(itr))
        {
            case boost::tree_node::pre_order_traversal:
            {
                ++max_depth;

                for (
                    typename Node::size_type depth = 0;
                    depth < max_depth;
                    ++depth
                )
                {
                    std::cout << "    ";
                }

                if (Node const* p = itr->get_parent_ptr())
                {
                    std::cout << (
                        (&*itr == p->get_left_child_ptr()) ? "left" : "right"
                    );
                }

                std::cout << '(' << get(
                    *itr
                  , boost::tree_node::height_key()
                ) << ", ";
                test_output_data(get(*itr, boost::tree_node::data_key()));
                std::cout << std::endl;
                break;
            }

            case boost::tree_node::post_order_traversal:
            {
                for (
                    typename Node::size_type depth = 0;
                    depth < max_depth;
                    ++depth
                )
                {
                    std::cout << "    ";
                }

                --max_depth;
                std::cout << get(
                    *itr
                  , boost::tree_node::height_key()
                ) << ", ";
                test_output_data(get(*itr, boost::tree_node::data_key()));
                std::cout << ')' << std::endl;
                break;
            }

            default:
            {
                BOOST_CHECK(false);
            }
        }
    }

    for (
        boost::tree_node::breadth_first_iterator<Node const> itr(root);
        itr;
        ++itr
    )
    {
        if (itr->get_left_child_ptr())
        {
            if (itr->get_right_child_ptr())
            {
                BOOST_CHECK(
                    (
                        get(
                            *itr->get_left_child_ptr()
                          , boost::tree_node::height_key()
                        ) == get(
                            *itr->get_right_child_ptr()
                          , boost::tree_node::height_key()
                        )
                    ) || (
                        1 + get(
                            *itr->get_left_child_ptr()
                          , boost::tree_node::height_key()
                        ) == get(
                            *itr->get_right_child_ptr()
                          , boost::tree_node::height_key()
                        )
                    ) || (
                        get(
                            *itr->get_left_child_ptr()
                          , boost::tree_node::height_key()
                        ) == 1 + get(
                            *itr->get_right_child_ptr()
                          , boost::tree_node::height_key()
                        )
                    )
                );
            }
            else
            {
                BOOST_CHECK(
                    !get(
                        *itr->get_left_child_ptr()
                      , boost::tree_node::height_key()
                    )
                );
            }
        }
        else if (itr->get_right_child_ptr())
        {
            BOOST_CHECK(
                !get(
                    *itr->get_right_child_ptr()
                  , boost::tree_node::height_key()
                )
            );
        }
    }
}

template <typename K1, typename V1, typename K2, typename V2>
bool test_tree_values(std::pair<K1,V1> const& p1, std::pair<K2,V2> const& p2)
{
    return (p1.first == p2.first) && (p1.second == p2.second);
}

template <typename T1, typename T2>
bool test_tree_values(T1 const& t1, T2 const& t2)
{
    return t1 == t2;
}

struct test_equal_trees_predicate
{
    template <typename T1, typename T2>
    bool operator()(T1 const& t1, T2 const& t2) const
    {
        return test_tree_values(t1, t2);
    }
};

template <typename Tree, typename Values>
void test_tree_container(Tree const& tree, Values const& values)
{
    BOOST_CHECK(tree.empty() == values.empty());
    BOOST_CHECK(tree.size() == values.size());
    BOOST_CHECK(
        boost::range::equal(tree, values, test_equal_trees_predicate())
    );

    typename Tree::const_reverse_iterator t_rend = tree.crend();
    typename Values::const_reverse_iterator v_ritr = values.rbegin();
    typename Values::const_reverse_iterator v_rend = values.rend();

    for (
        typename Tree::const_reverse_iterator t_ritr = tree.crbegin();
        t_ritr != t_rend;
        ++t_ritr
    )
    {
        if (v_ritr == v_rend)
        {
            BOOST_CHECK(false);
            break;
        }

        BOOST_CHECK(test_tree_values(*t_ritr, *v_ritr));
        ++v_ritr;
    }

    BOOST_CHECK(v_ritr == v_rend);

    typename Tree::size_type index = 0;
    typename Tree::const_iterator t_end = tree.cend();

    for (
        typename Tree::const_iterator t_itr = tree.cbegin();
        t_itr != t_end;
        ++t_itr
    )
    {
        BOOST_CHECK(test_tree_values(tree[index], *t_itr));
        ++index;
    }
}

template <typename Tree, typename Values>
void test_clear(Tree& tree, Values& values)
{
    tree.clear();
    values.clear();
    test_tree_container(tree, values);
}

typedef std::deque<boost::int32_t>
        ValueSequence;
typedef boost::tree_node::with_red_black_flag_gen<
            boost::tree_node::with_count_base_gen<
                boost::tree_node::binary_node_base_gen<>
            >
        >
        RedBlackNodeGen;
typedef boost::tree_node::binode_container<RedBlackNodeGen,boost::int32_t>
        RedBlackTreeSequence;

void
    test_push_front(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::value_type t
    )
{
    red_black_tree.push_front(t);
    std::cout << std::endl << "After red_black_tree.push_front(" << t << "):";
    test_red_black_node(*red_black_tree.data());
    values.push_front(t);
    test_tree_container(red_black_tree, values);
}

void
    test_push_back(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::value_type t
    )
{
    red_black_tree.push_back(t);
    std::cout << std::endl << "After red_black_tree.push_back(" << t << "):";
    test_red_black_node(*red_black_tree.data());
    values.push_back(t);
    test_tree_container(red_black_tree, values);
}

void
    test_pop_front(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
    )
{
    red_black_tree.pop_front();
    std::cout << std::endl << "After red_black_tree.pop_front():";
    test_red_black_node(*red_black_tree.data());
    values.pop_front();
    test_tree_container(red_black_tree, values);
}

void
    test_pop_back(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
    )
{
    red_black_tree.pop_back();
    std::cout << std::endl << "After red_black_tree.pop_back():";
    test_red_black_node(*red_black_tree.data());
    values.pop_back();
    test_tree_container(red_black_tree, values);
}

void
    test_insert(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::size_type index
      , RedBlackTreeSequence::value_type t
    )
{
    red_black_tree.insert(red_black_tree.begin() + index, t);
    std::cout << std::endl << "After red_black_tree.insert[" << index << "](";
    std::cout << t << "):";
    test_red_black_node(*red_black_tree.data());
    values.insert(values.begin() + index, t);
    test_tree_container(red_black_tree, values);
}

void
    test_erase(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::size_type index
    )
{
    RedBlackTreeSequence::iterator tree_itr = red_black_tree.erase(
        red_black_tree.begin() + index
    );

    if (index == red_black_tree.size())
    {
        BOOST_CHECK(tree_itr == red_black_tree.end());
    }
    else
    {
        BOOST_CHECK(test_tree_values(*tree_itr, red_black_tree[index]));
    }

    std::cout << std::endl << "After red_black_tree.erase[" << index << "]:";
    test_red_black_node(*red_black_tree.data());
    values.erase(values.begin() + index);
    test_tree_container(red_black_tree, values);
}

typedef boost::tree_node::with_height_gen<
            boost::tree_node::with_count_base_gen<
                boost::tree_node::binary_node_base_gen<>
            >
        >
        AVLNodeGen;
typedef boost::tree_node::binode_container<
            AVLNodeGen
          , boost::int32_t
          , boost::tree_node::adelson_velskii_landis_balancer
        >
        AVLTreeSequence;

void
    test_push_front(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::value_type t
    )
{
    avl_tree.push_front(t);
    std::cout << std::endl << "After avl_tree.push_front(" << t << "):";
    test_avl_node(*avl_tree.data());
    values.push_front(t);
    test_tree_container(avl_tree, values);
}

void
    test_push_back(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::value_type t
    )
{
    avl_tree.push_back(t);
    std::cout << std::endl << "After avl_tree.push_back(" << t << "):";
    test_avl_node(*avl_tree.data());
    values.push_back(t);
    test_tree_container(avl_tree, values);
}

void test_pop_front(AVLTreeSequence& avl_tree, ValueSequence& values)
{
    avl_tree.pop_front();
    std::cout << std::endl << "After avl_tree.pop_front():";
    test_avl_node(*avl_tree.data());
    values.pop_front();
    test_tree_container(avl_tree, values);
}

void test_pop_back(AVLTreeSequence& avl_tree, ValueSequence& values)
{
    avl_tree.pop_back();
    std::cout << std::endl << "After avl_tree.pop_back():";
    test_avl_node(*avl_tree.data());
    values.pop_back();
    test_tree_container(avl_tree, values);
}

void
    test_insert(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::size_type index
      , AVLTreeSequence::value_type t
    )
{
    avl_tree.insert(avl_tree.begin() + index, t);
    std::cout << std::endl << "After avl_tree.insert[" << index << "](";
    std::cout << t << "):";
    test_avl_node(*avl_tree.data());
    values.insert(values.begin() + index, t);
    test_tree_container(avl_tree, values);
}

void
    test_erase(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::size_type index
    )
{
    AVLTreeSequence::iterator tree_itr = avl_tree.erase(
        avl_tree.begin() + index
    );

    if (index == avl_tree.size())
    {
        BOOST_CHECK(tree_itr == avl_tree.end());
    }
    else
    {
        BOOST_CHECK(test_tree_values(*tree_itr, avl_tree[index]));
    }

    std::cout << std::endl << "After avl_tree.erase[" << index << "]:";
    test_avl_node(*avl_tree.data());
    values.erase(values.begin() + index);
    test_tree_container(avl_tree, values);
}

template <typename TreeSequence>
void test_sequence(TreeSequence& tree_sequence, ValueSequence& values)
{
    BOOST_CHECK(tree_sequence.empty());
    BOOST_CHECK(0 == tree_sequence.size());

    for (boost::int32_t i = -5; -15 < i; --i)
    {
        test_push_back(tree_sequence, values, i);
    }

    for (boost::int32_t i = 5; i < 15; ++i)
    {
        test_push_front(tree_sequence, values, i);
    }

    test_pop_back(tree_sequence, values);
    test_pop_front(tree_sequence, values);
    typename TreeSequence::size_type index = 0;

    for (boost::int32_t i = -4; i < 5; ++i)
    {
        test_insert(tree_sequence, values, index += 2, i);
    }
}

void test_red_black_sequence()
{
    RedBlackTreeSequence red_black_tree;
    ValueSequence values;

    test_sequence(red_black_tree, values);

    RedBlackTreeSequence red_black_copy;
    ValueSequence value_copies;

    for (
        RedBlackTreeSequence::size_type index = 0;
        index + 1 < red_black_tree.size();
        ++index
    )
    {
        red_black_copy = red_black_tree;
        value_copies = values;

        if (!index)
        {
            test_tree_container(red_black_copy, value_copies);
        }

        test_erase(red_black_copy, value_copies, index);

        switch (index)
        {
            case 2:
            {
                test_erase(red_black_copy, value_copies, 1);
                break;
            }

            case 4:
            {
                test_erase(red_black_copy, value_copies, 4);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

void test_avl_sequence()
{
    AVLTreeSequence avl_tree;
    ValueSequence values;

    test_sequence(avl_tree, values);

    AVLTreeSequence avl_copy;
    ValueSequence value_copies;

    for (
        AVLTreeSequence::size_type index = 0;
        index + 1 < avl_tree.size();
        ++index
    )
    {
        avl_copy = avl_tree;
        value_copies = values;

        if (!index)
        {
            test_tree_container(avl_copy, value_copies);
        }

        test_erase(avl_copy, value_copies, index);

        switch (index)
        {
            case 0:
            {
                test_erase(avl_copy, value_copies, 0);
                break;
            }

            case 1:
            {
                test_erase(avl_copy, value_copies, 1);
                break;
            }

            case 3:
            {
                test_erase(avl_copy, value_copies, 5);
                break;
            }

            case 4:
            {
                test_erase(avl_copy, value_copies, 4);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

typedef std::set<boost::int32_t>
        ValueSet;
typedef std::map<boost::int32_t,boost::int32_t>
        ValueMap;

void test_value_insert(ValueSet& values, ValueSet::key_type const& key)
{
    values.insert(key);
}

void test_value_insert(ValueMap& values, ValueMap::key_type const& key)
{
    values.insert(ValueMap::value_type(key, key));
}

typedef boost::tree_node::binode_set<RedBlackNodeGen,boost::int32_t>
        RedBlackTreeSet;

void
    test_insert(
        RedBlackTreeSet& red_black_tree
      , ValueSet& values
      , RedBlackTreeSet::key_type const& key
    )
{
    std::pair<RedBlackTreeSet::iterator,bool> p = red_black_tree.insert(key);

    if (values.insert(key).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After inserting " << key << ':';
        test_red_black_node(*red_black_tree.data());
        BOOST_CHECK(*p.first == key);
        BOOST_CHECK(p.first == red_black_tree.find(key));
        BOOST_CHECK(!red_black_tree.empty());
        test_tree_container(red_black_tree, values);
    }
    else
    {
        BOOST_CHECK(!p.second);
    }
}

void
    test_erase(
        RedBlackTreeSet& red_black_tree
      , ValueSet& values
      , RedBlackTreeSet::key_type const& key
    )
{
    BOOST_CHECK(red_black_tree.erase(key) == values.erase(key));
    std::cout << std::endl << "After erasing " << key;

    if (red_black_tree.empty())
    {
        std::cout << ", red_black_tree is empty." << std::endl;
    }
    {
        std::cout << ':';
        test_red_black_node(*red_black_tree.data());
    }

    test_tree_container(red_black_tree, values);
}

typedef boost::tree_node::binode_map<
            RedBlackNodeGen
          , boost::int32_t
          , boost::int32_t
        >
        RedBlackTreeMap;

void
    test_insert(
        RedBlackTreeMap& red_black_tree
      , ValueMap& values
      , RedBlackTreeMap::key_type const& key
    )
{
    std::pair<RedBlackTreeMap::iterator,bool> p = red_black_tree.emplace(
        key
      , key
    );

    if (values.insert(ValueMap::value_type(key, key)).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After emplacing " << key << ':';
        test_red_black_node(*red_black_tree.data());
        BOOST_CHECK(p.first->first == key);
        BOOST_CHECK(p.first->second == key);
        BOOST_CHECK(p.first == red_black_tree.find(key));
        BOOST_CHECK(!red_black_tree.empty());
        test_tree_container(red_black_tree, values);
    }
    else
    {
        BOOST_CHECK(!p.second);
    }
}

void
    test_erase(
        RedBlackTreeMap& red_black_tree
      , ValueMap& values
      , RedBlackTreeMap::key_type const& key
    )
{
    BOOST_CHECK(red_black_tree.erase(key) == values.erase(key));
    std::cout << std::endl << "After erasing " << key;

    if (red_black_tree.empty())
    {
        std::cout << ", red_black_tree is empty." << std::endl;
    }
    {
        std::cout << ':';
        test_red_black_node(*red_black_tree.data());
    }

    test_tree_container(red_black_tree, values);
}

template <typename Tree, typename Values>
void test_red_black_tree()
{
    Tree red_black_tree;
    Values values;

    BOOST_CHECK(red_black_tree.empty());
    BOOST_CHECK(0 == red_black_tree.size());
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 2);
    test_insert(red_black_tree, values, 4);
    test_insert(red_black_tree, values, 3);
    test_erase(red_black_tree, values, 1);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, -2);
    test_insert(red_black_tree, values, -4);
    test_insert(red_black_tree, values, -3);
    test_erase(red_black_tree, values, -1);
    test_clear(red_black_tree, values);

    for (int i = 5; i < 10; ++i)
    {
        test_insert(red_black_tree, values, i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, i);
    }

    test_erase(red_black_tree, values, 5);
    test_clear(red_black_tree, values);

    for (int i = 5; i < 10; ++i)
    {
        test_insert(red_black_tree, values, -i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, -i);
    }

    test_erase(red_black_tree, values, -5);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, 13);
    test_insert(red_black_tree, values, 8);
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 6);
    test_insert(red_black_tree, values, 11);
    test_insert(red_black_tree, values, 17);
    test_insert(red_black_tree, values, 15);
    test_insert(red_black_tree, values, 22);
    test_insert(red_black_tree, values, 25);
    test_insert(red_black_tree, values, 28);

    Tree red_black_copy(red_black_tree);

    test_tree_container(red_black_copy, values);
    test_insert(red_black_copy, values, 26);
    test_insert(red_black_copy, values, 27);
    test_erase(red_black_copy, values, 15);
    test_value_insert(values, 15);
    values.erase(27);
    values.erase(26);
    test_insert(red_black_tree, values, 20);
    test_insert(red_black_tree, values, 21);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 11);
    red_black_copy = red_black_tree;
    test_value_insert(values, 11);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 15);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, -13);
    test_insert(red_black_tree, values, -8);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, -6);
    test_insert(red_black_tree, values, -11);
    test_insert(red_black_tree, values, -17);
    test_insert(red_black_tree, values, -15);
    test_insert(red_black_tree, values, -22);
    test_insert(red_black_tree, values, -25);
    test_insert(red_black_tree, values, -28);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_insert(red_black_copy, values, -26);
    test_insert(red_black_copy, values, -27);
    test_erase(red_black_copy, values, -15);
    test_value_insert(values, -15);
    values.erase(-27);
    values.erase(-26);
    test_insert(red_black_tree, values, -20);
    test_insert(red_black_tree, values, -21);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -11);
    red_black_copy = red_black_tree;
    test_value_insert(values, -11);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -15);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, 8);
    test_insert(red_black_tree, values, 4);
    test_insert(red_black_tree, values, 9);
    test_insert(red_black_tree, values, 2);
    test_insert(red_black_tree, values, 6);
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 3);
    test_insert(red_black_tree, values, 5);
    test_insert(red_black_tree, values, 7);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 9);
    test_erase(red_black_copy, values, 2);
    test_erase(red_black_copy, values, 3);
    test_erase(red_black_copy, values, 1);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, -8);
    test_insert(red_black_tree, values, -4);
    test_insert(red_black_tree, values, -9);
    test_insert(red_black_tree, values, -2);
    test_insert(red_black_tree, values, -6);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, -3);
    test_insert(red_black_tree, values, -5);
    test_insert(red_black_tree, values, -7);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -9);
    test_erase(red_black_copy, values, -2);
    test_erase(red_black_copy, values, -3);
    test_erase(red_black_copy, values, -1);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 10; ++i)
    {
        test_insert(red_black_tree, values, i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, i);
    }

    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 1);
    red_black_copy = red_black_tree;
    test_value_insert(values, 1);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 3);
    red_black_copy = red_black_tree;
    test_value_insert(values, 3);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 5);
    red_black_copy = red_black_tree;
    test_value_insert(values, 5);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 7);
    test_erase(red_black_copy, values, 6);
    test_erase(red_black_copy, values, 5);
    test_erase(red_black_copy, values, 8);
    test_erase(red_black_copy, values, 9);
    red_black_copy = red_black_tree;
    test_value_insert(values, 9);
    test_value_insert(values, 8);
    test_value_insert(values, 5);
    test_value_insert(values, 6);
    test_value_insert(values, 7);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 15);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 10; ++i)
    {
        test_insert(red_black_tree, values, -i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, -i);
    }

    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -1);
    red_black_copy = red_black_tree;
    test_value_insert(values, -1);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -3);
    red_black_copy = red_black_tree;
    test_value_insert(values, -3);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -5);
    red_black_copy = red_black_tree;
    test_value_insert(values, -5);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -7);
    test_erase(red_black_copy, values, -6);
    test_erase(red_black_copy, values, -5);
    test_erase(red_black_copy, values, -8);
    test_erase(red_black_copy, values, -9);
    red_black_copy = red_black_tree;
    test_value_insert(values, -9);
    test_value_insert(values, -8);
    test_value_insert(values, -5);
    test_value_insert(values, -6);
    test_value_insert(values, -7);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -15);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 16; ++i)
    {
        test_insert(red_black_tree, values, i);
    }

    test_erase(red_black_tree, values, 5);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 16; ++i)
    {
        test_insert(red_black_tree, values, -i);
    }

    test_erase(red_black_tree, values, -5);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, 0);
    test_insert(red_black_tree, values, -8);
    test_insert(red_black_tree, values, 8);
    test_insert(red_black_tree, values, -16);
    test_insert(red_black_tree, values, -4);
    test_insert(red_black_tree, values, 4);
    test_insert(red_black_tree, values, 16);
    test_insert(red_black_tree, values, -18);
    test_insert(red_black_tree, values, -12);
    test_insert(red_black_tree, values, -6);
    test_insert(red_black_tree, values, -2);
    test_insert(red_black_tree, values, 2);
    test_insert(red_black_tree, values, 6);
    test_insert(red_black_tree, values, 12);
    test_insert(red_black_tree, values, 18);
    test_insert(red_black_tree, values, -19);
    test_insert(red_black_tree, values, -17);
    test_insert(red_black_tree, values, -14);
    test_insert(red_black_tree, values, -10);
    test_insert(red_black_tree, values, -7);
    test_insert(red_black_tree, values, -5);
    test_insert(red_black_tree, values, -3);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 3);
    test_insert(red_black_tree, values, 5);
    test_insert(red_black_tree, values, 7);
    test_insert(red_black_tree, values, 10);
    test_insert(red_black_tree, values, 14);
    test_insert(red_black_tree, values, 17);
    test_insert(red_black_tree, values, 19);
    test_insert(red_black_tree, values, -15);
    test_insert(red_black_tree, values, -13);
    test_insert(red_black_tree, values, -11);
    test_insert(red_black_tree, values, -9);
    test_insert(red_black_tree, values, 9);
    test_insert(red_black_tree, values, 11);
    test_insert(red_black_tree, values, 13);
    test_insert(red_black_tree, values, 15);
    test_erase(red_black_tree, values, -19);
    test_erase(red_black_tree, values, -17);
    test_erase(red_black_tree, values, -7);
    test_erase(red_black_tree, values, -5);
    test_erase(red_black_tree, values, -3);
    test_erase(red_black_tree, values, -1);
    test_erase(red_black_tree, values, 1);
    test_erase(red_black_tree, values, 3);
    test_erase(red_black_tree, values, 5);
    test_erase(red_black_tree, values, 7);
    test_erase(red_black_tree, values, 17);
    test_erase(red_black_tree, values, 19);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 0);
    test_erase(red_black_copy, values, 2);
    test_value_insert(values, 2);
    test_value_insert(values, 0);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -2);
    test_erase(red_black_copy, values, 0);
}

typedef boost::tree_node::binode_set<
            AVLNodeGen
          , boost::int32_t
          , boost::default_ordering_selector
          , boost::tree_node::adelson_velskii_landis_balancer
        >
        AVLTreeSet;

void
    test_insert(
        AVLTreeSet& avl_tree
      , ValueSet& values
      , AVLTreeSet::key_type const& key
    )
{
    std::pair<AVLTreeSet::iterator,bool> p = avl_tree.insert(key);

    if (values.insert(key).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After inserting " << key << ':';
        test_avl_node(*avl_tree.data());
        BOOST_CHECK(*p.first == key);
        BOOST_CHECK(p.first == avl_tree.find(key));
        BOOST_CHECK(!avl_tree.empty());
        test_tree_container(avl_tree, values);
    }
    else
    {
        BOOST_CHECK(!p.second);
    }
}

void
    test_erase(
        AVLTreeSet& avl_tree
      , ValueSet& values
      , AVLTreeSet::key_type const& key
    )
{
    BOOST_CHECK(avl_tree.erase(key) == values.erase(key));
    std::cout << std::endl << "After erasing " << key;

    if (avl_tree.empty())
    {
        std::cout << ", avl_tree is empty." << std::endl;
    }
    else
    {
        std::cout << ':';
        test_avl_node(*avl_tree.data());
    }

    test_tree_container(avl_tree, values);
}

typedef boost::tree_node::binode_map<
            AVLNodeGen
          , boost::int32_t
          , boost::int32_t
          , boost::default_ordering_selector
          , boost::tree_node::adelson_velskii_landis_balancer
        >
        AVLTreeMap;

void
    test_insert(
        AVLTreeMap& avl_tree
      , ValueMap& values
      , AVLTreeMap::key_type const& key
    )
{
    std::pair<AVLTreeMap::iterator,bool> p = avl_tree.emplace(key, key);

    if (values.insert(ValueMap::value_type(key, key)).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After emplacing " << key << ':';
        test_avl_node(*avl_tree.data());
        BOOST_CHECK(p.first->first == key);
        BOOST_CHECK(p.first->second == key);
        BOOST_CHECK(p.first == avl_tree.find(key));
        BOOST_CHECK(!avl_tree.empty());
        test_tree_container(avl_tree, values);
    }
    else
    {
        BOOST_CHECK(!p.second);
    }
}

void
    test_erase(
        AVLTreeMap& avl_tree
      , ValueMap& values
      , AVLTreeMap::key_type const& key
    )
{
    BOOST_CHECK(avl_tree.erase(key) == values.erase(key));
    std::cout << std::endl << "After erasing " << key;

    if (avl_tree.empty())
    {
        std::cout << ", avl_tree is empty." << std::endl;
    }
    else
    {
        std::cout << ':';
        test_avl_node(*avl_tree.data());
    }

    test_tree_container(avl_tree, values);
}

template <typename Tree, typename Values>
void test_avl_tree()
{
    Tree avl_tree;
    Values values;

    BOOST_CHECK(avl_tree.empty());
    BOOST_CHECK(0 == avl_tree.size());

    test_insert(avl_tree, values, 13);
    test_insert(avl_tree, values, 8);
    test_insert(avl_tree, values, 1);
    test_insert(avl_tree, values, 6);
    test_insert(avl_tree, values, 11);
    test_insert(avl_tree, values, 17);
    test_insert(avl_tree, values, 15);
    test_insert(avl_tree, values, 22);
    test_insert(avl_tree, values, 25);
    test_insert(avl_tree, values, 27);
    test_insert(avl_tree, values, 20);
    test_insert(avl_tree, values, 21);
    test_erase(avl_tree, values, 1);
    test_erase(avl_tree, values, 11);
    test_erase(avl_tree, values, 15);
}

int test_main(int argc, char** argv)
{
    test_red_black_sequence();
    test_avl_sequence();
    test_red_black_tree<RedBlackTreeSet,ValueSet>();
    test_red_black_tree<RedBlackTreeMap,ValueMap>();
    test_avl_tree<AVLTreeSet,ValueSet>();
    test_avl_tree<AVLTreeMap,ValueMap>();
    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif


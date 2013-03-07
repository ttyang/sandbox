// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_CONTAINER_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_CONTAINER_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <utility>
#include <boost/utility/value_init.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/tree_node/key/data.hpp>
#include <boost/tree_node/key/red_black_flag.hpp>
#include <boost/tree_node/key/height.hpp>
#include <boost/tree_node/iterator/breadth_first.hpp>
#include <boost/tree_node/iterator/breadth_first_descendant.hpp>
#include <boost/tree_node/iterator/depth_first.hpp>

template <typename T1, typename T2>
void test_output_data(std::pair<T1,T2> const& p)
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

#endif  // LIBS_TREE_NODE_TEST_CONTAINER_FUNCTIONS_HPP_INCLUDED


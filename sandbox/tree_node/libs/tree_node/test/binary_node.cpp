// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TYPEOF_COMPLIANT

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <utility>
#include <boost/tuple/tuple.hpp>
#include <boost/assign/std/deque.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/tree_node/binary_node.hpp>
#include <boost/tree_node/with_count.hpp>
#include <boost/tree_node/with_height.hpp>
#include <boost/tree_node/with_position.hpp>
#include "../example/default_unconstruct_type.hpp"
#include "iterator_functions.hpp"

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/std/string.hpp>
#else
#include <string>
#endif
typedef std::string
        TestString;
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/boost/container/string.hpp>
#else
#include <boost/container/string.hpp>
#endif
typedef boost::container::string
        TestString;
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

typedef boost::tree_node::binary_node<default_unconstructible_example_type>
        DNode;
typedef boost::tree_node::with_height<
            boost::tree_node::with_count_gen<
                boost::tree_node::with_position_gen<
                    boost::tree_node::binary_node_gen
                >
            >
          , TestString
        >
        ANode;
typedef std::deque<std::size_t>
        SizeValues;
typedef std::deque<std::pair<boost::tree_node::traversal_state,std::size_t> >
        DFSizeValues;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<TestString,std::size_t,std::size_t>
        >::type
        StringValues;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::traversal_state
              , TestString
              , std::size_t
              , std::size_t
            >
        >::type
        DFStringValues;
typedef boost::emplace_function_gen<boost::dequeS>::type
        DFEmplacer;

int test_main(int argc, char** argv)
{
    using namespace boost::assign;

    DNode d_root(5);
    ANode a_root;

    BOOST_CHECK(
        !d_root.get_parent_ptr()
//      , "Parent member uninitialized."
    );
    BOOST_CHECK(
        a_root.get_data().empty()
//      , "Data member not default-constructed."
    );

    for (
        boost::tree_node::breadth_first_iterator<DNode> itr(d_root);
        itr;
        ++itr
    )
    {
        std::size_t const count = itr->get_data().number;

        if (1 < count)
        {
            DNode::iterator child_itr(itr->emplace_left(count - 2));
            DNode::const_pointer const_child(&*child_itr);

            BOOST_CHECK(
                (child_itr->get_parent_ptr() == &*itr)
//              , "Ctor not linking child to parent."
            );
            BOOST_CHECK(
                (itr->get_left_child_ptr() == &*child_itr)
//              , "Ctor not linking parent to child."
            );
            BOOST_CHECK(
                (child_itr->get_parent_ptr() == const_child->get_parent_ptr())
//              , "Why are these pointers different?"
            );

            child_itr = itr->emplace_right(count - 1);
            const_child = &*child_itr;

            BOOST_CHECK(
                (child_itr->get_parent_ptr() == &*itr)
//              , "Ctor not linking child to parent."
            );
            BOOST_CHECK(
                (itr->get_right_child_ptr() == &*child_itr)
//              , "Ctor not linking parent to child."
            );
            BOOST_CHECK(
                (child_itr->get_parent_ptr() == const_child->get_parent_ptr())
//              , "Why are these pointers different?"
            );
        }
    }

    {
        SizeValues bf_vals, pre_vals, post_vals, in_vals;
        DFSizeValues df_vals;

        bf_vals   += 5, 3, 4, 1, 2, 2, 3, 0, 1, 0, 1, 1, 2, 0, 1;
        pre_vals  += 5, 3, 1, 2, 0, 1, 4, 2, 0, 1, 3, 1, 2, 0, 1;
        post_vals += 1, 0, 1, 2, 3, 0, 1, 2, 1, 0, 1, 2, 3, 4, 5;
        in_vals   += 1, 3, 0, 2, 1, 5, 0, 2, 1, 4, 1, 3, 0, 2, 1;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::pre_order_traversal, 4)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::post_order_traversal, 4)
            (boost::tree_node::post_order_traversal, 5);
        test_node(
            d_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::false_()
        );
    }

    {
        DNode d_copy(d_root);
        boost::tree_node::breadth_first_iterator<DNode const>
            bf_root_itr(d_root), bf_copy_itr(d_copy);
        boost::tree_node::breadth_first_descendant_iterator<DNode const>
            bf_d_root_itr(d_root), bf_d_copy_itr(d_copy);
        boost::tree_node::pre_order_iterator<DNode const>
            pre_root_itr(d_root), pre_copy_itr(d_copy);
        boost::tree_node::pre_order_descendant_iterator<DNode const>
            pre_d_root_itr(d_root), pre_d_copy_itr(d_copy);
        boost::tree_node::post_order_iterator<DNode const>
            post_root_itr(d_root), post_copy_itr(d_copy);
        boost::tree_node::post_order_descendant_iterator<DNode const>
            post_d_root_itr(d_root), post_d_copy_itr(d_copy);
        boost::tree_node::in_order_iterator<DNode const>
            in_root_itr(d_root), in_copy_itr(d_copy);
        boost::tree_node::depth_first_iterator<DNode const>
            df_root_itr(d_root), df_copy_itr(d_copy);
        boost::tree_node::depth_first_descendant_iterator<DNode const>
            df_d_root_itr(d_root), df_d_copy_itr(d_copy);

        test_node_copies(bf_root_itr, bf_copy_itr);
        test_node_copies(bf_d_root_itr, bf_d_copy_itr);
        test_node_copies(pre_root_itr, pre_copy_itr);
        test_node_copies(pre_d_root_itr, pre_d_copy_itr);
        test_node_copies(post_root_itr, post_copy_itr);
        test_node_copies(post_d_root_itr, post_d_copy_itr);
        test_node_copies(in_root_itr, in_copy_itr);
        test_node_copies(df_root_itr, df_copy_itr);
        test_node_copies(df_d_root_itr, df_d_copy_itr);
    }

    {
        DNode::pointer p = d_root.get_left_child_ptr()->get_left_child_ptr();
        DNode::iterator p_child_itr = p->insert_left(d_root);
        SizeValues bf_vals, pre_vals, post_vals, in_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 3, 4, 1, 2, 2, 3, 5, 0, 1, 0, 1, 1, 2, 3, 4, 0, 1, 1
                    , 2, 2, 3, 0, 1, 0, 1, 1, 2, 0, 1;
        pre_vals   += 5, 3, 1, 5, 3, 1, 2, 0, 1, 4, 2, 0, 1, 3, 1, 2, 0, 1, 2
                    , 0, 1, 4, 2, 0, 1, 3, 1, 2, 0, 1;
        post_vals  += 1, 0, 1, 2, 3, 0, 1, 2, 1, 0, 1, 2, 3, 4, 5, 1, 0, 1, 2
                    , 3, 0, 1, 2, 1, 0, 1, 2, 3, 4, 5;
        in_vals    += 1, 3, 0, 2, 1, 5, 0, 2, 1, 4, 1, 3, 0, 2, 1, 1, 3, 0, 2
                    , 1, 5, 0, 2, 1, 4, 1, 3, 0, 2, 1;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 5)
                            (boost::tree_node::pre_order_traversal, 3)
                                (boost::tree_node::pre_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 1)
                                (boost::tree_node::pre_order_traversal, 2)
                                    (boost::tree_node::pre_order_traversal, 0)
                                    (boost::tree_node::post_order_traversal, 0)
                                    (boost::tree_node::pre_order_traversal, 1)
                                    (boost::tree_node::post_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 2)
                            (boost::tree_node::post_order_traversal, 3)
                            (boost::tree_node::pre_order_traversal, 4)
                                (boost::tree_node::pre_order_traversal, 2)
                                    (boost::tree_node::pre_order_traversal, 0)
                                    (boost::tree_node::post_order_traversal, 0)
                                    (boost::tree_node::pre_order_traversal, 1)
                                    (boost::tree_node::post_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 2)
                                (boost::tree_node::pre_order_traversal, 3)
                                    (boost::tree_node::pre_order_traversal, 1)
                                    (boost::tree_node::post_order_traversal, 1)
                                    (boost::tree_node::pre_order_traversal, 2)
                                    (boost::tree_node::pre_order_traversal, 0)
                                    (boost::tree_node::post_order_traversal, 0)
                                    (boost::tree_node::pre_order_traversal, 1)
                                    (boost::tree_node::post_order_traversal, 1)
                                    (boost::tree_node::post_order_traversal, 2)
                                (boost::tree_node::post_order_traversal, 3)
                            (boost::tree_node::post_order_traversal, 4)
                        (boost::tree_node::post_order_traversal, 5)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::pre_order_traversal, 4)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::post_order_traversal, 4)
            (boost::tree_node::post_order_traversal, 5);
        test_node(
            d_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::false_()
        );

        d_root = *p_child_itr;
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        in_vals.clear();
        df_vals.clear();
        bf_vals   += 5, 3, 4, 1, 2, 2, 3, 0, 1, 0, 1, 1, 2, 0, 1;
        pre_vals  += 5, 3, 1, 2, 0, 1, 4, 2, 0, 1, 3, 1, 2, 0, 1;
        post_vals += 1, 0, 1, 2, 3, 0, 1, 2, 1, 0, 1, 2, 3, 4, 5;
        in_vals   += 1, 3, 0, 2, 1, 5, 0, 2, 1, 4, 1, 3, 0, 2, 1;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::pre_order_traversal, 4)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::post_order_traversal, 4)
            (boost::tree_node::post_order_traversal, 5);
        test_node(
            d_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::false_()
        );
    }

    *(d_root.get_right_child_ptr()) = d_root;

    {
        SizeValues bf_vals, pre_vals, post_vals, in_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 3, 5, 1, 2, 3, 4, 0, 1, 1, 2, 2, 3, 0, 1, 0, 1, 1, 2
                    , 0, 1;
        pre_vals   += 5, 3, 1, 2, 0, 1, 5, 3, 1, 2, 0, 1, 4, 2, 0, 1, 3, 1, 2
                    , 0, 1;
        post_vals  += 1, 0, 1, 2, 3, 1, 0, 1, 2, 3, 0, 1, 2, 1, 0, 1, 2, 3, 4
                    , 5, 5;
        in_vals    += 1, 3, 0, 2, 1, 5, 1, 3, 0, 2, 1, 5, 0, 2, 1, 4, 1, 3, 0
                    , 2, 1;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::pre_order_traversal, 5)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 4)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 3)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::pre_order_traversal, 2)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::post_order_traversal, 3)
                    (boost::tree_node::post_order_traversal, 4)
                (boost::tree_node::post_order_traversal, 5)
            (boost::tree_node::post_order_traversal, 5);
        test_node(
            d_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::false_()
        );
    }

    d_root.get_right_child_ptr()->rotate_left();

    {
        SizeValues bf_vals, pre_vals, post_vals, in_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 3, 4, 1, 2, 5, 3, 0, 1, 3, 2, 1, 2, 1, 2, 0, 1, 0, 1
                    , 0, 1;
        pre_vals   += 5, 3, 1, 2, 0, 1, 4, 5, 3, 1, 2, 0, 1, 2, 0, 1, 3, 1, 2
                    , 0, 1;
        post_vals  += 1, 0, 1, 2, 3, 1, 0, 1, 2, 3, 0, 1, 2, 5, 1, 0, 1, 2, 3
                    , 4, 5;
        in_vals    += 1, 3, 0, 2, 1, 5, 1, 3, 0, 2, 1, 5, 0, 2, 1, 4, 1, 3, 0
                    , 2, 1;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::pre_order_traversal, 4)
                    (boost::tree_node::pre_order_traversal, 5)
                        (boost::tree_node::pre_order_traversal, 3)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::pre_order_traversal, 2)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::post_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 5)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::post_order_traversal, 4)
            (boost::tree_node::post_order_traversal, 5);
        test_node(
            d_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::false_()
        );
    }

    d_root.get_right_child_ptr()->rotate_right();

    {
        SizeValues bf_vals, pre_vals, post_vals, in_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 3, 5, 1, 2, 3, 4, 0, 1, 1, 2, 2, 3, 0, 1, 0, 1, 1, 2
                    , 0, 1;
        pre_vals   += 5, 3, 1, 2, 0, 1, 5, 3, 1, 2, 0, 1, 4, 2, 0, 1, 3, 1, 2
                    , 0, 1;
        post_vals  += 1, 0, 1, 2, 3, 1, 0, 1, 2, 3, 0, 1, 2, 1, 0, 1, 2, 3, 4
                    , 5, 5;
        in_vals    += 1, 3, 0, 2, 1, 5, 1, 3, 0, 2, 1, 5, 0, 2, 1, 4, 1, 3, 0
                    , 2, 1;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::post_order_traversal, 3)
                (boost::tree_node::pre_order_traversal, 5)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::post_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 4)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 3)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::pre_order_traversal, 2)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::post_order_traversal, 3)
                    (boost::tree_node::post_order_traversal, 4)
                (boost::tree_node::post_order_traversal, 5)
            (boost::tree_node::post_order_traversal, 5);
        test_node(
            d_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::false_()
        );
    }

    a_root.get_data() = "5";

    for (
        boost::tree_node::breadth_first_iterator<ANode> itr(a_root);
        itr;
        ++itr
    )
    {
        char digit = itr->get_data()[0];

        if ('1' < digit)
        {
            {
                ANode::iterator child_itr(itr->emplace_left());
                TestString& data = child_itr->get_data();

                BOOST_CHECK(
                    data.empty()
//                  , "Data member not default-constructed."
                );
                data += digit - 1;
                BOOST_CHECK(
                    (child_itr->get_parent_ptr() == &*itr)
//                  , "Ctor not linking child to parent."
                );
                BOOST_CHECK(
                    (itr->get_left_child_ptr() == &*child_itr)
//                  , "Ctor not linking parent to child."
                );
                BOOST_CHECK(
                    (child_itr->get_position() == child_itr)
//                  , "Position iterator incorrect."
                );
            }

            {
                ANode::iterator child_itr(itr->emplace_right());
                TestString& data = child_itr->get_data();

                BOOST_CHECK(
                    data.empty()
//                  , "Data member not default-constructed."
                );
                data += digit - 2;
                BOOST_CHECK(
                    (child_itr->get_parent_ptr() == &*itr)
//                  , "Ctor not linking child to parent."
                );
                BOOST_CHECK(
                    (itr->get_right_child_ptr() == &*child_itr)
//                  , "Ctor not linking parent to child."
                );
                BOOST_CHECK(
                    (child_itr->get_position() == child_itr)
//                  , "Position iterator incorrect."
                );
            }
        }
    }

    {
        StringValues bf_vals, pre_vals, post_vals, in_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 15)("4", 3, 9)("3", 2, 5)("3", 2, 5)("2", 1, 3)("2", 1, 3)
            ("1", 0, 1)("2", 1, 3)("1", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 15)("4", 3, 9)("3", 2, 5)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 5)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("3", 2, 5)("1", 0, 1)
            ("0", 0, 1)("2", 1, 3)("4", 3, 9)("1", 0, 1)("0", 0, 1)("2", 1, 3)
            ("1", 0, 1)("3", 2, 5)("5", 4, 15);
        emplacer[in_vals]
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("3", 2, 5)("1", 0, 1)("4", 3, 9)
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("5", 4, 15)("1", 0, 1)("2", 1, 3)
            ("0", 0, 1)("3", 2, 5)("1", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 15)
                (boost::tree_node::pre_order_traversal, "4", 3, 9)
                    (boost::tree_node::pre_order_traversal, "3", 2, 5)
                        (boost::tree_node::pre_order_traversal, "2", 1, 3)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 5)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                (boost::tree_node::post_order_traversal, "4", 3, 9)
                (boost::tree_node::pre_order_traversal, "3", 2, 5)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 5)
            (boost::tree_node::post_order_traversal, "5", 4, 15);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::true_()
        );
    }

    {
        ANode a_copy(a_root);
        boost::tree_node::breadth_first_iterator<ANode const>
            bf_root_itr(a_root), bf_copy_itr(a_copy);
        boost::tree_node::breadth_first_descendant_iterator<ANode const>
            bf_d_root_itr(a_root), bf_d_copy_itr(a_copy);
        boost::tree_node::pre_order_iterator<ANode const>
            pre_root_itr(a_root), pre_copy_itr(a_copy);
        boost::tree_node::pre_order_descendant_iterator<ANode const>
            pre_d_root_itr(a_root), pre_d_copy_itr(a_copy);
        boost::tree_node::post_order_iterator<ANode const>
            post_root_itr(a_root), post_copy_itr(a_copy);
        boost::tree_node::post_order_descendant_iterator<ANode const>
            post_d_root_itr(a_root), post_d_copy_itr(a_copy);
        boost::tree_node::in_order_iterator<ANode const>
            in_root_itr(a_root), in_copy_itr(a_copy);
        boost::tree_node::depth_first_iterator<ANode const>
            df_root_itr(a_root), df_copy_itr(a_copy);
        boost::tree_node::depth_first_descendant_iterator<ANode const>
            df_d_root_itr(a_root), df_d_copy_itr(a_copy);

        test_node_with_depth_copies(bf_root_itr, bf_copy_itr);
        test_node_with_depth_copies(bf_d_root_itr, bf_d_copy_itr);
        test_node_with_depth_copies(pre_root_itr, pre_copy_itr);
        test_node_with_depth_copies(pre_d_root_itr, pre_d_copy_itr);
        test_node_with_depth_copies(post_root_itr, post_copy_itr);
        test_node_with_depth_copies(post_d_root_itr, post_d_copy_itr);
        test_node_with_depth_copies(in_root_itr, in_copy_itr);
        test_node_with_depth_copies(df_root_itr, df_copy_itr);
        test_node_with_depth_copies(df_d_root_itr, df_d_copy_itr);
    }

    {
        ANode::pointer p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator p_child_itr(p->emplace_right());

        BOOST_CHECK(
            (p_child_itr->get_position() == p_child_itr)
//          , "Position iterator incorrect."
        );
        BOOST_CHECK(
            (p->begin() == p_child_itr)
//          , "Begin iterator incorrect."
        );
        p_child_itr->get_data().push_back('7');

        StringValues bf_vals, pre_vals, post_vals, in_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 16)("4", 3, 9)("3", 2, 6)("3", 2, 5)("2", 1, 3)("2", 1, 3)
            ("1", 1, 2)("2", 1, 3)("1", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("7", 0, 1)("1", 0, 1)("0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 16)("4", 3, 9)("3", 2, 5)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 1, 2)("7", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("3", 2, 5)("1", 0, 1)
            ("0", 0, 1)("2", 1, 3)("4", 3, 9)("1", 0, 1)("0", 0, 1)("2", 1, 3)
            ("7", 0, 1)("1", 1, 2)("3", 2, 6)("5", 4, 16);
        emplacer[in_vals]
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("3", 2, 5)("1", 0, 1)("4", 3, 9)
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("5", 4, 16)("1", 0, 1)("2", 1, 3)
            ("0", 0, 1)("3", 2, 6)("1", 1, 2)("7", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 16)
                (boost::tree_node::pre_order_traversal, "4", 3, 9)
                    (boost::tree_node::pre_order_traversal, "3", 2, 5)
                        (boost::tree_node::pre_order_traversal, "2", 1, 3)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 5)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                (boost::tree_node::post_order_traversal, "4", 3, 9)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 1, 2)
                        (boost::tree_node::pre_order_traversal, "7", 0, 1)
                        (boost::tree_node::post_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 1, 2)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
            (boost::tree_node::post_order_traversal, "5", 4, 16);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::true_()
        );
    }

    a_root.get_left_child_ptr()->rotate_right();

    {
        StringValues bf_vals, pre_vals, post_vals, in_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 16)("3", 3, 9)("3", 2, 6)("2", 1, 3)("4", 2, 5)("2", 1, 3)
            ("1", 1, 2)("1", 0, 1)("0", 0, 1)("1", 0, 1)("2", 1, 3)("1", 0, 1)
            ("0", 0, 1)("7", 0, 1)("1", 0, 1)("0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 16)("3", 3, 9)("2", 1, 3)("1", 0, 1)("0", 0, 1)("4", 2, 5)
            ("1", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 1, 2)("7", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("1", 0, 1)("0", 0, 1)
            ("2", 1, 3)("4", 2, 5)("3", 3, 9)("1", 0, 1)("0", 0, 1)("2", 1, 3)
            ("7", 0, 1)("1", 1, 2)("3", 2, 6)("5", 4, 16);
        emplacer[in_vals]
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("3", 3, 9)("1", 0, 1)("4", 2, 5)
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("5", 4, 16)("1", 0, 1)("2", 1, 3)
            ("0", 0, 1)("3", 2, 6)("1", 1, 2)("7", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 16)
                (boost::tree_node::pre_order_traversal, "3", 3, 9)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "4", 2, 5)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "2", 1, 3)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::post_order_traversal, "4", 2, 5)
                (boost::tree_node::post_order_traversal, "3", 3, 9)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 1, 2)
                        (boost::tree_node::pre_order_traversal, "7", 0, 1)
                        (boost::tree_node::post_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 1, 2)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
            (boost::tree_node::post_order_traversal, "5", 4, 16);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::true_()
        );
    }

    a_root.get_left_child_ptr()->rotate_left();

    {
        StringValues bf_vals, pre_vals, post_vals, in_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 16)("4", 3, 9)("3", 2, 6)("3", 2, 5)("2", 1, 3)("2", 1, 3)
            ("1", 1, 2)("2", 1, 3)("1", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("7", 0, 1)("1", 0, 1)("0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 16)("4", 3, 9)("3", 2, 5)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 1, 2)("7", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("3", 2, 5)("1", 0, 1)
            ("0", 0, 1)("2", 1, 3)("4", 3, 9)("1", 0, 1)("0", 0, 1)("2", 1, 3)
            ("7", 0, 1)("1", 1, 2)("3", 2, 6)("5", 4, 16);
        emplacer[in_vals]
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("3", 2, 5)("1", 0, 1)("4", 3, 9)
            ("1", 0, 1)("2", 1, 3)("0", 0, 1)("5", 4, 16)("1", 0, 1)("2", 1, 3)
            ("0", 0, 1)("3", 2, 6)("1", 1, 2)("7", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 16)
                (boost::tree_node::pre_order_traversal, "4", 3, 9)
                    (boost::tree_node::pre_order_traversal, "3", 2, 5)
                        (boost::tree_node::pre_order_traversal, "2", 1, 3)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 5)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                (boost::tree_node::post_order_traversal, "4", 3, 9)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 1, 2)
                        (boost::tree_node::pre_order_traversal, "7", 0, 1)
                        (boost::tree_node::post_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 1, 2)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
            (boost::tree_node::post_order_traversal, "5", 4, 16);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::true_()
        );
    }

    a_root.begin()->clear();

    {
        StringValues bf_vals, pre_vals, post_vals, in_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        emplacer[bf_vals]
            ("5", 3, 8)("4", 0, 1)("3", 2, 6)("2", 1, 3)("1", 1, 2)("1", 0, 1)
            ("0", 0, 1)("7", 0, 1);
        emplacer[pre_vals]
            ("5", 3, 8)("4", 0, 1)("3", 2, 6)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 1, 2)("7", 0, 1);
        emplacer[post_vals]
            ("4", 0, 1)("1", 0, 1)("0", 0, 1)("2", 1, 3)("7", 0, 1)("1", 1, 2)
            ("3", 2, 6)("5", 3, 8);
        emplacer[in_vals]
            ("4", 0, 1)("5", 3, 8)("1", 0, 1)("2", 1, 3)("0", 0, 1)("3", 2, 6)
            ("1", 1, 2)("7", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 3, 8)
                (boost::tree_node::pre_order_traversal, "4", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 1, 2)
                        (boost::tree_node::pre_order_traversal, "7", 0, 1)
                        (boost::tree_node::post_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 1, 2)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
            (boost::tree_node::post_order_traversal, "5", 3, 8);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
          , boost::mpl::true_()
        );
    }

    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif


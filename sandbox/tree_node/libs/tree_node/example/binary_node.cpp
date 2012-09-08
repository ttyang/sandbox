// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TYPEOF_COMPLIANT

#include <iostream>
#include <boost/assert.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tree_node/typeof/binary_node.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>
#include <boost/tree_node/typeof/breadth_first_iterator.hpp>
#include <boost/tree_node/typeof/pre_order_desc_iterator.hpp>
#include <boost/tree_node/typeof/post_order_iterator.hpp>
#include "default_unconstruct_type.hpp"
#include "show_functions.hpp"
#include "showcase_iterators.hpp"

typedef boost::tree_node::binary_node<default_unconstructible_example_type>
        DNode;
typedef boost::tree_node::with_height<
            boost::tree_node::with_count_gen<
                boost::tree_node::with_position_gen<
                    boost::tree_node::binary_node_gen
                >
            >
          , char*
        >
        ANode;

int main()
{
    DNode d_root(5);
    ANode a_root;

    BOOST_ASSERT_MSG(
        !d_root.get_parent_ptr()
      , "Parent member uninitialized."
    );
    BOOST_ASSERT_MSG(
        !a_root.get_data()
      , "Data member not default-constructed."
    );

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_breadth_first_iterator(d_root)
        );
        itr;
        ++itr
    )
    {
        std::size_t const count = itr->get_data().number;

        if (1 < count)
        {
            DNode::iterator child_itr(itr->emplace_left(count - 2));
            DNode::const_pointer const_child(&*child_itr);

            BOOST_ASSERT_MSG(
                (child_itr->get_parent_ptr() == &*itr)
              , "Ctor not linking child to parent."
            );
            BOOST_ASSERT_MSG(
                (itr->get_left_child_ptr() == &*child_itr)
              , "Ctor not linking parent to child."
            );
            BOOST_ASSERT_MSG(
                (child_itr->get_parent_ptr() == const_child->get_parent_ptr())
              , "Why are these pointers different?"
            );

            child_itr = itr->emplace_right(count - 1);
            const_child = &*child_itr;

            BOOST_ASSERT_MSG(
                (child_itr->get_parent_ptr() == &*itr)
              , "Ctor not linking child to parent."
            );
            BOOST_ASSERT_MSG(
                (itr->get_right_child_ptr() == &*child_itr)
              , "Ctor not linking parent to child."
            );
            BOOST_ASSERT_MSG(
                (child_itr->get_parent_ptr() == const_child->get_parent_ptr())
              , "Why are these pointers different?"
            );
        }
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_in_order_iterator(d_root, show_number<DNode>);
    showcase_iterators(d_root, show_number<DNode>, show_number_tree());

    {
        DNode::pointer p = d_root.get_left_child_ptr()->get_left_child_ptr();
        DNode::iterator p_child_itr = p->insert_left(d_root);

        std::cout << "After insert_left call," << std::endl;
        showcase_in_order_iterator(d_root, show_number<DNode>);
        showcase_iterators(d_root, show_number<DNode>, show_number_tree());

        d_root = *p_child_itr;
        std::cout << "After assignment to descendant," << std::endl;
        showcase_in_order_iterator(d_root, show_number<DNode>);
        showcase_iterators(d_root, show_number<DNode>, show_number_tree());
    }

    *(d_root.get_right_child_ptr()) = d_root;
    std::cout << "After assignment to ancestor," << std::endl;
    showcase_in_order_iterator(d_root, show_number<DNode>);
    showcase_iterators(d_root, show_number<DNode>, show_number_tree());

    d_root.get_right_child_ptr()->rotate_left();
    std::cout << "After rotate_left call," << std::endl;
    showcase_in_order_iterator(d_root, show_number<DNode>);
    showcase_iterators(d_root, show_number<DNode>, show_number_tree());

    {
        char* root_data = new char[2];

        root_data[0] = '5';
        root_data[1] = '\0';
        a_root.get_data() = root_data;
    }

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_breadth_first_iterator(a_root)
        );
        itr;
        ++itr
    )
    {
        char digit = itr->get_data()[0];

        if ('1' < digit)
        {
            {
                ANode::iterator child_itr(itr->emplace_left());
                char*& data = child_itr->get_data();

                BOOST_ASSERT_MSG(
                    !data
                  , "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = digit - 1;
                data[1] = '\0';
                BOOST_ASSERT_MSG(
                    (child_itr->get_parent_ptr() == &*itr)
                  , "Ctor not linking child to parent."
                );
                BOOST_ASSERT_MSG(
                    (itr->get_left_child_ptr() == &*child_itr)
                  , "Ctor not linking parent to child."
                );
                BOOST_ASSERT_MSG(
                    (child_itr->get_position() == child_itr)
                  , "Position iterator incorrect."
                );
            }

            {
                ANode::iterator child_itr(itr->emplace_right());
                char*& data = child_itr->get_data();

                BOOST_ASSERT_MSG(
                    !data
                  , "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = digit - 2;
                data[1] = '\0';
                BOOST_ASSERT_MSG(
                    (child_itr->get_parent_ptr() == &*itr)
                  , "Ctor not linking child to parent."
                );
                BOOST_ASSERT_MSG(
                    (itr->get_right_child_ptr() == &*child_itr)
                  , "Ctor not linking parent to child."
                );
                BOOST_ASSERT_MSG(
                    (child_itr->get_position() == child_itr)
                  , "Position iterator incorrect."
                );
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_in_order_iterator(a_root, show_data<ANode>);
    showcase_iterators(a_root, show_data<ANode>, show_data_tree());

    {
        ANode::pointer p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator p_child_itr(p->emplace_right());

        BOOST_ASSERT_MSG(
            (p_child_itr->get_position() == p_child_itr)
          , "Position iterator incorrect."
        );
        BOOST_ASSERT_MSG(
            (p->begin() == p_child_itr)
          , "Begin iterator incorrect."
        );
        p_child_itr->get_data() = new char[2];
        p_child_itr->get_data()[0] = '7';
        p_child_itr->get_data()[1] = '\0';
        std::cout << "After emplace_right call," << std::endl;
        showcase_in_order_iterator(a_root, show_data<ANode>);
        showcase_iterators(a_root, show_data<ANode>, show_data_tree());
    }

    a_root.get_left_child_ptr()->rotate_right();
    std::cout << "After rotate_right call," << std::endl;
    showcase_in_order_iterator(a_root, show_data<ANode>);
    showcase_iterators(a_root, show_data<ANode>, show_data_tree());

    a_root.get_left_child_ptr()->rotate_left();
    std::cout << "After rotate_left call," << std::endl;
    showcase_in_order_iterator(a_root, show_data<ANode>);
    showcase_iterators(a_root, show_data<ANode>, show_data_tree());

    {
        ANode::iterator leaf = a_root.begin();

        for (
            BOOST_AUTO(
                itr
              , boost::tree_node::make_pre_order_descendant_iterator(*leaf)
            );
            itr;
            ++itr
        )
        {
            delete[] itr->get_data();
        }

        leaf->clear();
        std::cout << "After clear call," << std::endl;
        showcase_in_order_iterator(a_root, show_data<ANode>);
        showcase_iterators(a_root, show_data<ANode>, show_data_tree());
    }

    for (
        BOOST_AUTO(itr, boost::tree_node::make_post_order_iterator(a_root));
        itr;
        ++itr
    )
    {
        delete[] itr->get_data();
    }

    return 0;
}


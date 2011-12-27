// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/assert.hpp>
#include <boost/tree_node/typeof.hpp>
#include "default_unconstruct_type.hpp"
#include "show_functions.hpp"
#include "showcase_iterators.hpp"

typedef boost::tree_node::binary_node<default_unconstructible_example_type>
        DNode;
typedef boost::tree_node::with_depth<
            boost::tree_node::with_position_gen<
                boost::tree_node::binary_node_gen
            >
          , char*
        >
        ANode;

int main()
{
    DNode d_root(create_instance(5));
    ANode a_root;

    BOOST_ASSERT(
        !d_root.get_parent_ptr()
     && "Parent member uninitialized."
    );
    BOOST_ASSERT(
        !a_root.get_data()
     && "Data member not default-constructed."
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
            DNode::iterator child_itr(
                itr->add_left_child(create_instance(count - 2))
            );
            DNode::const_pointer const_child(&*child_itr);

            BOOST_ASSERT(
                (child_itr->get_parent_ptr() == &*itr)
             && "Ctor not linking child to parent."
            );
            BOOST_ASSERT(
                (itr->get_left_child_ptr() == &*child_itr)
             && "Ctor not linking parent to child."
            );
            BOOST_ASSERT(
                (child_itr->get_parent_ptr() == const_child->get_parent_ptr())
             && "Why are these pointers different?"
            );

            child_itr = itr->add_right_child(create_instance(count - 1));
            const_child = &*child_itr;

            BOOST_ASSERT(
                (child_itr->get_parent_ptr() == &*itr)
             && "Ctor not linking child to parent."
            );
            BOOST_ASSERT(
                (itr->get_right_child_ptr() == &*child_itr)
             && "Ctor not linking parent to child."
            );
            BOOST_ASSERT(
                (child_itr->get_parent_ptr() == const_child->get_parent_ptr())
             && "Why are these pointers different?"
            );
        }
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_in_order_iterator(d_root, show_number<DNode>);
    showcase_iterators(d_root, show_number<DNode>, show_number_tree());

    {
        DNode::pointer p = d_root.get_left_child_ptr()->get_left_child_ptr();
        DNode::iterator p_child_itr = p->add_left_child_copy(d_root);

        std::cout << "After add_left_child_copy call," << std::endl;
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
                ANode::iterator child_itr(itr->add_left_child());
                char*& data = child_itr->get_data();

                BOOST_ASSERT(
                    !data
                 && "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = digit - 1;
                data[1] = '\0';
                BOOST_ASSERT(
                    (child_itr->get_parent_ptr() == &*itr)
                 && "Ctor not linking child to parent."
                );
                BOOST_ASSERT(
                    (itr->get_left_child_ptr() == &*child_itr)
                 && "Ctor not linking parent to child."
                );
                BOOST_ASSERT(
                    (child_itr->get_position() == child_itr)
                 && "Position iterator incorrect."
                );
            }

            {
                ANode::iterator child_itr(itr->add_right_child());
                char*& data = child_itr->get_data();

                BOOST_ASSERT(
                    !data
                 && "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = digit - 2;
                data[1] = '\0';
                BOOST_ASSERT(
                    (child_itr->get_parent_ptr() == &*itr)
                 && "Ctor not linking child to parent."
                );
                BOOST_ASSERT(
                    (itr->get_right_child_ptr() == &*child_itr)
                 && "Ctor not linking parent to child."
                );
                BOOST_ASSERT(
                    (child_itr->get_position() == child_itr)
                 && "Position iterator incorrect."
                );
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_in_order_iterator(a_root, show_data<ANode>);
    showcase_iterators(a_root, show_data<ANode>, show_data_tree());

    {
        ANode::pointer p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator p_child_itr(p->add_right_child());

        p_child_itr->get_data() = new char[2];
        p_child_itr->get_data()[0] = '7';
        p_child_itr->get_data()[1] = '\0';
        BOOST_ASSERT(
            (p_child_itr->get_position() == p_child_itr)
         && "Position iterator incorrect."
        );
        std::cout << "After add_right_child call," << std::endl;
        showcase_in_order_iterator(a_root, show_data<ANode>);
        showcase_iterators(a_root, show_data<ANode>, show_data_tree());
    }

    a_root.get_left_child_ptr()->rotate_right();
    std::cout << "After rotate_right call," << std::endl;
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


// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/assert.hpp>
#include <boost/tree_node/typeof.hpp>
#include "default_unconstructible_type.hpp"
#include "show_functions.hpp"
#include "showcase_iterators.hpp"

typedef boost::tree_node::raw_binary_node<default_unconstructible_example_type>
        DNode;
typedef boost::tree_node::with_depth<
            boost::tree_node::raw_binary_node_gen
          , char*
        >
        ANode;
typedef boost::tree_node::factory<ANode>
        ANodeFactory;

int main()
{
    DNode d_root(create_instance(5));
    ANode::pointer a_root(ANodeFactory::create());

    BOOST_ASSERT(
        !d_root.get_parent()
     && "Parent member uninitialized."
    );
    BOOST_ASSERT(
        !a_root->get_data()
     && "Data member not default-constructed."
    );

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_breadth_first_iterator(&d_root)
        );
        itr;
        ++itr
    )
    {
        std::size_t const count = (*itr)->get_data().number;

        if (1 < count)
        {
            DNode::pointer child(
                (*itr)->add_left_child(create_instance(count - 2))
            );
            DNode::const_pointer const_child(child);

            BOOST_ASSERT(
                (child->get_parent() == *itr)
             && "Ctor not linking child to parent."
            );
            BOOST_ASSERT(
                (child->get_parent() == const_child->get_parent())
             && "Why are these pointers different?"
            );

            child = (*itr)->add_right_child(create_instance(count - 1));
            const_child = child;

            BOOST_ASSERT(
                (child->get_parent() == *itr)
             && "Ctor not linking child to parent."
            );
            BOOST_ASSERT(
                (child->get_parent() == const_child->get_parent())
             && "Why are these pointers different?"
            );
        }
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_in_order_iterator(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
    );
    showcase_iterators(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
      , show_number_tree()
    );

    {
        DNode::pointer p = d_root.get_left_child()->get_left_child();
        DNode::pointer p_child = p->add_left_child_copy(&d_root);

        std::cout << "After add_left_child_copy call," << std::endl;
        showcase_in_order_iterator(
            DNode::const_pointer(&d_root)
          , show_number<DNode::const_pointer>
        );
        showcase_iterators(
            DNode::const_pointer(&d_root)
          , show_number<DNode::const_pointer>
          , show_number_tree()
        );

        d_root = *p_child;
        std::cout << "After assignment to descendant," << std::endl;
        showcase_in_order_iterator(
            DNode::const_pointer(&d_root)
          , show_number<DNode::const_pointer>
        );
        showcase_iterators(
            DNode::const_pointer(&d_root)
          , show_number<DNode::const_pointer>
          , show_number_tree()
        );
    }

    *(d_root.get_right_child()) = d_root;
    std::cout << "After assignment to ancestor," << std::endl;
    showcase_in_order_iterator(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
    );
    showcase_iterators(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
      , show_number_tree()
    );

    d_root.get_right_child()->rotate_left();
    std::cout << "After rotate_left call," << std::endl;
    showcase_in_order_iterator(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
    );
    showcase_iterators(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
      , show_number_tree()
    );

    {
        char* root_data = new char[2];

        root_data[0] = '5';
        root_data[1] = '\0';
        a_root->get_data() = root_data;
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
        char digit = (*itr)->get_data()[0];

        if ('1' < digit)
        {
            {
                ANode::pointer child((*itr)->add_left_child());
                char*& data = child->get_data();

                BOOST_ASSERT(
                    !data
                 && "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = digit - 1;
                data[1] = '\0';
                BOOST_ASSERT(
                    (child->get_parent() == *itr)
                 && "Ctor not linking child to parent."
                );
            }

            {
                ANode::pointer child((*itr)->add_right_child());
                char*& data = child->get_data();

                BOOST_ASSERT(
                    !data
                 && "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = digit - 2;
                data[1] = '\0';
                BOOST_ASSERT(
                    (child->get_parent() == *itr)
                 && "Ctor not linking child to parent."
                );
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_in_order_iterator(
        ANode::const_pointer(a_root)
      , show_data<ANode::const_pointer>
    );
    showcase_iterators(
        ANode::const_pointer(a_root)
      , show_data<ANode::const_pointer>
      , show_data_tree()
    );

    {
        ANode::pointer p = a_root->get_right_child()->get_right_child();
        ANode::pointer p_child = p->add_right_child();

        p_child->get_data() = new char[2];
        p_child->get_data()[0] = '7';
        p_child->get_data()[1] = '\0';
        std::cout << "After add_right_child call," << std::endl;
        showcase_in_order_iterator(
            ANode::const_pointer(a_root)
          , show_data<ANode::const_pointer>
        );
        showcase_iterators(
            ANode::const_pointer(a_root)
          , show_data<ANode::const_pointer>
          , show_data_tree()
        );
    }

    a_root->get_left_child()->rotate_right();
    std::cout << "After rotate_right call," << std::endl;
    showcase_in_order_iterator(
        ANode::const_pointer(a_root)
      , show_data<ANode::const_pointer>
    );
    showcase_iterators(
        ANode::const_pointer(a_root)
      , show_data<ANode::const_pointer>
      , show_data_tree()
    );

    {
        ANode::pointer leaf = *a_root->get_child_begin();

        for (
            BOOST_AUTO(
                itr
              , boost::tree_node::make_pre_order_descendant_iterator(leaf)
            );
            itr;
            ++itr
        )
        {
            delete[] (*itr)->get_data();
        }

        leaf->remove_all_children();
        std::cout << "After remove_all_children call," << std::endl;
        showcase_in_order_iterator(
            ANode::const_pointer(a_root)
          , show_data<ANode::const_pointer>
        );
        showcase_iterators(
            ANode::const_pointer(a_root)
          , show_data<ANode::const_pointer>
          , show_data_tree()
        );
    }

    for (
        BOOST_AUTO(itr, boost::tree_node::make_post_order_iterator(a_root));
        itr;
        ++itr
    )
    {
        delete[] (*itr)->get_data();
    }

    delete a_root;
    return 0;
}


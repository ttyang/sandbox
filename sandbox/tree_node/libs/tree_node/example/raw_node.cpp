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

typedef boost::tree_node::raw_node<default_unconstructible_example_type> DNode;
typedef boost::tree_node::raw_node<char*>                                ANode;

int main()
{
    DNode d_root(create_instance(5));
    ANode a_root;

    BOOST_ASSERT(
        !d_root.get_parent()
     && "Parent member uninitialized."
    );
    BOOST_ASSERT(
        !a_root.get_data()
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
            for (std::size_t i = 0; i < count; ++i)
            {
                DNode::pointer child((*itr)->add_child(create_instance(i)));
                DNode::const_pointer const_child(child);

                BOOST_ASSERT(
                    (child->get_parent() == *itr)
                 && "Ctor not linking child to parent."
                );
                BOOST_ASSERT(
                    (child == *((*itr)->get_child_begin() + i))
                 && "Ctor not linking parent to child."
                );
                BOOST_ASSERT(
                    (child->get_parent() == const_child->get_parent())
                 && "Why are these pointers different?"
                );
            }
        }
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_iterators(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
      , show_number_tree()
    );

    {
        DNode::pointer d_child = (
            *(d_root.get_child_begin() + 2)
        )->add_child_copy(&d_root);

        std::cout << "After add_child_copy call," << std::endl;
        showcase_iterators(
            DNode::const_pointer(&d_root)
          , show_number<DNode::const_pointer>
          , show_number_tree()
        );

        d_root = *d_child;
        std::cout << "After assignment to descendant," << std::endl;
        showcase_iterators(
            DNode::const_pointer(&d_root)
          , show_number<DNode::const_pointer>
          , show_number_tree()
        );
    }

    *(*(d_root.get_child_begin() + 4)) = d_root;
    std::cout << "After assignment to ancestor," << std::endl;
    showcase_iterators(
        DNode::const_pointer(&d_root)
      , show_number<DNode::const_pointer>
      , show_number_tree()
    );

    char* root_data = new char[2];

    root_data[0] = '5';
    root_data[1] = '\0';
    a_root.get_data() = root_data;

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_breadth_first_iterator(&a_root)
        );
        itr;
        ++itr
    )
    {
        char digit = (*itr)->get_data()[0];

        if ('1' < digit)
        {
            char numchar = digit;

            while (numchar != '0')
            {
                ANode::pointer child((*itr)->add_child());
                char*& data = child->get_data();

                BOOST_ASSERT(
                    !data
                 && "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = --numchar;
                data[1] = '\0';
                BOOST_ASSERT(
                    (child->get_parent() == *itr)
                 && "Ctor not linking child to parent."
                );
                BOOST_ASSERT(
                    (
                        child
                     == *((*itr)->get_child_begin() + (digit - (numchar + 1)))
                    )
                 && "Ctor not linking parent to child."
                );
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_iterators(
        ANode::const_pointer(&a_root)
      , show_data<ANode::const_pointer>
      , show_data_tree()
    );

    {
        ANode::pointer a_child(
            (*(a_root.get_child_begin() + 2))->add_child()
        );

        a_child->get_data() = new char[2];
        a_child->get_data()[0] = '7';
        a_child->get_data()[1] = '\0';
        std::cout << "After a_child construction," << std::endl;
        showcase_iterators(
            ANode::const_pointer(&a_root)
          , show_data<ANode::const_pointer>
          , show_data_tree()
        );
    }

    {
        ANode::pointer leaf = *a_root.get_child_begin();

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
        showcase_iterators(
            ANode::const_pointer(&a_root)
          , show_data<ANode::const_pointer>
          , show_data_tree()
        );
    }

    for (
        BOOST_AUTO(itr, boost::tree_node::make_post_order_iterator(&a_root));
        itr;
        ++itr
    )
    {
        delete[] (*itr)->get_data();
    }

    return 0;
}


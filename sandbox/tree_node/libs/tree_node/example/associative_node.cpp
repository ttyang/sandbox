// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/assert.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/tree_node/typeof.hpp>
#include "default_unconstruct_type.hpp"
#include "show_functions.hpp"
#include "showcase_desc_iterators.hpp"

typedef boost::tree_node::associative_node<
            char const*
          , default_unconstructible_example_type
          , boost::boost_multimapS
        >
        DNode;
typedef boost::tree_node::with_depth<
            boost::tree_node::with_position_gen<
                boost::tree_node::associative_node_gen<
                    boost::hash_multimapS
                >
            >
          , char const*
          , char*
        >
        ANode;

int main()
{
    char const* names[] = {"able", "baker", "charlie", "dog", "easy", "fox"};
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
            for (std::size_t i = 0; i < count; ++i)
            {
                for (std::size_t j = 0; j + i < count; ++j)
                {
                    DNode::iterator child_itr(
                        itr->add_child(names[j], create_instance(i))
                    );
                    DNode const& const_child(child_itr->second);

                    BOOST_ASSERT(
                        (child_itr->second.get_parent_ptr() == &*itr)
                         && "Ctor not linking child to parent."
                    );
                    BOOST_ASSERT(
                        (
                            child_itr->second.get_parent_ptr()
                         == const_child.get_parent_ptr()
                        )
                     && "Why are these pointers different?"
                    );
                }
            }
        }
    }

    {
        boost::tree_node::depth_first_iterate(d_root, show_number_tree());
        std::cout << std::endl;
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_descendant_iterators(
        d_root
      , show_key_and_number<char const*,DNode>
      , show_key_and_number_tree()
    );

    {
        DNode d_copy(d_root);
        BOOST_ASSERT((d_copy == d_root) && "Clones not equal.");
    }

    {
        DNode::iterator d_child_itr = d_root.find_child(
            names[2]
        )->second.add_child_copy(names[5], d_root);

        std::cout << "After add_child_copy call," << std::endl;
        showcase_descendant_iterators(
            d_root
          , show_key_and_number<char const*,DNode>
          , show_key_and_number_tree()
        );

        d_root = d_child_itr->second;
        std::cout << "After assignment to descendant," << std::endl;
        showcase_descendant_iterators(
            d_root
          , show_key_and_number<char const*,DNode>
          , show_key_and_number_tree()
        );
    }

    d_root.find_child(names[4])->second = d_root;
    std::cout << "After assignment to ancestor," << std::endl;
    showcase_descendant_iterators(
        d_root
      , show_key_and_number<char const*,DNode>
      , show_key_and_number_tree()
    );

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
            char numchar = digit;

            while (numchar != '0')
            {
                --numchar;

                for (char j = 0; numchar + j < digit; ++j)
                {
                    ANode::iterator child_itr(itr->add_child(names[j]));
                    char*& data = child_itr->second.get_data();

                    BOOST_ASSERT(
                        !data
                     && "Data member not default-constructed."
                    );
                    data = new char[2];
                    data[0] = numchar;
                    data[1] = '\0';
                    BOOST_ASSERT(
                        (child_itr->second.get_parent_ptr() == &*itr)
                     && "Ctor not linking child to parent."
                    );
                    BOOST_ASSERT(
                        (child_itr->second.get_position() == child_itr)
                     && "Position iterator incorrect."
                    );
                }
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_descendant_iterators(
        a_root
      , show_key_and_data<char const*,ANode>
      , show_key_and_data_tree()
    );

    {
        ANode::iterator a_child_itr(
            a_root.find_child(names[2])->second.add_child(names[5])
        );
        ANode& a_child(a_child_itr->second);

        a_child.get_data() = new char[2];
        a_child.get_data()[0] = '7';
        a_child.get_data()[1] = '\0';
        BOOST_ASSERT(
            (a_child.get_position() == a_child_itr)
         && "Position iterator incorrect."
        );
        std::cout << "After a_child construction," << std::endl;
        showcase_descendant_iterators(
            a_root
          , show_key_and_data<char const*,ANode>
          , show_key_and_data_tree()
        );
    }

    {
        ANode& to_be_pruned = a_root.begin()->second;
        ANode::iterator c_itr, c_end;

        for (
            ::std::tr1::tie(c_itr, c_end) = to_be_pruned.find_children(
                names[1]
            );
            c_itr != c_end;
            ++c_itr
        )
        {
            for (
                BOOST_AUTO(
                    itr
                  , boost::tree_node::make_pre_order_iterator(c_itr->second)
                );
                itr;
                ++itr
            )
            {
                delete[] itr->get_data();
            }
        }

        to_be_pruned.remove_children(names[1]);
        std::cout << "After remove_children call," << std::endl;
        showcase_descendant_iterators(
            a_root
          , show_key_and_data<char const*,ANode>
          , show_key_and_data_tree()
        );
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


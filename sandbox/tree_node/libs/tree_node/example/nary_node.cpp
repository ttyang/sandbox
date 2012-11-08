// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TYPEOF_COMPLIANT

#include <iostream>
#include <iterator>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/container_gen/selectors_typeof.hpp>
#include <boost/tree_node/typeof/nary_node.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>
#include <boost/tree_node/typeof/breadth_first_iterator.hpp>
#include <boost/tree_node/typeof/pre_order_desc_iterator.hpp>
#include <boost/tree_node/typeof/post_order_iterator.hpp>
#include "default_unconstruct_type.hpp"
#include "show_functions.hpp"
#include "showcase_iterators.hpp"

template <typename Selector>
void example()
{
    typedef boost::tree_node::nary_node<
                default_unconstructible_example_type
              , Selector
            >
            DNode;
    typedef boost::tree_node::with_height<
                boost::tree_node::with_count_gen<
                    boost::tree_node::with_position_gen<
                        boost::tree_node::nary_node_gen<Selector>
                    >
                >
              , char*
            >
            ANode;

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
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_breadth_first_iterator(d_root)
        );
        itr;
        ++itr
    )
    {
        std::size_t const count = (*itr).get_data().number;

        if (1 < count)
        {
            for (std::size_t i = 0; i < count; ++i)
            {
                typename DNode::iterator child_itr((*itr).emplace(i));
                typename DNode::const_pointer const_child(&*child_itr);

                BOOST_ASSERT_MSG(
                    ((*child_itr).get_parent_ptr() == &*itr)
                  , "Ctor not linking child to parent."
                );
                BOOST_ASSERT_MSG(
                    (
                        (*child_itr).get_parent_ptr()
                     == const_child->get_parent_ptr()
                    )
                  , "Why are these pointers different?"
                );

                {
                    typename DNode::iterator c_itr((*itr).begin());

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                    if (!std::tr1::is_same<Selector,boost::slistS>::value)
#endif
                    std::advance(c_itr, i);
                    BOOST_ASSERT_MSG(
                        (&*child_itr == &*c_itr)
                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_iterators(d_root, show_number<DNode>, show_number_tree());

    {
        DNode d_copy(d_root);

        std::cout << "After d_copy construction," << std::endl;
        showcase_iterators(d_copy, show_number<DNode>, show_number_tree());
    }

    {
        typename DNode::iterator d_child(
            (*(++(++d_root.begin()))).insert(d_root)
        );

        std::cout << "After insert call," << std::endl;
        showcase_iterators(d_root, show_number<DNode>, show_number_tree());

        d_root = *d_child;
        std::cout << "After assignment to descendant," << std::endl;
        showcase_iterators(d_root, show_number<DNode>, show_number_tree());
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    if (!std::tr1::is_same<Selector,boost::slistS>::value)
        *(d_root.begin()) = d_root;
    else
#endif
    *(++(++(++(++d_root.begin())))) = d_root;
    std::cout << "After assignment to ancestor," << std::endl;
    showcase_iterators(d_root, show_number<DNode>, show_number_tree());

    {
        char* root_data = new char[2];

        root_data[0] = '5';
        root_data[1] = '\0';
        a_root.get_data() = root_data;
    }

    for (
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_breadth_first_iterator(a_root)
        );
        itr;
        ++itr
    )
    {
        char digit = (*itr).get_data()[0];

        if ('1' < digit)
        {
            char numchar = digit;

            while (numchar != '0')
            {
                typename ANode::iterator child_itr((*itr).insert(ANode()));
                char*& data = (*child_itr).get_data();

                BOOST_ASSERT_MSG(
                    !data
                  , "Data member not default-constructed."
                );
                data = new char[2];
                data[0] = --numchar;
                data[1] = '\0';
                BOOST_ASSERT_MSG(
                    ((*child_itr).get_parent_ptr() == &*itr)
                  , "Ctor not linking child to parent."
                );
                BOOST_ASSERT_MSG(
                    ((*child_itr).get_position() == child_itr)
                  , "Position iterator incorrect."
                );

                {
                    typename ANode::iterator c_itr = (*itr).begin();

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                    if (!std::tr1::is_same<Selector,boost::slistS>::value)
#endif
                    std::advance(c_itr, digit - (numchar + 1));
                    BOOST_ASSERT_MSG(
                        (child_itr == c_itr)
                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_iterators(a_root, show_data<ANode>, show_data_tree());

    {
        typename ANode::iterator a_child_itr(
            (*(++(++a_root.begin()))).emplace()
        );

        (*a_child_itr).get_data() = new char[2];
        (*a_child_itr).get_data()[0] = '7';
        (*a_child_itr).get_data()[1] = '\0';
        BOOST_ASSERT_MSG(
            ((*a_child_itr).get_position() == a_child_itr)
          , "Position iterator incorrect."
        );
        std::cout << "After emplace call," << std::endl;
        showcase_iterators(a_root, show_data<ANode>, show_data_tree());
    }

    {
        typename ANode::iterator leaf = a_root.begin();

        for (
            BOOST_AUTO_TPL(
                itr
              , boost::tree_node::make_pre_order_descendant_iterator(*leaf)
            );
            itr;
            ++itr
        )
        {
            delete[] (*itr).get_data();
        }

        (*leaf).clear();
        std::cout << "After clear call," << std::endl;
        showcase_iterators(a_root, show_data<ANode>, show_data_tree());
    }

    for (
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_post_order_iterator(a_root)
        );
        itr;
        ++itr
    )
    {
        delete[] (*itr).get_data();
    }
}

#if defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors_typeof.hpp>
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/ptr_container/ptr_vector.hpp>
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/container/slist.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#else  // !defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors.hpp>
#endif  // BOOST_TYPEOF_EMULATION

int main()
{
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    example<boost::ptr_vecS>();
#else
    example<boost::slistS>();
#endif
    return 0;
}


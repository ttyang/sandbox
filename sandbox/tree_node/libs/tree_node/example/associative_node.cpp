// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TYPEOF_COMPLIANT

#include <iostream>
#include <cstring>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tree_node/typeof/associative_node.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>
#include <boost/tree_node/typeof/breadth_first_iterator.hpp>
#include <boost/tree_node/typeof/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/typeof/pre_order_iterator.hpp>
#include <boost/tree_node/typeof/post_order_iterator.hpp>
#include <boost/tree_node/typeof/depth_first_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include "default_unconstruct_type.hpp"
#include "show_functions.hpp"
#include "showcase_assoc_iterators.hpp"
#include "match_predicate.hpp"

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/std/string.hpp>
#else
#include <string>
#endif
typedef std::string TestString;
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/boost/container/string.hpp>
#else
#include <boost/container/string.hpp>
#endif
typedef boost::container::string TestString;
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template <typename USelector, typename MSelector>
void example()
{
    typedef boost::tree_node::associative_node<
                char const*
              , default_unconstructible_example_type
              , USelector
            >
            DNode;
    typedef boost::tree_node::with_height<
                boost::tree_node::with_count_gen<
                    boost::tree_node::with_position_gen<
                        boost::tree_node::associative_node_gen<MSelector>
                    >
                >
              , char const*
              , TestString
            >
            ANode;

    char const* names[] = {"able", "baker", "charlie", "dog", "easy", "fox"};
    DNode d_root(5);
    ANode a_root;

    BOOST_ASSERT_MSG(
        !d_root.get_parent_ptr()
      , "Parent member uninitialized."
    );
    BOOST_ASSERT_MSG(
        a_root.get_data().empty()
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
        std::size_t const count = itr->get_data().number;

        if (1 < count)
        {
            for (std::size_t i = 0; i < count; ++i)
            {
                for (std::size_t j = 0; j + i < count; ++j)
                {
                    typename DNode::iterator find_itr(itr->find(names[j]));
                    bool not_found = find_itr == itr->end();
                    typename DNode::iterator child_itr(
                        itr->emplace(names[j], i)
                    );
                    DNode& child(
                        boost::tree_node::dereference_iterator(child_itr)
                    );
                    DNode const& const_child(child);

                    if (not_found)
                    {
                        BOOST_ASSERT_MSG(
                            (child.get_parent_ptr() == &*itr)
                          , "Ctor not linking child to parent."
                        );
                        BOOST_ASSERT_MSG(
                            (
                                child.get_parent_ptr()
                             == const_child.get_parent_ptr()
                            )
                          , "Why are these pointers different?"
                        );
                    }
                    else
                    {
                        BOOST_ASSERT_MSG(
                            (find_itr->first == child_itr->first)
                          , "Keys do not match."
                        );
                        BOOST_ASSERT_MSG(
                            (
                                boost::tree_node::dereference_iterator(
                                    find_itr
                                ).get_data()
                             == const_child.get_data()
                            )
                          , "Ctor not linking parent to child."
                        );
                    }
                }
            }
        }
    }

    std::cout << "After d_root tree construction," << std::endl;
    showcase_associative_iterators(
        d_root
      , show_number<DNode>
      , show_number_tree()
      , show_key_and_number<char const*,DNode>
      , show_key_and_number_tree()
    );

    {
        DNode d_copy(d_root);

        std::cout << "After d_copy construction," << std::endl;
        showcase_associative_iterators(
            d_copy
          , show_number<DNode>
          , show_number_tree()
          , show_key_and_number<char const*,DNode>
          , show_key_and_number_tree()
        );
    }

    {
        typename DNode::iterator d_child_itr(
            boost::tree_node::dereference_iterator(
                d_root.find(names[2])
            ).insert(names[5], d_root)
        );

        std::cout << "After insert call," << std::endl;
        showcase_associative_iterators(
            d_root
          , show_number<DNode>
          , show_number_tree()
          , show_key_and_number<char const*,DNode>
          , show_key_and_number_tree()
        );

        boost::tree_node::dereference_iterator(d_child_itr) = d_root;
        std::cout << "After assignment to ancestor," << std::endl;
        showcase_associative_iterators(
            d_root
          , show_number<DNode>
          , show_number_tree()
          , show_key_and_number<char const*,DNode>
          , show_key_and_number_tree()
        );
    }

    d_root = boost::tree_node::dereference_iterator(d_root.find(names[4]));
    std::cout << "After assignment to descendant," << std::endl;
    showcase_associative_iterators(
        d_root
      , show_number<DNode>
      , show_number_tree()
      , show_key_and_number<char const*,DNode>
      , show_key_and_number_tree()
    );

    a_root.get_data() = "5";

    for (
        BOOST_AUTO_TPL(
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
                    typename ANode::iterator child_itr(itr->emplace(names[j]));
                    typename ANode::traits::iterator_range c_range(
                        itr->equal_range(names[j])
                    );
                    ANode& child(
                        boost::tree_node::dereference_iterator(child_itr)
                    );
                    TestString& data = child.get_data();

                    BOOST_ASSERT_MSG(
                        data.empty()
                      , "Data member not default-constructed."
                    );
                    data += numchar;
                    BOOST_ASSERT_MSG(
                        (child.get_parent_ptr() == &*itr)
                      , "Ctor not linking child to parent."
                    );
                    BOOST_ASSERT_MSG(
                        (child.get_position() == child_itr)
                      , "Position iterator incorrect."
                    );
                    BOOST_ASSERT_MSG(
                        (
                            boost::range::find_if(
                                c_range
                              , example_match_predicate<ANode,MSelector>(
                                    child_itr
                                )
                            )
                         != boost::end(c_range)
                        )
                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    std::cout << "After a_root tree construction," << std::endl;
    showcase_associative_iterators(
        a_root
      , show_data<ANode>
      , show_data_tree()
      , show_key_and_data<char const*,ANode>
      , show_key_and_data_tree()
    );

    {
        ANode a_copy(a_root);
        std::cout << "After copy construction," << std::endl;
        showcase_associative_iterators(
            a_copy
          , show_data<ANode>
          , show_data_tree()
          , show_key_and_data<char const*,ANode>
          , show_key_and_data_tree()
        );
    }

    {
        typename ANode::iterator a_child_itr(
            boost::tree_node::dereference_iterator(
                a_root.find(names[2])
            ).emplace(names[5])
        );
        ANode& a_child(boost::tree_node::dereference_iterator(a_child_itr));

        BOOST_ASSERT_MSG(
            (a_child.get_position() == a_child_itr)
          , "Position iterator incorrect."
        );
        a_child.get_data().push_back('7');
        std::cout << "After emplace call," << std::endl;
        showcase_associative_iterators(
            a_root
          , show_data<ANode>
          , show_data_tree()
          , show_key_and_data<char const*,ANode>
          , show_key_and_data_tree()
        );

        a_child = a_root;
        std::cout << "After assignment to ancestor," << std::endl;
        showcase_associative_iterators(
            a_root
          , show_data<ANode>
          , show_data_tree()
          , show_key_and_data<char const*,ANode>
          , show_key_and_data_tree()
        );

        a_root = a_child;
        std::cout << "After assignment to descendant," << std::endl;
        showcase_associative_iterators(
            a_root
          , show_data<ANode>
          , show_data_tree()
          , show_key_and_data<char const*,ANode>
          , show_key_and_data_tree()
        );
    }

    std::cout << "After " << boost::tree_node::dereference_iterator(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || defined LIBS_TREE_NODE_EXAMPLE_ASSOCIATIVE_NODE_USE_FLAT_MAP
        a_root.begin()
#else
        a_root.find(names[0])
#endif
    ).erase(names[1]) << " nodes erased with their descendants," << std::endl;
    showcase_associative_iterators(
        a_root
      , show_data<ANode>
      , show_data_tree()
      , show_key_and_data<char const*,ANode>
      , show_key_and_data_tree()
    );
}

#if defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors_typeof.hpp>
#include <boost/container_gen/c_str_cmp_selectors_typeof.hpp>
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/ptr_container/ptr_map.hpp>
#elif defined LIBS_TREE_NODE_EXAMPLE_ASSOCIATIVE_NODE_USE_FLAT_MAP
#include <boost/typeof/boost/container/flat_map.hpp>
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/std/tr1/unordered_map.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#else  // !defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/c_str_cmp_selectors.hpp>
#endif  // BOOST_TYPEOF_EMULATION

int main()
{
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    example<
        boost::ptr_map_selector<boost::c_str_ordering_selector>
      , boost::ptr_multimap_selector<boost::c_str_ordering_selector>
    >();
#elif defined LIBS_TREE_NODE_EXAMPLE_ASSOCIATIVE_NODE_USE_FLAT_MAP
    example<
        boost::flat_map_selector<boost::c_str_ordering_selector>
      , boost::flat_multimap_selector<boost::c_str_ordering_selector>
    >();
#else
    example<
        boost::hash_map_selector<
            boost::mpl::true_
          , boost::tr1_hash_selector
          , boost::c_str_equivalence_selector
        >
      , boost::hash_multimap_selector<
            boost::mpl::true_
          , boost::tr1_hash_selector
          , boost::c_str_equivalence_selector
        >
    >();
#endif

    return 0;
}


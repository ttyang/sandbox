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
#include <boost/container_gen/selectors_typeof.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/tree_node/nary_node.hpp>
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

template <typename Selector>
void test()
{
    using namespace boost::assign;

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
              , TestString
            >
            ANode;

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
            for (std::size_t i = 0; i < count; ++i)
            {
                typename DNode::iterator child_itr(itr->emplace(i));
                typename DNode::const_pointer const_child(&*child_itr);

                BOOST_CHECK(
                    (child_itr->get_parent_ptr() == &*itr)
//                  , "Ctor not linking child to parent."
                );
                BOOST_CHECK(
                    (
                        child_itr->get_parent_ptr()
                     == const_child->get_parent_ptr()
                    )
//                  , "Why are these pointers different?"
                );

                {
                    typename DNode::iterator c_itr = itr->begin();

                    std::advance(c_itr, i);
                    BOOST_CHECK(
                        (&*child_itr == &*c_itr)
//                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    {
        SizeValues bf_vals, pre_vals, post_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 0, 1, 2, 3, 4, 0, 1, 0, 1, 2, 0, 1, 2, 3, 0, 1, 0, 1
                    , 0, 1, 2, 0, 1;
        pre_vals   += 5, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1, 4, 0, 1, 2, 0, 1, 3
                    , 0, 1, 2, 0, 1;
        post_vals  += 0, 1, 0, 1, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1, 2, 0, 1, 0
                    , 1, 2, 3, 4, 5;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::pre_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
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
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
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
        test_node_copies(df_root_itr, df_copy_itr);
        test_node_copies(df_d_root_itr, df_d_copy_itr);
    }

    {
        typename DNode::iterator d_ins_itr(d_root.begin());
        std::advance(d_ins_itr, 2);
        typename DNode::iterator d_child_itr(d_ins_itr->insert(d_root));
        SizeValues bf_vals, pre_vals, post_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 0, 1, 2, 3, 4, 0, 1, 5, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2
                    , 3, 4, 0, 1, 0, 1, 0, 1, 2, 0, 1, 0, 1, 2, 0, 1, 2, 3, 0
                    , 1, 0, 1, 0, 1, 0, 1, 2, 0, 1;
        pre_vals   += 5, 0, 1, 2, 0, 1, 5, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1, 4
                    , 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1, 4, 0
                    , 1, 2, 0, 1, 3, 0, 1, 2, 0, 1;
        post_vals  += 0, 1, 0, 1, 0, 1, 0, 1, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1
                    , 2, 0, 1, 0, 1, 2, 3, 4, 5, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0
                    , 1, 2, 0, 1, 0, 1, 2, 3, 4, 5;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::pre_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 5)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 3)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
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
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::pre_order_traversal, 2)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 1)
                                (boost::tree_node::post_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 3)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
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
                (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
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
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
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
          , df_vals
          , boost::mpl::false_()
        );

        d_root = *d_child_itr;
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        df_vals.clear();
        bf_vals    += 5, 0, 1, 2, 3, 4, 0, 1, 0, 1, 2, 0, 1, 2, 3, 0, 1, 0, 1
                    , 0, 1, 2, 0, 1;
        pre_vals   += 5, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1, 4, 0, 1, 2, 0, 1, 3
                    , 0, 1, 2, 0, 1;
        post_vals  += 0, 1, 0, 1, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1, 2, 0, 1, 0
                    , 1, 2, 3, 4, 5;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::pre_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
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
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
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
          , df_vals
          , boost::mpl::false_()
        );
    }

    {
        typename DNode::iterator d_itr(d_root.begin());

        std::advance(d_itr, 4);
        *d_itr = d_root;
    }

    {
        SizeValues bf_vals, pre_vals, post_vals;
        DFSizeValues df_vals;

        bf_vals    += 5, 0, 1, 2, 3, 5, 0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 0, 1, 0
                    , 1, 0, 1, 2, 0, 1, 2, 3, 0, 1, 0, 1, 0, 1, 2, 0, 1;
        pre_vals   += 5, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1, 5, 0, 1, 2, 0, 1, 3
                    , 0, 1, 2, 0, 1, 4, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 1;
        post_vals  += 0, 1, 0, 1, 2, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1, 2, 0, 1, 0
                    , 1, 2, 3, 0, 1, 0, 1, 2, 0, 1, 0, 1, 2, 3, 4, 5, 5;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::pre_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                (boost::tree_node::post_order_traversal, 2)
                (boost::tree_node::pre_order_traversal, 3)
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
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
                    (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::pre_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                    (boost::tree_node::post_order_traversal, 2)
                    (boost::tree_node::pre_order_traversal, 3)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
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
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::pre_order_traversal, 2)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 1)
                            (boost::tree_node::post_order_traversal, 1)
                        (boost::tree_node::post_order_traversal, 2)
                        (boost::tree_node::pre_order_traversal, 3)
                            (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 0)
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
            char numchar = digit;

            while (numchar != '0')
            {
                typename ANode::iterator child_itr(itr->emplace());
                TestString& data = child_itr->get_data();

                BOOST_CHECK(
                    data.empty()
//                  , "Data member not default-constructed."
                );
                BOOST_CHECK(
                    (child_itr->get_parent_ptr() == &*itr)
//                  , "Ctor not linking child to parent."
                );
                BOOST_CHECK(
                    (child_itr->get_position() == child_itr)
//                  , "Position iterator incorrect."
                );
                data.push_back(--numchar);

                {
                    typename ANode::iterator c_itr = itr->begin();

                    std::advance(c_itr, digit - (numchar + 1));
                    BOOST_CHECK(
                        (child_itr == c_itr)
//                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    {
        StringValues bf_vals, pre_vals, post_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        boost::assign::push_back(bf_vals)
            ("5", 4, 24)("4", 3, 12)("3", 2, 6)("2", 1, 3)("1", 0, 1)
            ("0", 0, 1)("3", 2, 6)("2", 1, 3)("1", 0, 1)("0", 0, 1)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1);
        boost::assign::push_back(pre_vals)
            ("5", 4, 24)("4", 3, 12)("3", 2, 6)("2", 1, 3)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("3", 2, 6)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1);
        boost::assign::push_back(post_vals)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("4", 3, 12)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("5", 4, 24);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 24)
                (boost::tree_node::pre_order_traversal, "4", 3, 12)
                    (boost::tree_node::pre_order_traversal, "3", 2, 6)
                        (boost::tree_node::pre_order_traversal, "2", 1, 3)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 12)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
                (boost::tree_node::pre_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 3)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 4, 24);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
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
        test_node_with_depth_copies(df_root_itr, df_copy_itr);
        test_node_with_depth_copies(df_d_root_itr, df_d_copy_itr);
    }

    {
        typename ANode::iterator a_ins_itr(a_root.begin());
        std::advance(a_ins_itr, 2);
        typename ANode::iterator a_child_itr(a_ins_itr->emplace());

        BOOST_CHECK(
            (a_child_itr->get_position() == a_child_itr)
//          , "Position iterator incorrect."
        );
        a_child_itr->get_data().push_back('7');

        StringValues bf_vals, pre_vals, post_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        boost::assign::push_back(bf_vals)
            ("5", 4, 25)("4", 3, 12)("3", 2, 6)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("3", 2, 6)("2", 1, 3)("1", 0, 1)("0", 0, 1)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("7", 0, 1)("2", 1, 3)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1);
        boost::assign::push_back(pre_vals)
            ("5", 4, 25)("4", 3, 12)("3", 2, 6)("2", 1, 3)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("3", 2, 6)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("7", 0, 1)
            ("1", 0, 1)("0", 0, 1);
        boost::assign::push_back(post_vals)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("4", 3, 12)
            ("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)("3", 2, 6)
            ("1", 0, 1)("0", 0, 1)("7", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("5", 4, 25);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 25)
                (boost::tree_node::pre_order_traversal, "4", 3, 12)
                    (boost::tree_node::pre_order_traversal, "3", 2, 6)
                        (boost::tree_node::pre_order_traversal, "2", 1, 3)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 12)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "7", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 4, 25);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , df_vals
          , boost::mpl::true_()
        );
    }

    a_root.begin()->clear();

    {
        StringValues bf_vals, pre_vals, post_vals;
        DFStringValues df_vals;
        DFEmplacer emplacer;

        boost::assign::push_back(bf_vals)
            ("5", 3, 14)("4", 0, 1)("3", 2, 6)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("2", 1, 3)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("7", 0, 1)
            ("1", 0, 1)("0", 0, 1);
        boost::assign::push_back(pre_vals)
            ("5", 3, 14)("4", 0, 1)("3", 2, 6)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("7", 0, 1)
            ("1", 0, 1)("0", 0, 1);
        boost::assign::push_back(post_vals)
            ("4", 0, 1)("1", 0, 1)("0", 0, 1)("2", 1, 3)("1", 0, 1)("0", 0, 1)
            ("3", 2, 6)("1", 0, 1)("0", 0, 1)("7", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("5", 3, 14);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 3, 14)
                (boost::tree_node::pre_order_traversal, "4", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 6)
                    (boost::tree_node::pre_order_traversal, "2", 1, 3)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 3)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 6)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "7", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 3, 14);
        test_node(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , df_vals
          , boost::mpl::true_()
        );
    }
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/boost/ptr_container/ptr_vector.hpp>
#include <boost/typeof/boost/ptr_container/ptr_deque.hpp>
#include <boost/typeof/boost/ptr_container/ptr_list.hpp>
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/container/vector.hpp>
#include <boost/typeof/boost/container/stable_vector.hpp>
#include <boost/typeof/boost/container/deque.hpp>
#include <boost/typeof/boost/container/list.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#endif  // BOOST_TYPEOF_EMULATION

int test_main(int argc, char** argv)
{
    test<boost::ptr_vecS>();
    test<boost::ptr_dequeS>();
    test<boost::ptr_listS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test<boost::vector_selector<boost::mpl::true_> >();
    test<boost::stable_vecS>();
    test<boost::deque_selector<boost::mpl::true_> >();
    test<boost::list_selector<boost::mpl::true_> >();
#endif

    return 0;
}


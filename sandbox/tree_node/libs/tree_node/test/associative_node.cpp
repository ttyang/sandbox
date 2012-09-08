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
#include <cstring>
#include <boost/tuple/tuple.hpp>
#include <boost/assign/std/deque.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/tree_node/typeof/associative_node.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>
#include "../example/default_unconstruct_type.hpp"
#include "../example/match_predicate.hpp"
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
        Sizes;
typedef std::deque<std::pair<char const*,std::size_t> >
        KeySizes;
typedef std::deque<std::pair<boost::tree_node::traversal_state,std::size_t> >
        DFSizes;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::traversal_state
              , char const*
              , std::size_t
            >
        >::type
        DFKeySizes;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<TestString,std::size_t,std::size_t>
        >::type
        Strings;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                char const*
              , TestString
              , std::size_t
              , std::size_t
            >
        >::type
        KeyStrings;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::traversal_state
              , TestString
              , std::size_t
              , std::size_t
            >
        >::type
        DFStrings;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::traversal_state
              , char const*
              , TestString
              , std::size_t
              , std::size_t
            >
        >::type
        DFKeyStrings;
typedef boost::emplace_function_gen<boost::dequeS>::type
        Emplacer;

template <typename USelector, typename MSelector>
void test()
{
    using namespace boost::assign;

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
                        BOOST_CHECK(
                            (child.get_parent_ptr() == &*itr)
//                          , "Ctor not linking child to parent."
                        );
                        BOOST_CHECK(
                            (
                                child.get_parent_ptr()
                             == const_child.get_parent_ptr()
                            )
//                          , "Why are these pointers different?"
                        );
                    }
                    else
                    {
                        BOOST_CHECK(
                            (find_itr->first == child_itr->first)
//                          , "Keys do not match."
                        );
                        BOOST_CHECK(
                            (
                                boost::tree_node::dereference_iterator(
                                    find_itr
                                ).get_data()
                             == const_child.get_data()
                            )
//                          , "Ctor not linking parent to child."
                        );
                    }
                }
            }
        }
    }

    {
        Sizes bf_vals, pre_vals, post_vals;
        KeySizes bf_d_vals, pre_d_vals, post_d_vals;
        DFSizes df_vals;
        DFKeySizes df_d_vals;
        Emplacer emplacer;

        bf_vals    += 5, 0, 0, 0, 0, 0;
        boost::assign::push_back(bf_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("dog", 0)("easy", 0);
        pre_vals   += 5, 0, 0, 0, 0, 0;
        boost::assign::push_back(pre_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("dog", 0)("easy", 0);
        post_vals  += 0, 0, 0, 0, 0, 5;
        boost::assign::push_back(post_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("dog", 0)("easy", 0);
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
            (boost::tree_node::post_order_traversal, 5);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0)
            (boost::tree_node::post_order_traversal, "able", 0)
            (boost::tree_node::pre_order_traversal, "baker", 0)
            (boost::tree_node::post_order_traversal, "baker", 0)
            (boost::tree_node::pre_order_traversal, "charlie", 0)
            (boost::tree_node::post_order_traversal, "charlie", 0)
            (boost::tree_node::pre_order_traversal, "dog", 0)
            (boost::tree_node::post_order_traversal, "dog", 0)
            (boost::tree_node::pre_order_traversal, "easy", 0)
            (boost::tree_node::post_order_traversal, "easy", 0);
        test_associative_node(
            d_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
          , boost::mpl::false_()
        );
    }

    {
        typename DNode::iterator d_child_itr(
            boost::tree_node::dereference_iterator(
                d_root.find(names[2])
            ).insert(names[5], d_root)
        );
        Sizes bf_vals, pre_vals, post_vals;
        KeySizes bf_d_vals, pre_d_vals, post_d_vals;
        DFSizes df_vals;
        DFKeySizes df_d_vals;
        Emplacer emplacer;

        bf_vals    += 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0;
        boost::assign::push_back(bf_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("dog", 0)("easy", 0)
            ("fox", 5)("able", 0)("baker", 0)("charlie", 0)("dog", 0)
            ("easy", 0);
        pre_vals   += 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0;
        boost::assign::push_back(pre_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("fox", 5)("able", 0)
            ("baker", 0)("charlie", 0)("dog", 0)("easy", 0)("dog", 0)
            ("easy", 0);
        post_vals  += 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5;
        boost::assign::push_back(post_d_vals)
            ("able", 0)("baker", 0)("able", 0)("baker", 0)("charlie", 0)
            ("dog", 0)("easy", 0)("fox", 5)("charlie", 0)("dog", 0)("easy", 0);
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 5)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 5)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
            (boost::tree_node::post_order_traversal, 5);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0)
            (boost::tree_node::post_order_traversal, "able", 0)
            (boost::tree_node::pre_order_traversal, "baker", 0)
            (boost::tree_node::post_order_traversal, "baker", 0)
            (boost::tree_node::pre_order_traversal, "charlie", 0)
                (boost::tree_node::pre_order_traversal, "fox", 5)
                    (boost::tree_node::pre_order_traversal, "able", 0)
                    (boost::tree_node::post_order_traversal, "able", 0)
                    (boost::tree_node::pre_order_traversal, "baker", 0)
                    (boost::tree_node::post_order_traversal, "baker", 0)
                    (boost::tree_node::pre_order_traversal, "charlie", 0)
                    (boost::tree_node::post_order_traversal, "charlie", 0)
                    (boost::tree_node::pre_order_traversal, "dog", 0)
                    (boost::tree_node::post_order_traversal, "dog", 0)
                    (boost::tree_node::pre_order_traversal, "easy", 0)
                    (boost::tree_node::post_order_traversal, "easy", 0)
                (boost::tree_node::post_order_traversal, "fox", 5)
            (boost::tree_node::post_order_traversal, "charlie", 0)
            (boost::tree_node::pre_order_traversal, "dog", 0)
            (boost::tree_node::post_order_traversal, "dog", 0)
            (boost::tree_node::pre_order_traversal, "easy", 0)
            (boost::tree_node::post_order_traversal, "easy", 0);
        test_associative_node(
            d_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
          , boost::mpl::false_()
        );

        boost::tree_node::dereference_iterator(d_child_itr) = d_root;
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();
        bf_vals    += 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0;
        boost::assign::push_back(bf_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("dog", 0)("easy", 0)
            ("fox", 5)("able", 0)("baker", 0)("charlie", 0)("dog", 0)
            ("easy", 0)("fox", 5)("able", 0)("baker", 0)("charlie", 0)
            ("dog", 0)("easy", 0);
        pre_vals   += 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        boost::assign::push_back(pre_d_vals)
            ("able", 0)("baker", 0)("charlie", 0)("fox", 5)("able", 0)
            ("baker", 0)("charlie", 0)("fox", 5)("able", 0)("baker", 0)
            ("charlie", 0)("dog", 0)("easy", 0)("dog", 0)("easy", 0)("dog", 0)
            ("easy", 0);
        post_vals  += 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5;
        boost::assign::push_back(post_d_vals)
            ("able", 0)("baker", 0)("able", 0)("baker", 0)("able", 0)
            ("baker", 0)("charlie", 0)("dog", 0)("easy", 0)("fox", 5)
            ("charlie", 0)("dog", 0)("easy", 0)("fox", 5)("charlie", 0)
            ("dog", 0)("easy", 0);
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 5)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                    (boost::tree_node::pre_order_traversal, 5)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                            (boost::tree_node::pre_order_traversal, 5)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                                (boost::tree_node::pre_order_traversal, 0)
                                (boost::tree_node::post_order_traversal, 0)
                            (boost::tree_node::post_order_traversal, 5)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                        (boost::tree_node::pre_order_traversal, 0)
                        (boost::tree_node::post_order_traversal, 0)
                    (boost::tree_node::post_order_traversal, 5)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
                (boost::tree_node::pre_order_traversal, 0)
                (boost::tree_node::post_order_traversal, 0)
            (boost::tree_node::post_order_traversal, 5);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0)
            (boost::tree_node::post_order_traversal, "able", 0)
            (boost::tree_node::pre_order_traversal, "baker", 0)
            (boost::tree_node::post_order_traversal, "baker", 0)
            (boost::tree_node::pre_order_traversal, "charlie", 0)
                (boost::tree_node::pre_order_traversal, "fox", 5)
                    (boost::tree_node::pre_order_traversal, "able", 0)
                    (boost::tree_node::post_order_traversal, "able", 0)
                    (boost::tree_node::pre_order_traversal, "baker", 0)
                    (boost::tree_node::post_order_traversal, "baker", 0)
                    (boost::tree_node::pre_order_traversal, "charlie", 0)
                        (boost::tree_node::pre_order_traversal, "fox", 5)
                            (boost::tree_node::pre_order_traversal, "able", 0)
                            (boost::tree_node::post_order_traversal, "able", 0)
                            (boost::tree_node::pre_order_traversal, "baker", 0)
                            (boost::tree_node::post_order_traversal, "baker", 0)
                            (boost::tree_node::pre_order_traversal, "charlie", 0)
                            (boost::tree_node::post_order_traversal, "charlie", 0)
                            (boost::tree_node::pre_order_traversal, "dog", 0)
                            (boost::tree_node::post_order_traversal, "dog", 0)
                            (boost::tree_node::pre_order_traversal, "easy", 0)
                            (boost::tree_node::post_order_traversal, "easy", 0)
                        (boost::tree_node::post_order_traversal, "fox", 5)
                    (boost::tree_node::post_order_traversal, "charlie", 0)
                    (boost::tree_node::pre_order_traversal, "dog", 0)
                    (boost::tree_node::post_order_traversal, "dog", 0)
                    (boost::tree_node::pre_order_traversal, "easy", 0)
                    (boost::tree_node::post_order_traversal, "easy", 0)
                (boost::tree_node::post_order_traversal, "fox", 5)
            (boost::tree_node::post_order_traversal, "charlie", 0)
            (boost::tree_node::pre_order_traversal, "dog", 0)
            (boost::tree_node::post_order_traversal, "dog", 0)
            (boost::tree_node::pre_order_traversal, "easy", 0)
            (boost::tree_node::post_order_traversal, "easy", 0);
        test_associative_node(
            d_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
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
        test_associative_node_copies(bf_d_root_itr, bf_d_copy_itr);
        test_node_copies(pre_root_itr, pre_copy_itr);
        test_associative_node_copies(pre_d_root_itr, pre_d_copy_itr);
        test_node_copies(post_root_itr, post_copy_itr);
        test_associative_node_copies(post_d_root_itr, post_d_copy_itr);
        test_node_copies(df_root_itr, df_copy_itr);
        test_associative_node_copies(df_d_root_itr, df_d_copy_itr);
    }

    d_root = boost::tree_node::dereference_iterator(d_root.find(names[4]));

    {
        Sizes bf_vals, pre_vals, post_vals;
        KeySizes bf_d_vals, pre_d_vals, post_d_vals;
        DFSizes df_vals;
        DFKeySizes df_d_vals;

        bf_vals    += 0;
        pre_vals   += 0;
        post_vals  += 0;
        boost::assign::push_back(df_vals)
            (boost::tree_node::pre_order_traversal, 0)
            (boost::tree_node::post_order_traversal, 0);
        test_associative_node(
            d_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
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

                    BOOST_CHECK(
                        data.empty()
//                      , "Data member not default-constructed."
                    );
                    data += numchar;
                    BOOST_CHECK(
                        (child.get_parent_ptr() == &*itr)
//                      , "Ctor not linking child to parent."
                    );
                    BOOST_CHECK(
                        (child.get_position() == child_itr)
//                      , "Position iterator incorrect."
                    );
                    BOOST_CHECK(
                        (
                            boost::range::find_if(
                                c_range
                              , example_match_predicate<ANode,MSelector>(
                                    child_itr
                                )
                            )
                         != boost::end(c_range)
                        )
//                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    {
        Strings bf_vals, pre_vals, post_vals;
        KeyStrings bf_d_vals, pre_d_vals, post_d_vals;
        DFStrings df_vals;
        DFKeyStrings df_d_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 68)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[bf_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "3", 2, 10)
            ("baker", "2", 1, 4)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "2", 1, 4)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "1", 0, 1)("dog", "0", 0, 1)("easy", "0", 0, 1)
            ("able", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 68)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[pre_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "1", 0, 1)("dog", "0", 0, 1)
            ("easy", "0", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("4", 3, 26)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("5", 4, 68);
        emplacer[post_d_vals]
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "4", 3, 26)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "3", 2, 10)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 1, 4)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "1", 0, 1)("dog", "0", 0, 1)
            ("easy", "0", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 68)
                (boost::tree_node::pre_order_traversal, "4", 3, 26)
                    (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 4, 68);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "4", 3, 26)
            (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "easy", "0", 0, 1);
        test_associative_node(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
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
        test_assoc_node_with_depth_copies(bf_d_root_itr, bf_d_copy_itr);
        test_node_with_depth_copies(pre_root_itr, pre_copy_itr);
        test_assoc_node_with_depth_copies(pre_d_root_itr, pre_d_copy_itr);
        test_node_with_depth_copies(post_root_itr, post_copy_itr);
        test_assoc_node_with_depth_copies(post_d_root_itr, post_d_copy_itr);
        test_node_with_depth_copies(df_root_itr, df_copy_itr);
        test_assoc_node_with_depth_copies(df_d_root_itr, df_d_copy_itr);
    }

    {
        typename ANode::iterator a_child_itr(
            boost::tree_node::dereference_iterator(
                a_root.find(names[2])
            ).emplace(names[5])
        );
        ANode& a_child(boost::tree_node::dereference_iterator(a_child_itr));

        BOOST_CHECK(
            (a_child.get_position() == a_child_itr)
//          , "Position iterator incorrect."
        );
        a_child.get_data().push_back('7');

        Strings bf_vals, pre_vals, post_vals;
        KeyStrings bf_d_vals, pre_d_vals, post_d_vals;
        DFStrings df_vals;
        DFKeyStrings df_d_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 69)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 5)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("7", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[bf_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "3", 2, 10)
            ("baker", "2", 1, 4)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "2", 1, 5)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "1", 0, 1)("dog", "0", 0, 1)("easy", "0", 0, 1)
            ("able", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "7", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 69)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("2", 1, 5)("1", 0, 1)("0", 0, 1)("0", 0, 1)("7", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[pre_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 1, 5)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("fox", "7", 0, 1)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("4", 3, 26)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("7", 0, 1)("2", 1, 5)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("5", 4, 69);
        emplacer[post_d_vals]
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "4", 3, 26)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "3", 2, 10)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "7", 0, 1)("charlie", "2", 1, 5)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 69)
                (boost::tree_node::pre_order_traversal, "4", 3, 26)
                    (boost::tree_node::pre_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "2", 1, 5)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "7", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 4, 69);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "4", 3, 26)
            (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "fox", "7", 0, 1)
                (boost::tree_node::post_order_traversal, "fox", "7", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "2", 1, 5)
            (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "easy", "0", 0, 1);
        test_associative_node(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
          , boost::mpl::true_()
        );

        a_child = a_root;
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();
        emplacer[bf_vals]
            ("5", 6, 137)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("2", 5, 73)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("5", 4, 69)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("4", 3, 26)("3", 2, 10)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("2", 1, 5)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("7", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1);
        emplacer[bf_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "3", 2, 10)
            ("baker", "2", 1, 4)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "2", 5, 73)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "1", 0, 1)("dog", "0", 0, 1)("easy", "0", 0, 1)
            ("able", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "5", 4, 69)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "4", 3, 26)
            ("able", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "3", 2, 10)("baker", "2", 1, 4)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "2", 1, 5)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "2", 1, 4)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("fox", "7", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1);
        emplacer[pre_vals]
            ("5", 6, 137)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("2", 5, 73)("1", 0, 1)("0", 0, 1)("0", 0, 1)("5", 4, 69)
            ("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("2", 1, 5)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("7", 0, 1)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1);
        emplacer[pre_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 5, 73)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("fox", "5", 4, 69)
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 1, 5)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("fox", "7", 0, 1)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "1", 0, 1)("dog", "0", 0, 1)
            ("easy", "0", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("4", 3, 26)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("4", 3, 26)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("3", 2, 10)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("7", 0, 1)("2", 1, 5)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("5", 4, 69)("2", 5, 73)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("5", 6, 137);
        emplacer[post_d_vals]
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "4", 3, 26)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "3", 2, 10)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "3", 2, 10)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "2", 1, 4)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "4", 3, 26)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "3", 2, 10)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "2", 1, 4)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("fox", "7", 0, 1)
            ("charlie", "2", 1, 5)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "1", 0, 1)("dog", "0", 0, 1)("easy", "0", 0, 1)
            ("fox", "5", 4, 69)("charlie", "2", 5, 73)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "1", 0, 1)("dog", "0", 0, 1)
            ("easy", "0", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 6, 137)
                (boost::tree_node::pre_order_traversal, "4", 3, 26)
                    (boost::tree_node::pre_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "2", 5, 73)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "5", 4, 69)
                        (boost::tree_node::pre_order_traversal, "4", 3, 26)
                        (boost::tree_node::pre_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "4", 3, 26)
                        (boost::tree_node::pre_order_traversal, "3", 2, 10)
                            (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "3", 2, 10)
                            (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "2", 1, 5)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "7", 0, 1)
                            (boost::tree_node::post_order_traversal, "7", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 5)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "5", 4, 69)
                (boost::tree_node::post_order_traversal, "2", 5, 73)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 6, 137);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "4", 3, 26)
            (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "2", 5, 73)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "fox", "5", 4, 69)
                (boost::tree_node::pre_order_traversal, "able", "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "fox", "7", 0, 1)
                (boost::tree_node::post_order_traversal, "fox", "7", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "easy", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "easy", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "fox", "5", 4, 69)
            (boost::tree_node::post_order_traversal, "charlie", "2", 5, 73)
            (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "easy", "0", 0, 1);
        test_associative_node(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
          , boost::mpl::true_()
        );

        a_root = a_child;
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();
        emplacer[bf_vals]
            ("5", 4, 69)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 5)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("7", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[bf_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "3", 2, 10)
            ("baker", "2", 1, 4)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "2", 1, 5)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "1", 0, 1)("dog", "0", 0, 1)("easy", "0", 0, 1)
            ("able", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "7", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 69)("4", 3, 26)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("2", 1, 5)("1", 0, 1)("0", 0, 1)("0", 0, 1)("7", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[pre_d_vals]
            ("able", "4", 3, 26)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 1, 5)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("fox", "7", 0, 1)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("4", 3, 26)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("7", 0, 1)("2", 1, 5)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("5", 4, 69);
        emplacer[post_d_vals]
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "4", 3, 26)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "3", 2, 10)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "7", 0, 1)("charlie", "2", 1, 5)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 69)
                (boost::tree_node::pre_order_traversal, "4", 3, 26)
                    (boost::tree_node::pre_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "2", 1, 5)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "7", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 4, 69);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", "4", 3, 26)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "4", 3, 26)
            (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "fox", "7", 0, 1)
                (boost::tree_node::post_order_traversal, "fox", "7", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "2", 1, 5)
            (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "easy", "0", 0, 1);
        test_associative_node(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
          , boost::mpl::true_()
        );
    }

    BOOST_CHECK(
        boost::tree_node::dereference_iterator(a_root.begin()).erase(
            names[1]
        ) == 3
    );

    {
        Strings bf_vals, pre_vals, post_vals;
        KeyStrings bf_d_vals, pre_d_vals, post_d_vals;
        DFStrings df_vals;
        DFKeyStrings df_d_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            ("5", 4, 63)("4", 3, 20)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)("2", 1, 5)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("7", 0, 1)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[bf_d_vals]
            ("able", "4", 3, 20)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "3", 2, 10)
            ("baker", "2", 1, 4)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "2", 1, 5)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "1", 0, 1)("dog", "0", 0, 1)("easy", "0", 0, 1)
            ("able", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "7", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1);
        emplacer[pre_vals]
            ("5", 4, 63)("4", 3, 20)("3", 2, 10)("2", 1, 4)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("3", 2, 10)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)
            ("2", 1, 4)("1", 0, 1)("0", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("2", 1, 5)("1", 0, 1)("0", 0, 1)("0", 0, 1)("7", 0, 1)("1", 0, 1)
            ("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1);
        emplacer[pre_d_vals]
            ("able", "4", 3, 20)("able", "3", 2, 10)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("charlie", "1", 0, 1)
            ("charlie", "0", 0, 1)("dog", "0", 0, 1)("able", "3", 2, 10)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "1", 0, 1)("baker", "0", 0, 1)
            ("charlie", "0", 0, 1)("baker", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "2", 1, 5)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("fox", "7", 0, 1)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1);
        emplacer[post_vals]
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("4", 3, 20)("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)
            ("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)
            ("1", 0, 1)("0", 0, 1)("0", 0, 1)("3", 2, 10)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("2", 1, 4)("1", 0, 1)("0", 0, 1)("1", 0, 1)("0", 0, 1)
            ("0", 0, 1)("7", 0, 1)("2", 1, 5)("1", 0, 1)("0", 0, 1)("1", 0, 1)
            ("0", 0, 1)("0", 0, 1)("5", 4, 63);
        emplacer[post_d_vals]
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("able", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("able", "2", 1, 4)("able", "1", 0, 1)
            ("able", "0", 0, 1)("charlie", "1", 0, 1)("charlie", "0", 0, 1)
            ("dog", "0", 0, 1)("able", "4", 3, 20)("able", "1", 0, 1)
            ("able", "0", 0, 1)("baker", "0", 0, 1)("able", "2", 1, 4)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("charlie", "0", 0, 1)("able", "3", 2, 10)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("able", "1", 0, 1)("able", "0", 0, 1)("baker", "0", 0, 1)
            ("able", "2", 1, 4)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "1", 0, 1)("baker", "0", 0, 1)("charlie", "0", 0, 1)
            ("baker", "3", 2, 10)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("baker", "2", 1, 4)("baker", "1", 0, 1)
            ("baker", "0", 0, 1)("able", "1", 0, 1)("able", "0", 0, 1)
            ("baker", "0", 0, 1)("fox", "7", 0, 1)("charlie", "2", 1, 5)
            ("charlie", "1", 0, 1)("charlie", "0", 0, 1)("dog", "1", 0, 1)
            ("dog", "0", 0, 1)("easy", "0", 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, "5", 4, 63)
                (boost::tree_node::pre_order_traversal, "4", 3, 20)
                    (boost::tree_node::pre_order_traversal, "3", 2, 10)
                        (boost::tree_node::pre_order_traversal, "2", 1, 4)
                            (boost::tree_node::pre_order_traversal, "1", 0, 1)
                            (boost::tree_node::post_order_traversal, "1", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                            (boost::tree_node::pre_order_traversal, "0", 0, 1)
                            (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "4", 3, 20)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "3", 2, 10)
                    (boost::tree_node::pre_order_traversal, "2", 1, 4)
                        (boost::tree_node::pre_order_traversal, "1", 0, 1)
                        (boost::tree_node::post_order_traversal, "1", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                        (boost::tree_node::pre_order_traversal, "0", 0, 1)
                        (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "2", 1, 4)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "2", 1, 5)
                    (boost::tree_node::pre_order_traversal, "1", 0, 1)
                    (boost::tree_node::post_order_traversal, "1", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "0", 0, 1)
                    (boost::tree_node::post_order_traversal, "0", 0, 1)
                    (boost::tree_node::pre_order_traversal, "7", 0, 1)
                    (boost::tree_node::post_order_traversal, "7", 0, 1)
                (boost::tree_node::post_order_traversal, "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "1", 0, 1)
                (boost::tree_node::post_order_traversal, "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "0", 0, 1)
                (boost::tree_node::post_order_traversal, "0", 0, 1)
            (boost::tree_node::post_order_traversal, "5", 4, 63);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", "4", 3, 20)
                (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "4", 3, 20)
            (boost::tree_node::pre_order_traversal, "able", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "3", 2, 10)
                (boost::tree_node::pre_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "3", 2, 10)
            (boost::tree_node::pre_order_traversal, "baker", "2", 1, 4)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "2", 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "2", 1, 5)
                (boost::tree_node::pre_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "1", 0, 1)
                (boost::tree_node::pre_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "able", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::post_order_traversal, "baker", "0", 0, 1)
                (boost::tree_node::pre_order_traversal, "fox", "7", 0, 1)
                (boost::tree_node::post_order_traversal, "fox", "7", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "2", 1, 5)
            (boost::tree_node::pre_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "charlie", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "1", 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "dog", "0", 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", "0", 0, 1)
            (boost::tree_node::post_order_traversal, "easy", "0", 0, 1);
        test_associative_node(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
          , boost::mpl::true_()
        );
    }
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

#if defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors_typeof.hpp>
#include <boost/container_gen/c_str_cmp_selectors_typeof.hpp>
#include <boost/typeof/boost/ptr_container/ptr_map.hpp>
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/container/map.hpp>
#include <boost/typeof/boost/container/flat_map.hpp>
#endif
#else  // !defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/c_str_cmp_selectors.hpp>
#endif  // BOOST_TYPEOF_EMULATION

int test_main(int argc, char** argv)
{
    test<
        boost::ptr_map_selector<boost::c_str_ordering_selector>
      , boost::ptr_multimap_selector<boost::c_str_ordering_selector>
    >();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test<
        boost::map_selector<boost::mpl::true_,boost::c_str_ordering_selector>
      , boost::multimap_selector<
            boost::mpl::true_
          , boost::c_str_ordering_selector
        >
    >();
    test<
        boost::flat_map_selector<boost::c_str_ordering_selector>
      , boost::flat_multimap_selector<boost::c_str_ordering_selector>
    >();
#endif

    return 0;
}


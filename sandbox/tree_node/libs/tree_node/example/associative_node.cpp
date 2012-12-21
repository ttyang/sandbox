// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_TYPEOF_COMPLIANT

#include <iostream>
#include <boost/config.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/range/begin.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/typeof/associative_node.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/tree_node/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/pre_order_iterator.hpp>
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/tree_node/typeof/with_accumulation.hpp>
#endif

#include "type_definitions.hpp"
#include "output_preamble.hpp"
#include "output_functions.hpp"
#include "iterator_functions.hpp"
#include "assoc_iterator_functions.hpp"

char const* names[] = {"able", "baker", "chuck", "dog", "easy", "fox"};

template <typename Node>
void initialize(Node& root)
{
    for (boost::tree_node::breadth_first_iterator<Node> itr(root); itr; ++itr)
    {
        BOOST_AUTO_TPL(data, get(*itr, boost::tree_node::data_key()));

        if (1 < data)
        {
            for (std::size_t i = 0; i < data; ++i)
            {
                for (std::size_t j = 0; j + i < data; ++j)
                {
                    itr->emplace(names[j], i);
                }
            }
        }
    }
}

#if defined BOOST_NO_SFINAE
template <typename DNode>
void out_with_it(DNode const& d_node)
{
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 6);
    associative_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 3);
    associative_out_df(d_node, output_tree<boost::mpl::false_>(2, 5, true));
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
}
#else
template <typename DNode, typename ANode>
void out_with_them(DNode const& d_node, ANode const& a_node)
{
    std::cout << std::endl << "#if defined BOOST_NO_SFINAE";
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 6);
    associative_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 3);
    associative_out_df(d_node, output_tree<boost::mpl::false_>(2, 5, true));
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
    std::cout << "#else  // !defined BOOST_NO_SFINAE";
    iterator_out_bf_pre_post(a_node, output_node<boost::mpl::true_>(), 2);
    associative_out_bf_pre_post(a_node, output_node<boost::mpl::true_>(), 2);
    associative_out_df(a_node, output_tree<boost::mpl::true_>(4, 7, false));
    iterator_out_df(a_node, output_tree<boost::mpl::true_>(4, 7, false));
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
}
#endif

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename FNode>
void out_with_all(FNode const& f_node)
{
    iterator_out_bf_pre_post(f_node, output_uint_char_node(), 5);
    associative_out_bf_pre_post(f_node, output_uint_char_node(), 3);
    associative_out_df(f_node, output_uint_char_tree(4, 9, false));
    iterator_out_df(f_node, output_uint_char_tree(4, 9, false));
}
#endif

template <typename Selector>
void output_driver()
{
    typedef boost::tree_node::with_height<
                boost::tree_node::with_position_gen<
                    boost::tree_node::with_count_gen<
                        boost::tree_node::associative_node_gen<Selector>
                    >
                >
              , char const*
              , double
            >
            DNode;

    DNode d_root(5.0);

    initialize(d_root);

#if !defined BOOST_NO_SFINAE
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::with_height_gen<
                    boost::tree_node::with_accumulation_gen<
                        boost::tree_node::with_position_gen<
                            boost::tree_node::with_accumulation_gen<
                                boost::tree_node::with_count_gen<
                                    boost::tree_node::with_accumulation_gen<
                                        boost::tree_node::associative_node_gen<
                                            Selector
                                        >
                                    >
                                >
                              , AccuAccuKey
                            >
                        >
                      , AccuCountKey
                    >
                >
              , char const*
              , double
              , AccuHeightKey
            >
            ANode;

    ANode a_root(5.0);

    initialize(a_root);
#endif  // BOOST_NO_SFINAE

    std::cout << std::endl << "template <typename Selector>";
    std::cout << std::endl << (
        boost::is_unique_associative_selector<Selector>::value
      ? "void test_unique_associative()"
      : "void test_multiple_associative()"
    ) << std::endl << '{' << std::endl;
#if !defined BOOST_NO_SFINAE
    std::cout << "#if defined BOOST_NO_SFINAE" << std::endl;
#endif
    std::cout << "    typedef boost::tree_node::with_height<" << std::endl << (
        "                boost::tree_node::with_position_gen<"
    ) << std::endl << (
        "                    boost::tree_node::with_count_gen<"
    ) << std::endl << "                        ";
    std::cout << "boost::tree_node::associative_node_gen<Selector>";
    std::cout << std::endl << "                    >" << std::endl;
    std::cout << "                >" << std::endl;
    std::cout << "              , char const*" << std::endl;
    std::cout << "              , double" << std::endl;
    std::cout << "            >" << std::endl;
    std::cout << "            ANode;" << std::endl;
#if !defined BOOST_NO_SFINAE
    std::cout << "#else  // !defined BOOST_NO_SFINAE" << std::endl << (
        "    typedef boost::tree_node::with_accumulation<"
    ) << std::endl << "                boost::tree_node::with_height_gen<";
    std::cout << std::endl << (
        "                    boost::tree_node::with_accumulation_gen<"
    ) << std::endl << (
        "                        boost::tree_node::with_position_gen<"
    ) << std::endl << (
        "                            boost::tree_node::with_accumulation_gen<"
    ) << std::endl << (
        "                                boost::tree_node::with_count_gen<"
    ) << std::endl << "                                    ";
    std::cout << "boost::tree_node::with_accumulation_gen<" << std::endl << (
        "                                        "
    ) << "boost::tree_node::associative_node_gen<" << std::endl;
    std::cout << "                                            Selector";
    std::cout << std::endl << "                                        >";
    std::cout << std::endl << "                                    >";
    std::cout << std::endl << "                                >" << std::endl;
    std::cout << "                              , AccuAccuKey" << std::endl;
    std::cout << "                            >" << std::endl;
    std::cout << "                        >" << std::endl;
    std::cout << "                      , AccuCountKey" << std::endl;
    std::cout << "                    >" << std::endl;
    std::cout << "                >" << std::endl;
    std::cout << "              , char const*" << std::endl;
    std::cout << "              , double" << std::endl;
    std::cout << "              , AccuHeightKey" << std::endl;
    std::cout << "            >" << std::endl << "            ANode;";
    std::cout << std::endl << "#endif  // BOOST_NO_SFINAE";
#endif  // BOOST_NO_SFINAE
    output_container_type_preamble();
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    typename ANode::traits::key_type";
    std::cout << std::endl << "                  , BOOST_TYPEOF_TPL(";
    std::cout << std::endl << "                        get(" << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                          , boost::tree_node::data_key()";
    std::cout << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl;
    std::cout << "                        get(" << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                          , boost::tree_node::height_key()";
    std::cout << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl;
    std::cout << "                        get(" << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                          , boost::tree_node::count_key()";
    std::cout << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "#if !defined BOOST_NO_SFINAE" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            boost::tree_node::accumulation_key<>"
    ) << std::endl << (
        "                        >(boost::get_reference<ANode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuHeightKey>("
    ) << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuCountKey>("
    ) << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuAccuKey>("
    ) << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            KeyValues;" << std::endl;
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , typename ANode::traits::key_type"
    ) << std::endl << "                  , BOOST_TYPEOF_TPL(" << std::endl;
    std::cout << "                        get(" << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                          , boost::tree_node::data_key()";
    std::cout << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl;
    std::cout << "                        get(" << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                          , boost::tree_node::height_key()";
    std::cout << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl;
    std::cout << "                        get(" << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << (
        "                          , boost::tree_node::count_key()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "#if !defined BOOST_NO_SFINAE" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            boost::tree_node::accumulation_key<>"
    ) << std::endl << (
        "                        >(boost::get_reference<ANode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuHeightKey>("
    ) << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuCountKey>("
    ) << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuAccuKey>("
    ) << std::endl << (
        "                            boost::get_reference<ANode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            DFKeyValues;" << std::endl;
    std::cout << std::endl << "    ANode a_root(5.0);" << std::endl;
    std::cout << std::endl << "    BOOST_CHECK(" << std::endl;
    std::cout << "        !a_root.get_parent_ptr()" << std::endl;
    std::cout << "//      , \"Parent member uninitialized.\"" << std::endl;
    std::cout << "    );" << std::endl << std::endl;
    std::cout << "    initialize<Selector>(a_root);" << std::endl << std::endl;
    std::cout << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals;" << std::endl;
    std::cout << "        KeyValues bf_d_vals, pre_d_vals, post_d_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        DFKeyValues df_d_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
    out_with_it(d_root);
#else
    out_with_them(d_root, a_root);
#endif
    std::cout << "        test_associative_node(" << std::endl;
    std::cout << "            a_root" << std::endl;
    std::cout << "          , bf_vals" << std::endl;
    std::cout << "          , bf_d_vals" << std::endl;
    std::cout << "          , pre_vals" << std::endl;
    std::cout << "          , pre_d_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl;
    std::cout << "          , post_d_vals" << std::endl;
    std::cout << "          , df_vals" << std::endl;
    std::cout << "          , df_d_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;

    {
        typename DNode::iterator d_child_itr(
            boost::tree_node::dereference_iterator(
                d_root.find(names[2])
            ).insert(names[5], d_root)
        );
#if !defined BOOST_NO_SFINAE
        typename ANode::iterator a_child_itr(
            boost::tree_node::dereference_iterator(
                a_root.find(names[2])
            ).insert(names[5], a_root)
        );
#endif

        std::cout << "    {" << std::endl << "        ANode a_copy(a_root);";
        std::cout << std::endl << (
            "        boost::tree_node::breadth_first_iterator<ANode const>"
        ) << std::endl << (
            "            bf_root_itr(a_root), bf_copy_itr(a_copy);"
        ) << std::endl << "        boost::tree_node::breadth_first";
        std::cout << "_descendant_iterator<ANode const>" << std::endl << (
            "            bf_d_root_itr(a_root), bf_d_copy_itr(a_copy);"
        ) << std::endl << (
            "        boost::tree_node::pre_order_iterator<ANode const>"
        ) << std::endl << (
            "            pre_root_itr(a_root), pre_copy_itr(a_copy);"
        ) << std::endl << "        boost::tree_node::pre_order";
        std::cout << "_descendant_iterator<ANode const>" << std::endl << (
            "            pre_d_root_itr(a_root), pre_d_copy_itr(a_copy);"
        ) << std::endl << (
            "        boost::tree_node::post_order_iterator<ANode const>"
        ) << std::endl << (
            "            post_root_itr(a_root), post_copy_itr(a_copy);"
        ) << std::endl << "        boost::tree_node::post_order";
        std::cout << "_descendant_iterator<ANode const>" << std::endl << (
            "            post_d_root_itr(a_root), post_d_copy_itr(a_copy);"
        ) << std::endl << (
            "        boost::tree_node::depth_first_iterator<ANode const>"
        ) << std::endl << (
            "            df_root_itr(a_root), df_copy_itr(a_copy);"
        ) << std::endl << "        boost::tree_node::depth_first";
        std::cout << "_descendant_iterator<ANode const>" << std::endl << (
            "            df_d_root_itr(a_root), df_d_copy_itr(a_copy);"
        ) << std::endl << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(bf_root_itr, bf_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << std::endl << "      " << (
            "      test_associative_node_copies(bf_d_root_itr, bf_d_copy_itr)"
        ) << std::endl << "        );" << std::endl << "        " << (
            "BOOST_CHECK(test_node_copies(pre_root_itr, pre_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << std::endl << "       " << (
            "     test_associative_node_copies(pre_d_root_itr, pre_d_copy_itr)"
        ) << std::endl << "        );" << std::endl << "        " << (
            "BOOST_CHECK(test_node_copies(post_root_itr, post_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << std::endl << "       " << (
            "     test_associative_node_copies(post_d_root_itr, post_d_copy_it"
        ) << "r)" << std::endl << "        );" << std::endl << "        " << (
            "BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << std::endl << "       " << (
            "     test_associative_node_copies(df_d_root_itr, df_d_copy_itr)"
        ) << std::endl << "        );" << std::endl << "    }" << std::endl;
        std::cout << std::endl << "    {" << std::endl << (
            "        typename ANode::iterator a_child_itr("
        ) << std::endl << "          boost::tree_node::dereference_iterator(";
        std::cout << std::endl << "            a_root.find(names[2])";
        std::cout << std::endl << "          ).insert(names[5], a_root)";
        std::cout << std::endl << "        );" << std::endl << (
            "        Values bf_vals, pre_vals, post_vals;"
        ) << std::endl;
        std::cout << "        KeyValues bf_d_vals, pre_d_vals, post_d_vals;";
        std::cout << std::endl << "        DFValues df_vals;" << std::endl;
        std::cout << "        DFKeyValues df_d_vals;" << std::endl;
        std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_associative_node(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , bf_d_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , pre_d_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , post_d_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "          , df_d_vals" << std::endl;
        std::cout << "        );" << std::endl << std::endl;

        d_root = boost::tree_node::dereference_iterator(d_child_itr);
#if !defined BOOST_NO_SFINAE
        a_root = boost::tree_node::dereference_iterator(a_child_itr);
#endif
        std::cout << "        a_root = boost::tree_node::";
        std::cout << "dereference_iterator(a_child_itr);" << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        bf_d_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        pre_d_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        post_d_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
        std::cout << "        df_d_vals.clear();" << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_associative_node(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , bf_d_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , pre_d_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , post_d_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "          , df_d_vals" << std::endl;
        std::cout << "        );" << std::endl << std::endl;

        if (boost::is_unique_associative_selector<Selector>::value)
        {
            boost::tree_node::dereference_iterator(
                d_child_itr = d_root.find(names[2])
            ) = d_root;
#if !defined BOOST_NO_SFINAE
            boost::tree_node::dereference_iterator(
                a_child_itr = a_root.find(names[2])
            ) = a_root;
#endif
            std::cout << "        a_child_itr = a_root.find(names[2]);";
            std::cout << std::endl;
        }
        else
        {
            d_child_itr = boost::begin(d_root.equal_range(names[2]));

            while (boost::tree_node::dereference_iterator(d_child_itr).empty())
            {
                ++d_child_itr;
            }

            d_child_itr = boost::begin(
                boost::tree_node::dereference_iterator(
                    d_child_itr
                ).equal_range(names[1])
            );
            boost::tree_node::dereference_iterator(d_child_itr) = d_root;
#if !defined BOOST_NO_SFINAE
            a_child_itr = boost::begin(a_root.equal_range(names[2]));

            while (boost::tree_node::dereference_iterator(a_child_itr).empty())
            {
                ++a_child_itr;
            }

            a_child_itr = boost::begin(
                boost::tree_node::dereference_iterator(
                    a_child_itr
                ).equal_range(names[1])
            );
            boost::tree_node::dereference_iterator(a_child_itr) = a_root;
#endif
            std::cout << "        a_child_itr = boost::begin(a_root.equal";
            std::cout << "_range(names[2]));" << std::endl << std::endl << (
                "        while (boost::tree_node::dereference_iterator(a_"
            ) << "child_itr).empty())" << std::endl << "        {";
            std::cout << std::endl << "            ++a_child_itr;";
            std::cout << std::endl << "        }" << std::endl;
            std::cout << std::endl << (
                "        a_child_itr = boost::begin("
            ) << std::endl << (
                "            boost::tree_node::dereference_iterator("
            ) << std::endl << "                a_child_itr" << std::endl;
            std::cout << "            ).equal_range(names[1])";
            std::cout << std::endl << "        );" << std::endl;
        }

        std::cout << "        boost::tree_node::dereference_iterator";
        std::cout << "(a_child_itr) = a_root;" << std::endl;
        std::cout << "        test_associative_node(" << std::endl;
        std::cout << "            boost::tree_node::dereference_iterator";
        std::cout << "(a_child_itr)" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , bf_d_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , pre_d_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , post_d_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "          , df_d_vals" << std::endl;
        std::cout << "        );" << std::endl << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        bf_d_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        pre_d_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        post_d_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
        std::cout << "        df_d_vals.clear();" << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_associative_node(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , bf_d_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , pre_d_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , post_d_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "          , df_d_vals" << std::endl << "        );";
        std::cout << std::endl << "        BOOST_CHECK(" << std::endl << (
            "            boost::tree_node::dereference_iterator("
        ) << std::endl << "                a_child_itr" << std::endl;
        std::cout << "            ).erase(names[1]) == ";
        std::cout << boost::tree_node::dereference_iterator(
            d_child_itr
        ).erase(names[1]) << std::endl << "        );" << std::endl;
#if !defined BOOST_NO_SFINAE
        boost::tree_node::dereference_iterator(a_child_itr).erase(names[1]);
#endif
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        bf_d_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        pre_d_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        post_d_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
        std::cout << "        df_d_vals.clear();" << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_associative_node(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , bf_d_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , pre_d_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , post_d_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "          , df_d_vals" << std::endl << "        );";
    }

    std::cout << std::endl << "    }";

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::associative_node_gen<Selector>
              , char const*
              , DataMap
              , AccuYourUintKey
            >
            FNode;

    FNode f_root(
        boost::fusion::make_pair<example_keys::your_uint>(5)
      , boost::fusion::make_pair<example_keys::your_char>('5')
    );

    for (
        boost::tree_node::breadth_first_iterator<FNode> itr(f_root);
        itr;
        ++itr
    )
    {
        BOOST_AUTO_TPL(
            data
          , boost::tree_node::get<example_keys::your_uint>(
                boost::tree_node::dereference_iterator(itr)
            )
        );

        if (1 < data)
        {
            for (unsigned int i = 0; i < data; ++i)
            {
                for (std::size_t j = 0; j + i < data; ++j)
                {
                    itr->emplace(
                        names[j]
                      , boost::fusion::make_pair<example_keys::your_uint>(i)
                      , boost::fusion::make_pair<example_keys::your_char>(
                            '0' + i
                        )
                    );
                }
            }
        }
    }

    std::cout << std::endl << std::endl << (
        "#if defined BOOST_TREE_NODE_CAN_USE_FUSION"
    ) << std::endl << "    typedef boost::tree_node::with_accumulation<";
    std::cout << std::endl << (
        "                boost::tree_node::associative_node_gen<Selector>"
    ) << std::endl << "              , char const*" << std::endl;
    std::cout << "              , DataMap" << std::endl;
    std::cout << "              , AccuYourUintKey" << std::endl;
    std::cout << "            >" << std::endl << "            FNode;";
    output_container_fused_type_preamble();
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl << (
        "                    typename FNode::traits::key_type"
    ) << std::endl << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_uint"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_char"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuYourUintKey>("
    ) << std::endl << (
        "                            boost::get_reference<FNode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl << "                >";
    std::cout << std::endl << "            >::type" << std::endl;
    std::cout << "            MoreKeyValues;" << std::endl;
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , typename FNode::traits::key_type"
    ) << std::endl << "                  , BOOST_TYPEOF_TPL(" << std::endl;
    std::cout << "                        boost::tree_node::get<" << std::endl;
    std::cout << "                            example_keys::your_uint";
    std::cout << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_char"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF_TPL(" << std::endl << (
        "                        boost::tree_node::get<AccuYourUintKey>("
    ) << std::endl << (
        "                            boost::get_reference<FNode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl << "                >";
    std::cout << std::endl << "            >::type" << std::endl;
    std::cout << "            DFMoreKeyValues;" << std::endl << std::endl;
    std::cout << "    FNode f_root(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::your_uint>(5)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::your_char>(\'5\')"
    ) << std::endl << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<FNode> itr(f_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_AUTO_TPL(" << std::endl;
    std::cout << "            data" << std::endl << (
        "          , boost::tree_node::get<example_keys::your_uint>("
    ) << std::endl << (
        "                boost::tree_node::dereference_iterator(itr)"
    ) << std::endl << "            )" << std::endl << "        );";
    std::cout << std::endl << std::endl << "        if (1 < data)";
    std::cout << std::endl << "        {" << std::endl;
    std::cout << "            for (unsigned int i = 0; i < data; ++i)";
    std::cout << std::endl << "            {" << std::endl << (
        "                for (std::size_t j = 0; j + i < data; ++j)"
    ) << std::endl << "                {" << std::endl;
    std::cout << "                    itr->emplace(" << std::endl;
    std::cout << "                        names[j]" << std::endl << (
        "                      , boost::fusion::make_pair<example_keys::your_"
    ) << "uint>(i)" << std::endl << "                      " << (
        ", boost::fusion::make_pair<example_keys::your_char>("
    ) << std::endl << "                            '0' + i" << std::endl;
    std::cout << "                        )" << std::endl;
    std::cout << "                    );" << std::endl << "                }";
    std::cout << std::endl << "            }" << std::endl << "        }";
    std::cout << std::endl << "    }" << std::endl;
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        MoreValues bf_vals, pre_vals, post_vals;";
    std::cout << std::endl << (
        "        MoreKeyValues bf_d_vals, pre_d_vals, post_d_vals;"
    ) << std::endl << "        DFMoreKeyValues df_d_vals;" << std::endl;
    std::cout << "        DFMoreValues df_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
    out_with_all(f_root);
    std::cout << "        test_f_associative_node(" << std::endl;
    std::cout << "            f_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , bf_d_vals" << std::endl;
    std::cout << "          , pre_vals" << std::endl;
    std::cout << "          , pre_d_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl;
    std::cout << "          , post_d_vals" << std::endl;
    std::cout << "          , df_vals" << std::endl << "          , df_d_vals";
    std::cout << std::endl << "        );" << std::endl << std::endl;

    put(
        boost::tree_node::dereference_iterator(f_root.find(names[2]))
      , example_keys::your_uint()
      , 7
    );
    std::cout << "        put(" << std::endl << "            boost::tree_node";
    std::cout << "::dereference_iterator(f_root.find(names[2]))" << std::endl;
    std::cout << "          , example_keys::your_uint()" << std::endl;
    std::cout << "          , 7" << std::endl << "        );" << std::endl;
    std::cout << "        bf_vals.clear();" << std::endl;
    std::cout << "        bf_d_vals.clear();" << std::endl;
    std::cout << "        pre_vals.clear();" << std::endl;
    std::cout << "        pre_d_vals.clear();" << std::endl;
    std::cout << "        post_vals.clear();" << std::endl;
    std::cout << "        post_d_vals.clear();" << std::endl;
    std::cout << "        df_vals.clear();" << std::endl;
    std::cout << "        df_d_vals.clear();" << std::endl;
    out_with_all(f_root);
    std::cout << "        test_f_associative_node(" << std::endl;
    std::cout << "            f_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , bf_d_vals" << std::endl;
    std::cout << "          , pre_vals" << std::endl;
    std::cout << "          , pre_d_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl;
    std::cout << "          , post_d_vals" << std::endl;
    std::cout << "          , df_vals" << std::endl << "          , df_d_vals";
    std::cout << std::endl << "        );" << std::endl << "    }";
    std::cout  << std::endl<< "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION";
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    std::cout << std::endl << '}' << std::endl;
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
#include <boost/typeof/boost/container/map.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#else  // !defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/c_str_cmp_selectors.hpp>
#endif  // BOOST_TYPEOF_EMULATION

int main()
{
    output_copyright_and_config_preamble();
    output_header_and_type_preamble();
    std::cout << "#include <boost/tree_node/typeof/associative_node.hpp>";
    std::cout << std::endl << (
        "#include <boost/container_gen/is_unique_assoc_selector.hpp>"
    ) << std::endl << std::endl << "char const* names[] = {\"able\"," << (
        " \"baker\", \"chuck\", \"dog\", \"easy\", \"fox\"};"
    ) << std::endl << std::endl << "template <typename Select, typename Node>";
    std::cout << std::endl << "void initialize(Node& root)" << std::endl;
    std::cout << '{' << std::endl << (
        "    for (boost::tree_node::breadth_first_iterator<Node> itr(root);"
    ) << " itr; ++itr)" << std::endl << "    {" << std::endl << "        " << (
        "BOOST_AUTO_TPL(data, get(*itr, boost::tree_node::data_key()));"
    ) << std::endl << std::endl << "        if (1 < data)" << std::endl;
    std::cout << "        {" << std::endl;
    std::cout << "            for (std::size_t i = 0; i < data; ++i)";
    std::cout << std::endl << "            {" << std::endl;
    std::cout << "                for (std::size_t j = 0; j + i < data; ++j)";
    std::cout << std::endl << "                {" << std::endl << "      " << (
        "              typename Node::iterator find_itr(itr->find(names[j]));"
    ) << std::endl << (
        "                    bool not_found = find_itr == itr->end();"
    ) << std::endl << (
        "                    typename Node::iterator child_itr("
    ) << std::endl << (
        "                        itr->emplace(names[j], i)"
    ) << std::endl << "                    );" << std::endl;
    std::cout << "                    Node& child(" << std::endl << (
        "                        boost::tree_node::dereference_iterator"
    ) << "(child_itr)" << std::endl << "                    );" << std::endl;
    std::cout << "                    Node const& const_child(child);";
    std::cout << std::endl << std::endl << (
        "                    if (not_found)"
    ) << std::endl << "                    {" << std::endl;
    std::cout << "                        typename Node::pointer child_ptr(";
    std::cout << std::endl << (
        "                            child.get_parent_ptr()"
    ) << std::endl << "                        );" << std::endl;
    std::cout << "                        BOOST_CHECK(" << std::endl;
    std::cout << "                            child_ptr == &*itr" << std::endl;
    std::cout << "//                          , \"Ctor not linking child to";
    std::cout << " parent.\"" << std::endl << "                        );";
    std::cout << std::endl << "                        BOOST_CHECK(";
    std::cout << std::endl << (
        "                            child_ptr == const_child.get_parent_ptr()"
    ) << std::endl << (
        "//                          , \"Why are these pointers different?\""
    ) << std::endl << "                        );" << std::endl;
    std::cout << "                    }" << std::endl;
    std::cout << "                    else if (" << std::endl;
    std::cout << "                        boost::";
    std::cout << "is_unique_associative_selector<Select>::value" << std::endl;
    std::cout << "                    )" << std::endl;
    std::cout << "                    {" << std::endl;
    std::cout << "                        BOOST_CHECK(" << std::endl << (
        "                            find_itr->first == child_itr->first"
    ) << std::endl;
    std::cout << "//                          , \"Keys do not match.\"";
    std::cout << std::endl << "                        );" << std::endl;
    std::cout << "                        BOOST_CHECK(" << std::endl;
    std::cout << "                            get(" << std::endl << "    " << (
        "                            boost::tree_node::dereference_iterator("
    ) << std::endl;
    std::cout << "                                    find_itr" << std::endl;
    std::cout << "                                )" << std::endl << (
        "                              , boost::tree_node::data_key()"
    ) << std::endl << "                            ) == get(" << std::endl;
    std::cout << "                                const_child";
    std::cout << std::endl << (
        "                              , boost::tree_node::data_key()"
    ) << std::endl << "                            )" << std::endl << (
        "//                          , \"Ctor not linking parent to child.\""
    ) << std::endl << "                        );" << std::endl;
    std::cout << "                    }" << std::endl << "                }";
    std::cout << std::endl << "            }" << std::endl << "        }";
    std::cout << std::endl << "    }" << std::endl << '}' << std::endl;

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    output_driver<
        boost::ptr_map_selector<boost::c_str_ordering_selector>
    >();
    output_driver<
        boost::ptr_multimap_selector<boost::c_str_ordering_selector>
    >();
#elif defined LIBS_TREE_NODE_EXAMPLE_ASSOCIATIVE_NODE_USE_FLAT_MAP
    output_driver<
        boost::flat_map_selector<boost::c_str_ordering_selector>
    >();
    output_driver<
        boost::flat_multimap_selector<boost::c_str_ordering_selector>
    >();
#else
    output_driver<boost::map_selector<boost::mpl::true_> >();
    output_driver<boost::multimap_selector<boost::mpl::true_> >();
#endif

    std::cout << std::endl << "#if defined BOOST_MSVC" << std::endl;
    std::cout << "   #pragma warning (pop)" << std::endl;
    std::cout << "#endif" << std::endl << std::endl;
    std::cout << "#if defined BOOST_TYPEOF_EMULATION" << std::endl << (
        "#include <boost/container_gen/selectors_typeof.hpp>"
    ) << std::endl << (
        "#include <boost/container_gen/c_str_cmp_selectors_typeof.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/ptr_container/ptr_map.hpp>"
    ) << std::endl << (
        "#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION"
    ) << std::endl;
    std::cout << "#include <boost/typeof/boost/mpl/bool.hpp>" << std::endl << (
        "#include <boost/typeof/boost/container/map.hpp>"
    ) << std::endl;
    std::cout << "#include <boost/typeof/boost/container/flat_map.hpp>";
    std::cout << std::endl << "#endif" << std::endl;
    std::cout << "#else  // !defined BOOST_TYPEOF_EMULATION" << std::endl;
    std::cout << "#include <boost/container_gen/selectors.hpp>" << std::endl;
    std::cout << "#include <boost/container_gen/c_str_cmp_selectors.hpp>";
    std::cout << std::endl << "#endif  // BOOST_TYPEOF_EMULATION" << std::endl;
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl << (
        "    test_unique_associative<"
    ) << std::endl << (
        "        boost::ptr_map_selector<boost::c_str_ordering_selector>"
    ) << std::endl << "    >();" << std::endl << (
        "    test_multiple_associative<"
    ) << std::endl << (
        "        boost::ptr_multimap_selector<boost::c_str_ordering_selector>"
    ) << std::endl << "    >();" << std::endl;
    std::cout << "#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION";
    std::cout << std::endl << "    test_unique_associative<" << std::endl;
    std::cout << "        boost::map_selector<boost::mpl::true_,";
    std::cout << "boost::c_str_ordering_selector>" << std::endl << "    >();";
    std::cout << std::endl << "    test_multiple_associative<" << std::endl;
    std::cout << "        boost::multimap_selector<" << std::endl;
    std::cout << "            boost::mpl::true_" << std::endl;
    std::cout << "          , boost::c_str_ordering_selector" << std::endl;
    std::cout << "        >" << std::endl << "    >();" << std::endl;
    std::cout << "    test_unique_associative<" << std::endl << (
        "        boost::flat_map_selector<boost::c_str_ordering_selector>"
    ) << std::endl << "    >();" << std::endl << (
        "    test_multiple_associative<"
    ) << std::endl << (
        "        boost::flat_multimap_selector<boost::c_str_ordering_selector>"
    ) << std::endl << "    >();" << std::endl << "#endif" << std::endl;
    std::cout << std::endl << "    return 0;" << std::endl;
    std::cout << '}' << std::endl << std::endl;

    return 0;
}


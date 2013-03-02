// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/config.hpp>
#include <boost/typeof/boost/rational.hpp>
#include <boost/typeof/boost/tree_node/binary_node.hpp>
#include <boost/typeof/boost/tree_node/with_count.hpp>
#include <boost/typeof/boost/tree_node/with_height.hpp>
#include <boost/typeof/boost/tree_node/with_position.hpp>
#include <boost/tree_node/iterator/breadth_first.hpp>
#include <boost/tree_node/iterator/pre_order_descendant.hpp>
#include <boost/tree_node/iterator/post_order.hpp>
#include <boost/tree_node/preprocessor.hpp>

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/typeof/boost/tree_node/with_accumulation.hpp>
#endif

#include "type_definitions.hpp"
#include "output_preamble.hpp"
#include "output_functions.hpp"
#include "iterator_functions.hpp"

typedef boost::tree_node::with_height<
            boost::tree_node::with_position_base_gen<
                boost::tree_node::with_count_base_gen<
                    boost::tree_node::binary_node_base_gen<>
                >
            >
          , boost::rational<long>
        >
        DNode;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
typedef boost::tree_node::with_accumulation<
            boost::tree_node::with_height_base_gen<
                boost::tree_node::with_accumulation_base_gen<
                    boost::tree_node::with_position_base_gen<
                        boost::tree_node::with_accumulation_base_gen<
                            boost::tree_node::with_count_base_gen<
                                boost::tree_node::with_accumulation_base_gen<
                                    boost::tree_node::binary_node_base_gen<>
                                >
                            >
                          , AccuAccuKey
                        >
                    >
                  , AccuCountKey
                >
            >
          , boost::rational<long>
          , void
          , AccuHeightKey
        >
        ANode;
typedef boost::tree_node::with_accumulation<
            boost::tree_node::binary_node_base_gen<>
          , DataMap
          , void
          , AccuYourUintKey
        >
        FNode;
typedef boost::tree_node::with_accumulation<
            boost::tree_node::with_accumulation_base_gen<
                boost::tree_node::binary_node_base_gen<>
              , HeightSumKey
            >
          , GUITable
          , void
          , MinPriorityKey
        >
        GUINode;

void out_with_it(FNode const& f_node)
{
    iterator_out_bf_pre_post(f_node, output_uint_char_node(), 5);
    iterator_out_in_order(f_node, output_uint_char_node(), 5);
    iterator_out_df(f_node, output_uint_char_tree(2, 7, true));
}

void out_with_it(GUINode const& gui_node)
{
    iterator_out_bf_pre_post(gui_node, output_gui_node(), 3);
    iterator_out_in_order(gui_node, output_gui_node(), 3);
    iterator_out_df(gui_node, output_gui_tree(2, 7, true));
}
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

template <typename Node>
void initialize(Node& root)
{
    for (boost::tree_node::breadth_first_iterator<Node> itr(root); itr; ++itr)
    {
        typename Node::traits::data_type const& data = get(
            *itr
          , boost::tree_node::data_key()
        );

        if (1 < data)
        {
            itr->emplace_left(data - 2);
            itr->emplace_right(data - 1);
        }
    }
}

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
void out_with_them(DNode const& d_node, ANode const& a_node)
{
    std::cout << std::endl << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION";
    iterator_out_bf_pre_post(a_node, output_node<boost::mpl::true_>(), 1);
    iterator_out_in_order(a_node, output_node<boost::mpl::true_>(), 1);
    iterator_out_df(a_node, output_tree<boost::mpl::true_>(2, 7, true));
    std::cout << "#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION";
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_in_order(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
}
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
void out_with_it(DNode const& d_node)
{
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_in_order(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
}
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

int main()
{
    DNode d_root(5);

    initialize(d_root);

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    ANode a_root(5);

    initialize(a_root);
#endif

    output_copyright_and_config_preamble();
    output_header_and_type_preamble();
    std::cout << "#include <boost/typeof/boost/tree_node/binary_node.hpp>";
    std::cout << std::endl << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "typedef boost::tree_node::with_accumulation<" << std::endl;
    std::cout << "            boost::tree_node::with_height_base_gen<";
    std::cout << std::endl << (
        "                boost::tree_node::with_accumulation_base_gen<"
    ) << std::endl << (
        "                    boost::tree_node::with_position_base_gen<"
    ) << std::endl << (
        "                        boost::tree_node::with_accumulation_base_gen<"
    ) << std::endl << (
        "                            boost::tree_node::with_count_base_gen<"
    ) << std::endl << "                                boost::tree_node::";
    std::cout << "with_accumulation_base_gen<" << std::endl << "        " << (
        "                            boost::tree_node::binary_node_base_gen<>"
    ) << std::endl << "                                >" << std::endl;
    std::cout << "                            >" << std::endl;
    std::cout << "                          , AccuAccuKey" << std::endl;
    std::cout << "                        >" << std::endl;
    std::cout << "                    >" << std::endl;
    std::cout << "                  , AccuCountKey" << std::endl;
    std::cout << "                >" << std::endl << "            >";
    std::cout << std::endl << "          , boost::rational<long>" << std::endl;
    std::cout << "          , void" << std::endl;
    std::cout << "          , AccuHeightKey" << std::endl << "        >";
    std::cout << std::endl << "        ANode;" << std::endl << (
        "#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION"
    ) << std::endl;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    std::cout << "typedef boost::tree_node::with_height<" << std::endl << (
        "            boost::tree_node::with_position_base_gen<"
    ) << std::endl << (
        "                boost::tree_node::with_count_base_gen<"
    ) << std::endl << (
        "                    boost::tree_node::binary_node_base_gen<>"
    ) << std::endl << "                >" << std::endl;
    std::cout << "            >" << std::endl;
    std::cout << "          , boost::rational<long>" << std::endl;
    std::cout << "        >" << std::endl;
    std::cout << "        ANode;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
#endif
    std::cout << std::endl << "typedef boost::container_gen<" << std::endl;
    std::cout << "            boost::dequeS" << std::endl;
    std::cout << "          , boost::tuples::tuple<" << std::endl;
    std::cout << "                boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::data_key" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::height_key";
    std::cout << std::endl << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::count_key";
    std::cout << std::endl << "                >::type" << std::endl;
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::accumulation_key<>";
    std::cout << std::endl << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , AccuHeightKey" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , AccuCountKey" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , AccuAccuKey" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "            >" << std::endl << "        >::type";
    std::cout << std::endl << "        Values;" << std::endl;
    std::cout << "typedef boost::container_gen<" << std::endl;
    std::cout << "            boost::dequeS" << std::endl;
    std::cout << "          , boost::tuples::tuple<" << std::endl << (
        "                boost::tree_node::traversal_state"
    ) << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::data_key" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::height_key";
    std::cout << std::endl << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::count_key";
    std::cout << std::endl << "                >::type" << std::endl;
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , boost::tree_node::accumulation_key<>";
    std::cout << std::endl << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , AccuHeightKey" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , AccuCountKey" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "              , boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "                    ANode const" << std::endl;
    std::cout << "                  , AccuAccuKey" << std::endl;
    std::cout << "                >::type" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "            >" << std::endl << "        >::type";
    std::cout << std::endl << "        DFValues;" << std::endl;
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl << "    ANode a_root(5);";
    std::cout << std::endl << std::endl << "    BOOST_CHECK(" << std::endl;
    std::cout << "        !a_root.get_parent_ptr()" << std::endl;
    std::cout << "//      , \"Parent member uninitialized.\"" << std::endl;
    std::cout << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<ANode> itr(a_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl << (
        "        ANode::traits::data_type const& data = get("
    ) << std::endl << "            *itr" << std::endl;
    std::cout << "          , boost::tree_node::data_key()" << std::endl;
    std::cout << "        );" << std::endl << std::endl;
    std::cout << "        if (1 < data)" << std::endl << "        {";
    std::cout << std::endl << (
        "            ANode::iterator child_itr(itr->emplace_left(data - 2));"
    ) << std::endl;
    std::cout << "            ANode::const_pointer const_child(&*child_itr);";
    std::cout << std::endl << std::endl << "            BOOST_CHECK(";
    std::cout << std::endl << (
        "                child_itr->get_parent_ptr() == &*itr"
    ) << std::endl << (
        "//              , \"Ctor not linking child to parent.\""
    ) << std::endl << "            );" << std::endl;
    std::cout << "            BOOST_CHECK(" << std::endl << (
        "                itr->get_left_child_ptr() == &*child_itr"
    ) << std::endl << (
        "//              , \"Ctor not linking parent to child.\""
    ) << std::endl << "            );" << std::endl;
    std::cout << "            BOOST_CHECK(" << std::endl << "                ";
    std::cout << (
        "child_itr->get_parent_ptr() == const_child->get_parent_ptr()"
    ) << std::endl << (
        "//              , \"Why are these pointers different?\""
    ) << std::endl << "            );" << std::endl;
    std::cout << "            BOOST_CHECK(" << std::endl;
    std::cout << "                get(" << std::endl;
    std::cout << "                    *child_itr" << std::endl;
    std::cout << "                  , boost::tree_node::position_key()";
    std::cout << std::endl << "                ) == child_itr" << std::endl;
    std::cout << "//              , \"Position iterator incorrect.\"";
    std::cout << std::endl << "            );" << std::endl << std::endl;
    std::cout << "            child_itr = itr->emplace_right(data - 1);";
    std::cout << std::endl << "            const_child = &*child_itr;";
    std::cout << std::endl << std::endl << "            BOOST_CHECK(";
    std::cout << std::endl << (
        "                child_itr->get_parent_ptr() == &*itr"
    ) << std::endl;
    std::cout << "//              , \"Ctor not linking child to parent.\"";
    std::cout << std::endl << "            );" << std::endl;
    std::cout << "            BOOST_CHECK(" << std::endl << (
        "                itr->get_right_child_ptr() == &*child_itr"
    ) << std::endl << (
        "//              , \"Ctor not linking parent to child.\""
    ) << std::endl << "            );" << std::endl;
    std::cout << "            BOOST_CHECK(" << std::endl << "                ";
    std::cout << (
        "child_itr->get_parent_ptr() == const_child->get_parent_ptr()"
    ) << std::endl << (
        "//              , \"Why are these pointers different?\""
    ) << std::endl << "            );" << std::endl;
    std::cout << "            BOOST_CHECK(" << std::endl;
    std::cout << "                get(" << std::endl;
    std::cout << "                    *child_itr" << std::endl;
    std::cout << "                  , boost::tree_node::position_key()";
    std::cout << std::endl << "                ) == child_itr" << std::endl;
    std::cout << "//              , \"Position iterator incorrect.\"";
    std::cout << std::endl << "            );" << std::endl << "        }";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    std::cout << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(" << std::endl;
    std::cout << "            a_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;

    {
        DNode::pointer d_p(
            d_root.get_left_child_ptr()->get_right_child_ptr()
        );
        DNode::iterator d_child_itr = d_p->insert_left(d_root);
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        ANode::pointer a_p(
            a_root.get_left_child_ptr()->get_right_child_ptr()
        );
        ANode::iterator a_child_itr = a_p->insert_left(a_root);
#endif

        std::cout << std::endl << "    {" << std::endl;
        std::cout << "        ANode a_copy(a_root);" << std::endl << (
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
            "        boost::tree_node::in_order_iterator<ANode const>"
        ) << std::endl << (
            "            in_root_itr(a_root), in_copy_itr(a_copy);"
        ) << std::endl << (
            "        boost::tree_node::depth_first_iterator<ANode const>"
        ) << std::endl << (
            "            df_root_itr(a_root), df_copy_itr(a_copy);"
        ) << std::endl << "        boost::tree_node::depth_first";
        std::cout << "_descendant_iterator<ANode const>" << std::endl << (
            "            df_d_root_itr(a_root), df_d_copy_itr(a_copy);"
        ) << std::endl << std::endl << (
            "        BOOST_CHECK(test_node_copies(bf_root_itr, bf_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(bf_d_root_itr, bf_d_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(pre_root_itr, pre_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(pre_d_root_itr, pre_d_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(post_root_itr, post_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(post_d_root_itr, post_d_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(in_root_itr, in_copy_itr));"
        ) << std::endl << (
            "        BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(df_d_root_itr, df_d_copy_itr));"
        ) << std::endl << "    }" << std::endl << std::endl << "    {";
        std::cout << std::endl << "        ANode::pointer p(" << std::endl << (
            "            a_root.get_left_child_ptr()->get_right_child_ptr()"
        ) << std::endl << "        );" << std::endl << (
            "        ANode::iterator a_child_itr = p->insert_left(a_root);"
        ) << std::endl << (
            "        Values bf_vals, pre_vals, post_vals, in_vals;"
        ) << std::endl << "        DFValues df_vals;" << std::endl << (
            "        Emplacer emplacer;"
        ) << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , in_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "        );" << std::endl << std::endl;

        d_root = *d_child_itr;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        a_root = *a_child_itr;
#endif
        std::cout << "        a_root = *a_child_itr;" << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        in_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , in_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "        );" << std::endl << std::endl;

        *(d_p = d_root.get_right_child_ptr()) = d_root;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        *(a_p = a_root.get_right_child_ptr()) = a_root;
#endif
        std::cout << "        *(p = a_root.get_right_child_ptr()) = a_root;";
        std::cout << std::endl << "        test_node<a_node_case>(";
        std::cout << std::endl << "            *p" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , in_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl;
        std::cout << "        );" << std::endl << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        in_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , in_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl << "        );";
        std::cout << std::endl << "    }" << std::endl << std::endl;
    }

    d_root.get_right_child_ptr()->rotate_left();
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    a_root.get_right_child_ptr()->rotate_left();
#endif
    std::cout << "    a_root.get_right_child_ptr()->rotate_left();";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(" << std::endl;
    std::cout << "            a_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;

    {
        DNode::pointer d_p(d_root.get_right_child_ptr()->get_right_child_ptr());
        DNode::iterator d_child_itr(d_p->emplace_right());

        put(*d_child_itr, boost::tree_node::data_key(), 7);

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        ANode::pointer a_p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator a_child_itr(a_p->emplace_right());

        put(*a_child_itr, boost::tree_node::data_key(), 7);
#endif
        std::cout << std::endl << "    {" << std::endl << "        ANode" << (
            "::pointer p(a_root.get_right_child_ptr()->get_right_child_ptr());"
        ) << std::endl << (
            "        ANode::iterator p_child_itr(p->emplace_right());"
        ) << std::endl << (
            "        Values bf_vals, pre_vals, post_vals, in_vals;"
        ) << std::endl << "        DFValues df_vals;" << std::endl;
        std::cout << "        Emplacer emplacer;" << std::endl << std::endl;
        std::cout << (
            "        put(*p_child_itr, boost::tree_node::data_key(), 7);"
        );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(" << std::endl;
        std::cout << "            a_root" << std::endl;
        std::cout << "          , bf_vals" << std::endl;
        std::cout << "          , pre_vals" << std::endl;
        std::cout << "          , post_vals" << std::endl;
        std::cout << "          , in_vals" << std::endl;
        std::cout << "          , df_vals" << std::endl << "        );";
        std::cout << std::endl << "    }" << std::endl << std::endl;
    }

    d_root.get_left_child_ptr()->rotate_right();
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    a_root.get_left_child_ptr()->rotate_right();
#endif
    std::cout << "    a_root.get_left_child_ptr()->rotate_right();";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(" << std::endl;
    std::cout << "            a_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    d_root.get_left_child_ptr()->rotate_left();
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    a_root.get_left_child_ptr()->rotate_left();
#endif
    std::cout << "    a_root.get_left_child_ptr()->rotate_left();";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(" << std::endl;
    std::cout << "            a_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;

    d_root.begin()->clear();
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    a_root.begin()->clear();
#endif
    std::cout << std::endl << "    a_root.begin()->clear();" << std::endl;
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(" << std::endl;
    std::cout << "            a_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
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
        boost::tree_node::result_of::value_at_key<
            FNode const
          , example_keys::your_uint
        >::type data = boost::tree_node::get<example_keys::your_uint>(*itr);

        if (1 < data)
        {
            --data;
            itr->emplace_right(
                boost::fusion::make_pair<example_keys::your_uint>(data)
              , boost::fusion::make_pair<example_keys::your_char>('0' + data)
            );
            --data;
            itr->emplace_left(
                boost::fusion::make_pair<example_keys::your_uint>(data)
              , boost::fusion::make_pair<example_keys::your_char>('0' + data)
            );
        }
    }

    std::cout << std::endl << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION";
    std::cout << std::endl << (
        "    typedef boost::tree_node::with_accumulation<"
    ) << std::endl << (
        "                boost::tree_node::binary_node_base_gen<>"
    ) << std::endl << "              , DataMap" << std::endl;
    std::cout << "              , void" << std::endl;
    std::cout << "              , AccuYourUintKey" << std::endl;
    std::cout << "            >" << std::endl << "            FNode;";
    std::cout << std::endl << "    typedef boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl << (
        "                    boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        FNode const" << std::endl << (
        "                      , example_keys::your_uint"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        FNode const" << std::endl << (
        "                      , example_keys::your_char"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        FNode const" << std::endl << (
        "                      , AccuYourUintKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            MoreValues;" << std::endl;
    std::cout << "    typedef boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        FNode const" << std::endl << (
        "                      , example_keys::your_uint"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        FNode const" << std::endl << (
        "                      , example_keys::your_char"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        FNode const" << std::endl << (
        "                      , AccuYourUintKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            DFMoreValues;" << std::endl;
    std::cout << std::endl << "    FNode f_root(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::your_uint>(5)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::your_char>(\'5\')"
    ) << std::endl << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<FNode> itr(f_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl;
    std::cout << "        boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "            FNode const" << std::endl;
    std::cout << "          , example_keys::your_uint" << std::endl << (
        "        >::type data = boost::tree_node::get<example_keys::your_uint>"
    ) << "(*itr);" << std::endl << std::endl << "        if (1 < data)";
    std::cout << std::endl << "        {" << std::endl;
    std::cout << "            --data;" << std::endl;
    std::cout << "            itr->emplace_right(" << std::endl << "    " << (
        "            boost::fusion::make_pair<example_keys::your_uint>(data)"
    ) << std::endl << "              , boost::fusion::make_pair<example_keys";
    std::cout << "::your_char>(\'0\' + data)" << std::endl << "            );";
    std::cout << std::endl << "            --data;" << std::endl;
    std::cout << "            itr->emplace_left(" << std::endl << "    " << (
        "            boost::fusion::make_pair<example_keys::your_uint>(data)"
    ) << std::endl << "              , boost::fusion::make_pair<example_keys";
    std::cout << "::your_char>(\'0\' + data)" << std::endl << "            );";
    std::cout << std::endl << "        }" << std::endl << "    }" << std::endl;
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        MoreValues bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFMoreValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
    out_with_it(f_root);
    std::cout << "        test_node<f_node_case>(" << std::endl;
    std::cout << "            f_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;

    put(
        *f_root.get_right_child_ptr()->get_left_child_ptr()
      , example_keys::your_uint()
      , 7
    );
    std::cout << std::endl << "    put(" << std::endl << (
        "        *f_root.get_right_child_ptr()->get_left_child_ptr()"
    ) << std::endl << "      , example_keys::your_uint()" << std::endl;
    std::cout << "      , 7" << std::endl << "    );" << std::endl;
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        MoreValues bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFMoreValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
    out_with_it(f_root);
    std::cout << "        test_node<f_node_case>(" << std::endl;
    std::cout << "            f_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;
    std::cout << std::endl << "    //[example__gui__binary_node__types";
    std::cout << std::endl << (
        "    typedef boost::tree_node::with_accumulation<"
    ) << std::endl << (
        "                boost::tree_node::with_accumulation_base_gen<"
    ) << std::endl << (
        "                    boost::tree_node::binary_node_base_gen<>"
    ) << std::endl << "                  , HeightSumKey" << std::endl;
    std::cout << "                >" << std::endl;
    std::cout << "              , GUITable" << std::endl;
    std::cout << "              , void" << std::endl;
    std::cout << "              , MinPriorityKey" << std::endl;
    std::cout << "            >" << std::endl << "            GUINode;";
    std::cout << std::endl << "    typedef boost::container_gen<";
    std::cout << std::endl << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl << (
        "                    boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_location"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_height"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_priority"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , HeightSumKey"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , MinPriorityKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            GUIValues;" << std::endl;
    std::cout << "    typedef boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_location"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_height"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_priority"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , HeightSumKey"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , boost::tree_node::result_of::value_at_key<"
    ) << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , MinPriorityKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            DFGUIValues;" << std::endl;
    std::cout << "    //]" << std::endl;

    GUINode gui_root(
        boost::fusion::make_pair<example_keys::row_location>(20)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(64)
    );

    gui_root.emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(0)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(20)
    );
    gui_root.emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(3)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(88)
    )->emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(4)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(79)
    );
    gui_root.emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(5)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(36)
    )->emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(10)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(5)
    )->emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(12)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(19)
    );
    gui_root.emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(59)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(25)
    );
    gui_root.emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(55)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(91)
    )->emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(51)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(7)
    );
    gui_root.emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(42)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(19)
    )->emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(22)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(54)
    );
    std::cout << std::endl << "    //[example__gui__binary_node__build";
    std::cout << std::endl << "    GUINode gui_root("<< std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(20)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(64)"
    ) << std::endl << "    );" << std::endl;
    std::cout << "    gui_root.emplace_left(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(0)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(20)"
    ) << std::endl << "    );" << std::endl;
    std::cout << "    gui_root.emplace_left(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(3)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(4)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(88)"
    ) << std::endl << "    )->emplace_right(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(4)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(79)"
    ) << std::endl << "    );" << std::endl;
    std::cout << "    gui_root.emplace_left(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(5)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(4)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(36)"
    ) << std::endl << "    )->emplace_right(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(10)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(4)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(5)"
    ) << std::endl << "    )->emplace_right(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(4)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(19)"
    ) << std::endl << "    );" << std::endl;
    std::cout << "    gui_root.emplace_right(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(59)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(25)"
    ) << std::endl << "    );" << std::endl;
    std::cout << "    gui_root.emplace_right(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(55)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(91)"
    ) << std::endl << "    )->emplace_left(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(51)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(7)"
    ) << std::endl << "    );" << std::endl;
    std::cout << "    gui_root.emplace_right(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(42)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(19)"
    ) << std::endl << "    )->emplace_left(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::row_location>(22)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_height>(12)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::row_priority>(54)"
    ) << std::endl << "    );" << std::endl << "    //]" << std::endl;
    std::cout << std::endl << "    //[example__gui__binary_node__test";
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        GUIValues bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFGUIValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
    out_with_it(gui_root);
    std::cout << "        test_node<gui_node_case>(" << std::endl;
    std::cout << "            gui_root" << std::endl << "          , bf_vals";
    std::cout << std::endl << "          , pre_vals" << std::endl;
    std::cout << "          , post_vals" << std::endl << "          , in_vals";
    std::cout << std::endl << "          , df_vals" << std::endl;
    std::cout << "        );" << std::endl << "    }" << std::endl;
    std::cout << "    //]" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    std::cout << std::endl << "    return 0;" << std::endl << '}' << std::endl;
    std::cout << std::endl << "#if defined BOOST_MSVC" << std::endl;
    std::cout << "   #pragma warning (pop)" << std::endl;
    std::cout << "#endif" << std::endl << std::endl;

    return 0;
}


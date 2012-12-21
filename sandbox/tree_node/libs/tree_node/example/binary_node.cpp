// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_TYPEOF_COMPLIANT

#include <iostream>
#include <boost/config.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/typeof/binary_node.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/tree_node/pre_order_desc_iterator.hpp>
#include <boost/tree_node/post_order_iterator.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/tree_node/typeof/with_accumulation.hpp>
#endif

#include "type_definitions.hpp"
#include "output_preamble.hpp"
#include "output_functions.hpp"
#include "iterator_functions.hpp"

typedef boost::tree_node::with_height<
            boost::tree_node::with_position_gen<
                boost::tree_node::with_count_gen<
                    boost::tree_node::binary_node_gen
                >
            >
          , double
        >
        DNode;

#if !defined BOOST_NO_SFINAE
typedef boost::tree_node::with_accumulation<
            boost::tree_node::with_height_gen<
                boost::tree_node::with_accumulation_gen<
                    boost::tree_node::with_position_gen<
                        boost::tree_node::with_accumulation_gen<
                            boost::tree_node::with_count_gen<
                                boost::tree_node::with_accumulation_gen<
                                    boost::tree_node::binary_node_gen
                                >
                            >
                          , AccuAccuKey
                        >
                    >
                  , AccuCountKey
                >
            >
          , double
          , void
          , AccuHeightKey
        >
        ANode;
#endif  // BOOST_NO_SFINAE

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
typedef boost::tree_node::with_accumulation<
            boost::tree_node::binary_node_gen
          , DataMap
          , void
          , AccuYourUintKey
        >
        FNode;

void out_with_it(FNode const& f_node)
{
    iterator_out_bf_pre_post(f_node, output_uint_char_node(), 5);
    iterator_out_in_order(f_node, output_uint_char_node(), 5);
    iterator_out_df(f_node, output_uint_char_tree(2, 7, true));
}
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

template <typename Node>
void initialize(Node& root)
{
    for (boost::tree_node::breadth_first_iterator<Node> itr(root); itr; ++itr)
    {
        BOOST_AUTO_TPL(data, get(*itr, boost::tree_node::data_key()));

        if (1 < data)
        {
            itr->emplace_left(data - 2);
            itr->emplace_right(data - 1);
        }
    }
}

#if defined BOOST_NO_SFINAE
void out_with_it(DNode const& d_node)
{
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_in_order(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
}
#else  // !defined BOOST_NO_SFINAE
void out_with_them(DNode const& d_node, ANode const& a_node)
{
    std::cout << std::endl << "#if defined BOOST_NO_SFINAE";
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_in_order(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
    std::cout << "#else  // !defined BOOST_NO_SFINAE";
    iterator_out_bf_pre_post(a_node, output_node<boost::mpl::true_>(), 2);
    iterator_out_in_order(a_node, output_node<boost::mpl::true_>(), 2);
    iterator_out_df(a_node, output_tree<boost::mpl::true_>(4, 7, false));
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
}
#endif  // BOOST_NO_SFINAE

int main()
{
    DNode d_root(5.0);

    initialize(d_root);

#if !defined BOOST_NO_SFINAE
    ANode a_root(5.0);

    initialize(a_root);
#endif

    output_copyright_and_config_preamble();
    output_header_and_type_preamble();
    std::cout << "#include <boost/tree_node/typeof/binary_node.hpp>";
    std::cout << std::endl;
#if !defined BOOST_NO_SFINAE
    std::cout << std::endl << "#if defined BOOST_NO_SFINAE";
#endif
    std::cout << std::endl << (
        "typedef boost::tree_node::with_height<"
    ) << std::endl << (
        "            boost::tree_node::with_position_gen<"
    ) << std::endl << (
        "                boost::tree_node::with_count_gen<"
    ) << std::endl << (
        "                    boost::tree_node::binary_node_gen"
    ) << std::endl << "                >" << std::endl;
    std::cout << "            >" << std::endl;
    std::cout << "          , double" << std::endl;
    std::cout << "        >" << std::endl;
    std::cout << "        ANode;" << std::endl;
#if !defined BOOST_NO_SFINAE
    std::cout << "#else  // !defined BOOST_NO_SFINAE" << std::endl;
    std::cout << "typedef boost::tree_node::with_accumulation<" << std::endl;
    std::cout << "            boost::tree_node::with_height_gen<" << std::endl;
    std::cout << "                boost::tree_node::with_accumulation_gen<";
    std::cout << std::endl << (
        "                    boost::tree_node::with_position_gen<"
    ) << std::endl << (
        "                        boost::tree_node::with_accumulation_gen<"
    ) << std::endl << (
        "                            boost::tree_node::with_count_gen<"
    ) << std::endl << "                                ";
    std::cout << "boost::tree_node::with_accumulation_gen<" << std::endl << (
        "                                    boost::tree_node::binary_node_gen"
    ) << std::endl << "                                >" << std::endl;
    std::cout << "                            >" << std::endl;
    std::cout << "                          , AccuAccuKey" << std::endl;
    std::cout << "                        >" << std::endl;
    std::cout << "                    >" << std::endl;
    std::cout << "                  , AccuCountKey" << std::endl;
    std::cout << "                >" << std::endl;
    std::cout << "            >" << std::endl;
    std::cout << "          , double" << std::endl;
    std::cout << "          , void" << std::endl;
    std::cout << "          , AccuHeightKey" << std::endl;
    std::cout << "        >" << std::endl;
    std::cout << "        ANode;" << std::endl;
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
#endif  // BOOST_NO_SFINAE
    std::cout << std::endl << "typedef boost::container_gen<" << std::endl;
    std::cout << "            boost::dequeS" << std::endl;
    std::cout << "          , boost::tuples::tuple<" << std::endl;
    std::cout << "                BOOST_TYPEOF(" << std::endl;
    std::cout << "                    get(" << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                      , boost::tree_node::data_key()";
    std::cout << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl;
    std::cout << "                    get(" << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                      , boost::tree_node::height_key()";
    std::cout << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl;
    std::cout << "                    get(" << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                      , boost::tree_node::count_key()";
    std::cout << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "#if !defined BOOST_NO_SFINAE" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<"
    ) << std::endl << (
        "                        boost::tree_node::accumulation_key<>"
    ) << std::endl << (
        "                    >(boost::get_reference<ANode const>())"
    ) << std::endl << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<AccuHeightKey>("
    ) << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<AccuCountKey>("
    ) << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<AccuAccuKey>("
    ) << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
    std::cout << "            >" << std::endl << "        >::type";
    std::cout << std::endl << "        Values;" << std::endl;
    std::cout << "typedef boost::container_gen<" << std::endl;
    std::cout << "            boost::dequeS" << std::endl;
    std::cout << "          , boost::tuples::tuple<" << std::endl;
    std::cout << "                boost::tree_node::traversal_state";
    std::cout << std::endl << "              , BOOST_TYPEOF(" << std::endl;
    std::cout << "                    get(" << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                      , boost::tree_node::data_key()";
    std::cout << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl;
    std::cout << "                    get(" << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                      , boost::tree_node::height_key()";
    std::cout << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl;
    std::cout << "                    get(" << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl;
    std::cout << "                      , boost::tree_node::count_key()";
    std::cout << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "#if !defined BOOST_NO_SFINAE" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<"
    ) << std::endl << (
        "                        boost::tree_node::accumulation_key<>"
    ) << std::endl << (
        "                    >(boost::get_reference<ANode const>())"
    ) << std::endl << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<AccuHeightKey>("
    ) << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<AccuCountKey>("
    ) << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "              , BOOST_TYPEOF(" << std::endl << (
        "                    boost::tree_node::get<AccuAccuKey>("
    ) << std::endl << (
        "                        boost::get_reference<ANode const>()"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                )" << std::endl;
    std::cout << "#endif  // BOOST_NO_SFINAE" << std::endl;
    std::cout << "            >" << std::endl << "        >::type";
    std::cout << std::endl << "        DFValues;" << std::endl;
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl << "    ANode a_root(5.0);";
    std::cout << std::endl << std::endl << "    BOOST_CHECK(" << std::endl;
    std::cout << "        !a_root.get_parent_ptr()" << std::endl;
    std::cout << "//      , \"Parent member uninitialized.\"" << std::endl;
    std::cout << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<ANode> itr(a_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_AUTO(data, get(*itr, ";
    std::cout << "boost::tree_node::data_key()));" << std::endl << std::endl;
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
    std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
    out_with_it(d_root);
#else
    out_with_them(d_root, a_root);
#endif
    std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    {
        DNode::pointer d_p = d_root.get_left_child_ptr()->get_left_child_ptr();
        DNode::iterator d_child_itr = d_p->insert_left(d_root);
#if !defined BOOST_NO_SFINAE
        ANode::pointer a_p = a_root.get_left_child_ptr()->get_left_child_ptr();
        ANode::iterator a_child_itr = a_p->insert_left(a_root);
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
        std::cout << std::endl << "        ANode::pointer p = ";
        std::cout << "a_root.get_left_child_ptr()->get_left_child_ptr();";
        std::cout << std::endl << (
            "        ANode::iterator a_child_itr = p->insert_left(a_root);"
        ) << std::endl << (
            "        Values bf_vals, pre_vals, post_vals, in_vals;"
        ) << std::endl << "        DFValues df_vals;" << std::endl << (
            "        DFEmplacer emplacer;"
        ) << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
        std::cout << " in_vals, df_vals);" << std::endl << std::endl;

        d_root = *d_child_itr;
#if !defined BOOST_NO_SFINAE
        a_root = *a_child_itr;
#endif
        std::cout << "        a_root = *a_child_itr;" << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        in_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
        std::cout << " in_vals, df_vals);" << std::endl << std::endl;

        *(d_p = d_root.get_right_child_ptr()) = d_root;
#if !defined BOOST_NO_SFINAE
        *(a_p = a_root.get_right_child_ptr()) = a_root;
#endif
        std::cout << "        *(p = a_root.get_right_child_ptr()) = a_root;";
        std::cout << std::endl << "        test_node(*p, bf_vals, pre_vals, ";
        std::cout << "post_vals, in_vals, df_vals);" << std::endl << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        in_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
        std::cout << " in_vals, df_vals);" << std::endl;
        std::cout << "    }" << std::endl << std::endl;
    }

    d_root.get_right_child_ptr()->rotate_left();
#if !defined BOOST_NO_SFINAE
    a_root.get_right_child_ptr()->rotate_left();
#endif
    std::cout << "    a_root.get_right_child_ptr()->rotate_left();";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
    out_with_it(d_root);
#else
    out_with_them(d_root, a_root);
#endif
    std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    {
        DNode::pointer d_p(d_root.get_right_child_ptr()->get_right_child_ptr());
        DNode::iterator d_child_itr(d_p->emplace_right());

        put(*d_child_itr, boost::tree_node::data_key(), 7);

#if !defined BOOST_NO_SFINAE
        ANode::pointer a_p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator a_child_itr(a_p->emplace_right());

        put(*a_child_itr, boost::tree_node::data_key(), 7);
#endif
        std::cout << "    {" << std::endl << "        ANode::pointer ";
        std::cout << "p(a_root.get_right_child_ptr()->get_right_child_ptr());";
        std::cout << std::endl << (
            "        ANode::iterator p_child_itr(p->emplace_right());"
        ) << std::endl << (
            "        Values bf_vals, pre_vals, post_vals, in_vals;"
        ) << std::endl << "        DFValues df_vals;" << std::endl;
        std::cout << "        DFEmplacer emplacer;" << std::endl << std::endl;
        std::cout << (
            "        put(*p_child_itr, boost::tree_node::data_key(), 7);"
        );
#if defined BOOST_NO_SFINAE
        out_with_it(d_root);
#else
        out_with_them(d_root, a_root);
#endif
        std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
        std::cout << " in_vals, df_vals);" << std::endl;
        std::cout << "    }" << std::endl << std::endl;
    }

    d_root.get_left_child_ptr()->rotate_right();
#if !defined BOOST_NO_SFINAE
    a_root.get_left_child_ptr()->rotate_right();
#endif
    std::cout << "    a_root.get_left_child_ptr()->rotate_right();";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
    out_with_it(d_root);
#else
    out_with_them(d_root, a_root);
#endif
    std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    d_root.get_left_child_ptr()->rotate_left();
#if !defined BOOST_NO_SFINAE
    a_root.get_left_child_ptr()->rotate_left();
#endif
    std::cout << "    a_root.get_left_child_ptr()->rotate_left();";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
    out_with_it(d_root);
#else
    out_with_them(d_root, a_root);
#endif
    std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    d_root.begin()->clear();
#if !defined BOOST_NO_SFINAE
    a_root.begin()->clear();
#endif
    std::cout << "    a_root.begin()->clear();" << std::endl << std::endl;
    std::cout << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
#if defined BOOST_NO_SFINAE
    out_with_it(d_root);
#else
    out_with_them(d_root, a_root);
#endif
    std::cout << "        test_node(a_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl << "    }" << std::endl;

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
        BOOST_AUTO(data, boost::tree_node::get<example_keys::your_uint>(*itr));

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
    ) << std::endl << "                boost::tree_node::binary_node_gen";
    std::cout << std::endl << "              , DataMap" << std::endl;
    std::cout << "              , void" << std::endl;
    std::cout << "              , AccuYourUintKey" << std::endl;
    std::cout << "            >" << std::endl << "            FNode;";
    std::cout << std::endl << "    typedef boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    BOOST_TYPEOF(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_uint"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_char"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF(" << std::endl << (
        "                        boost::tree_node::get<AccuYourUintKey>("
    ) << std::endl << (
        "                            boost::get_reference<FNode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl << "                >";
    std::cout << std::endl << "            >::type" << std::endl;
    std::cout << "            MoreValues;" << std::endl;
    std::cout << "    typedef boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << "                  , BOOST_TYPEOF(";
    std::cout << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_uint"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF(" << std::endl << (
        "                        boost::tree_node::get<"
    ) << std::endl << (
        "                            example_keys::your_char"
    ) << std::endl << (
        "                        >(boost::get_reference<FNode const>())"
    ) << std::endl << "                    )" << std::endl;
    std::cout << "                  , BOOST_TYPEOF(" << std::endl << (
        "                        boost::tree_node::get<AccuYourUintKey>("
    ) << std::endl << (
        "                            boost::get_reference<FNode const>()"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    )" << std::endl << "                >";
    std::cout << std::endl << "            >::type" << std::endl;
    std::cout << "            DFMoreValues;" << std::endl << std::endl;
    std::cout << "    FNode f_root(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::your_uint>(5)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::your_char>(\'5\')"
    ) << std::endl << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<FNode> itr(f_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_AUTO(data, boost::tree_node::get<example_";
    std::cout << "keys::your_uint>(*itr));" << std::endl << std::endl;
    std::cout << "        if (1 < data)" << std::endl << "        {";
    std::cout << std::endl << "            --data;" << std::endl;
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
    std::cout << "        DFEmplacer emplacer;" << std::endl;
    out_with_it(f_root);
    std::cout << "        test_f_node(f_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    put(
        *f_root.get_right_child_ptr()->get_left_child_ptr()
      , example_keys::your_uint()
      , 7
    );
    std::cout << "    put(";
    std::cout << std::endl << (
        "        *f_root.get_right_child_ptr()->get_left_child_ptr()"
    ) << std::endl << "      , example_keys::your_uint()" << std::endl;
    std::cout << "      , 7" << std::endl << "    );" << std::endl;
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        MoreValues bf_vals, pre_vals, post_vals, in_vals;";
    std::cout << std::endl << "        DFMoreValues df_vals;" << std::endl;
    std::cout << "        DFEmplacer emplacer;" << std::endl;
    out_with_it(f_root);
    std::cout << "        test_f_node(f_root, bf_vals, pre_vals, post_vals,";
    std::cout << " in_vals, df_vals);" << std::endl << "    }" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    std::cout << std::endl << "    return 0;" << std::endl << '}' << std::endl;
    std::cout << std::endl << "#if defined BOOST_MSVC" << std::endl;
    std::cout << "   #pragma warning (pop)" << std::endl;
    std::cout << "#endif" << std::endl << std::endl;

    return 0;
}


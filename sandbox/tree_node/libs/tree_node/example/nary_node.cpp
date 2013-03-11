// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//#define __BOOST_TEST_TREE_NODE_TEST_SPLICE_ONE_ELEMENT__

#include <iterator>
#include <iostream>
#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/typeof/boost/container_gen/selectors.hpp>
#include <boost/typeof/boost/rational.hpp>
#include <boost/typeof/boost/tree_node/nary_node.hpp>
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

template <typename Selector, typename Node>
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
            for (std::size_t i = 0; i < data; ++i)
            {
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                if (std::tr1::is_same<Selector,boost::slistS>::value)
                    (*itr).emplace(data - 1 - i);
                else
#endif
                (*itr).emplace(i);
            }
        }
    }
}

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename DNode, typename ANode>
void out_with_them(DNode const& d_node, ANode const& a_node)
{
    std::cout << std::endl << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION";
    iterator_out_bf_pre_post(a_node, output_node<boost::mpl::true_>(), 1);
    iterator_out_df(a_node, output_tree<boost::mpl::true_>(2, 7, true));
    std::cout << "#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION";
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
}

template <typename FNode>
void out_with_all(FNode const& f_node)
{
    iterator_out_bf_pre_post(f_node, output_uint_char_node(), 5);
    iterator_out_df(f_node, output_uint_char_tree(2, 7, true));
}
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename DNode>
void out_with_it(DNode const& d_node)
{
    iterator_out_bf_pre_post(d_node, output_node<boost::mpl::false_>(), 7);
    iterator_out_df(d_node, output_tree<boost::mpl::false_>(2, 7, true));
}
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

template <typename Selector>
void example()
{
    typedef boost::tree_node::with_height<
                boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_count_base_gen<
                        boost::tree_node::nary_node_base_gen<Selector>
                    >
                >
              , boost::rational<long>
            >
            DNode;

    DNode d_root(5);

    initialize<Selector>(d_root);

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
              boost::tree_node::with_height_base_gen<
                boost::tree_node::with_accumulation_base_gen<
                  boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_accumulation_base_gen<
                      boost::tree_node::with_count_base_gen<
                        boost::tree_node::with_accumulation_base_gen<
                          boost::tree_node::nary_node_base_gen<Selector>
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

    ANode a_root(5);

    initialize<Selector>(a_root);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    output_copyright_and_config_preamble();
    std::cout << std::endl << "#include <iterator>";
    output_header_and_type_preamble();
    std::cout << "#include <boost/typeof/boost/tree_node/nary_node.hpp>";
    std::cout << std::endl << std::endl << "template <typename Selector>";
    std::cout << std::endl << "void test()" << std::endl << '{' << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl << (
        "    typedef boost::tree_node::with_accumulation<"
    ) << std::endl << "              boost::tree_node::with_height_base_gen<";
    std::cout << std::endl << (
        "                boost::tree_node::with_accumulation_base_gen<"
    ) << std::endl << (
        "                  boost::tree_node::with_position_base_gen<"
    ) << std::endl << (
        "                    boost::tree_node::with_accumulation_base_gen<"
    ) << std::endl << (
        "                      boost::tree_node::with_count_base_gen<"
    ) << std::endl << "                        boost";
    std::cout << "::tree_node::with_accumulation_base_gen<" << std::endl << (
        "                          boost::tree_node::nary_node_base_gen"
    ) << "<Selector>" << std::endl << "                        >" << std::endl;
    std::cout << "                      >" << std::endl;
    std::cout << "                    , AccuAccuKey" << std::endl;
    std::cout << "                    >" << std::endl;
    std::cout << "                  >" << std::endl;
    std::cout << "                , AccuCountKey" << std::endl;
    std::cout << "                >" << std::endl << "              >";
    std::cout << std::endl << "            , boost::rational<long>";
    std::cout << std::endl << "            , void" << std::endl;
    std::cout << "            , AccuHeightKey" << std::endl << "            >";
    std::cout << std::endl << "            ANode;" << std::endl << (
        "#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION"
    ) << std::endl;
#endif  // BOOST_NO_SFINAE
    std::cout << "    typedef boost::tree_node::with_height<" << std::endl << (
        "                boost::tree_node::with_position_base_gen<"
    ) << std::endl << (
        "                    boost::tree_node::with_count_base_gen<"
    ) << std::endl << "                        " << (
        "boost::tree_node::nary_node_base_gen<Selector>"
    ) << std::endl << "                    >" << std::endl;
    std::cout << "                >" << std::endl;
    std::cout << "              , boost::rational<long>" << std::endl;
    std::cout << "            >" << std::endl;
    std::cout << "            ANode;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
#endif
    output_container_type_preamble();
    std::cout << std::endl << "    ANode a_root(5);" << std::endl;
    std::cout << std::endl << "    BOOST_CHECK(" << std::endl;
    std::cout << "        !a_root.get_parent_ptr()" << std::endl;
    std::cout << "//      , \"Parent member uninitialized.\"" << std::endl;
    std::cout << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<ANode> itr(a_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl << (
        "        typename ANode::traits::data_type const& data = get("
    ) << std::endl << "            *itr" << std::endl;
    std::cout << "          , boost::tree_node::data_key()" << std::endl;
    std::cout << "        );" << std::endl << std::endl;
    std::cout << "        if (1 < data)";
    std::cout << std::endl << "        {" << std::endl;
    std::cout << "            for (std::size_t i = 0; i < data; ++i)";
    std::cout << std::endl << "            {" << std::endl << (
        "                typename ANode::iterator child_itr("
    ) << std::endl << (
        "#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION"
    ) << std::endl << (
        "                    (std::tr1::is_same<Selector,boost::slistS>::value"
    ) << ") ? (" << std::endl;
    std::cout << "                        (*itr).emplace(data - 1 - i)";
    std::cout << std::endl << "                    ) :" << std::endl;
    std::cout << "#endif" << std::endl;
    std::cout << "                    (*itr).emplace(i)";
    std::cout << std::endl << "                );" << std::endl << (
        "                typename ANode::const_pointer const_child(&*child_itr"
    ) << ");" << std::endl << "                BOOST_CHECK(" << std::endl;
    std::cout << "                    (*child_itr).get_parent_ptr() == &*itr";
    std::cout << std::endl << (
        "//                  , \"Ctor not linking child to parent.\""
    ) << std::endl << "                );" << std::endl;
    std::cout << "                BOOST_CHECK(" << std::endl;
    std::cout << "                    (" << std::endl << (
        "                        (*child_itr).get_parent_ptr()"
    ) << std::endl << (
        "                    ) == (*const_child).get_parent_ptr()"
    ) << std::endl;
    std::cout << "//                  , \"Why are these pointers different?\"";
    std::cout << std::endl << "                );" << std::endl << std::endl;
    std::cout << "                {" << std::endl << (
        "                    typename ANode::iterator c_itr = (*itr).begin();"
    ) << std::endl << std::endl << (
        "#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION"
    ) << std::endl << "                    " << (
        "if (!std::tr1::is_same<Selector,boost::slistS>::value)"
    ) << std::endl << "#endif" << std::endl;
    std::cout << "                    std::advance(c_itr, i);" << std::endl;
    std::cout << "                    BOOST_CHECK(" << std::endl;
    std::cout << "                        &*child_itr == &*c_itr" << std::endl;
    std::cout << "//                      " << (
        ", \"Ctor not linking parent to child.\""
    ) << std::endl << "                    );" << std::endl;
    std::cout << "                }" << std::endl << "            }";
    std::cout << std::endl << "        }" << std::endl << "    }";
    std::cout << std::endl << std::endl << "    {" << std::endl;
    std::cout << "        Values bf_vals, pre_vals, post_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_vals,";
    std::cout << " post_vals, df_vals);" << std::endl;
    std::cout << "    }" << std::endl << std::endl;

    {
        typename DNode::iterator d_child_itr(
            (*(++d_root.begin())).insert(d_root)
        );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        typename ANode::iterator a_child_itr(
            (*(++a_root.begin())).insert(a_root)
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
        ) << std::endl << (
            "        BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));"
        ) << std::endl << "        BOOST_CHECK(" << (
            "test_node_copies(df_d_root_itr, df_d_copy_itr));"
        ) << std::endl << "    }" << std::endl << std::endl << "    {";
        std::cout << std::endl << (
            "        typename ANode::iterator a_child_itr("
        ) << std::endl << "            (*(++a_root.begin())).insert(a_root)";
        std::cout << std::endl << "        );" << std::endl;
        std::cout << "        Values bf_vals, pre_vals, post_vals;";
        std::cout << std::endl << "        DFValues df_vals;" << std::endl;
        std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_";
        std::cout << "vals, post_vals, df_vals);" << std::endl << std::endl;

        d_root = *d_child_itr;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        a_root = *a_child_itr;
#endif
        std::cout << "        a_root = *a_child_itr;" << std::endl;
        std::cout << "        bf_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_";
        std::cout << "vals, post_vals, df_vals);" << std::endl << std::endl;

        d_child_itr = d_root.begin();
        std::advance(d_child_itr, 4);
        d_child_itr = (*d_child_itr).begin();
        *d_child_itr = d_root;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        a_child_itr = a_root.begin();
        std::advance(a_child_itr, 4);
        a_child_itr = (*a_child_itr).begin();
        *a_child_itr = a_root;
#endif
        std::cout << "        a_child_itr = a_root.begin();" << std::endl;
        std::cout << "        std::advance(a_child_itr, 4);" << std::endl;
        std::cout << "        a_child_itr = (*a_child_itr).begin();";
        std::cout << std::endl << "        *a_child_itr = a_root;";
        std::cout << std::endl << "        test_node<a_node_case>";
        std::cout << "(*a_child_itr, bf_vals, pre_vals, post_vals, df_vals);";
        std::cout << std::endl << std::endl << "        bf_vals.clear();";
        std::cout << std::endl << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
        std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_";
        std::cout << "vals, post_vals, df_vals);" << std::endl << std::endl;

        d_child_itr = (*d_child_itr).begin();
        std::advance(d_child_itr, 2);

        typename DNode::iterator d_desc_itr = d_child_itr;
        typename DNode::iterator d_src_itr = (*(++d_desc_itr)).begin();
        typename DNode::iterator d_end_itr = (*d_desc_itr).end();

        (*d_child_itr).splice(
            ++(*d_child_itr).begin()
          , *d_desc_itr
          , ++d_src_itr
          , d_end_itr
        );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        a_child_itr = (*a_child_itr).begin();
        std::advance(a_child_itr, 2);

        typename ANode::iterator a_desc_itr = a_child_itr;
        typename ANode::iterator a_src_itr = (*(++a_desc_itr)).begin();
        typename ANode::iterator a_end_itr = (*a_desc_itr).end();

        (*a_child_itr).splice(
            ++(*a_child_itr).begin()
          , *a_desc_itr
          , ++a_src_itr
          , a_end_itr
        );
#endif
        std::cout << "        a_child_itr = (*a_child_itr).begin();";
        std::cout << std::endl << "        std::advance(a_child_itr, 2);";
        std::cout << std::endl << std::endl << "        typename ANode::";
        std::cout << "iterator a_desc_itr = a_child_itr;" << std::endl;
        std::cout << "        typename ANode::iterator a_src_itr";
        std::cout << " = (*(++a_desc_itr)).begin();" << std::endl;
        std::cout << "        typename ANode::iterator a_end_itr";
        std::cout << " = (*a_desc_itr).end();" << std::endl << std::endl;
        std::cout << "        (*a_child_itr).splice(" << std::endl;
        std::cout << "            ++(*a_child_itr).begin()" << std::endl;
        std::cout << "          , *a_desc_itr" << std::endl;
        std::cout << "          , ++a_src_itr" << std::endl;
        std::cout << "          , a_end_itr" << std::endl << "        );";
        std::cout << std::endl << "        bf_vals.clear();" << std::endl;
        std::cout << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif

#if defined __BOOST_TEST_TREE_NODE_TEST_SPLICE_ONE_ELEMENT__
        std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_";
        std::cout << "vals, post_vals, df_vals);" << std::endl << std::endl;

        d_child_itr = d_root.begin();
        std::advance(d_child_itr, 2);
        d_desc_itr = d_child_itr;
        d_src_itr = (*(++d_desc_itr)).begin();
        (*d_child_itr).splice(
            ++(*d_child_itr).begin()
          , *d_desc_itr
          , ++d_src_itr
        );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        a_child_itr = a_root.begin();
        std::advance(a_child_itr, 2);
        a_desc_itr = a_child_itr;
        a_src_itr = (*(++a_desc_itr)).begin();
        (*a_child_itr).splice(
            ++(*a_child_itr).begin()
          , *a_desc_itr
          , ++a_src_itr
        );
#endif
        std::cout << "        a_child_itr = a_root.begin();" << std::endl;
        std::cout << "        std::advance(a_child_itr, 2);" << std::endl;
        std::cout << "        a_desc_itr = a_child_itr;" << std::endl;
        std::cout << "        a_src_itr = (*(++a_desc_itr)).begin();";
        std::cout << std::endl << "        (*a_child_itr).splice(";
        std::cout << std::endl << "            ++(*a_child_itr).begin()";
        std::cout << std::endl << "          , *a_desc_itr" << std::endl;
        std::cout << "          , ++a_src_itr" << std::endl;
        std::cout << "        );" << std::endl << "        bf_vals.clear();";
        std::cout << std::endl << "        pre_vals.clear();" << std::endl;
        std::cout << "        post_vals.clear();" << std::endl;
        std::cout << "        df_vals.clear();" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        out_with_them(d_root, a_root);
#else
        out_with_it(d_root);
#endif
#endif  // __BOOST_TEST_TREE_NODE_TEST_SPLICE_ONE_ELEMENT__

        std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_";
        std::cout << "vals, post_vals, df_vals);" << std::endl;
        std::cout << "    }" << std::endl << std::endl;
    }

    {
        typename DNode::iterator d_child_itr(d_root.begin());

        std::advance(d_child_itr, 3);
        (*d_child_itr).clear();
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    {
        typename ANode::iterator a_child_itr(a_root.begin());

        std::advance(a_child_itr, 3);
        (*a_child_itr).clear();
    }
#endif

    std::cout << "    {" << std::endl << (
        "        typename ANode::iterator a_child_itr(a_root.begin());"
    ) << std::endl << std::endl << "        std::advance(a_child_itr, 3);";
    std::cout << std::endl << "        (*a_child_itr).clear();" << std::endl;
    std::cout << std::endl << "        Values bf_vals, pre_vals, post_vals;";
    std::cout << std::endl << "        DFValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    out_with_them(d_root, a_root);
#else
    out_with_it(d_root);
#endif
    std::cout << "        test_node<a_node_case>(a_root, bf_vals, pre_vals,";
    std::cout << " post_vals, df_vals);" << std::endl << "    }" << std::endl;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::nary_node_base_gen<Selector>
              , DataMap
              , void
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
        typename boost::tree_node::result_of::value_at_key<
            FNode const
          , example_keys::your_uint
        >::type data = boost::tree_node::get<example_keys::your_uint>(*itr);

        if (1 < data)
        {
            for (unsigned int i = 0; i < data; ++i)
            {
                if (std::tr1::is_same<Selector,boost::slistS>::value)
                {
                    (*itr).emplace(
                        boost::fusion::make_pair<example_keys::your_uint>(
                            data - 1 - i
                        )
                      , boost::fusion::make_pair<example_keys::your_char>(
                            '0' + data - 1 - i
                        )
                    );
                }
                else
                {
                    (*itr).emplace(
                        boost::fusion::make_pair<example_keys::your_uint>(i)
                      , boost::fusion::make_pair<example_keys::your_char>(
                            '0' + i
                        )
                    );
                }
            }
        }
    }

    std::cout << std::endl << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION";
    std::cout << std::endl << (
        "    typedef boost::tree_node::with_accumulation<"
    ) << std::endl << (
        "                boost::tree_node::nary_node_base_gen<Selector>"
    ) << std::endl << "              , DataMap" << std::endl;
    std::cout << "              , void" << std::endl;
    std::cout << "              , AccuYourUintKey" << std::endl;
    std::cout << "            >" << std::endl << "            FNode;";
    output_container_fused_type_preamble();
    std::cout << std::endl << "    FNode f_root(" << std::endl << (
        "        boost::fusion::make_pair<example_keys::your_uint>(5)"
    ) << std::endl << (
        "      , boost::fusion::make_pair<example_keys::your_char>(\'5\')"
    ) << std::endl << "    );" << std::endl << std::endl;
    std::cout << "    for (" << std::endl << (
        "        boost::tree_node::breadth_first_iterator<FNode> itr(f_root);"
    ) << std::endl << "        itr;" << std::endl << "        ++itr";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl;
    std::cout << "        typename boost::tree_node::result_of::value_at_key<";
    std::cout << std::endl << "            FNode const" << std::endl;
    std::cout << "          , example_keys::your_uint" << std::endl << (
        "        >::type data = boost::tree_node::get<example_keys::your_uint>"
    ) << "(*itr);" << std::endl << std::endl;
    std::cout << "        if (1 < data)" << std::endl << "        {";
    std::cout << std::endl << (
        "            for (unsigned int i = 0; i < data; ++i)"
    ) << std::endl << "            {" << std::endl << (
        "                if (std::tr1::is_same<Selector,boost::slistS>::value)"
    ) << std::endl << "                {" << std::endl;
    std::cout << "                    (*itr).emplace(" << std::endl << (
        "                        boost::fusion::make_pair<example_keys::your_"
    ) << "uint>(" << std::endl << "                            data - 1 - i";
    std::cout << std::endl << "                        )" << std::endl << (
        "                      , boost::fusion::make_pair<example_keys::your_"
    ) << "char>(" << std::endl << (
        "                            \'0\' + data - 1 - i"
    ) << std::endl << "                        )" << std::endl;
    std::cout << "                    );" << std::endl << "                }";
    std::cout << std::endl << "                else" << std::endl;
    std::cout << "                {" << std::endl;
    std::cout << "                    (*itr).emplace(" << std::endl << (
        "                        boost::fusion::make_pair<example_keys::your_"
    ) << "uint>(i)" << std::endl << "                      , boost::" << (
        "fusion::make_pair<example_keys::your_char>("
    ) << std::endl << "                            \'0\' + i" << std::endl;
    std::cout << "                        )" << std::endl;
    std::cout << "                    );" << std::endl;
    std::cout << "                }" << std::endl;
    std::cout << "            }" << std::endl;
    std::cout << std::endl << "        }" << std::endl << "    }" << std::endl;
    std::cout << std::endl << "    {" << std::endl;
    std::cout << "        MoreValues bf_vals, pre_vals, post_vals;";
    std::cout << std::endl << "        DFMoreValues df_vals;" << std::endl;
    std::cout << "        Emplacer emplacer;" << std::endl;
    out_with_all(f_root);
    std::cout << "        test_node<f_node_case>(f_root, bf_vals, pre_vals,";
    std::cout << " post_vals, df_vals);" << std::endl << std::endl << (
        "        typename FNode::iterator f_child_itr(f_root.begin());"
    ) << std::endl << std::endl << "        std::advance(f_child_itr, 3);";
    std::cout << std::endl << "        f_child_itr = (*f_child_itr).begin();";
    std::cout << std::endl << "        std::advance(f_child_itr, 2);";
    std::cout << std::endl << "        " << (
        "boost::tree_node::put(*f_child_itr, example_keys::your_uint(), 7);"
    ) << std::endl << "        bf_vals.clear();" << std::endl;
    std::cout << "        pre_vals.clear();" << std::endl;
    std::cout << "        post_vals.clear();" << std::endl;
    std::cout << "        df_vals.clear();" << std::endl;

    {
        typename FNode::iterator f_child_itr(f_root.begin());

        std::advance(f_child_itr, 3);
        f_child_itr = (*f_child_itr).begin();
        std::advance(f_child_itr, 2);
        put(*f_child_itr, example_keys::your_uint(), 7);
    }

    out_with_all(f_root);
    std::cout << "        test_node<f_node_case>(f_root, bf_vals, pre_vals,";
    std::cout << " post_vals, df_vals);" << std::endl << "    }" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    std::cout << '}' << std::endl << std::endl << "#if defined BOOST_MSVC";
    std::cout << std::endl << "   #pragma warning (pop)" << std::endl;
    std::cout << "#endif" << std::endl << std::endl;
    std::cout << "#if defined BOOST_TYPEOF_EMULATION" << std::endl << (
        "#include <boost/typeof/boost/ptr_container/ptr_vector.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/ptr_container/ptr_deque.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/ptr_container/ptr_list.hpp>"
    ) << std::endl << "#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION";
    std::cout << std::endl << (
        "#include <boost/typeof/boost/container/vector.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/container/stable_vector.hpp>"
    ) << std::endl << "#include <boost/typeof/boost/container/deque.hpp>";
    std::cout << std::endl << (
        "#include <boost/typeof/boost/container/list.hpp>"
    ) << std::endl << "#include <boost/typeof/boost/container/slist.hpp>";
    std::cout << std::endl << (
        "#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION"
    ) << std::endl << "#endif  // BOOST_TYPEOF_EMULATION" << std::endl;
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl;
    std::cout << "    test<boost::ptr_vecS>();" << std::endl;
    std::cout << "    test<boost::ptr_dequeS>();" << std::endl;
    std::cout << "    test<boost::ptr_listS>();" << std::endl << (
        "#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION"
    ) << std::endl << (
        "    test<boost::vector_selector<boost::mpl::true_> >();"
    ) << std::endl << "//    test<boost::stable_vecS>();" << std::endl;
    std::cout << "//    test<boost::deque_selector<boost::mpl::true_> >();";
    std::cout << std::endl << (
        "    test<boost::list_selector<boost::mpl::true_> >();"
    ) << std::endl << "    test<boost::slistS>();" << std::endl;
    std::cout << "#endif" << std::endl << std::endl;
    std::cout << "    return 0;" << std::endl << '}' << std::endl << std::endl;
}

#if defined BOOST_TYPEOF_EMULATION
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/ptr_container/ptr_vector.hpp>
#elif defined __BOOST_TEST_TREE_NODE_TEST_CONTAINER_DEQUE__
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/container/deque.hpp>
#elif defined __BOOST_TEST_TREE_NODE_TEST_STABLE_VECTOR__
#include <boost/typeof/boost/container/stable_vector.hpp>
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/container/slist.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#endif  // BOOST_TYPEOF_EMULATION

int main()
{
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    example<boost::ptr_vecS>();
#elif defined __BOOST_TEST_TREE_NODE_TEST_CONTAINER_DEQUE__
    example<boost::deque_selector<boost::mpl::true_> >();
#elif defined __BOOST_TEST_TREE_NODE_TEST_STABLE_VECTOR__
    example<boost::stable_vecS>();
#else
    example<boost::slistS>();
#endif
    return 0;
}


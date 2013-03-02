// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/tree_node/preprocessor.hpp>
#include "output_preamble.hpp"

void output_copyright_and_config_preamble()
{
    std::cout << "// Copyright (C) 2012-2013 Cromwell D. Enage" << std::endl;
    std::cout << (
        "// Distributed under the Boost Software License, Version 1.0."
    ) << std::endl << "// (See accompanying file LICENSE_1_0.txt or copy at";
    std::cout << std::endl << "// http://www.boost.org/LICENSE_1_0.txt)";
    std::cout << std::endl << std::endl << "#include <boost/config.hpp>";
    std::cout << std::endl << std::endl << "#if defined BOOST_MSVC";
    std::cout << std::endl << "    #pragma warning (push)" << std::endl;
    std::cout << "    #pragma warning (disable : 4996)  // fn called w/params";
    std::cout << " that may be unsafe" << std::endl << "#endif" << std::endl;
}

void output_header_and_type_preamble()
{
    std::cout << std::endl << "#include <boost/tuple/tuple.hpp>" << std::endl;
    std::cout << "#include <boost/typeof/boost/rational.hpp>" << std::endl;
    std::cout << "#include <boost/typeof/boost/container_gen/selectors.hpp>";
    std::cout << std::endl << (
        "#include <boost/container_gen/container_gen.hpp>"
    ) << std::endl << (
        "#include <boost/container_gen/emplace_function_gen.hpp>"
    ) << std::endl << (
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        "#include <boost/tree_node/preprocessor.hpp>"
    ) << std::endl << (
#endif
        "#include <boost/tree_node/intrinsic/value_at_key.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/tree_node/with_count.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/tree_node/with_height.hpp>"
    ) << std::endl << (
        "#include <boost/typeof/boost/tree_node/with_position.hpp>"
    ) << std::endl << std::endl;
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl << (
        "#include <boost/typeof/boost/tree_node/with_accumulation.hpp>"
    ) << std::endl << "#endif" << std::endl << std::endl;
    std::cout << "#include \"../example/type_definitions.hpp\"" << std::endl;
    std::cout << "#include \"iterator_functions.hpp\"" << std::endl;
    std::cout << std::endl << (
        "typedef boost::emplace_function_gen<boost::dequeS>::type"
    ) << std::endl << "        Emplacer;" << std::endl << std::endl;
}

void output_container_type_preamble()
{
    std::cout << std::endl << "    typedef typename boost::container_gen<";
    std::cout << std::endl << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl << (
        "                    typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , boost::tree_node::data_key";
    std::cout << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , boost::tree_node::height_key";
    std::cout << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , boost::tree_node::count_key";
    std::cout << std::endl << "                    >::type" << std::endl;
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl << (
        "                      , boost::tree_node::accumulation_key<>"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , AccuHeightKey" << std::endl;
    std::cout << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , AccuCountKey" << std::endl;
    std::cout << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , AccuAccuKey" << std::endl;
    std::cout << "                    >::type" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            Values;" << std::endl;
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , boost::tree_node::data_key";
    std::cout << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , boost::tree_node::height_key";
    std::cout << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , boost::tree_node::count_key";
    std::cout << std::endl << "                    >::type" << std::endl;
    std::cout << "#if defined BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl << (
        "                      , boost::tree_node::accumulation_key<>"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , AccuHeightKey" << std::endl;
    std::cout << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , AccuCountKey" << std::endl;
    std::cout << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl;
    std::cout << "                        ANode const" << std::endl;
    std::cout << "                      , AccuAccuKey" << std::endl;
    std::cout << "                    >::type" << std::endl;
    std::cout << "#endif  // BOOST_TREE_NODE_CAN_USE_FUSION" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            DFValues;" << std::endl;
}

void output_container_fused_type_preamble()
{
    std::cout << std::endl << "    typedef typename boost::container_gen<";
    std::cout << std::endl << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl << (
        "                    typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        FNode const";
    std::cout << std::endl << (
        "                      , example_keys::your_uint"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        FNode const";
    std::cout << std::endl << (
        "                      , example_keys::your_char"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        FNode const";
    std::cout << std::endl << (
        "                      , AccuYourUintKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            MoreValues;" << std::endl;
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        FNode const";
    std::cout << std::endl << (
        "                      , example_keys::your_uint"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        FNode const";
    std::cout << std::endl << (
        "                      , example_keys::your_char"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        FNode const";
    std::cout << std::endl << (
        "                      , AccuYourUintKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            DFMoreValues;" << std::endl;
}

void output_container_gui_type_preamble()
{
    std::cout << std::endl << "    typedef typename boost::container_gen<";
    std::cout << std::endl << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl << (
        "                    typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_location"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_height"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_priority"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , HeightSumKey"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , MinPriorityKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            GUIValues;" << std::endl;
    std::cout << "    typedef typename boost::container_gen<" << std::endl;
    std::cout << "                boost::dequeS" << std::endl;
    std::cout << "              , boost::tuples::tuple<" << std::endl;
    std::cout << "                    boost::tree_node::traversal_state";
    std::cout << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_location"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_height"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , example_keys::row_priority"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , HeightSumKey"
    ) << std::endl << "                    >::type" << std::endl << (
        "                  , typename boost::tree_node::result_of::value_at_"
    ) << "key<" << std::endl << "                        GUINode const";
    std::cout << std::endl << (
        "                      , MinPriorityKey"
    ) << std::endl << "                    >::type" << std::endl;
    std::cout << "                >" << std::endl << "            >::type";
    std::cout << std::endl << "            DFGUIValues;" << std::endl;
}


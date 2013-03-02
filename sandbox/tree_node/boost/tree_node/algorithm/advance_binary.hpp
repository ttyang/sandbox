// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_ADVANCE_BINARY_HPP
#define BOOST_TREE_NODE_ALGORITHM_ADVANCE_BINARY_HPP

#include <boost/config.hpp>

#if !defined BOOST_NO_CXX11_NULLPTR
#include <cstddef>
#endif

#include <boost/utility/value_init.hpp>
#include <boost/tree_node/key/count.hpp>
#include <boost/assert.hpp>

//[reference__tree_node__advance_binary
namespace boost { namespace tree_node {

    template <typename NodePointer, typename Difference>
    NodePointer
        advance_binary(
            NodePointer node_ptr
          , Difference difference
          , NodePointer const& root_ptr
        );

    template <typename NodePointer, typename Difference>
    NodePointer advance_binary(NodePointer node_ptr, Difference difference);

    //<-
    template <typename NodePointer, typename Difference>
    NodePointer
        advance_binary(
            NodePointer node_ptr
          , Difference difference
          , NodePointer const& root_ptr
        )
    {
        static Difference const zero_difference = ::boost::initialized_value;

#if defined BOOST_NO_CXX11_NULLPTR
        for (
            NodePointer child_ptr = ::boost::initialized_value;
            difference;
            child_ptr = ::boost::initialized_value
        )
#else
        for (NodePointer child_ptr = nullptr; difference; child_ptr = nullptr)
#endif
        {
            if (difference < zero_difference)
            {
                if ((child_ptr = node_ptr->get_left_child_ptr()))
                {
                    if (-(++difference) < get(*child_ptr, count_key()))
                    {
                        node_ptr = child_ptr;

                        if ((child_ptr = node_ptr->get_right_child_ptr()))
                        {
                            difference += get(*child_ptr, count_key());
                        }

                        continue;
                    }

                    if (node_ptr == root_ptr)
                    {
                        BOOST_ASSERT_MSG(
                            -difference == get(*child_ptr, count_key())
                          , "Result out of bounds."
                        );
#if defined BOOST_NO_CXX11_NULLPTR
                        node_ptr = ::boost::initialized_value;
#else
                        node_ptr = nullptr;
#endif
                        break;
                    }

                    child_ptr = node_ptr;

                    if (!(node_ptr = node_ptr->get_parent_ptr()))
                    {
                        BOOST_ASSERT_MSG(
                            -difference == get(*child_ptr, count_key())
                          , "Result out of bounds."
                        );
                        break;
                    }

                    --difference;
                }
                else  // if (!node_ptr->get_left_child_ptr())
                {
                    if (node_ptr == root_ptr)
                    {
                        BOOST_ASSERT_MSG(
                            !++difference
                          , "Result out of bounds."
                        );
#if defined BOOST_NO_CXX11_NULLPTR
                        node_ptr = ::boost::initialized_value;
#else
                        node_ptr = nullptr;
#endif
                        break;
                    }

                    child_ptr = node_ptr;

                    if (!(node_ptr = node_ptr->get_parent_ptr()))
                    {
                        BOOST_ASSERT_MSG(
                            !++difference
                          , "Result out of bounds."
                        );
                        break;
                    }
                }
            }
            else  // if (zero_difference < difference)
            {
                if ((child_ptr = node_ptr->get_right_child_ptr()))
                {
                    if (--difference < get(*child_ptr, count_key()))
                    {
                        node_ptr = child_ptr;

                        if ((child_ptr = node_ptr->get_left_child_ptr()))
                        {
                            difference -= get(*child_ptr, count_key());
                        }

                        continue;
                    }

                    if (node_ptr == root_ptr)
                    {
                        BOOST_ASSERT_MSG(
                            difference == get(*child_ptr, count_key())
                          , "Result out of bounds."
                        );
#if defined BOOST_NO_CXX11_NULLPTR
                        node_ptr = ::boost::initialized_value;
#else
                        node_ptr = nullptr;
#endif
                        break;
                    }

                    child_ptr = node_ptr;

                    if (!(node_ptr = node_ptr->get_parent_ptr()))
                    {
                        BOOST_ASSERT_MSG(
                            difference == get(*child_ptr, count_key())
                          , "Result out of bounds."
                        );
                        break;
                    }

                    ++difference;
                }
                else  // if (!node_ptr->get_right_child_ptr())
                {
                    if (node_ptr == root_ptr)
                    {
                        BOOST_ASSERT_MSG(
                            !--difference
                          , "Result out of bounds."
                        );
#if defined BOOST_NO_CXX11_NULLPTR
                        node_ptr = ::boost::initialized_value;
#else
                        node_ptr = nullptr;
#endif
                        break;
                    }

                    child_ptr = node_ptr;

                    if (!(node_ptr = node_ptr->get_parent_ptr()))
                    {
                        BOOST_ASSERT_MSG(
                            !--difference
                          , "Result out of bounds."
                        );
                        break;
                    }
                }
            }

            if (child_ptr == node_ptr->get_left_child_ptr())
            {
                --difference;

                if (child_ptr->get_right_child_ptr())
                {
                    difference -= get(
                        *child_ptr->get_right_child_ptr()
                      , count_key()
                    );
                }
            }
            else  // if (child_ptr == node_ptr->get_right_child_ptr())
            {
                ++difference;

                if (child_ptr->get_left_child_ptr())
                {
                    difference += get(
                        *child_ptr->get_left_child_ptr()
                      , count_key()
                    );
                }
            }
        }

        return node_ptr;
    }

    template <typename NodePointer, typename Difference>
    inline NodePointer
        advance_binary(NodePointer node_ptr, Difference difference)
    {
#if defined BOOST_NO_CXX11_NULLPTR
        return advance_binary(node_ptr, difference, 0);
#else
        return advance_binary(node_ptr, difference, nullptr);
#endif
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_ADVANCE_BINARY_HPP


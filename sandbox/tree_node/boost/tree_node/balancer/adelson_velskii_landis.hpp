// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BALANCER_ADELSON_VELSKII_LANDIS_HPP_INCLUDED
#define BOOST_TREE_NODE_BALANCER_ADELSON_VELSKII_LANDIS_HPP_INCLUDED

#include <boost/tree_node/key/height.hpp>

//[reference__adelson_velskii_landis_balancer
namespace boost { namespace tree_node {

    struct adelson_velskii_landis_balancer
    {
        template <typename NodePointer>
        static NodePointer post_insert(NodePointer node_ptr);

        template <typename Node>
        static bool choose_predecessor(Node const& node);

        template <typename Node>
        static bool pre_erase(Node const& node);

        template <typename NodePointer>
        static NodePointer post_erase_left(NodePointer node_ptr);

        template <typename NodePointer>
        static NodePointer post_erase_right(NodePointer node_ptr);

        //<-
     private:
        template <typename NodePointer>
        static NodePointer _balance(NodePointer node_ptr);
        //->
    };

    //<-
    template <typename NodePointer>
    inline NodePointer
        adelson_velskii_landis_balancer::post_insert(NodePointer node_ptr)
    {
        return adelson_velskii_landis_balancer::_balance(node_ptr);
    }

    template <typename Node>
    inline bool adelson_velskii_landis_balancer::choose_predecessor(Node const& node)
    {
        return get(*node.get_right_child_ptr(), height_key()) < get(
            *node.get_left_child_ptr()
          , height_key()
        );
    }

    template <typename Node>
    inline bool adelson_velskii_landis_balancer::pre_erase(Node const& node)
    {
        return true;
    }

    template <typename NodePointer>
    inline NodePointer
        adelson_velskii_landis_balancer::post_erase_left(NodePointer node_ptr)
    {
        return adelson_velskii_landis_balancer::_balance(node_ptr);
    }

    template <typename NodePointer>
    inline NodePointer
        adelson_velskii_landis_balancer::post_erase_right(NodePointer node_ptr)
    {
        return adelson_velskii_landis_balancer::_balance(node_ptr);
    }

    template <typename NodePointer>
    NodePointer adelson_velskii_landis_balancer::_balance(NodePointer node_ptr)
    {
        NodePointer grandparent_ptr;

        for (
            NodePointer parent_ptr;
            (parent_ptr = node_ptr->get_parent_ptr()) && (
                grandparent_ptr = parent_ptr->get_parent_ptr()
            );
            node_ptr = parent_ptr
        )
        {
            if (
                !grandparent_ptr->get_left_child_ptr() || (
                    grandparent_ptr->get_right_child_ptr() && (
                        1 + get(
                            *grandparent_ptr->get_left_child_ptr()
                          , height_key()
                        ) < get(
                            *grandparent_ptr->get_right_child_ptr()
                          , height_key()
                        )
                    )
                )
            )
            {
                parent_ptr = grandparent_ptr->get_right_child_ptr();

                if (
                    !parent_ptr->get_right_child_ptr() || (
                        parent_ptr->get_left_child_ptr() && (
                            get(
                                *parent_ptr->get_right_child_ptr()
                              , height_key()
                            ) < get(
                                *parent_ptr->get_left_child_ptr()
                              , height_key()
                            )
                        )
                    )
                )
                {
                    parent_ptr = parent_ptr->rotate_right();
                }

                grandparent_ptr = grandparent_ptr->rotate_left();

                if (!grandparent_ptr->get_parent_ptr())
                {
                    return grandparent_ptr;
                }
            }
            else if (
                !grandparent_ptr->get_right_child_ptr() || (
                    grandparent_ptr->get_left_child_ptr() && (
                        1 + get(
                            *grandparent_ptr->get_right_child_ptr()
                          , height_key()
                        ) < get(
                            *grandparent_ptr->get_left_child_ptr()
                          , height_key()
                        )
                    )
                )
            )
            {
                parent_ptr = grandparent_ptr->get_left_child_ptr();

                if (
                    !parent_ptr->get_left_child_ptr() || (
                        parent_ptr->get_right_child_ptr() && (
                            get(
                                *parent_ptr->get_left_child_ptr()
                              , height_key()
                            ) < get(
                                *parent_ptr->get_right_child_ptr()
                              , height_key()
                            )
                        )
                    )
                )
                {
                    parent_ptr = parent_ptr->rotate_left();
                }

                grandparent_ptr = grandparent_ptr->rotate_right();

                if (!grandparent_ptr->get_parent_ptr())
                {
                    return grandparent_ptr;
                }
            }
        }

        return node_ptr;
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BALANCER_ADELSON_VELSKII_LANDIS_HPP_INCLUDED


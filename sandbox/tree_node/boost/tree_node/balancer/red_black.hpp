// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BALANCER_RED_BLACK_HPP_INCLUDED
#define BOOST_TREE_NODE_BALANCER_RED_BLACK_HPP_INCLUDED

#include <boost/utility/value_init.hpp>
#include <boost/tree_node/key/red_black_flag.hpp>
#include <boost/assert.hpp>

//[reference__red_black_balancer
namespace boost { namespace tree_node {

    struct red_black_balancer
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
    NodePointer red_black_balancer::post_insert(NodePointer node_ptr)
    {
        NodePointer parent_ptr;
        NodePointer grandparent_ptr;
        NodePointer uncle_ptr;

        put(*node_ptr, red_flag_key(), true);

        while ((parent_ptr = node_ptr->get_parent_ptr()))
        {
            if (get(*parent_ptr, black_flag_key()))
            {
                return node_ptr;
            }

            grandparent_ptr = parent_ptr->get_parent_ptr();

            if (parent_ptr == grandparent_ptr->get_left_child_ptr())
            {
                if (
                    (
                        uncle_ptr = grandparent_ptr->get_right_child_ptr()
                    ) && get(*uncle_ptr, red_flag_key())
                )
                {
                    put(*parent_ptr, black_flag_key(), true);
                    put(*uncle_ptr, black_flag_key(), true);
                    put(*grandparent_ptr, red_flag_key(), true);
                    node_ptr = grandparent_ptr;
                    continue;
                }
            }
            else  // if (parent_ptr == grandparent_ptr->get_right_child_ptr())
            {
                if (
                    (
                        uncle_ptr = grandparent_ptr->get_left_child_ptr()
                    ) && get(*uncle_ptr, red_flag_key())
                )
                {
                    put(*parent_ptr, black_flag_key(), true);
                    put(*uncle_ptr, black_flag_key(), true);
                    put(*grandparent_ptr, red_flag_key(), true);
                    node_ptr = grandparent_ptr;
                    continue;
                }
            }

            if (
                (node_ptr == parent_ptr->get_right_child_ptr()) && (
                    parent_ptr == grandparent_ptr->get_left_child_ptr()
                )
            )
            {
                parent_ptr = parent_ptr->rotate_left();
                node_ptr = node_ptr->get_left_child_ptr();
            }
            else if (
                (node_ptr == parent_ptr->get_left_child_ptr()) && (
                    parent_ptr == grandparent_ptr->get_right_child_ptr()
                )
            )
            {
                parent_ptr = parent_ptr->rotate_right();
                node_ptr = node_ptr->get_right_child_ptr();
            }

            grandparent_ptr = parent_ptr->get_parent_ptr();
            put(*parent_ptr, black_flag_key(), true);
            put(*grandparent_ptr, red_flag_key(), true);

            return (node_ptr == parent_ptr->get_left_child_ptr()) ? (
                grandparent_ptr->rotate_right()
            ) : grandparent_ptr->rotate_left();
        }

        put(*node_ptr, black_flag_key(), true);
        return node_ptr;
    }

    template <typename Node>
    inline bool red_black_balancer::choose_predecessor(Node const& node)
    {
        typename Node::const_pointer succ_ptr = node.get_right_child_ptr();

        while (succ_ptr->get_left_child_ptr())
        {
            succ_ptr = succ_ptr->get_left_child_ptr();
        }

        return get(*succ_ptr, black_flag_key()) && succ_ptr->empty();
    }

    template <typename Node>
    inline bool red_black_balancer::pre_erase(Node const& node)
    {
        return get(node, black_flag_key());
    }

    template <typename NodePointer>
    NodePointer red_black_balancer::post_erase_left(NodePointer node_ptr)
    {
        NodePointer result_ptr = ::boost::initialized_value;
        NodePointer child_ptr = node_ptr->get_right_child_ptr();

        if (get(*child_ptr, red_flag_key()))
        {
std::cout << "Right Sib 5.1" << std::endl;
            put(*node_ptr, red_flag_key(), true);
            put(*child_ptr, black_flag_key(), true);
            result_ptr = node_ptr->rotate_left();
            child_ptr = node_ptr->get_right_child_ptr();
        }

        NodePointer grandchild_ptr = child_ptr->get_right_child_ptr();

        if (grandchild_ptr)
        {
            BOOST_ASSERT(get(*grandchild_ptr, red_flag_key()));
std::cout << "Right Sib 5.3.2" << std::endl;
            put(*grandchild_ptr, black_flag_key(), true);
            put(
                *child_ptr
              , red_flag_key()
              , get(*node_ptr, red_flag_key())
            );
            put(*node_ptr, black_flag_key(), true);

            if (result_ptr)
            {
                node_ptr->rotate_left();
            }
            else
            {
                result_ptr = node_ptr->rotate_left();
            }

            return result_ptr;
        }

        if ((grandchild_ptr = child_ptr->get_left_child_ptr()))
        {
            BOOST_ASSERT(get(*grandchild_ptr, red_flag_key()));
std::cout << "Right Sib 5.3.1" << std::endl;
            put(
                *(child_ptr = child_ptr->rotate_right())
              , red_flag_key()
              , get(*node_ptr, red_flag_key())
            );
            put(*node_ptr, black_flag_key(), true);

            if (result_ptr)
            {
                node_ptr->rotate_left();
            }
            else
            {
                result_ptr = node_ptr->rotate_left();
            }

            return result_ptr;
        }

std::cout << "Right Sib 5.2" << std::endl;
        put(*child_ptr, red_flag_key(), true);

        if (result_ptr)
        {
            BOOST_ASSERT(get(*node_ptr, red_flag_key()));
            put(*node_ptr, black_flag_key(), true);
            return result_ptr;
        }
        else if (get(*node_ptr, red_flag_key()))
        {
            put(*node_ptr, black_flag_key(), true);
            return node_ptr;
        }
        else
        {
            return red_black_balancer::_balance(node_ptr);
        }
    }

    template <typename NodePointer>
    NodePointer red_black_balancer::post_erase_right(NodePointer node_ptr)
    {
        NodePointer result_ptr = ::boost::initialized_value;
        NodePointer child_ptr = node_ptr->get_left_child_ptr();

        if (get(*child_ptr, red_flag_key()))
        {
std::cout << "Left Sib 5.1" << std::endl;
            put(*node_ptr, red_flag_key(), true);
            put(*child_ptr, black_flag_key(), true);
            result_ptr = node_ptr->rotate_right();
            child_ptr = node_ptr->get_left_child_ptr();
        }

        NodePointer grandchild_ptr = child_ptr->get_left_child_ptr();

        if (grandchild_ptr)
        {
            BOOST_ASSERT(get(*grandchild_ptr, red_flag_key()));
std::cout << "Left Sib 5.3.2" << std::endl;
            put(*grandchild_ptr, black_flag_key(), true);
            put(
                *child_ptr
              , red_flag_key()
              , get(*node_ptr, red_flag_key())
            );
            put(*node_ptr, black_flag_key(), true);

            if (result_ptr)
            {
                node_ptr->rotate_right();
            }
            else
            {
                result_ptr = node_ptr->rotate_right();
            }

            return result_ptr;
        }

        if ((grandchild_ptr = child_ptr->get_right_child_ptr()))
        {
            BOOST_ASSERT(get(*grandchild_ptr, red_flag_key()));
std::cout << "Left Sib 5.3.1" << std::endl;
            put(
                *(child_ptr = child_ptr->rotate_left())
              , red_flag_key()
              , get(*node_ptr, red_flag_key())
            );
            put(*node_ptr, black_flag_key(), true);

            if (result_ptr)
            {
                node_ptr->rotate_right();
            }
            else
            {
                result_ptr = node_ptr->rotate_right();
            }

            return result_ptr;
        }

std::cout << "Left Sib 5.2" << std::endl;
        put(*child_ptr, red_flag_key(), true);

        if (result_ptr)
        {
            BOOST_ASSERT(get(*node_ptr, red_flag_key()));
            put(*node_ptr, black_flag_key(), true);
            return result_ptr;
        }
        else if (get(*node_ptr, red_flag_key()))
        {
            put(*node_ptr, black_flag_key(), true);
            return node_ptr;
        }
        else
        {
            return red_black_balancer::_balance(node_ptr);
        }
    }

    template <typename NodePointer>
    NodePointer red_black_balancer::_balance(NodePointer node_ptr)
    {
        NodePointer parent_ptr;
        NodePointer sibling_ptr;
        NodePointer nephew_ptr;

        for (
            bool is_left;
            (parent_ptr = node_ptr->get_parent_ptr());
            node_ptr = parent_ptr
        )
        {
            sibling_ptr = (
                is_left = (node_ptr == parent_ptr->get_left_child_ptr())
            ) ? parent_ptr->get_right_child_ptr() : (
                parent_ptr->get_left_child_ptr()
            );

            if (get(*sibling_ptr, red_flag_key()))
            {
std::cout << "5.1" << std::endl;
                put(*parent_ptr, red_flag_key(), true);
                put(*sibling_ptr, black_flag_key(), true);

                if (is_left)
                {
                    parent_ptr->rotate_left();
                    sibling_ptr = parent_ptr->get_right_child_ptr();
                }
                else
                {
                    parent_ptr->rotate_right();
                    sibling_ptr = parent_ptr->get_left_child_ptr();
                }

                put(*sibling_ptr, red_flag_key(), true);
                put(*parent_ptr, black_flag_key(), true);
                return parent_ptr->get_parent_ptr();
            }

            nephew_ptr = is_left ? sibling_ptr->get_right_child_ptr() : (
                sibling_ptr->get_left_child_ptr()
            );

            if (nephew_ptr)
            {
                if (get(*nephew_ptr, red_flag_key()))
                {
std::cout << "5.3.2" << std::endl;
                    put(*nephew_ptr, black_flag_key(), true);
                    put(
                        *sibling_ptr
                      , red_flag_key()
                      , get(*parent_ptr, red_flag_key())
                    );
                    put(*parent_ptr, black_flag_key(), true);
                    return is_left ? parent_ptr->rotate_left() : (
                        parent_ptr->rotate_right()
                    );
                }
            }

            if (
                (
                    nephew_ptr = is_left ? (
                        sibling_ptr->get_left_child_ptr()
                    ) : sibling_ptr->get_right_child_ptr()
                )
            )
            {
                if (get(*nephew_ptr, red_flag_key()))
                {
std::cout << "5.3.1" << std::endl;
                    put(
                        *(
                            sibling_ptr = is_left ? (
                                sibling_ptr->rotate_right()
                            ) : sibling_ptr->rotate_left()
                        )
                      , red_flag_key()
                      , get(*parent_ptr, red_flag_key())
                    );
                    put(*parent_ptr, black_flag_key(), true);
                    return is_left ? parent_ptr->rotate_left() : (
                        parent_ptr->rotate_right()
                    );
                }
            }

std::cout << "5.2" << std::endl;
            put(*sibling_ptr, red_flag_key(), true);

            if (get(*parent_ptr, red_flag_key()))
            {
                put(*parent_ptr, black_flag_key(), true);
                return parent_ptr;
            }
        }

        return node_ptr;
    }
    //->

    namespace balancer {

        typedef ::boost::tree_node::red_black_balancer red_black;
    }  // namespace balancer
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BALANCER_RED_BLACK_HPP_INCLUDED


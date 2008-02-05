// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BLUEPRINT_WINDOW_HPP
#define BLUEPRINT_WINDOW_HPP

#include <gui/frame_window.hpp>

#include <boost/dataflow/blueprint/network.hpp>
#include <boost/dataflow/signals/runtime_support.hpp>

namespace boost { namespace dataflow { namespace cppgui {

class blueprint_component;
class blueprint_component_port;

class connection
    :  public std::pair<blueprint_component_port *, blueprint_component_port *>
{
public:
    connection(blueprint_component_port *p1, blueprint_component_port *p2)
        : std::pair<blueprint_component_port *, blueprint_component_port *>(p1, p2)
    {}
};

class blueprint_window : public gui::subclass<blueprint_window, gui::frame_window>
{
public:
    blueprint_window();
    void add_component(std::auto_ptr<blueprint::component> c, const std::string &name);
    void add_component(boost::function<blueprint::component *()> f, const std::string &name);
    void register_drag(blueprint_component_port *port)
    {
        m_dragged = port;
    }
    bool register_drop(blueprint_component_port *port);
    void connect_dragged_with(blueprint_component_port *port);
private:
    void add_component_helper(blueprint_component &bc);
    virtual void draw();
    virtual int handle(int event);
    blueprint::network m_network;
    std::vector<blueprint_component *> m_components;
    blueprint_component_port *m_dragged;
    std::vector<connection> m_connections;
    std::vector<connection>::iterator m_selected;
    int m_next_created_x;
    int m_next_created_y;
};

} } }
#endif
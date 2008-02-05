// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gui/gui.hpp>
#include "blueprint_window.hpp"
#include "blueprint_component.hpp"

namespace boost { namespace dataflow { namespace cppgui {

blueprint_window::blueprint_window()
{
    m_next_created_x = 100;
    m_next_created_y = 50;
}

void blueprint_window::add_component(std::auto_ptr<blueprint::component> c, const std::string &name)
{
    //BlueprintComponent *bc = new BlueprintComponent(m_next_created_x, m_next_created_y, 100, 100, name.c_str(), *c, m_network.add_component(c));
    //add_component_helper(bc);
}

void blueprint_window::add_component(boost::function<blueprint::component *()> f, const std::string &name)
{
    gui::wnd<blueprint_window> this_ = wnd_from_this();
    
/*    gui::wnd<blueprint_component> bc = gui::create<blueprint_component>
        ( gui::_pos = std::make_pair(m_next_created_x, m_next_created_y)
        , gui::_size = std::make_pair(100, 100)
        , gui::_text = name
        , gui::_parent = this_);*/

//    bc->gui_begin();
//    std::auto_ptr<blueprint::component> c(f());
//    blueprint::network::component_type id = m_network.add_component(c);
//    bc->set_component(m_network[id], id);
//    bc->gui_end();

//    add_component_helper(*bc);
}

void blueprint_window::add_component_helper(blueprint_component &bc)
{
/*    add(bc);
    redraw();*/
    m_next_created_x += 150;
    if (m_next_created_x + 100 > bc.size().first)
    {
        m_next_created_x = 100;
        m_next_created_y += 150;
    }
}
    

bool blueprint_window::register_drop(blueprint_component_port *port)
{
//    return m_network.are_connectable(m_dragged->component().id(), m_dragged->id(), port->component().id(), port->id());
}

void blueprint_window::connect_dragged_with(blueprint_component_port *port)
{
/*    m_network.add_connection(m_dragged->component().id(), m_dragged->id(), port->component().id(), port->id(), true);
    m_connections.push_back(Connection(m_dragged, port));
    redraw();*/
}

void blueprint_window::draw()
{
/*    fltk::Window::draw();
    for (std::vector<Connection>::iterator it=m_connections.begin(); it!=m_connections.end(); it++)
    {
        fltk::setcolor(it == m_selected ? fltk::RED : fltk::GREEN);
        fltk::drawline(
            it->first->center_x_root(),
            it->first->center_y_root(),
            it->second->center_x_root(),
            it->second->center_y_root());
    }*/
}

namespace detail
{
    double distance(int x0, int y0, int x1, int y1)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        return sqrt(dx*dx+dy*dy);    
    }
    
    double distance(int x0, int y0, int x1, int y1, int xp, int yp)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        if (dx==0 && dy==0)
            return distance(x0, y0, xp, yp);
            
        double r = double((xp - x0) * dx + (yp - y0) * dy) / (dx*dx + dy*dy);
        if (r<0)
            return distance(x0, y0, xp, yp);
        else if (r>1)
            return distance(x1, y1, xp, yp);
        else
            return distance((1-r)*x0 + r*x1, (1-r)*y0 + r*y1, xp, yp);
    }
}

int blueprint_window::handle(int event)
{
/*    if (fltk::Window::handle(event))
        return 1;
    bool found=false;
    if(event == fltk::PUSH)
        for (std::vector<Connection>::iterator it=m_connections.begin(); it!=m_connections.end(); it++)
            if (detail::distance(
                it->first->center_x_root(),
                it->first->center_y_root(),
                it->second->center_x_root(),
                it->second->center_y_root(),
                fltk::event_x(),
                fltk::event_y()) < 3)
            {
                m_selected = it;
                found = true;
            }
    if (!found)
        m_selected = std::vector<Connection>::iterator();
    redraw();*/
    return 0;
}


} } }
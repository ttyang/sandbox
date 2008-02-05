// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BLUEPRINT_COMPONENT_HPP
#define BLUEPRINT_COMPONENT_HPP

#include "blueprint_window.hpp"

namespace boost { namespace dataflow { namespace cppgui {

class blueprint_component : public gui::subclass<blueprint_component, gui::window>
{
    typedef blueprint::network::component_type id_type;
public:
    blueprint_component();
    void set_component(blueprint::component &c, id_type id);
    void gui_begin();
    void gui_end();
    void invoke() {m_component->invoke();}
    id_type id() {return m_id;}
private:
    blueprint::component *m_component;
    std::string m_name;
    id_type m_id;
//    fltk::Group *m_gui_group;
};

class blueprint_component_port// : public fltk::Button
{
public:
    blueprint_component_port()
    {}
    int handle(int event);
    blueprint_component &component()
    {   return *static_cast<blueprint_component *>(0/*parent()*/); }
    int center_x_root()
    {   /*return parent()->x() + center_x(); */ return 0;}
    int center_y_root()
    {   /*return parent()->y() + center_y(); */ return 0;}
    size_t id() {return m_id;}
private:
    blueprint_window &blueprint()
    {   return *static_cast<blueprint_window *>(0/*parent()->parent()*/); }
    size_t m_id;
};

} } }

#endif
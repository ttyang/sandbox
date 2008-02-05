// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BLUEPRINT_COMPONENT_BANK_HPP
#define BLUEPRINT_COMPONENT_BANK_HPP

#include <boost/dataflow/blueprint/component_bank.hpp>

#include <gui/controls/button.hpp>
#include <gui/frame_window.hpp>

namespace boost { namespace dataflow { namespace cppgui {

class blueprint_window;

class blueprint_bank : public gui::subclass<blueprint_bank, gui::frame_window>
{
public:
    blueprint_bank() {};
    
    static void create_wnd(create_params&);

    void set_bank(const blueprint::component_bank &bank)
    {
        m_bank = bank;
        rearrange();
    }
    void set_blueprint(blueprint_window &blueprint)
    {
        m_blueprint = &blueprint;
    }
    
    typedef std::vector<child_wnd<gui::controls::button> > component_buttons_type;
private:
    void rearrange();
    blueprint_window * m_blueprint;
    blueprint::component_bank m_bank;
    component_buttons_type m_component_buttons;

    struct events;
};

} } }

#endif
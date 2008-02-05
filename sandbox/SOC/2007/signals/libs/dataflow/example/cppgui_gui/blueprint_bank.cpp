// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gui/gui.hpp>
#include "blueprint_bank.hpp"
#include "blueprint_window.hpp"

namespace boost { namespace dataflow { namespace cppgui {

struct blueprint_bank::events
{
    events(gui::wnd<blueprint_bank> w)
    {
        for (blueprint_bank::component_buttons_type::iterator it
            = w->m_component_buttons.begin(); it!= w->m_component_buttons.end(); it++)
            (*it)->click_signal().connect(boost::bind(w->use_event(&events::click), "argh"));
    }

    void click(gui::wnd<blueprint_bank> bank, const std::string &text)
    {
        bank->m_blueprint->add_component(bank->m_bank[text], text);
    }
};


void blueprint_bank::rearrange()
{
    gui::wnd<blueprint_bank> this_ = wnd_from_this();
    namespace controls = gui::controls;

//    clear();
    int y = 0;

    for(blueprint::component_bank::iterator it=m_bank.begin(); it!=m_bank.end(); it++)
    {
        m_component_buttons.push_back(
            gui::create<controls::button>
                ( gui::_text = it->c_str()
                , gui::_parent = this_
                , gui::_size = std::make_pair(100, 100)
                , gui::_pos = std::make_pair(0, y) ) );
            y += 100;
    }

    std::auto_ptr<events> pe(new events(this_));
    add_event_class<events>(pe);
}

void blueprint_bank::create_wnd(create_params& params)
{
    gui::params(params, gui::_size = std::make_pair(100, 600));
}

} } }

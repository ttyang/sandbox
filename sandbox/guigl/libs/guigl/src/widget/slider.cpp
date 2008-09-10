/*=================================---------------------------------------------
    Copyright 2007,2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/


#include <boost/guigl/window.hpp>
#include <boost/guigl/widget/slider.hpp>
#include <boost/guigl/view/impl/active_colored.hpp>
#include <boost/guigl/view/impl/positioned.hpp>
#include <boost/guigl/view/impl/solid_background.hpp>
#include <boost/guigl/view/impl/draggable.hpp>
#include <iostream>

namespace boost { namespace guigl { namespace widget {

BOOST_GUIGL_WIDGET_DRAW_IMPL(slider)

inline void slider::draw_prologue()
{
    base_type::draw_prologue();

    use_active_color();
    glRectd(0,0,(m_value-m_min) * size().x / (m_max-m_min), size().y);
}

inline void slider::draw_epilogue()
{
    base_type::draw_epilogue();
}

void slider::draggable_on_drag(const position_type &position)
{
    double new_value = (position.x / size().x) * (m_max-m_min);
    if(m_step!=0.0)
        new_value = round(new_value / m_step) * m_step;
    new_value += m_min;
    set_value(new_value);
}

void slider::set_value(double value)
{
    if(m_value != value)
    {
        m_value = value;
        on_value_change(value);
        guigl::window::redraw(*this);
    }
}


}}}
/*=================================---------------------------------------------
    Copyright 2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#ifndef BOOST__GUIGL__WIDGET__LABELED_BUTTON_HPP
#define BOOST__GUIGL__WIDGET__LABELED_BUTTON_HPP

#include <boost/guigl/view/colored.hpp>
#include <boost/guigl/view/labeled.hpp>
#include <boost/guigl/widget/button.hpp>

namespace boost { namespace guigl { namespace widget {

typedef view::labeled<
            view::colored<
                widget::button
        >   > labeled_button_base_type;

class labeled_button : public labeled_button_base_type
{
    typedef labeled_button_base_type base_type;
public:
    template<typename ArgumentPack>
    labeled_button(const ArgumentPack &args)
        : base_type(args)
    {}
    labeled_button(const labeled_button &rhs)
        : base_type(static_cast<const base_type &>(rhs))
    {}

protected:
    void draw();
    bool on_event(const event_type &event_info);
    friend class guigl::access;
};

}}}

#endif // BOOST__GUIGL__WIDGET__LABELED_BUTTON_HPP

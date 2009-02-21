/*=================================---------------------------------------------
    Copyright 2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/


#include <boost/guigl/application.hpp>
#include <boost/guigl/window.hpp>
#include <boost/guigl/widget/custom.hpp>

#include <boost/guigl/platform/opengl.hpp>

using namespace boost::guigl;

void draw_stuff()
{
    glColor3d(1.0, 0.0, 0.0);
    glRectd(0.0, 0.0, 50.0, 50.0);
}

int main()
{
    window test_window1(( _label = "custom example", _size=size_type(300,300) ));
    
    test_window1 << new widget::custom((
        _size=size_type(300,300),
        _draw_prologue=draw_stuff
    ));

    application::run();
}

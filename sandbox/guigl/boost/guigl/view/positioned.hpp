/*=================================---------------------------------------------
    Copyright 2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#ifndef BOOST__GUIGL__VIEW__POSITIONED_HPP
#define BOOST__GUIGL__VIEW__POSITIONED_HPP

#include <boost/guigl/view/base.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace guigl { namespace view {

template<typename View>
struct is_positioned
    : public is_positioned<typename View::base_type>
{};

template<>
struct is_positioned<base> : public mpl::false_
{};

/// Behavior adding a position to the view.
/** positioned adds a position to the inheriting view.  Since it is intended for
    views that are positioned inside other views, it also has a pointer to
    a possible parent view.
*/
template<typename BaseView=base>
class positioned : public BaseView
{
    typedef BaseView base_type;
public:
    template<typename ArgumentPack>
    positioned(const ArgumentPack &args)
        : base_type(args)
        , m_position(args[_position])
        , m_parent(0)
    {}
    positioned(const positioned &rhs)
        : base_type(static_cast<const base_type &>(rhs))
        , m_position(rhs.m_position)
        , m_parent(0)
    {}
    
    /** Returns the position */
    const position_type &position() const
    {   return m_position; }

    /** Sets the position */
    void set_position(const position_type &position)
    {   m_position = position; }

    /** Returns the topmost ancestor, as defined by following the parent pointer
        as long as the parent is also a positioned<> view. */
    const base *root() const
    {
        const base *root = this;
        const positioned<> *p_view;
        while((p_view = dynamic_cast<const positioned<> *>(root)))
            root = p_view->m_parent;
        return root;
    }
    const base &parent() const
    {
        return *m_parent;
    }
protected:
    void draw_prologue();
    void draw_epilogue();

    friend class guigl::access;
    void set_parent(base &parent)
    {   m_parent = &parent; }
private:

    position_type m_position;
    base *m_parent;
};

template<typename BaseView>
struct is_positioned<positioned<BaseView> > : public mpl::true_
{};

/** Returns the topmost ancestor, as defined by following the parent pointer
as long as the parent is also a positioned<> view. */
template<typename View>
inline const base *root(const positioned<View> &view)
{
    const base *root = view;
    const positioned<> *p_view;
    while((p_view = dynamic_cast<const positioned<> *>(root)))
        root = p_view->parent();
    return root;
}

/** Returns the position relative to topmost ancestor,
    as defined by following the parent pointer
    as long as the parent is also a positioned<> view. */
inline position_type root_position(const positioned<> &view)
{
    const positioned<> *p_view = &view;
    position_type position = view.position();
    while((p_view = dynamic_cast<const positioned<> *>(&p_view->parent())))
        position += p_view->position();
    return position;
}
    
} // namespace view

}}

#endif // BOOST__GUIGL__VIEW__POSITIONED_HPP
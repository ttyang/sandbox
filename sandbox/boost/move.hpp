//-----------------------------------------------------------------------------
// boost move.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MOVE_HPP
#define BOOST_MOVE_HPP

#include "boost/move_fwd.hpp"

#include <cstring> // for std::memcpy
#include <new> // for placement new

#include "boost/type_traits/has_nothrow_copy.hpp"
#include "boost/type_traits/has_trivial_copy.hpp"
#include "boost/type_traits/is_convertible.hpp"
#include "boost/utility/addressof.hpp"

#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/logical/not.hpp"

namespace boost {
namespace detail {

//////////////////////////////////////////////////////////////////////////
// class not_moveable_tag
//
struct not_moveable_tag
{
protected:
    ~not_moveable_tag() { }
};

//////////////////////////////////////////////////////////////////////////
// class memcpy_move_traits
//
// Implements move for objects of 'memcpy-able' types.
//
template <typename T>
struct memcpy_move_traits
{
    static void move(void* dest, T& src)
    {
        std::memcpy(dest, boost::addressof(src));
    }
};

//////////////////////////////////////////////////////////////////////////
// class nothrow_copy_move_traits
//
// Implements move for objects of types with nothrow copy.
//
template <typename T>
struct nothrow_copy_move_traits
{
    static void move(void* dest, T& src)
    {
        new(dest) T(src);
    }
};

} // namespace detail

//////////////////////////////////////////////////////////////////////////
// class template move_traits
//
// Traits template to facilitate *nothrow* move of objects of the
// specified type.
//
template <typename T>
struct move_traits
    : mpl::apply_if<
          // [If trivially copyable (i.e., memcpy-able):]
          has_trivial_copy<T>
        , mpl::identity< detail::memcpy_move_traits<T> >

        , mpl::apply_if<
              // [...else if nothrow copyable:]
              has_nothrow_copy<T>
            , mpl::identity< detail::nothrow_copy_move_traits<T> >

              // [...else T not moveable (without specialization):]
            , mpl::identity<detail::not_moveable_tag>
            >
        >::type
{
};

//////////////////////////////////////////////////////////////////////////
// class template is_moveable
//
// Traits template indicates whether specified type is moveable.
// 
// NOTE: This template never needs to be specialized!
//
template <typename T>
struct is_moveable
{
    typedef typename mpl::logical_not<
          is_convertible<move_traits<T>, detail::not_moveable_tag>
        >::type type;

    BOOST_STATIC_CONSTANT(bool, value = type::value);
};

//////////////////////////////////////////////////////////////////////////
// function template move
//
// Moves the source object to the given storage, leaving the source
// object in a consistent, yet unpredictable, state.
//
template <typename T>
T* move(void* dest, T& src)
{
    move_traits<T>::move(dest, src);
    return static_cast<T*>(dest);
}

} // namespace boost

#endif // BOOST_MOVE_HPP

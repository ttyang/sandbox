// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_BASE_POINTEE_HPP_INCLUDED
#define BOOST_DETAIL_BASE_POINTEE_HPP_INCLUDED

namespace boost { namespace detail {

    template <typename Derived>
    struct base_pointee
    {
        typedef Derived const* const_pointer;
        typedef Derived* pointer;

        const_pointer get_derived() const;

        pointer get_derived();
    };

    template <typename Derived>
    inline typename base_pointee<Derived>::const_pointer
        base_pointee<Derived>::get_derived() const
    {
        return static_cast<const_pointer>(this);
    }

    template <typename Derived>
    inline typename base_pointee<Derived>::pointer
        base_pointee<Derived>::get_derived()
    {
        return static_cast<pointer>(this);
    }
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_BASE_POINTEE_HPP_INCLUDED


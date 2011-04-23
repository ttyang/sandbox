/**
	@file
	Boost pack_allocator.hpp header file.

	@note
	Copyright (c) 2008 Phil Bouchard <phil@fornux.com>.

	Distributed under the Boost Software License, Version 1.0.

	See accompanying file LICENSE_1_0.txt or copy at
	http://www.boost.org/LICENSE_1_0.txt

	See http://www.boost.org/libs/smart_ptr/doc/index.html for documentation.
*/


#ifndef BOOST_SHIFTED_ALLOCATOR_HPP_INCLUDED
#define BOOST_SHIFTED_ALLOCATOR_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/pack_ptr.hpp>


namespace boost
{

namespace detail
{

namespace sh
{


/**
    STL compliant allocator.
    
    @note
    Default object contructor is called inside allocate() to save temporaries.
*/

template <typename T>
    class pack_allocator
    {
        typedef T                       element_type;

    public:
        typedef pack<T>              value_type;
        typedef size_t                  size_type;
        typedef ptrdiff_t               difference_type;
        typedef T *                     pointer;
        typedef const T *               const_pointer;
        typedef element_type &          reference;
        typedef const element_type &    const_reference;

        template <typename U>
            struct rebind
            {
                typedef pack_allocator<U> other;
            };

        pack_allocator() throw()                                 {}
        pack_allocator(const pack_allocator &) throw()        {}
        template <typename U>
            pack_allocator(const pack_allocator<U> &) throw() {}

        ~pack_allocator() throw()                                {}
        pointer address(reference x) const                          { return & x; }
        const_pointer address(const_reference x) const              { return & x; }

        size_type max_size() const throw()
        {
            return size_t(-1) / sizeof(T);
        }

        pointer allocate(size_type s, const void * = 0)
        {
            //value_type * p = (value_type *) value_type::operator new(sizeof(value_type));
            value_type * p = new value_type();

            return p->element();
        }

        void construct(pointer p, const T & x)
        {
            //::new (p) owned_base;
            //::new (p->element()) T(x);
        }

        void destroy(pointer p)
        {
            p->reset();
        }

        void deallocate(pointer p, size_type)
        {
        }
    };

template <typename T>
    inline bool operator == (const pack_allocator<T> &, const pack_allocator<T> &)
    {
        return true;
    }

template <typename T>
    inline bool operator != (const pack_allocator<T> &, const pack_allocator<T> &)
    {
        return false;
    }


} // namespace sh

} // namespace detail

using detail::sh::pack_allocator;
using detail::sh::operator ==;
using detail::sh::operator !=;

} // namespace boost

#endif  // #ifndef BOOST_SHIFTED_ALLOCATOR_HPP_INCLUDED

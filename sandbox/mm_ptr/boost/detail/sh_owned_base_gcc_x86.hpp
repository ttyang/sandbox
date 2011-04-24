#ifndef BOOST_DETAIL_SH_OWNED_BASE_GCC_X86_HPP_INCLUDED
#define BOOST_DETAIL_SH_OWNED_BASE_GCC_X86_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sh_owned_base_gcc_x86.hpp - g++ on 486+ or AMD64
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//
//  Thanks to Ben Hitchings for the #weak + (#shared != 0)
//  formulation
//

#include <boost/detail/sp_owned_base_gcc_x86.hpp>

#include <typeinfo>

namespace boost
{

namespace detail
{

namespace sh
{

inline int atomic_exchange_and_add( int * pw, int dv )
{
    // int r = *pw;
    // *pw += dv;
    // return r;

    int r;

    __asm__ __volatile__
    (
        "lock\n\t"
        "xadd %1, %0":
        "=m"( *pw ), "=r"( r ): // outputs (%0, %1)
        "m"( *pw ), "1"( dv ): // inputs (%2, %3 == %1)
        "memory", "cc" // clobbers
    );

    return r;
}

inline void atomic_increment( int * pw )
{
    //atomic_exchange_and_add( pw, 1 );

    __asm__
    (
        "lock\n\t"
        "incl %0":
        "=m"( *pw ): // output (%0)
        "m"( *pw ): // input (%1)
        "cc" // clobbers
    );
}

inline int atomic_conditional_increment( int * pw )
{
    // int rv = *pw;
    // if( rv != 0 ) ++*pw;
    // return rv;

    int rv, tmp;

    __asm__
    (
        "movl %0, %%eax\n\t"
        "0:\n\t"
        "test %%eax, %%eax\n\t"
        "je 1f\n\t"
        "movl %%eax, %2\n\t"
        "incl %2\n\t"
        "lock\n\t"
        "cmpxchgl %2, %0\n\t"
        "jne 0b\n\t"
        "1:":
        "=m"( *pw ), "=&a"( rv ), "=&r"( tmp ): // outputs (%0, %1, %2)
        "m"( *pw ): // input (%3)
        "cc" // clobbers
    );

    return rv;
}

class owned_base : public sp_counted_base
{
private:

    owned_base( owned_base const & );
    owned_base & operator= ( owned_base const & );

    long seg_count_;        // #set
    owned_base * po_;
    owned_base ** ppo_;

public:

    owned_base(): seg_count_( 1 ), po_( this ), ppo_( po_ )
    {
    }

    void add_own_copy()
    {
        atomic_increment( &(*ppo_)->seg_count_ );
    }

    bool add_own_lock() // true on success
    {
        return atomic_conditional_increment( &(*ppo_)->seg_count_ ) != 0;
    }

    void release() // nothrow
    {
        if( atomic_exchange_and_add( &(*ppo_)->seg_count_, -1 ) == 1 )
        {
            dispose();
        }
    }

    long seg_count() const // nothrow
    {
        return static_cast<int const volatile &>( (*ppo_)->seg_count_ );
    }
	
    owned_base * owner() const // nothrow
    {
        return (*ppo_);
    }
	
    void owner(owned_base * p) // nothrow
    {
        (*ppo_) = p;
    }
};

} // namespace sh

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_DETAIL_SH_OWNED_BASE_GCC_X86_HPP_INCLUDED

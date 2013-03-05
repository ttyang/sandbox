
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_OLDOF_HPP_
#define BOOST_CONTRACT_AUX_OLDOF_HPP_

#include <boost/contract/oldof.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace contract { namespace aux {

// Must be empty struct so any attempt to use it will generate a compiler-error,
// plus struct name is used to report error message.
struct ERROR_missing_const_copy_constructor_for_oldof_type
{
    // Has dummy const-correct copy constructor from any type so it will
    // never fail an old-of copy<>.
    template< typename T >
    ERROR_missing_const_copy_constructor_for_oldof_type( T const& ) {}
};

// Select type above iff a type T has no old-of (not has_oldof<T>) so the
// BOOST_CONTRACT_OLDOF declaration will compile but any attempt to use the
// old-of value for the empty struct type above in an assertion will generate a
// compiler-error unless the assertion adds has_oldof to its requirements.
template< typename T >
struct oldof_ // Don't use oldof to leave that symbol for eventual user #define.
{
    typedef typename boost::mpl::if_< has_oldof<T>,
        T
    ,
        ERROR_missing_const_copy_constructor_for_oldof_type
    >::type type;
};

} } } // namespace

#endif // #include guard


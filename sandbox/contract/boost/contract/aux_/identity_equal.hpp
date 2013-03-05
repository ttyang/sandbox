
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_IDENTITY_EQUAL_HPP_
#define BOOST_CONTRACT_AUX_IDENTITY_EQUAL_HPP_

namespace boost { namespace contract { namespace aux {

// Used to internally deal with old-of value assignment symbol `var =`.
struct identity_equal {};

template< typename Left >
Left const& operator== ( Left const& left, identity_equal const& )
{
    return left;
}

} } } // namespace

#endif // #include guard


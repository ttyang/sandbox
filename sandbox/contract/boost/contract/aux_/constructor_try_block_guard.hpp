
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CONSTRUCTOR_TRY_BLOCK_GUARD_HPP_
#define BOOST_CONTRACT_AUX_CONSTRUCTOR_TRY_BLOCK_GUARD_HPP_

#include <boost/contract/aux_/symbol.hpp>

namespace boost { namespace contract { namespace aux {

// Need Class tparam to make this a unique base type for each new class.
template< class Class >
struct constructor_try_block_guard {
    // Default constructor also handles constructor with no try-block.
    constructor_try_block_guard ( ) : enabled_(false) {}

    // These need to be named with library reserved symbols to not clash
    // with member func/var names in user-defined derived class.

    bool BOOST_CONTRACT_AUX_SYMBOL( (enabled) ) ( ) const { return enabled_; }
    
    // NOTE: These need to return a value to be used within member inits set.
    bool BOOST_CONTRACT_AUX_SYMBOL( (enable) ) ( ) { return enabled_ = true; }
    bool BOOST_CONTRACT_AUX_SYMBOL( (disable) ) ( ) { return enabled_ = false; }

private:
    // Constructors never const or volatile so no need to make this mutable,
    // provide volatile access members, etc.
    bool enabled_;
};

} } } // namespace

#endif // #include guard


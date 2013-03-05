
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include "override_member.hpp"

#if defined(CONTRACT_CONFIG_NO_PRECONDITIONS) && \
        defined(CONTRACT_CONFIG_NO_POSTCONDITIONS) && \
        defined(CONTRACT_CONFIG_NO_CLASS_INVARIANTS)
#   error "virtual specifiers require appropriate contracts to be enabled"
#endif

//[override_member_error
CONTRACT_CLASS(
    class (z) extends( public x )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public void (g) ( void ) override // Correctly errors, cannot override.
    ) {}
};
//]

int main ( void ) { return 0; }


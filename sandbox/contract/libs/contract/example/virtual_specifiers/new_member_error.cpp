
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include "new_member.hpp"

#if defined(CONTRACT_CONFIG_NO_PRECONDITIONS) && \
        defined(CONTRACT_CONFIG_NO_POSTCONDITIONS) && \
        defined(CONTRACT_CONFIG_NO_CLASS_INVARIANTS)
#   error "virtual specifiers require appropriate contracts to be enabled"
#endif

//[new_member_error
CONTRACT_CLASS(
    class (z) extends( public y )
) {
    CONTRACT_CLASS_INVARIANT( void )

    CONTRACT_FUNCTION(
        public virtual void (g) ( void ) new // Correctly errors because `y::g`.
    ) {}
};
//]

int main ( void ) { return 0; }


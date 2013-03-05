
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <contract.hpp>
#include <iostream>

//[default_subcontracting_base
CONTRACT_CLASS(
    class (base) // Declared with contract macros.
) {
    CONTRACT_CLASS_INVARIANT( std::clog << "base::inv" << std::endl )

    CONTRACT_FUNCTION(
        public virtual void (f) ( void )
            precondition( std::clog << "base::f::pre" << std::endl )
            postcondition( std::clog << "base::f::post" << std::endl )
    ) = 0;
};

class deriv : public base // Declared without contract macros...
{
    // ...but using `BODY` instead of `CLASS` and `FUNCTION` macros, overriding
    // functions have exact same contracts as base (not real subcontracting).
    public: virtual void CONTRACT_MEMBER_BODY(f) ( void )
    {
        std::clog << "deriv::f::body" << std::endl;
    }
};
//]

int main ( void )
{
    deriv().f(); // Check `base::f` contract but execute `deriv::f` body.
    return 0;
}


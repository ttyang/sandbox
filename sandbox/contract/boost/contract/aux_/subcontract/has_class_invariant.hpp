
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_HAS_CLASS_INVARIANT_HPP_
#define BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_HAS_CLASS_INVARIANT_HPP_

#include <boost/contract/aux_/has_xxx_member_function.hpp>

// NOTE: This symbol must be used to name the subcontract class invariant meber
// function in order for this introspection check to work.
#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_HAS_CLASS_INVARIANT_FUNC \
    BOOST_CONTRACT_AUX_SYMBOL( (subcontracted_class_invariant) )

namespace boost { namespace contract { namespace aux {

// Declare has_subcontracted_class_invariant< void (Base::*) ( void ) const>
// meta-function.
// NOTE: This can be done here because all class invariant functions have the
// same name and signature. Unfortunately, that is not true instead of user
// defined member functions for which the introspecting meta-function must be
// defined within the user class declaration itself by the expansion of the
// FUNCTION macro (and similarly for the virtual specifier introspection tag
// functions and check meta-functions that also depend by the function names
// and signature).
BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION(has_subcontracted_class_invariant,
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_HAS_CLASS_INVARIANT_FUNC)

} } } // namespace

#endif // #include guard


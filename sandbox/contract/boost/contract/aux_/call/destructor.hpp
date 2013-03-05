
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CALL_DESTRUCTOR_HPP_
#   define BOOST_CONTRACT_AUX_CALL_DESTRUCTOR_HPP_
#   include <boost/contract/aux_/call/impl_/include.hpp>
#   include <boost/contract/aux_/call/impl_/define.hpp>

namespace boost { namespace contract { namespace aux {

#   define BOOST_CONTRACT_AUX_CALL_ARITY 0 // Destructors have no argument.
#   define BOOST_CONTRACT_AUX_CALL_IS_MEMBER 1
#   define BOOST_CONTRACT_AUX_CALL_IS_STATIC 0
#   define BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR 1
#   define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY 0
#   define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT 0
#   include <boost/contract/aux_/call/impl_/function.hpp> // Generate func code.

} } } // namespace

#   include <boost/contract/aux_/call/impl_/undef.hpp>
#endif // #include guard


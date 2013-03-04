
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CALL_GLOBALS_HPP_
#define BOOST_CONTRACT_AUX_CALL_GLOBALS_HPP_

#include <boost/contract/aux_/thread_variable.hpp>

namespace boost { namespace contract { namespace aux {

// NOTE: A template is used to wrap these variables so they can be defined in
// this header (instead of requiring to link a pre-compiled .cpp for these
// definitions) without causing a multiple definition error (static or extern
// specifiers cannot be used here because static creates a different variable
// copy for each translation unit when these variables need to globally have
// the same value for the entire program, and extern still requires the
// definitions somewhere in a .cpp which we wanted to avoid).
template< int Unused = 0 >
struct call_globals
{
    // POLICY: Used to globally disable contract checking while already
    // checking another contract.
    static thread_variable<bool> is_checking_contract;
};
    
template< int Unused >
thread_variable<bool> call_globals<Unused>::is_checking_contract = false;

} } } // namespace

#endif // #include guard


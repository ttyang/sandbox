
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CONTRACT_AUX_CALL_CONSTRUCTOR_ENTRY_HPP_
#       define BOOST_CONTRACT_AUX_CALL_CONSTRUCTOR_ENTRY_HPP_
#       include <boost/contract/aux_/call/impl_/include.hpp>
#       include <boost/contract/aux_/preprocessor/iteration/params.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/contract/aux_/call/impl_/define.hpp>

namespace boost{ namespace contract { namespace aux {

// NOTE: The Class tparam is necessary to make this a new type to inherit from
// for each new class (to avoid inheritance ambiguity errors-- virtual
// inheritance cannot be used to resolve ambiguity because it will create only
// one call_constructor_entry base object and therefore check constructor entry
// contracts only for one of the base classes).
template< class Class >
struct call_constructor_entry
{
    // NOTE: This default constructor is necessary to allow for eventual user
    // constructors without a contract (i.e., not wrapped by this lib macros).
    call_constructor_entry ( void ) {}

    // Only defines additional constructors so it does not clash with member
    // func/var names defined by user deriving from this class.

#       define BOOST_PP_ITERATION_PARAMS_1 \
                BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
                        "boost/contract/aux_/call/constructor_entry.hpp")
#       include BOOST_PP_ITERATE()

};

} } } // namespace

#       include <boost/contract/aux_/call/impl_/undef.hpp>
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
// Define BOOST_CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <boost/contract/aux_/preprocessor/iteration/arity_1.hpp>
#   define BOOST_CONTRACT_AUX_CALL_ARITY BOOST_CONTRACT_AUX_PP_ITERATION_ARITY
#   define BOOST_CONTRACT_AUX_CALL_IS_MEMBER 1
#   define BOOST_CONTRACT_AUX_CALL_IS_STATIC 0
#   define BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR 0
#   define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY 1
#   define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT 0
#   include <boost/contract/aux_/call/impl_/function.hpp> // Generate func code.
#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration


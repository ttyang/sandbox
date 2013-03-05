
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CONTRACT_AUX_CALL_CONSTRUCTOR_EXIT_HPP_
#       define BOOST_CONTRACT_AUX_CALL_CONSTRUCTOR_EXIT_HPP_
#       include <boost/contract/aux_/call/impl_/include.hpp>
#       include <boost/contract/aux_/preprocessor/iteration/params.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/contract/aux_/call/impl_/define.hpp>

namespace boost { namespace contract { namespace aux {

#       define BOOST_PP_ITERATION_PARAMS_1 \
                BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
                        "boost/contract/aux_/call/constructor_exit.hpp")
#       include BOOST_PP_ITERATE()

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
#   define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY 0
#   define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT 1
#   include <boost/contract/aux_/call/impl_/function.hpp> // Generate func code.
#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration


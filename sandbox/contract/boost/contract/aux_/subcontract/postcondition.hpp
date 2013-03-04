
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_POSTCONDITION_HPP_
#       define BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_POSTCONDITION_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/preprocessor/iteration/params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <list>

#define BOOST_CONTRACT_comma_const_arg_param(z, n, unused) \
    , typename SignTraits::BOOST_PP_CAT(const_arg_type, n) \
            BOOST_PP_CAT(const_arg, n)
#define BOOST_CONTRACT_const_arg(z, n, unused) \
    BOOST_PP_CAT(const_arg, n)

#       define BOOST_PP_ITERATION_PARAMS_1 \
                BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
  "boost/contract/aux_/subboost/contract/postcondition.hpp")
#       include BOOST_PP_ITERATE()
#       undef BOOST_CONTRACT_comma_const_arg_param
#       undef BOOST_CONTRACT_const_arg
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
// Define BOOST_CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <boost/contract/aux_/preprocessor/iteration/arity_1.hpp>

namespace boost { namespace contract { namespace aux {

template< class SignTraits >
void subcontract_postcondition(
      std::list< typename SignTraits::bound_postcondition_type >
            const& subcontracted_bound_posts
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
            BOOST_CONTRACT_comma_const_arg_param, ~)
    , typename SignTraits::const_result_type const_result
) {
    // Check all (bound with old-of and obj) post in short-circuit AND.
    
    for(typename std::list< typename SignTraits::bound_postcondition_type >::
        const_iterator post = subcontracted_bound_posts.begin();
        post != subcontracted_bound_posts.end();
        ++post
    ) {
        (*post)( // If one throws, entire AND fails.
            BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_const_arg, ~)
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY)
            const_result
        );
    } // None threw so entire AND passes.
}

} } } // namespace

#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration


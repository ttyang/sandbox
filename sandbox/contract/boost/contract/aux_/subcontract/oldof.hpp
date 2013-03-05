
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_OLDOF_HPP_
#       define BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_OLDOF_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/subboost/contract/from.hpp>
#include <boost/contract/aux_/preprocessor/iteration/params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <list>

#define BOOST_CONTRACT_comma_base_params(z, n, unused) \
    , typename SignTraits::BOOST_PP_CAT(base, n)::const_obj_type const \
            BOOST_PP_CAT(base, n) \
    , typename SignTraits::BOOST_PP_CAT(base, n)::subcontracted_oldof_type \
            const BOOST_PP_CAT(sub_oldof, n)
#define BOOST_CONTRACT_comma_const_arg_param(z, n, unused) \
    , typename SignTraits::BOOST_PP_CAT(const_arg_type, n) \
            BOOST_PP_CAT(const_arg, n)
#define BOOST_CONTRACT_comma_const_arg(z, n, unused) \
    , BOOST_PP_CAT(const_arg, n)

#define BOOST_CONTRACT_base_oldof_eval(z, n, unused) \
    if(is_subcontracted_from< \
          typename SignTraits::class_type \
        , typename SignTraits::BOOST_PP_CAT(base, n)::class_type \
       >::value \
    ) { \
        all_posts_type base_posts = \
            (BOOST_PP_CAT(base, n)->*BOOST_PP_CAT(sub_oldof, n)) \
        ( \
            typename SignTraits::BOOST_PP_CAT(base, n)::body_type() \
            BOOST_PP_REPEAT_ ## z(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY, \
                    BOOST_CONTRACT_comma_const_arg, ~) \
        ); \
        all_posts.insert(all_posts.end(), \
                base_posts.begin(), base_posts.end()); \
    }

#       define BOOST_PP_ITERATION_PARAMS_1 \
                BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
                        "boost/contract/aux_/subboost/contract/oldof.hpp")
#       include BOOST_PP_ITERATE()
#       undef BOOST_CONTRACT_comma_base_params
#       undef BOOST_CONTRACT_comma_const_arg_param
#       undef BOOST_CONTRACT_comma_const_arg
#       undef BOOST_CONTRACT_base_oldof_eval
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
// Define BOOST_CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <boost/contract/aux_/preprocessor/iteration/arity_1.hpp>

namespace boost { namespace contract { namespace aux {

template< class SignTraits >
std::list< typename SignTraits::bound_postcondition_type >
subcontract_oldof(
      typename SignTraits::const_obj_type const obj
    , typename SignTraits::oldof_type const this_oldof
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_base_params, ~)
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
            BOOST_CONTRACT_comma_const_arg_param, ~)
) {
    // Execute all old-of bindings to return list of all bound post functions.
    typedef std::list< typename SignTraits::bound_postcondition_type >
            all_posts_type;
    all_posts_type all_posts;
    
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_base_oldof_eval, ~)

    typename SignTraits::bound_postcondition_type post = (obj->*this_oldof)(
        typename SignTraits::body_type()
        BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                BOOST_CONTRACT_comma_const_arg, ~)
    );
    all_posts.push_back(post);
    
    return all_posts;
}

} } } // namespace

#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration


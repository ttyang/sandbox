
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_PRECONDITION_HPP_
#       define BOOST_CONTRACT_AUX_SUBBOOST_CONTRACT_PRECONDITION_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/subboost/contract/from.hpp>
#include <boost/contract/aux_/preprocessor/iteration/params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#define BOOST_CONTRACT_comma_base_params(z, n, unused) \
    , typename SignTraits::BOOST_PP_CAT(base, n)::const_obj_type const \
            BOOST_PP_CAT(base, n) \
    , typename SignTraits::BOOST_PP_CAT(base, n)::precondition_type const \
            BOOST_PP_CAT(sub_pre, n)
#define BOOST_CONTRACT_comma_const_arg_param(z, n, unused) \
    , typename SignTraits::BOOST_PP_CAT(const_arg_type, n) \
            BOOST_PP_CAT(const_arg, n)
#define BOOST_CONTRACT_comma_const_arg(z, n, unused) \
    , BOOST_PP_CAT(const_arg, n)

#define BOOST_CONTRACT_and_not_first_error(z, n, unused) \
    && ! BOOST_PP_CAT(first_error, n)
#define BOOST_CONTRACT_begin_base_pre_check(z, n, unused) \
    BOOST_PP_EXPR_IIF( \
  BOOST_CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01, \
        bool BOOST_PP_CAT(first_error, n) = \
            true /* assume error until 1st checked */ \
            BOOST_PP_REPEAT_ ## z(n, BOOST_CONTRACT_and_not_first_error, ~) \
        ; \
    ) \
    try \
    { \
        if(is_subcontracted_from< \
              typename SignTraits::class_type \
            , typename SignTraits::BOOST_PP_CAT(base, n)::class_type \
           >::value \
        ) { \
            (BOOST_PP_CAT(base, n)->*BOOST_PP_CAT(sub_pre, n))( \
                typename SignTraits::BOOST_PP_CAT(base, n)::body_type() \
                BOOST_PP_REPEAT_ ## z(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY, \
                        BOOST_CONTRACT_comma_const_arg, ~) \
            ); \
            return; /* this base's pre passed so entire OR is true (done) */ \
        } /* else, not subcontracting from this base */ \
        BOOST_PP_EXPR_IIF( \
  BOOST_CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01, \
            BOOST_PP_CAT(first_error, n) = false; /* not subcontr so no err */ \
        ) \
        throw not_subcontracting(); /* not subcontracting but check next */ \
    } \
    catch(...) /* either this check failed or not subcontracting this base */ \
    { /* end with macro below... */
#define BOOST_CONTRACT_end_base_pre_check(z, n, unused) \
    /* ...start with macro above */ \
        BOOST_PP_EXPR_IIF( \
  BOOST_CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01, \
            /* if this is 1st error... */ \
            if(BOOST_PP_CAT(first_error, BOOST_PP_SUB(BOOST_PP_DEC( \
                    BOOST_CONTRACT_CONFIG_INHERITANCE_MAX), n))) \
        ) \
        throw; /* ...re-throw error */ \
    }

#       define BOOST_PP_ITERATION_PARAMS_1 \
                BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
  "boost/contract/aux_/subboost/contract/precondition.hpp")
#       include BOOST_PP_ITERATE()
#       undef BOOST_CONTRACT_comma_base_params
#       undef BOOST_CONTRACT_comma_const_arg_param
#       undef BOOST_CONTRACT_comma_const_arg
#       undef BOOST_CONTRACT_and_not_first_error
#       undef BOOST_CONTRACT_begin_base_pre_check
#       undef BOOST_CONTRACT_end_base_pre_check
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
// Define BOOST_CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <boost/contract/aux_/preprocessor/iteration/arity_1.hpp>

namespace boost { namespace contract { namespace aux {

template< class SignTraits >
void subcontract_precondition(
      typename SignTraits::const_obj_type const obj
    , typename SignTraits::precondition_type const this_pre
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_base_params, ~)
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
            BOOST_CONTRACT_comma_const_arg_param, ~)
) {
    // Check all pre in short-circuit OR (OK unless all throw).
    
    // Nesting used to re-throw the very first exception in case all fail.
    struct not_subcontracting {}; // Internal only, don't inherit from except.
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_begin_base_pre_check, ~)

    BOOST_PP_EXPR_IIF(
            BOOST_CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01,
        bool first_error =
            true BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
                    BOOST_CONTRACT_and_not_first_error, ~) 
        ;
    )
    try
    {
        (obj->*this_pre)(
            typename SignTraits::body_type()
            BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_comma_const_arg, ~)
        );
        return; // This check passed so entire OR is true.
    }
    catch(...)
    {
        BOOST_PP_EXPR_IIF(
  BOOST_CONTRACT_AUX_CONFIG_REPORT_OVERRIDDEN_PRECONDITION_FAILURE_01,
            if(first_error) // If this is 1st error...
        )
        throw; // ...re-throw error.
    }

    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_end_base_pre_check, ~)
    throw not_subcontracting(); // Should never get here.
}

} } } // namespace

#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration


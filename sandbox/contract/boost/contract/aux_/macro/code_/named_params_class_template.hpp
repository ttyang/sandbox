
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HPP_
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HPP_

#include <boost/preprocessor/comparison/greater_equal.hpp>
#include <boost/parameter.hpp>

// PRIVATE //

// Arg template param.

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_( \
        unused0, n, unused1) /* unused so it can be used with ENUM, etc */ \
    BOOST_CONTRACT_AUX_SYMBOL( (NamedTParamsArg)(n) )
    
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_ENUM_( \
        r, arity_minus_defaults, i, t) \
    BOOST_PP_COMMA_IF(i) \
    typename BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_(~, i, ~) \
    BOOST_PP_EXPR_IIF(BOOST_PP_GREATER_EQUAL(i, arity_minus_defaults), \
        = ::boost::parameter::void_ \
    )

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_PAREN_( \
        z, unused, i, t) \
    ( typename BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_( \
            ~, i, ~) )

// Args template param.

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ \
    BOOST_CONTRACT_AUX_SYMBOL( (NamedTParamsArgs) )

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_PARAM_ENUM_( \
        r, tparams, i, t) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)), \
        ::boost::parameter::optional< \
    , \
        ::boost::parameter::required< \
    ) \
        /* tag (possibly deduced) */ \
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
            ::boost::parameter::deduced< \
        ) \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TEMPLATE_TAG(tparams, t) \
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
            > \
        ) \
        /* NOTE: type requirement (if there is any type requirement then it */ \
        /* must be a matching type requirement for a type template */ \
        /* parameter because no exact type requirement applies to a type */ \
        /* template parameter and only template parameters are supported so */ \
        /* no need to check if KIND ends in `requires` in this case) */ \
        BOOST_PP_COMMA_IF(BOOST_PP_ARRAY_SIZE( \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)))\
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)),\
            BOOST_PP_ARRAY_ENUM \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)) \
    >   

// Original template params.

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_(\
        r, tparams, t) \
    , typename BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t) = \
        typename ::boost::parameter::value_type \
    < \
          BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ \
        , BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TEMPLATE_TAG(tparams, t) \
        BOOST_PP_COMMA_IF(BOOST_PP_ARRAY_SIZE( \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t))) \
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)), \
            BOOST_PP_ARRAY_ENUM \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)) \
      >::type

#define \
BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_PAREN_( \
        r, unused, t) \
    ( typename BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t) )
    
// Template declaration.

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HAS_DEFAULT_( \
        d, unused, t) \
    BOOST_PP_BOOL(BOOST_PP_ARRAY_SIZE( \
            BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)))

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DEFAULT_COUNT_( \
        named_and_deduced_tparams) \
    BOOST_PP_LIST_SIZE(BOOST_PP_LIST_FILTER( \
            BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HAS_DEFAULT_,\
            ~, named_and_deduced_tparams))

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL_( \
        template01, tparams, named_and_deduced_tparams) \
    /* open template<...> (even if no tparams for specializations) */ \
    BOOST_PP_EXPR_IIF(template01, template< ) \
    /* Arg */ \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_ENUM_,\
            BOOST_PP_SUB(BOOST_PP_LIST_SIZE(named_and_deduced_tparams), \
  BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DEFAULT_COUNT_( \
                        named_and_deduced_tparams)), \
            named_and_deduced_tparams) \
    /* Args */ \
    , typename BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ = \
            typename ::boost::parameter::parameters< \
        BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_PARAM_ENUM_, \
                tparams, named_and_deduced_tparams) \
      >::bind< \
        BOOST_PP_ENUM(BOOST_PP_LIST_SIZE(named_and_deduced_tparams), \
                BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_, ~) \
      >::type \
    /* original template params */ \
    BOOST_PP_LIST_FOR_EACH( \
  BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_, \
            tparams, named_and_deduced_tparams) \
    /* close template<...> */ \
    BOOST_PP_EXPR_IIF(template01, > )

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C_(c, \
        named_and_deduced_tparams) \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_REPLACE( \
    c, /* new template params: without named/deduced syntax */ \
        template( \
            BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_PAREN_, \
                    ~, named_and_deduced_tparams) \
            ( typename \
              BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ ) \
            BOOST_PP_LIST_FOR_EACH( \
  BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_PAREN_,\
                    ~, named_and_deduced_tparams) \
            ) \
    )

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL( \
        template01, tparams) \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL_( \
            template01, tparams, \
            BOOST_PP_LIST_APPEND( \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(tparams), \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED(tparams)))

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C(c) \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C_(c, \
            BOOST_PP_LIST_APPEND( \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                                c)), \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                                c))))

#endif // #include guard


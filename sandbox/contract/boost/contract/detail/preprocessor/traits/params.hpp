
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/traits/params/void.hpp>
#include <boost/contract/detail/preprocessor/traits/params/namespace.hpp>
#include <boost/contract/detail/preprocessor/traits/params/group.hpp>
#include <boost/contract/detail/preprocessor/traits/func_param.hpp>
#include <boost/contract/detail/preprocessor/keyword/template.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/first_n.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PUBLIC //

// Expand to 4-tuple `(NIL tag_namespace, positional_params, named_params,
// deduced_params)` (params are all pp-list and they are NIL is no params).
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAMS_TRAITS(sign) \
    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_GROUP( \
          BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_NAMESPACE( \
              BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_VOID( \
                  BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST( \
                      sign \
                    , 1 /* might be empty (for tpl specializations) */ \
                    , 1 /* might have defaults */ \
                    , BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT \
                    , BOOST_CONTRACT_DETAIL_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
                    , BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS \
                  ) \
                , BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME \
              ) \
            , BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME \
          ) \
        , BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND \
    )

// Expand to 4-tuple `(NIL tag_namespace, positional_params, named_params,
// deduced_params)` (params are all pp-list and they are NIL is no params).
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAMS_TRAITS(sign) \
    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_GROUP( \
          BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_NAMESPACE( \
              BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_AUX_VOID( \
                  BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST( \
                      sign \
                    , 1 /* might be empty */ \
                    , 1 /* might have defaults */ \
                    , BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS \
                  ) \
                  , BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME \
              ) \
            , BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME \
          ) \
        , BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER \
    )

#endif // #include guard


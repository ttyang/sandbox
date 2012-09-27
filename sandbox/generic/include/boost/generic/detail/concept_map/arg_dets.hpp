/*==============================================================================
    Copyright (c) 2010, 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_MAP_ARG_DETS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_ARG_DETS_HPP

#include <boost/generic/detail/concept_map/body_dets.hpp>
#include <boost/generic/detail/concept_map/concept_and_params_dets.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/num_args_is_1.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/generic/detail/template_decl_details.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS( ... )                       \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_IMPL                                      \
( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS                                   \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_IS_VALID( dets )             \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS( dets )        \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS_IS_VALID(dets) \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID                               \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS( dets ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_DETS(dets)\
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT( dets )              \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_CONCEPT                           \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_DETS( dets ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_ARGS( dets )                 \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_CONCEPT                           \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_DETS( dets ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS( dets )   \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_                  \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_DETS( dets ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_( dets )  \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_CONCEPT( dets )                   \
< BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_PARAMS( dets ) >

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_PARAMS( dets )               \
BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_PARAMS                            \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_CONCEPT_AND_PARAMS_DETS            \
  ( dets )                                                                     \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_BODY_DETS( dets )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 3, dets ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_HAS_BODY( dets )             \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_BODY_DETS( dets ) )              \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_VISIT_BODY( dets, macro_base \
                                                            , data             \
                                                            )                  \
BOOST_PP_IIF( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_HAS_BODY( dets )       \
            , BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_VISIT_BODY_            \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets, macro_base, data )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_VISIT_BODY_( dets, macro_base\
                                                             , data            \
                                                             )                 \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_VISIT                               \
( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_BODY_DETS( dets )                  \
, macro_base                                                                   \
, BOOST_PP_INC                                                                 \
  ( BOOST_PP_INC                                                               \
    ( BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_TEMPLATE_DETS_IS_VALID(dets) ) \
  )                                                                            \
, data                                                                         \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_IMPL( template_dets, ... )        \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID( template_dets )\
            , BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_WITH_TEMPLATE              \
            , BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_NO_TEMPLATE                \
            )( template_dets, __VA_ARGS__ )

// ToDo: Gracefully handle no tail arguments
#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_WITH_TEMPLATE(template_dets, ...)\
BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_WITH_TEMPLATE_                           \
( template_dets, BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ ) )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_WITH_TEMPLATE_(template_dets,...)\
BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_WITH_TEMPLATE_IMPL                       \
( template_dets                                                                \
, BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS                                 \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_WITH_TEMPLATE_IMPL( template_dets\
                                                      , concept_and_params_dets\
                                                      , ...                    \
                                                      )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID                        \
  ( concept_and_params_dets )                                                  \
, BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_OPENER                           \
, BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_INVALID_OPENER                         \
)( template_dets, concept_and_params_dets, 3, __VA_ARGS__ )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_NO_TEMPLATE( template_dets, ... )\
BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_NO_TEMPLATE_                             \
( template_dets                                                                \
, BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS                                 \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_NO_TEMPLATE_(                    \
                                                        template_dets          \
                                                      , concept_and_params_dets\
                                                      , ...                    \
                                                      )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_CONCEPT_AND_PARAMS_DETS_IS_VALID                        \
  ( concept_and_params_dets )                                                  \
, BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_OPENER                           \
, BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_INVALID_OPENER                         \
)( template_dets, concept_and_params_dets, 2, __VA_ARGS__ )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_OPENER(                    \
                                                        template_dets          \
                                                      , concept_and_params_dets\
                                                      , curr_param_index       \
                                                      , ...                    \
                                                      )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1( __VA_ARGS__ )                            \
, BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_EMPTY                            \
, BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_NONEMPTY                         \
)( template_dets, concept_and_params_dets, 2, __VA_ARGS__ )

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_NONEMPTY(                  \
                                                        template_dets          \
                                                      , concept_and_params_dets\
                                                      , curr_param_index       \
                                                      , ...                    \
                                                      )                        \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_NONEMPTY_                          \
( template_dets, concept_and_params_dets, curr_param_index                     \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS                                   \
  ( BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ ) )                       \
)

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_NONEMPTY_(                 \
                                                        template_dets          \
                                                      , concept_and_params_dets\
                                                      , base_param_index       \
                                                      , body_dets              \
                                                      )                        \
(BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IS_VALID( body_dets ))             \
(template_dets)(concept_and_params_dets)((body_dets))

#define BOOST_GENERIC_CONCEPT_MAP_DETAIL_IMPL_VALID_EMPTY(                     \
                                                        template_dets          \
                                                      , concept_and_params_dets\
                                                      , curr_param_index       \
                                                      , ...                    \
                                                      )                        \
(1)(template_dets)(concept_and_params_dets)(())("No opener error.")

#endif // BOOST_GENERIC_DETAIL_CONCEPT_MAP_ARG_DETS_HPP

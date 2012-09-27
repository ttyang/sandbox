/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_ARG_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_ARG_DETAILS_HPP

#include <boost/generic/detail/concept/req_dets.hpp>
#include <boost/generic/detail/concept_sig_dets.hpp>
#include <boost/generic/detail/public_dets.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/num_args_is_1.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// ToDo: Better error handling if user passes no parameters at all

// Arguments are of the form:
//   concept_sig
// , ?[public_req]
// , *[asm_req|typename_req|function_req|if_req|type_template_req|this_req]
// Result is of the form:
// (validity_bit)(concept_sig_dets)(req_dets)
#define BOOST_GENERIC_DETAIL_CONCEPT_DETS( ... )                               \
BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL                                         \
( BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS                                        \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IS_VALID( dets )                     \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_SIG_DETS( dets )             \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                 \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_CONCEPT                                  \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_SIG_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets )           \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_PARAM_DETS                               \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_SIG_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARAMS( dets )                       \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAMS                                 \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets )                         \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS                                   \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME_AND_ARGS( dets )        \
BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                         \
< BOOST_GENERIC_DETAIL_CONCEPT_DETS_ARGS( dets ) >

#if 0

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_AUGMENTED_PARAMS( dets, aug )        \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_PARAMS                       \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets ), aug )

#endif

#if 0

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_AUGMENTED_ARGS( dets, aug )          \
BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_AUGMENTED_ARGS                         \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets ), aug )

#endif

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_VISIT_BODY( dets, macro_base, data ) \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_REQ_DETS( dets )           \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_VISIT_BODY_                    \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets, macro_base, data )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_VISIT_BODY_( dets, macro_base, data )\
BOOST_GENERIC_DETAIL_REQ_DETS_VISIT                                            \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_REQ_DETS( dets )                           \
, macro_base                                                                   \
, BOOST_PP_INC                                                                 \
  ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets ) ) )     \
, data                                                                         \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_FOLD_BODY( dets, macro_base, state ) \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_REQ_DETS( dets )           \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_FOLD_BODY_                     \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( state )                  \
            )( dets, macro_base, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_FOLD_BODY_( dets, macro_base, state )\
BOOST_GENERIC_DETAIL_REQ_DETS_FOLD                                             \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_REQ_DETS( dets )                           \
, macro_base                                                                   \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_NAME( dets )                       \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS_CONCEPT_PARAM_DETS( dets )                 \
, BOOST_PP_INC                                                                 \
  ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets ) ) )     \
, state                                                                        \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_PUBLIC_DETS( dets )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_PUBLIC( dets )                   \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_CONCEPT_DETS_PUBLIC_DETS( dets ) )                    \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_PARENTS( dets )                      \
BOOST_GENERIC_DETAIL_PUBLIC_DETS_PARENTS                                       \
( BOOST_GENERIC_DETAIL_CONCEPT_DETS_PUBLIC_DETS( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_HAS_REQ_DETS( dets )                 \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_CONCEPT_DETS_REQ_DETS( dets ) )                       \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_REQ_DETS( dets )                     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 3, dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL( concept_sig_dets, ... )        \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1( __VA_ARGS__ )                \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_EMPTY                     \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NONEMPTY                  \
            )( concept_sig_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NONEMPTY( concept_sig_dets,... )\
BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NONEMPTY_                               \
( concept_sig_dets, BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NONEMPTY_(concept_sig_dets,...) \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( concept_sig_dets )           \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NONEMPTY_IMPL                         \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_INVALID                               \
)( concept_sig_dets                                                            \
 , BOOST_GENERIC_DETAIL_WRAPPED_PUBLIC_DETS                                    \
   ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                       \
 , __VA_ARGS__                                                                 \
 )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_INVALID( concept_sig_dets       \
                                                      , req_dets               \
                                                      )                        \
(0)(concept_sig_dets)(())((req_dets))

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NONEMPTY_IMPL( concept_sig_dets \
                                                            , public_dets, ... \
                                                            )                  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_PARTIAL( public_dets )       \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_PUBLIC                    \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NO_PUBLIC                 \
            )( concept_sig_dets, public_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_NO_PUBLIC( concept_sig_dets     \
                                                        , public_dets, ...     \
                                                        )                      \
BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_BODY( concept_sig_dets, , __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_PUBLIC( concept_sig_dets        \
                                                     , public_dets, ...        \
                                                     )                         \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1( __VA_ARGS__ )                \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_JUST_PUBLIC               \
            , BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_PUBLIC_AND_MORE           \
            )( concept_sig_dets, public_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_PUBLIC_AND_MORE(concept_sig_dets\
                                                              , public_dets,...\
                                                              )                \
BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_BODY                                    \
( concept_sig_dets, public_dets                                                \
, BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ )                           \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_PUBLIC_DETS_NO_TOP_LEVEL_ERROR( dets )\
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY( dets )                                        \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 1 )                                  \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID                                    \
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_BODY( concept_sig_dets          \
                                                   , public_dets               \
                                                   , ...                       \
                                                   )                           \
BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_BODY_                                   \
( concept_sig_dets, public_dets                                                \
, BOOST_GENERIC_DETAIL_REQ_DETS( __VA_ARGS__ )                                 \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_BODY_( concept_sig_dets         \
                                                    , public_dets              \
                                                    , req_dets                 \
                                                    )                          \
(BOOST_PP_BITAND                                                               \
 ( BOOST_PP_BITAND                                                             \
   ( BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( concept_sig_dets )        \
   , BOOST_GENERIC_DETAIL_CONCEPT_SIG_PUBLIC_DETS_NO_TOP_LEVEL_ERROR           \
     ( public_dets )                                                           \
   )                                                                           \
 , BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( req_dets )                          \
 )                                                                             \
)                                                                              \
(concept_sig_dets)                                                             \
((public_dets))                                                                \
((req_dets))

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_EMPTY( concept_sig_dets, ... )  \
(BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( concept_sig_dets ))           \
(concept_sig_dets)                                                             \
(())                                                                           \
(())

#define BOOST_GENERIC_DETAIL_CONCEPT_DETS_IMPL_JUST_PUBLIC( concept_sig_dets   \
                                                          , public_dets        \
                                                          , ...                \
                                                          )                    \
(BOOST_PP_BITAND                                                               \
 ( BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( concept_sig_dets )          \
 , BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( public_dets )                    \
 )                                                                             \
)                                                                              \
(concept_sig_dets)                                                             \
((public_dets))                                                                \
(())

#endif // BOOST_GENERIC_DETAIL_CONCEPT_ARG_DETAILS_HPP

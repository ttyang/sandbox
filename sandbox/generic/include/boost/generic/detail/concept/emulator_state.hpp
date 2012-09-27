#ifndef BOOST_GENERIC_DETAIL_EMULATOR_STATE_HPP
#define BOOST_GENERIC_DETAIL_EMULATOR_STATE_HPP

// ToDo: Insert requires checks along the way when doing first pass and second
//       pass typename deduction, otherwise it risks reaching into a concept map
//       that is not valid.

// State structure:
//   ((first_pass_type_metafunctions))
//   ((first_pass_typedefs))
//   ((deducer_helpers))
//   ((concept_map_body))
//   ((concept_body))
//   ((trailing_typename_params))
//   ((trailing_typename_args))
//   (num_requires)
//   (num_functions)
//   ((trailing_is_valid_conditions))
//
// typename_base_function_seq is a sequence where each element is:
//   (name)(base_function_number)

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/first_n.hpp>
#include <boost/preprocessor/seq/rest_n.hpp>

#define BOOST_GENERIC_DETAIL_CONCEPT_EMPTY_EMULATOR_STATE()                    \
(())(())(())(())(())(())(())(0)(0)(())

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPE_METAFUNCTIONS( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_FIRST_PASS_TYPEDEFS( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_DEDUCER_HELPERS( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_MAP_BODY( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 3, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_CONCEPT_BODY( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 4, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 5, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_PARAMS( state )   \
BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN                               \
( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_PARAMS         \
  ( state )                                                                    \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_ARGS( state )\
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 6, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state )\
BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN                               \
( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_TYPENAME_ARGS         \
  ( state )                                                                    \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_REQUIRES( state )\
BOOST_PP_SEQ_ELEM( 7, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_NUM_FUNCTIONS( state )\
BOOST_PP_SEQ_ELEM( 8, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS(state) \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 9, state ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_IS_VALID_CONDITIONS(state) \
BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN                               \
( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TRAILING_IS_VALID_CONDITIONS     \
  ( state )                                                                    \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC_FIRST_PASS_MAC( r, data, name )\
typename boost_generic_detail_typename_deducers::name,

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC_FIRST_PASS( i, seq )\
BOOST_PP_SEQ_FOR_EACH                                                                               \
( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC_FIRST_PASS_MAC            \
, ~, BOOST_PP_SEQ_REST_N( i, seq )                                                                 \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC_EXISTS( i, seq )\
BOOST_PP_SEQ_ENUM( BOOST_PP_SEQ_FIRST_N( i, seq ) ),

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC( r, data, i, name )\
typedef typename ::boost::mpl::eval_if_c                                       \
        < ::boost::generic::detail::is_dummy_type                              \
          < typename boost_generic_detail_typename_deducers::name >::value     \
        , BOOST_PP_CAT( boost_generic_detail_deduce, name )                    \
          < BoostGenericDetailConceptMap                                       \
          , boost_generic_detail_params                                        \
            < BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARGS                     \
              ( BOOST_PP_SEQ_ELEM( 0, data ) )                                 \
            >                                                                  \
          , ::boost::generic::detail::type_list                                \
            < BOOST_PP_IF \
              ( i \
              , BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC_EXISTS\
              , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY\
              )( i, BOOST_PP_SEQ_ELEM( 1, data ) )\
              BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC_FIRST_PASS\
              ( i, BOOST_PP_SEQ_ELEM( 1, data ) )\
              void**********                                                   \
            >                                                                  \
          >                                                                    \
        , ::boost::mpl::identity                                               \
          < typename boost_generic_detail_typename_deducers::name >            \
        >::type name;

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_( params, typename_seq )\
BOOST_PP_SEQ_FOR_EACH_I\
( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_MAC\
, (params)(typename_seq), typename_seq\
)

#define BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY( state, params )\
BOOST_PP_IIF\
( BOOST_GENERIC_DETAIL_IS_EMPTY( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )\
, BOOST_GENERIC_DETAIL_VARIADIC_EMPTY\
, BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_ACTUAL_CONCEPT_MAP_BODY_\
)\
( params                                                                       \
, BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE \
  ( BOOST_GENERIC_DETAIL_CONCEPT_EMULATOR_STATE_TYPENAME_ARGS( state ) )       \
)

#endif // BOOST_GENERIC_DETAIL_EMULATOR_STATE_HPP
